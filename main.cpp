#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <functional>
#include <numeric>
#include <string>

struct Node {
    int key;
    Node* left;
    Node* right;
};

Node* newNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

Node* insert(Node* node, int key) {
    // Wenn der Baum leer ist, wird ein neuer Knoten zugewiesen
    if (node == nullptr)return newNode(key);

    // Andernfalls wird der Baum rekursiv durchlaufen
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    return node;
}

int height(Node* node) {
    if (node == nullptr)
        return 0;
    return std::max(height(node->left), height(node->right)) + 1;
}

int balanceFactor(Node* node) {
    if (node == nullptr)
        return 0;
    return height(node->right) - height(node->left);
}

void inOrder(Node* node, std::vector<int>& keys) {
    if (node != nullptr) {
        inOrder(node->left, keys);
        keys.push_back(node->key);
        inOrder(node->right, keys);
    }
}

bool isAVL(Node* node) {
    if (node == nullptr)
        return true;

    int balance = balanceFactor(node);
    if (balance > 1 || balance < -1) {
        std::cout << "bal(" << node->key << ") = " << balance << " (AVL violation!)\n";
        isAVL(node->left) && isAVL(node->right);
        return false;
    }
    std::cout << "bal(" << node->key << ") = " << balance << "\n";
    return isAVL(node->left) && isAVL(node->right);
}

void checkAVL(Node* root) {
    if (isAVL(root))std::cout << "AVL: yes\n";
    else std::cout << "AVL: no\n";
}
// Hinzuf�gen einer Funktion zum Suchen eines Knotens im Baum
void searchkey(Node *root, int key, std::string path = "") {
    if (root == nullptr) {
        std::cout << key << " not found!" << std::endl;
        return ;
    }
    path += std::to_string(root->key);
    if (key < root->key){
        path+= ", ";
        searchkey(root->left, key, path);
    }
    else if (key > root->key){
        path+= ", ";
        searchkey(root->right, key, path);
    }
    else
        std::cout << key << " found " << path << std::endl;
}

// Funktion zum �berpr�fen, ob ein Subtree in einem anderen Baum vorhanden ist
bool isSubtree(Node* root, Node* subtree) {
    if (subtree == nullptr)
        return true;
    if (root == nullptr)
        return false;
    if (root->key == subtree->key)
        return isSubtree(root->left, subtree->left)&&isSubtree(root->right, subtree->right);
    return isSubtree(root->left, subtree) || isSubtree(root->right, subtree);
}
int main() {
    Node* root = nullptr;
    std::ifstream file("filename.txt");
    int key;
    std::vector<int> keys;
    //Checken ob das File ge�ffnet werden kann
    if (!file.is_open()){
        std::cout << "Error opening file." << std::endl;
        return 1;
    }
    while (file >> key) {
        root = insert(root, key);
    }
    file.close();

    //AVL
    checkAVL(root);
    //Ausgabe min, max, avg
    inOrder(root, keys);
    std::cout << std::endl;
    std::cout << "min: " << keys.front() << ", max: " << keys.back() << ", avg: " << std::accumulate(keys.begin(), keys.end(), 0.0) / keys.size() << std::endl;
    std::cout << std::endl;
    //Subtree
    Node* subtree = nullptr;
    std::ifstream subtreeFile("subtree.txt");
    if (!subtreeFile.is_open()){
        std::cout << "Error opening file." << std::endl;
        return 1;
    }
    while (subtreeFile >> key) {
        subtree = insert(subtree, key);
    }
    subtreeFile.close();

    std::cout << "Subtree Suche" << std::endl;
     // �berpr�fen, ob der Subtree im Suchbaum vorhanden ist
    if (isSubtree(root, subtree))
        std::cout << "Subtree found" << std::endl;
    else
        std::cout << "Subtree not found!" << std::endl;

    std::cout << "Einfache Suche" << std::endl;
    searchkey(root, 22, "");
    return 0;
}
