#include "header.h"

    Massive::Massive(){
        for (int i=0; i<size; i++){
            elements[i] = "";
        }
    }

    string Massive::operator[](int ind){
        return elements[ind];
    }

    void Massive::MPrint(){
        if (realsize <= 0){
            return;
        }
        for (int i=0; i<realsize; i++){
            cout<< elements[i] << endl;
        }
    }
    void Massive::MPush_ind(string element,int ind){
        if (ind > realsize || ind<0){
            return;
        }
        realsize++;
        if (size <= realsize){
            string* elements2 = new string [size*2];
            for (int i = 0; i<ind; i++){
                elements2[i] = elements[i];
            }
            elements2[ind]= element;
            for (int i = ind+1; i < size-1; i++){
                elements2[i]=elements[i-1];
            }
            delete[] elements;
            elements = elements2;
            return;
        }
        for (int i = realsize-1; i>ind; i--){
            elements[i]=elements[i-1];
            }
        elements[ind]=element;
    }

    void Massive::MPush_back(string element){
        realsize++;
        if (size < realsize){
            string* elements2 = new string [size*2];
            for (int i =0; i<size; i++ ){
                elements2[i]=elements[i];
            }
            delete[] elements;
            elements = elements2;
        }
        elements[realsize-1]=element;
    }

    void Massive::MPop_ind(int ind){
        if (ind >= realsize || ind<0){
            return;
        }
        if (realsize <= 0 ){
            return;
        }
        realsize--;
        for (int i = ind; i<= realsize; i++){
            elements[i]=elements[i+1];
        }
    }

    void Massive::MChange (int ind, string element){
        if (ind >= realsize || ind<0){
            return;
        }
        if (realsize <= 0 ){
            return;
        }
        elements[ind]=element;
    }

    void Massive::MSize(){
        if (realsize <= 0 ){
            return;
        }
        cout<< realsize <<endl;
    }

    void Massive::MWrite(string& read, string filename, int ind_start, int end){
        ofstream in;
        in.open(filename);
        if (realsize <= 0){
            cout << "Massive is empty" << endl;
            in << read;
            in.close();
            return;
        }
        int i = 0;
        while (i < realsize - 1){
            read.insert(ind_start+1, '\"' + elements[i] + '\"' + ';');
            ind_start += elements[i].size() + 3;
            i++;
        }
        read.insert(ind_start+1, '\"' + elements[realsize - 1] + '\"');
        in << read;
        in.close();
        return;
    }

    void Massive::MRead(string& read, int& ind_start, int& ind){
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
            MPush_back(datas);
            datas = "";
        }
        read.erase(ind_start + 1, ind - ind_start - 1);
        return;
    }




    // Сопоставление с паттерном
bool Massive::PatternMatch(const string& pattern, const string& str) {
    int p = 0; // Индекс для паттерна
    int s = 0; // Индекс для строки
    int starIndex = -1; // Позиция '*' в паттерне
    int matchIndex = 0; // Позиция, где началось совпадение после '*'

    while (s < str.size()) {
        if (p < pattern.size() && (pattern[p] == '?' || pattern[p] == str[s])) {
            // Символы совпадают или паттерн содержит '?'
            p++;
            s++;
        } else if (p < pattern.size() && pattern[p] == '*') {
            // Найден '*', запоминаем позицию и продолжаем
            starIndex = p;
            matchIndex = s;
            p++;
        } else if (starIndex != -1) {
            // Возвращаемся к последней '*' и пробуем совпадение дальше
            p = starIndex + 1;
            matchIndex++;
            s = matchIndex;
        } else {
            // Нет совпадения
            return false;
        }
    }

    // Пропускаем оставшиеся '*' в паттерне
    while (p < pattern.size() && pattern[p] == '*') {
        p++;
    }

    // Если дошли до конца паттерна, значит, строка соответствует
    return p == pattern.size();
}