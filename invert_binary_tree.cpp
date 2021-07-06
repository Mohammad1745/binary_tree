#include <iostream>
using namespace std;

struct Node {
    float data;
    struct Node* parent;
    struct Node* left;
    struct Node* right;

    Node (float _data, struct Node* _parent=NULL)
    {
        data = _data;
        if (_parent) parent = _parent;
    }
};

struct BinaryTree {
    static void invert(struct Node* node) {
        if (!node) return;

        invert(node->left);
        invert(node->right);

        Node* temp = node->left;
        node->left = node->right;
        node->right = temp;
    }
    static void print_tree(struct Node* node)
    {
        if (!node) return;

        if (node->left || node->right) cout << node->data << " -> ";
        if (node->left) cout << node->left->data << " ";
        if (node->right) cout << node->right->data << " " << endl;
        print_tree(node->left);
        print_tree(node->right);
    }
};

int main() {
    Node* root = new Node(0);
    Node* node1 = new Node(1, root);
    Node* node2 = new Node(2, root);
    Node* node3 = new Node(3, node1);
    Node* node4 = new Node(4, node1);
    Node* node5 = new Node(5, node2);
    Node* node6 = new Node(6, node2);

    root->left = node1;
    root->right = node2;
    node1->left = node3;
    node1->right = node4;
    node2->left = node5;
    node2->right = node6;

    BinaryTree::print_tree(root);
    cout << endl;

    BinaryTree::invert(root);
    cout << "Inverted" << endl;

    BinaryTree::print_tree(root);

    return 0;
}
