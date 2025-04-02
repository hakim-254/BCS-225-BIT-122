#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* createNode(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

Node* insert(Node* root, int data) {
    if (root == nullptr) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    return root;
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != nullptr)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root, int data) {
    if (root == nullptr) return root;

    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

bool search(Node* root, int data) {
    if (root == nullptr) return false;
    if (root->data == data) return true;
    if (data < root->data)
        return search(root->left, data);
    else
        return search(root->right, data);
}

void inorder(Node* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

int height(Node* root) {
    if (root == nullptr) return 0;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return max(leftHeight, rightHeight) + 1;
}

int size(Node* root) {
    if (root == nullptr) return 0;
    return 1 + size(root->left) + size(root->right);
}

int main() {
    Node* root = nullptr;

    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);

    cout << "Inorder traversal: ";
    inorder(root);
    cout << "\nHeight of tree: " << height(root);
    cout << "\nSize of tree: " << size(root);

    cout << "\nSearch for 40: " << (search(root, 40) ? "Found" : "Not found");
    cout << "\nSearch for 100: " << (search(root, 100) ? "Found" : "Not found");

    root = deleteNode(root, 20);
    cout << "\nAfter deleting 20, inorder traversal: ";
    inorder(root);

    root = deleteNode(root, 30);
    cout << "\nAfter deleting 30, inorder traversal: ";
    inorder(root);

    root = deleteNode(root, 50);
    cout << "\nAfter deleting 50, inorder traversal: ";
    inorder(root);

    cout << "\nNew height of tree: " << height(root);
    cout << "\nNew size of tree: " << size(root) << endl;

    return 0;
}