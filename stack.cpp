#include "header.h"

Stack::Stack() : head (nullptr){};

    void Stack::SPop(){
        if (head == nullptr){
            return;
        }
        SNode* current = head;
        head = head -> sled;
        delete current;
    }

    void Stack::SPrint(){
         if (head == nullptr){
            return;
        }
        SNode* current = head;
        while (current != nullptr){
            cout << current -> data << endl;
            current = current -> sled;
        }
    }

    void Stack::SPush(string new_data){
        SNode* new_node = new SNode;
        new_node->data = new_data;
        new_node->sled = head;
        head = new_node; 
    }

    void Stack::SWrite(string& read, string filename, int ind_start, int end){
        ofstream in;
        in.open(filename);
        if (head==nullptr){
            cout << "Stack is empty" << endl;
            in << read;
            in.close();
            return;
        }
        SNode* current = head;
        while (current->sled != nullptr){
            read.insert(ind_start+1, '\"' + current->data + '\"' + ';' + '\n');
            ind_start += current->data.size() + 4;
            current = current->sled;
        }
        read.insert(ind_start+1, '\"' + current->data + '\"');
        in << read;
        in.close();
        return;
    }

    void Stack::SRead(string& read, int& ind_start, int& ind){
        for (ind; read[ind] != '{' && ind < read.size(); ind++);
        ind_start = ind;
        ind++;
        if (read[ind] == '}'){
            return;
        }
        Stack flip;
        string datas = "";
        for (ind; read[ind] != '}' && read[ind] != '\n' && ind < read.size(); ind++){
            for (ind; read[ind] != '\"' && read[ind] != '}' && ind < read.size(); ind++);
            ind++;
            for (ind; read[ind] != '\"' && read[ind] != '}' && ind < read.size(); ind++){
                datas += read[ind];
            }
            flip.SPush(datas);
            datas = "";
        }
        while(flip.head != nullptr){
            SPush(flip.head->data);
            flip.head = flip.head->sled;
        }
        read.erase(ind_start + 1, ind - ind_start - 1);
        return;
    }
