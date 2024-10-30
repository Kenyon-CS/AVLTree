#include <iostream>
#include <algorithm>  // For std::max

// AVL tree node structure
class Node {
public:
    int key;
    Node* left;
    Node* right;
    int height;

    // Constructor to initialize a node
    Node(int value) : key(value), left(nullptr), right(nullptr), height(1) {}
};

// Function to get the height of a node
int getHeight(Node* node) {
    return node ? node->height : 0;
}

// Function to get the balance factor of a node
int getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// Right rotation function
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;  // Return new root
}

// Left rotation function
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;  // Return new root
}

// Insert a key into the AVL tree and balance the tree
Node* insert(Node* node, int key) {
    if (node == nullptr) {
        return new Node(key);  // Create a new node if tree/subtree is empty
    }

    // Perform normal BST insertion
    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        return node;  // Duplicate keys are not allowed
    }

    // Update height of the node
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    // Check the balance factor of the node to see if it became unbalanced
    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && key < node->left->key) {
        return rightRotate(node);
    }

    // Right Right Case
    if (balance < -1 && key > node->right->key) {
        return leftRotate(node);
    }

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;  // Return the unchanged node pointer
}

// Pre-order traversal function to print keys of the AVL tree
void preOrder(Node* root) {
    if (root != nullptr) {
        std::cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Function to delete the entire tree and free memory
void deleteTree(Node* node) {
    if (node != nullptr) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

// Main function to demonstrate AVL tree insertion and traversal
int main() {
    Node* root = nullptr;

    // Insert nodes into the AVL tree
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    /* The constructed AVL Tree will look like this:
                30
               /  \
             20    40
            /  \     \
          10   25     50
    */

    std::cout << "Pre-order traversal of the constructed AVL tree: ";
    preOrder(root);
    std::cout << std::endl;

    // Clean up the tree and free memory
    deleteTree(root);

    return 0;
}
