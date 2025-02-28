#include "header.h"

   Queue::Queue () : head(nullptr), tail(nullptr) {};

    void Queue::QPop(){
        if (head == nullptr){
            return;
        }
        QNode* current = head;
        head = head -> sled;
        delete current;
    }

    void Queue::QPrint(){
        if (head == nullptr){
            return;
        }
        QNode* current = head;
        while(current!= nullptr){
            cout<<current -> data<< endl;
            current = current -> sled;
        }
    }

    void Queue::QPush(string new_data){
        QNode* new_node = new QNode;
        new_node->data = new_data;
        new_node->sled = nullptr;
        if (head == nullptr){
            head = new_node;
            tail = new_node;
            return;           
        }
        tail->sled = new_node;
        tail = new_node;

    }

    void Queue::QWrite(string& read, string filename, int ind_start, int end){
        ofstream in;
        in.open(filename);
        if (head==nullptr){
            cout << "Queue is empty" << endl;
            in << read;
            in.close();
            return;
        }
        QNode* current = head;
        while (current != tail){
            read.insert(ind_start+1, '\"' + current->data + '\"' + ';');
            ind_start += current->data.size() + 3;
            current = current->sled;
        }
        read.insert(ind_start+1, '\"' + tail->data + '\"');
        in << read;
        in.close();
        return;
    }

    void Queue::QRead(string& read, int& ind_start, int& ind){
        for (ind; read[ind] != '{' && ind < read.size(); ind++);
        ind_start = ind;
        ind++;
        if (read[ind] == '}'){
            return;
        }
        string datas = "";
        for (ind; read[ind] != '}' && read[ind] != '\n' && ind < read.size(); ind++){
            for (ind; read[ind] != '\"' && read[ind] != '}' && ind < read.size(); ind++);
            ind++;
            for (ind; read[ind] != '\"' && read[ind] != '}' && ind < read.size(); ind++){
                datas += read[ind];
            }
            QPush(datas);
            datas = "";
        }
        read.erase(ind_start + 1, ind - ind_start - 1);
        return;
    }