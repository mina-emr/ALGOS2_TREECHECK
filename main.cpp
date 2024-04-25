#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

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
    if (node == nullptr)
        return newNode(key);
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
    if (balance > 1 || balance < -1)
        return false;
    return isAVL(node->left) && isAVL(node->right);
}

int main() {
    Node* root = nullptr;
    std::ifstream file("filename.txt");
    int key;
    while (file >> key) {
        root = insert(root, key);
    }
    file.close();

    std::vector<int> keys;
    inOrder(root, keys);

    std::cout << "AVL: " << (isAVL(root) ? "yes" : "no") << std::endl;
    std::cout << "min: " << keys.front() << ", max: " << keys.back() << ", avg: " << std::accumulate(keys.begin(), keys.end(), 0.0) / keys.size() << std::endl;

    return 0;
}
