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



//
//#include <iostream>
//#include <fstream>
//#include <cmath>
//#include <algorithm>
//#include <vector>
//
//using namespace std;
//
//// Node structure for the AVL tree
//struct Node
//{
//    int key;
//    Node *left;
//    Node *right;
//};
//
//// Function to create a new node
//Node *createNewNode(int key)
//{
//    // Error handling for memory allocation
//    Node *node = new (nothrow) Node;
//    if (!node)
//    {
//        cerr << "Memory allocation failed" << endl;
//        return nullptr;
//    }
//    node->key = key;
//    node->left = node->right = nullptr;
//    return node;
//}
//
//// Function to insert a new node into the AVL tree
//Node *insertNodeIntoAVLTree(Node *node, int key)
//{
//    if (node == nullptr)
//        return createNewNode(key);
//    if (key < node->key)
//        node->left = insertNodeIntoAVLTree(node->left, key);
//    else if (key > node->key)
//        node->right = insertNodeIntoAVLTree(node->right, key);
//    return node;
//}
//
//// Function to calculate the height of a node
//int calculateNodeHeight(Node *node)
//{
//    if (node == nullptr)
//        return 0;
//    return max(calculateNodeHeight(node->left), calculateNodeHeight(node->right)) + 1;
//}
//
//// Function to calculate the balance factor of a node
//int calculateBalanceFactor(Node *node)
//{
//    if (node == nullptr)
//        return 0;
//    return calculateNodeHeight(node->right) - calculateNodeHeight(node->left);
//}
//
//bool isAVL = true;
//
//// Function to check if the tree is an AVL tree
//void checkIfTreeIsAVLTree(Node *root)
//{
//    if (root != nullptr)
//    {
//        checkIfTreeIsAVLTree(root->left);
//        int balance = calculateBalanceFactor(root);
//        cout << "bal(" << root->key << ") = " << balance;
//        if (balance > 1 || balance < -1)
//        {
//            cout << " (AVL violation!)";
//            isAVL = false;
//        }
//        cout << endl;
//        checkIfTreeIsAVLTree(root->right);
//    }
//}
//
//int minKey = INT_MAX;
//int maxKey = INT_MIN;
//double sumKeys = 0;
//int countKeys = 0;
//
//// Function to calculate the minimum, maximum and average keys
//void calculateMinMaxAvgKeys(Node *root)
//{
//    if (root != nullptr)
//    {
//        calculateMinMaxAvgKeys(root->left);
//        minKey = min(minKey, root->key);
//        maxKey = max(maxKey, root->key);
//        sumKeys += root->key;
//        countKeys++;
//        calculateMinMaxAvgKeys(root->right);
//    }
//}
//
//// Function to read the keys from a file and build the AVL tree
//Node *buildAVLTreeFromFile(string filename)
//{
//    // Error handling for file opening
//    ifstream file(filename);
//    if (!file)
//    {
//        cerr << "Cannot open file: " << filename << endl;
//        return nullptr;
//    }
//
//    Node *root = nullptr;
//    int key;
//    while (file >> key)
//    {
//        // Error handling for reading key from file
//        if (file.fail())
//        {
//            cerr << "Error reading key from file" << endl;
//            break;
//        }
//        root = insertNodeIntoAVLTree(root, key);
//    }
//
//    if (root != nullptr)
//    {
//        checkIfTreeIsAVLTree(root);
//        cout << "AVL: " << (isAVL ? "yes" : "no") << endl;
//
//        calculateMinMaxAvgKeys(root);
//        cout << "min: " << minKey << ", max: " << maxKey << ", avg: " << sumKeys / countKeys << endl;
//    }
//
//    return root;
//}
//
//// Function to search a key in the AVL tree
//void searchKeyInAVLTree(Node *root, int key)
//{
//    if (root == nullptr)
//    {
//        cout << key << " not found!" << endl;
//        return;
//    }
//    if (key < root->key)
//        searchKeyInAVLTree(root->left, key);
//    else if (key > root->key)
//        searchKeyInAVLTree(root->right, key);
//    else
//        cout << key << " found" << endl;
//}
//
//// Function to check if a tree is a subtree of another tree
//bool checkIfExactSubtree(Node *tree, Node *subtree)
//{
//    if (subtree == nullptr)
//        return true;
//    if (tree == nullptr)
//        return false;
//    if (tree->key == subtree->key)
//        return checkIfExactSubtree(tree->left, subtree->left) && checkIfExactSubtree(tree->right, subtree->right);
//    return checkIfExactSubtree(tree->left, subtree) || checkIfExactSubtree(tree->right, subtree);
//}
//
//// Function to search a key in the AVL tree and print the path
//void searchKeyAndPrintPath(Node *root, int key, string path = "")
//{
//    if (root == nullptr)
//    {
//        cout << key << " not found!" << endl;
//        return;
//    }
//    path += to_string(root->key) + ", ";
//    if (key < root->key)
//        searchKeyAndPrintPath(root->left, key, path);
//    else if (key > root->key)
//        searchKeyAndPrintPath(root->right, key, path);
//    else
//        cout << key << " found " << path << endl;
//}
//
//// Function to convert the AVL tree to a list
//void convertAVLTreeToList(Node *root, vector<int> &list)
//{
//    if (root != nullptr)
//    {
//        convertAVLTreeToList(root->left, list);
//        list.push_back(root->key);
//        convertAVLTreeToList(root->right, list);
//    }
//}
//
//// Function to join the elements of a list into a string
//string joinListElementsIntoString(const vector<int> &list, const string &delimiter)
//{
//    string result;
//    for (int i = 0; i < list.size(); i++)
//    {
//        result += to_string(list[i]);
//        if (i < list.size() - 1)
//            result += delimiter;
//    }
//    return result;
//}
//
//// Function to check if a tree is a subtree of another tree
//bool checkIfSubtree(Node *tree, Node *subtree)
//{
//    vector<int> treeList, subtreeList;
//    convertAVLTreeToList(tree, treeList);
//    convertAVLTreeToList(subtree, subtreeList);
//
//    string treeStr = "," + joinListElementsIntoString(treeList, ",") + ",";
//    string subtreeStr = "," + joinListElementsIntoString(subtreeList, ",") + ",";
//
//    return treeStr.find(subtreeStr) != string::npos;
//}
//
//// Main function
//int main()
//{
//    // read filename from user
//    string filename;
//    while (true)
//    {
//        cout << "Enter filename: ";
//        cin >> filename;
//        if (!filename.empty() && ifstream(filename))
//        {
//            break;
//        }
//        else
//        {
//            cerr << "Invalid filename. Please try again." << endl;
//        }
//    }
//
//    Node *root = buildAVLTreeFromFile(filename);
//
//    // Perform the simple search
//    int keyToSearch;
//    while (true)
//    {
//        cout << "Enter a key to search: ";
//        cin >> keyToSearch;
//        if (!cin.fail())
//        {
//            break;
//        }
//        else
//        {
//            cerr << "Invalid key. Please try again." << endl;
//            cin.clear();
//            cin.ignore(numeric_limits<streamsize>::max(), '\n');
//        }
//    }
//    searchKeyAndPrintPath(root, keyToSearch);
//
//    // Perform the subtree search
//    string subtreeFilename;
//    while (true)
//    {
//        cout << "Enter subtree filename: ";
//        cin >> subtreeFilename;
//        if (!subtreeFilename.empty() && ifstream(subtreeFilename))
//        {
//            break;
//        }
//        else
//        {
//            cerr << "Invalid filename. Please try again." << endl;
//        }
//    }
//
//    Node *subtree = buildAVLTreeFromFile(subtreeFilename);
//    if (subtree != nullptr)
//    {
//        cout << (checkIfExactSubtree(root, subtree) ? "Subtree found" : "Subtree not found!") << endl;
//    }
//
//    return 0;
//}
