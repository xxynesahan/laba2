#include "header.h"

List2::List2() : head(nullptr), tail(nullptr){};
    
    void List2::L2Push_back(string new_data){
        LNode2* new_node = new LNode2;
        new_node->data = new_data;
        if (head == nullptr){
            head = new_node;
            tail = new_node;
            return;
        }
        tail->sled = new_node;
        new_node->pred=tail;
    }

    void List2::L2Push_head(string new_data){
        LNode2* new_node = new LNode2;
        new_node->data = new_data;
        if (head == nullptr){
            head = new_node;
            tail = new_node;
            return;
        }
        new_node->sled = head;
        head->pred=new_node;
        head=new_node;
    }

    void List2::L2Print(){
        if (head == nullptr){
            return;
        }
        LNode2* current = head;
        for (current; current!= nullptr; current=current->sled){
            cout<< current->data <<endl;
        } 
    }

     void List2::L2Pop_head(){
        if (head == nullptr){
            return;
        }
        if (head==tail){
            delete head;
            head=nullptr;
            return;
        }
        LNode2* del_node = head;
        head = head ->sled;
        head->pred=nullptr;
        delete del_node; 
    }

    void List2::L2Pop_back(){
            if (head == nullptr){
                return;
            }
            if (tail == head){
                L2Pop_head();
                return;
            }
            tail->pred->sled=nullptr;
            tail->pred=nullptr;
            LNode2* del_node = tail;
            delete del_node;
    }

     void List2::L2Pop_value(string value){
        if (head == nullptr){
            return;
        }
        LNode2* current = head;
        if (value == current->data){
            while (value == head->data){
            L2Pop_head();
            }
            if (head == nullptr) {
                return;
            }
        }
        if (value == tail->data){
            while (value == tail->data){
            L2Pop_back();
            }
            if (tail == nullptr) {
                return;
            }
        }
        LNode2* kill_node = head;
        while (current->sled != nullptr){
            if (current->sled->data==value){
                kill_node=current->sled;
                kill_node->sled->pred=kill_node->pred;
                kill_node->pred->sled=kill_node->sled;
                delete kill_node;
            }
            current=current->sled;
        }
        if (current->sled==nullptr){
            return;
        }
    }

    bool List2::L2Find_value(string value){
        if (head == nullptr){
            return false;
        }
        LNode2* current = head;
        if (value == current->data){
            return true;
        }
        if (value == tail->data){
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

     void  List2::LdWrite(string& read, string filename, int ind_start, int end){
        ofstream in;
        in.open(filename);
        if (head == nullptr){
            cout << "List is empty" << endl;
            in << read;
            in.close();
            return;
        }
        LNode2* current = head;
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

    void  List2::LdRead(string& read, int& ind_start, int& ind){
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
            L2Push_back(datas);
            datas = "";
        }
        read.erase(ind_start + 1, ind - ind_start - 1);
        return;
    }
