#include "header.h"

    List1::List1() : head(nullptr){};

    void List1::L1Push_back(string new_data){
        LNode1* new_node = new LNode1;
        new_node->data = new_data;
        if (head == nullptr){
            head = new_node;
            return;
        }
        LNode1* current = head; 
        for (current; current->sled!=nullptr ; current=current->sled);
        current->sled = new_node;
    }

    void List1::L1Push_head(string new_data){
        LNode1* new_node = new LNode1;
        new_node->data = new_data;
        if (head == nullptr){
            head = new_node;
            return;
        }
        new_node->sled = head;
        head=new_node;
    }

    void List1::L1Pop_head(){
        if (head == nullptr){
            return;
        }
        LNode1* del_node = head;
        head = head ->sled;
        delete del_node; 
    }

    void List1::L1Pop_back(){
        if (head == nullptr){
            return;
        }
        if (head->sled==nullptr){
            delete head;
            return;
        }
        LNode1* current = head;
        while(current->sled->sled!= nullptr){
            current=current->sled;
        }
        LNode1* del_node = current->sled;
        current->sled=nullptr;
        delete del_node;
    }

    void List1::L1Pop_value(string value){
        if (head == nullptr){
            return;
        }
        LNode1* current = head;
        if (value == current->data){
            while (value == head->data){
                L1Pop_head();
            }
            if (head == nullptr) {
                return;
            }
        }
        LNode1* kill_node = head;
        while (current->sled != nullptr){
            if (current->sled->data==value){
                kill_node=current->sled;
                current->sled=current->sled->sled;
                delete kill_node;
            }
            current=current->sled;
        }
        if (current->data == value){
            L1Pop_back();
            return;
        }    
    }

    bool List1::L1Find_value(string value){
        if (head == nullptr){
            return false;
        }
        LNode1* current = head;
        if (value == current->data){
            return true;
        }
        while (current->sled != nullptr && current->sled->data != value){
            current=current->sled;
        }
        if (current->sled==nullptr){
            return false;
        }
        return true;
    }

    void List1::L1Print(){
        if (head == nullptr){
            return;
        }
        LNode1* current = head;
        for (current; current!= nullptr; current=current->sled){
            cout<< current->data <<endl;
        } 
    }

    void  List1::LsWrite(string& read, string filename, int ind_start, int end){
        ofstream in;
        in.open(filename);
        if (head == nullptr){
            cout << "List is empty" << endl;
            in << read;
            in.close();
            return;
        }
        LNode1* current = head;
        while (current->sled != nullptr){
            read.insert(ind_start+1, '\"' + current->data + '\"' + ';');
            ind_start += current->data.size() + 3;
            current = current->sled;
        }
        read.insert(ind_start+1, '\"' + current->data + '\"');
        in << read;
        in.close();
        return;
    }

    void  List1::LsRead(string& read, int& ind_start, int& ind){
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
            L1Push_back(datas);
            datas = "";
        }
        read.erase(ind_start + 1, ind - ind_start - 1);
        return;
    }