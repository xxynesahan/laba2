#include "header.h"
#include "queue.cpp"
#include "stack.cpp"
#include "massive.cpp"
#include "list1.cpp"
#include "list2.cpp"
#include "hash.cpp"
#include "tree.cpp"
#include "set.cpp"

using namespace std;

void zadanie1(){
    Tree tree;
    tree.TPush(tree.root, "root");
    tree.TPush(tree.root, "left");
    tree.TPush(tree.root, "right");
    tree.TPush(tree.root, "left_left");
    tree.TPush(tree.root, "left_right");
    cout << "DFS traversal: ";
    tree.DFS();
    cout << endl;
}

void zadanie3(){
Set set1(10);
    set1.SetPush("apple");
    set1.SetPush("banana");
    set1.SetPush("cherry");

    Set set2(10);
    set2.SetPush("banana");
    set2.SetPush("date");
    set2.SetPush("fig");

    // Объединение
    Set unionSet = set1.Union(set2);
    cout << "Union: ";
    unionSet.SPrint();

    // Пересечение
    Set intersectionSet = set1.Intersection(set2);
    cout << "Intersection: ";
    intersectionSet.SPrint();

    // Разность
    Set differenceSet = set1.Difference(set2);
    cout << "Difference: ";
    differenceSet.SPrint();
}

void zadanie4(){
    Massive arr;
    arr.MPush_back("sobaka");
    arr.MPush_back("sak");

    string pattern1 = "s*ak?";
    string pattern2 = "s*ak?";

    for (int i = 0; i < 2; i++) {
        string str = arr[i];
        if (arr.PatternMatch(pattern1, str)) {
            cout << str << " соответствует паттерну " << pattern1 << endl;
        } else if (arr.PatternMatch(pattern2, str)) {
            cout << str << " соответствует паттерну " << pattern2 << endl;
        } else {
            cout << str << " не соответствует ни одному паттерну" << endl;
        }
    }
}

void zadanie5(){
    Tree tree;
    string data;
    int value;
    
    // Ввод данных
    while (true) {
        cin >> value;
        if (value == 0) break;  // Завершаем ввод на нуле
        data = to_string(value);
        tree.TPush(tree.root, data);  // Добавляем в дерево
    }
    tree.print(tree.root, 0);
    tree.check_balanced();  // Проверка сбалансированности дерева
}

void zadanie6(){
    Hash hash_table;

// Добавление маршрутов с задержками
hash_table.HPush("A-C", "3");
hash_table.HPush("A-B", "1");
hash_table.HPush("B-C", "4");

// Ищем минимальную задержку между серверами A и C
int min_delay = hash_table.find_min_delay("A-C");
cout << "Задержка для маршрута A-С " << min_delay << endl; 

min_delay = hash_table.find_min_delay("A-B");
cout << "Задержка для маршрута A-B: " << min_delay << endl; 

min_delay = hash_table.find_min_delay("B-C");
cout << "Задержка для маршрута B-C: " << min_delay << endl; 
}


int main() {
    zadanie1();
    zadanie3();
    zadanie4();
    zadanie5();
    zadanie6();
    return 0;
}
