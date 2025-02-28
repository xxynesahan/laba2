#include "header.h"

    Set::Set(int num) : size(num){
        setik = new SetNode*[size];
        for (int i = 0; i < size; i++){
            setik[i] = nullptr;
        }
    }

    bool Set::is_empty(){
        for (int i = 0; i < size; i++){
            if (setik[i] != nullptr){
                return 0;
            }
        }
        return 1;
    }

    bool Set::is_full(){
        int count = 0;
        for (int i = 0; i < size; i++){
            if (setik[i] != nullptr) count++;
        }
        if (count == size) return 1;
        return 0;
    }

    int Set::HSet (string data){
        int sum = 0;
        for (int i = 0; i < data.size(); i++){
            sum += data[i];
        }
        return sum % size;
    }

    bool Set::FindInd(string value, int& ind){
        if (is_empty()){
            return 0;
        }
        for (ind = 0; ind < size; ind++){
            if (setik[ind] == nullptr) continue;
            if (setik[ind]->data == value) return 1;
        }
        return 0;
    }

    bool Set::Set_At(string data){
        int key = HSet(data);
        if (setik[key] != nullptr && setik[key]->data == data){
            return 1;
        }
        bool is_here = FindInd(data, key);
        if (is_here){
            return 1;
        }
        return 0;
    }

    void Set::SetPush(string new_data){
        if(is_full()) return;
        if (Set_At(new_data)) return;       
        int new_key = HSet(new_data);
        SetNode* new_node = new SetNode{new_data};
        if (setik[new_key] != nullptr){
            for (int i = 0; i < size; i++){
                if (setik[i] == nullptr){
                    setik[i] = new_node;
                    return;
                }
            }
        }
        else {
            setik[new_key] = new_node;
            return;
        }   
    }

    void Set::SetPop(string data){
        if(is_empty()) return;
        int key = HSet(data);
        if (setik[key] != nullptr && setik[key]->data == data){
            delete setik[key];
            setik[key] = nullptr;
            return;
        }
        if (FindInd(data, key)){
            delete setik[key];
            setik[key] = nullptr;
            return;
        }
        cout << "Don't have" << endl;
        return;
    }

    void Set::SPrint(){
        if (is_empty()) return;
        for (int i = 0; i < size; i++){
            if (setik[i] == nullptr) continue;
            cout << setik[i]->data << endl;
        }
    }

    void Set::SetWrite(string& read, string filename, int ind_start, int end){
        ofstream in;
        in.open(filename);
        if (is_empty()){
            cout << "Set is empty" << endl;
            in << read;
            in.close();
            return;
        }
        int i = 0;
        while (i < size){
            if (setik[i] != nullptr){
                read.insert(ind_start+1, '\"' + setik[i]->data + '\"' + ';');
                ind_start += setik[i]->data.size() + 3;
            }
            i++;
        }
        end = ind_start + 1;
        read.erase(ind_start, end - ind_start);
        in << read;
        in.close();
        return;
    }

    void Set::SetRead(string& read, int& ind_start, int& ind){
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
            SetPush(datas);
            datas = "";
        }
        read.erase(ind_start + 1, ind - ind_start - 1);
        return;
    }



    // Объединение множеств
     Set Set::Union( Set& other) {
        Set result(size + other.size); // Создаем новое множество с размером, достаточным для объединения

        // Добавляем все элементы из текущего множества
        for (int i = 0; i < size; i++) {
            if (setik[i] != nullptr) {
                result.SetPush(setik[i]->data);
            }
        }

        // Добавляем все элементы из второго множества
        for (int i = 0; i < other.size; i++) {
            if (other.setik[i] != nullptr) {
                result.SetPush(other.setik[i]->data);
            }
        }

        return result;
    }

    // Пересечение множеств
    Set Set::Intersection( Set& other) {
        Set result(size); // Создаем новое множество

        // Проходим по текущему множеству и проверяем, есть ли элементы во втором множестве
        for (int i = 0; i < size; i++) {
            if (setik[i] != nullptr && other.Set_At(setik[i]->data)) {
                result.SetPush(setik[i]->data);
            }
        }

        return result;
    }

    // Разность множеств
    Set Set::Difference( Set& other) {
        Set result(10); // Создаем новое множество

        // Проходим по текущему множеству и добавляем элементы, которых нет во втором множестве
        for (int i = 0; i < size; i++) {
            if (setik[i] != nullptr && !other.Set_At(setik[i]->data)) {
                result.SetPush(setik[i]->data);
            }
        }

        return result;
    }