#include "header.h"

Hash::Hash(){
        for(int i=0; i<size; i++){
           tabl[i]=nullptr; 
        }
    }

    bool Hash::Empty(){
        for(int i=0; i<size; i++){
           if (tabl[i]!=nullptr){
            return false;
           }
        }
        return true;
    }

    void Hash::HPrint(){
        int ind = 0;
        if (Empty()){
            return;
        }
    HNode* current=nullptr;
    while (ind<size){
        if (tabl[ind]!=nullptr){
            for (current=tabl[ind]; current!=nullptr; current=current->sled){
                cout<<current->key << " " << current->data <<endl;
            }
        }
        ind++;   
    }
    }
    
    int Hash::Hashirovanie(string new_key){
        int sum=0;
        for (int i=0; i<new_key.size(); i++){
            sum+=new_key[i];
        }
        return sum%size;//получаем индекс
    }

    void Hash::HPush(string key_s, string value){
        int new_key = Hashirovanie(key_s);
        if (tabl[new_key] != nullptr){
            HNode* current = tabl[new_key];
            for (current; current != nullptr; current = current->sled){
                if (current->key == key_s) {
                    current->data = value;
                    return;
                }
            }
        }
        int delay = stoi(value); // Преобразуем строку в целое число для задержки
        HNode* new_node = new HNode{0, "", value, key_s, tabl[new_key]};
        tabl[new_key] = new_node;
    }

    void Hash::HPop(string key_s){
        if (Empty()){
            return;
        }
        int new_key = Hashirovanie(key_s);
        if (tabl[new_key]==nullptr){
            return;
        }
        HNode* current = tabl[new_key];
        if (tabl[new_key]->key==key_s){
            current = tabl[new_key];
            delete current;
            tabl[new_key]=tabl[new_key]->sled;
            return;
        }
        while (current->sled!=nullptr){
            if (current->sled->key==key_s){
                HNode* kill_node = current->sled;
                current->sled=kill_node->sled;
                delete kill_node;
                return;
            }
                current=current->sled;
            }
        if (current->sled==nullptr){
            return;
        }
    }

    void Hash::HGet(string key_s){
        if (Empty()){
            return;
        }
        int new_key = Hashirovanie(key_s);
        if (tabl[new_key]==nullptr){
            return;
        }
        HNode* current = tabl[new_key];
        while (current != nullptr){
            if (current->key == key_s){
                cout << current->data << endl;
            }
            current = current->sled;
        }
        if (current == nullptr){
            return;
        }
        return;
    }

     void Hash::HWrite(string& read, string filename, int ind_start, int end){
        ofstream in;
        in.open(filename);
        if (Empty()){
            cout << "Hash is empty" << endl;
            in << read;
            in.close();
            return;
        }
        int i = 0;
        while (i < size){
            if (tabl[i] != nullptr){
                HNode* current = tabl[i];
                while(current != nullptr){
                    read.insert(ind_start+1, '(' + current->key + ',' + current->data + ')');
                    ind_start += current->key.size() + current->data.size() + 3;
                    current = current->sled;
                }
            }
            i++;
        }
        in << read;
        in.close();
        return;
    }

    void Hash::HRead(string& read, int& ind_start, int& ind){
        for (ind; read[ind] != '{' && ind < read.size(); ind++);
        ind_start = ind;
        ind++;
        if (read[ind] == '}'){
            return;
        }
        string datas = "";
        string key = "";
        for (ind; read[ind] != '}' && read[ind] != '\n' && ind < read.size(); ind++){
            for (ind; read[ind] != '(' && read[ind] != '}' && ind < read.size(); ind++);
            ind++;
            for (ind; read[ind] != ',' && read[ind] != ')' && ind < read.size(); ind++){
                key += read[ind];
            }
            ind++;
            for (ind; read[ind] != ')' && read[ind] != '}' && ind < read.size(); ind++){
                datas += read[ind];
            }
            HPush(key, datas);
            datas = "";
            key = "";
        }
        read.erase(ind_start + 1, ind - ind_start - 1);
        return;
    }


int Hash::find_min_delay(string start_end) {
    size_t pos = start_end.find('-');
    string start = start_end.substr(0, pos);
    string end = start_end.substr(pos + 1);

    // Если мы не нашли такой маршрут в таблице
    if (tabl[Hashirovanie(start + "-" + end)] == nullptr) {
        cout << "Маршрут не найден." << endl;
        return -1; // Возвращаем -1, если путь не найден
    }

    // для нахождения минимальной задержки
    int* delays = new int[size];
    bool* visited = new bool[size];
    string* path = new string[size];

    // Инициализация
    for (int i = 0; i < size; i++) {
        visited[i] = false;
        delays[i] = 1000;
    }
    delays[Hashirovanie(start)] = 0;

    // Для обхода используем индексный массив
    bool path_found = false;

    while (!path_found) {
        // Ищем сервер с минимальной задержкой
        int min_index = -1;
        int min = 1000;
        for (int i = 0; i < size; i++) {
            if (!visited[i] && delays[i] < min) {
                min = delays[i];
                min_index = i;
            }
        }

        if (min_index == -1) break;  // Если нет доступных серверов, выходим

        // Помечаем сервер как посещенный
        visited[min_index] = true;

        // Перебираем все маршруты, выходящие из этого сервера
        HNode* current = tabl[min_index];
        while (current != nullptr) {
            string from = current->key.substr(0, current->key.find("-"));
            string to = current->key.substr(current->key.find("-") + 1);
            int delay = stoi(current->data); // Задержка для маршрута

            // Если мы ещё не посетили этот сервер
            int to_index = Hashirovanie(to);
            if (!visited[to_index] && delays[min_index] + delay < delays[to_index]) {
                delays[to_index] = delays[min_index] + delay;
                path[to_index] = from;
            }

            current = current->sled;
        }

        // Проверяем, достигли ли конечного сервера
        if (delays[Hashirovanie(end)] != 1000) {
            path_found = true;
        }
    }

    // Возвращаем минимальную задержку или -1, если путь не найден
    int result = delays[Hashirovanie(end)];
    delete[] delays;
    delete[] visited;
    delete[] path;

    return result == 1000 ? -1 : result;
}
