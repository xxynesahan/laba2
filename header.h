#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class QNode {
public:
    string data;
    QNode* sled;
};

class SNode{
public:
    string data;
    SNode* sled;
};

class Queue {
public:
    QNode* head;
    QNode* tail;

    Queue ();

    void QPop();

    void QPrint();

    void QPush(string new_data);

    void QWrite(string& read, string filename, int ind_start, int end);

    void QRead(string& read, int& ind_start, int& ind);
};

class Stack{
public:
    SNode* head;

    Stack();

    void SPop();

    void SPrint();

    void SPush(string new_data);

    void SWrite(string& read, string filename, int ind_start, int end);

    void SRead(string& read, int& ind_start, int& ind);

};

class Massive{
public:
    int size=10;
    int realsize=0;

    string* elements = new string[size];

    Massive();

    string operator[](int ind);

    void MPrint();

    void MPush_ind(string element,int ind);

    void MPush_back(string element);

    void MPop_ind(int ind);

    void MChange (int ind, string element);

    void MSize(); 

    void MWrite(string& read, string filename, int ind_start, int end);

    void MRead(string& read, int& ind_start, int& ind);

    bool PatternMatch(const string& pattern, const string& str);
};

class LNode1{
public:
    string data;
    LNode1* sled;
};

class List1{
public:
    LNode1* head;

    List1();

    void L1Push_back(string new_data);

    void L1Push_head(string new_data);

    void L1Pop_head();

    void L1Pop_back();

    void L1Pop_value(string value);

    bool L1Find_value(string value);

    void L1Print();

    void LsWrite(string& read, string filename, int ind_start, int end);

    void LsRead(string& read, int& ind_start, int& ind);
}; 

class LNode2{
public:
    string data;
    LNode2* sled;
    LNode2* pred;
};

class List2{
public:
    LNode2* head;
    LNode2* tail;

    List2();

    void L2Push_back(string new_data);

    void L2Push_head(string new_data);

    void L2Pop_head();

    void L2Pop_back();

    void L2Pop_value(string value);

    bool L2Find_value(string value);

    void L2Print();

    void LdWrite(string& read, string filename, int ind_start, int end);

    void LdRead(string& read, int& ind_start, int& ind);

};

class HNode {
public:
    int delay; // Задержка
    string server; // Имя сервера
    string data;
    string key;
    HNode* sled;

    // Конструктор для удобной инициализации
    HNode(int d, const string& srv, const string& dta, const string& k, HNode* sl)
        : delay(d), server(srv), data(dta), key(k), sled(sl) {}
};

class Hash{
public:
    int size=7;
    HNode** tabl= new HNode*[size];

    Hash();

    bool Empty();

    void HPrint();

    int Hashirovanie(string new_key);

    void HPush(string key_s, string value);

    void HPop(string key_s);

    void HGet(string key_s);
    
    void HWrite(string& read, string filename, int ind_start, int end);

    void HRead(string& read, int& ind_start, int& ind);

    int find_min_delay(string start);

};

class TNode{
public:
    string data;
    TNode* left;
    TNode* right;
};

class Tree{
public:
    TNode* root;

    Tree();

    bool Empty();

    void TPush(TNode* current, string new_data);

    bool TFind(TNode* current, string find_data);

    bool is_full(TNode* current);

    //void print(TNode* root, int level);

    void TWrite(string& read, string filename, int ind_start, int ind, string data);

    int TRead(string& read, int& ind_start, int& ind);
    
    void DFS();

    int height(TNode* node, bool& balanced);
     
    bool is_balanced();

    void print(TNode* root, int level);

    void check_balanced();
}; 

class SetNode{
public:
    string data;
};

class Set{
public:
    int size;
    SetNode** setik;

    Set(int num);

    bool is_empty();

    bool is_full();

    int HSet (string data);

    bool FindInd(string value, int& ind);

    bool Set_At(string data);

    void SetPush(string new_data);

    void SetPop(string data);

    void SPrint();

    void SetWrite(string& read, string filename, int ind_start, int end);

    void SetRead(string& read, int& ind_start, int& ind);

    Set Union( Set& other);

    Set Intersection( Set& other);
   
    Set Difference( Set& other);

};


