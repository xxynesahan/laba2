#include "header.h"

Tree::Tree(){
    root=nullptr;
}

bool Tree::Empty(){
        return root==nullptr;
    }

    void Tree::TPush(TNode* current, string new_data){
        if (Empty()){
            root = new TNode{new_data, nullptr, nullptr};
            return;
        }
        if (current->left == nullptr){
            current->left = new TNode{new_data, nullptr, nullptr};
            return;
        }
        if (current->right == nullptr){
            current->right = new TNode{new_data, nullptr, nullptr};
            return;
        }
        if (new_data >= current->data){
            TPush(current->right, new_data);
            return;
        } else {
            TPush(current->left, new_data);
            return;
        }
    }
     bool Tree::TFind(TNode* current, string find_data){
        if (Empty()){
            cout << "Tree is empty" << endl;
            return false;
        }
        if (current->data == find_data){
            return true;
        }
        bool is_here = false;
        while ((current != nullptr) && (current->right != nullptr && current->left != nullptr)){
            if (current->left->data == find_data || current->right->data == find_data){
                is_here = true;
                break;
            }
            if (find_data > current->data){
                current = current->right;
            } else {
                current = current->left;
            }
        }
        return is_here;
    }
    
    bool Tree::is_full(TNode* current){
        if (Empty()){
            cout << "List is empty" << endl;
            return false;
        }
        if (current == nullptr){
            return true;
        }
        if (current->left == nullptr && current->right == nullptr){
            return true;
        }

        if (current->right != nullptr && current->left != nullptr){
            return is_full(current->left) && is_full(current->right);
        }

        return false;

    }
    /*void Tree::print(TNode* root, int level)
    {
        if (root != NULL)
        {
            print(root->right, level + 1);
            for (int i = 0; i < level * 4; i++) cout << "   ";
            cout << root->data << endl;
            print(root->left, level + 1);
        }
    }*/

    void Tree::TWrite(string& read, string filename, int ind_start, int ind, string data){
        ofstream in;
        in.open(filename);
        if (Empty()){
            cout << "List is empty" << endl;
            in << read;
            in.close();
            return;
        }
        if (read[ind_start+1] == '}') read.insert(ind_start + 1, '\"' + data + '\"');
        else {
            read.insert(ind, '\"' + data + '\"');
        }
        in << read;
        in.close();
        return;
    }   

    int Tree::TRead(string& read, int& ind_start, int& ind){
        for (ind; read[ind] != '{' && ind < read.size(); ind++);
        ind_start = ind;
        ind++;
        if (read[ind] == '}'){
            return 0;
        }
        int count = 1;
        string datas = "";
        for (ind; read[ind] != '}' && read[ind] != '\n' && ind < read.size(); ind++){
            count++;
            for (ind; read[ind] != '\"' && read[ind] != '}' && read[ind] != '\n'; ind++) count++;
            ind++;
            for (ind; read[ind] != '\"' && read[ind] != '}' && read[ind] != '\n'; ind++){
                datas += read[ind];
                count++;
            }
            TPush(root, datas);
            datas = "";
        }
        return count;
    }

    void Tree::DFS() {
        if (Empty()) {
            cout << "Tree is empty" << endl;
            return;
        }

        Stack stack;
        stack.SPush(root->data);

        while (stack.head != nullptr) {
            string current_data = stack.head->data;
            stack.SPop();
            cout << current_data << " ";

            TNode* current = root;
            while (current != nullptr && current->data != current_data) {
                if (current_data > current->data) {
                    current = current->right;
                } else {
                    current = current->left;
                }
            }

            if (current != nullptr) {
                if (current->right != nullptr) {
                    stack.SPush(current->right->data);
                }
                if (current->left != nullptr) {
                    stack.SPush(current->left->data);
                }
            }
        }
    }


    // Метод для вычисления высоты дерева и проверки сбалансированности
    int Tree::height(TNode* node, bool& balanced) {
        if (node == nullptr) {
            return 0;  // Если узел пустой, высота равна 0
        }

        // Вычисляем высоту левого поддерева
        int left_height = height(node->left, balanced);
        if (!balanced) return 0;  // Если дерево уже несбалансировано, прерываем

        // Вычисляем высоту правого поддерева
        int right_height = height(node->right, balanced);
        if (!balanced) return 0;  // Если дерево уже несбалансировано, прерываем

        // Если разница в высотах левого и правого поддеревьев больше 1, дерево несбалансировано
        if (abs(left_height - right_height) > 1) {
            balanced = false;
        }

        // Возвращаем высоту текущего узла
        return max(left_height, right_height) + 1;
    }

   // Метод для проверки сбалансированности
    bool Tree::is_balanced() {
        bool balanced = true;  // Флаг сбалансированности
        height(root, balanced);  // Вызываем метод для вычисления высоты и проверки баланса
        return balanced;
    }

    // Метод для печати дерева
    void Tree::print(TNode* root, int level) {
        if (root != nullptr) {
            print(root->right, level + 1);  // Рекурсивный вызов для правого поддерева
            for (int i = 0; i < level * 4; i++) cout << "   ";  // Отступы для уровней
            cout << root->data << endl;  // Печать текущего узла
            print(root->left, level + 1);  // Рекурсивный вызов для левого поддерева
        }
    }

    // Проверка на сбалансированность
    void Tree::check_balanced() {
        if (is_balanced()) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
