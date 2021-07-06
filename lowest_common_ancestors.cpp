#include <iostream>
using namespace std;

struct Node {
    string data;
    struct Node* parent;
    struct Node* left;
    struct Node* right;

    Node (string _data, struct Node * _parent=NULL)
    {
        data = _data;
        if (_parent) parent = _parent;
    }
};

struct BinaryTree {

    static void print_tree(struct Node * node)
    {
        if (!node) return;

        if (node->left || node->right) cout << node->data << " -> ";
        if (node->left) cout << node->left->data << " ";
        if (node->right) cout << node->right->data << " " << endl;

        print_tree(node->left);
        print_tree(node->right);
    }

    static int node_level (Node * root, Node * input_node) {
        int level = 0;
        Node* node = input_node;
        while (node != root) {
            node = node->parent;
            level++;
        }
        return level;
    }

    static Node * lowest_common_ancestor (struct Node * root, struct Node * node_1, struct Node * node_2)
    {
        int node_1_level = node_level(root, node_1);
        int node_2_level = node_level(root, node_2);

        while (node_2_level > node_1_level) {
            node_2 = node_2->parent;
            node_2_level--;
        }
        while (node_1_level > node_2_level) {
            node_1 = node_1->parent;
            node_1_level--;
        }

        while (node_1->parent != node_2->parent){
            node_1 = node_1->parent;
            node_2 = node_2->parent;
        }
        return node_1->parent;
    }
};

int main() {

    Node* node_A = new Node("A");
    Node* node_B = new Node("B", node_A);
    Node* node_C = new Node("C", node_A);
    Node* node_D = new Node("D", node_B);
    Node* node_E = new Node("E", node_B);
    Node* node_F = new Node("F", node_C);
    Node* node_G = new Node("G", node_C);
    Node* node_H = new Node("H", node_D);
    Node* node_I = new Node("I", node_D);

    node_A->left = node_B;
    node_A->right = node_C;
    node_B->left = node_D;
    node_B->right = node_E;
    node_C->left = node_F;
    node_C->right = node_G;
    node_D->left = node_H;
    node_D->right = node_I;

    cout << "Tree: " << endl;
    BinaryTree::print_tree(node_A);
    cout << endl;

    Node * result = BinaryTree::lowest_common_ancestor(node_A, node_E, node_I);

    cout << "Lowest Common Ancestor: " << result->data << endl;

    return 0;
}
