#include <iostream>
using namespace std;

struct Node {
    string data;
    struct Node* parent;
    struct Node* left;
    struct Node* right;

    Node (string _data, struct Node* _parent=NULL)
    {
        data = _data;
        if (_parent) parent = _parent;
    }
};

struct BinaryTree {
    static void print_tree(struct Node* node)
    {
        if (!node) return;

        if (node->left || node->right) cout << node->data << " -> ";
        if (node->left) cout << node->left->data << " ";
        else if(node->right) cout << "- ";
        if (node->right) cout << node->right->data << " " << endl;
        else if(node->left) cout << endl;

        print_tree(node->left);
        print_tree(node->right);
    }

    static string* left_view(struct Node* node) {
        auto* left_view = new string[10];

        int level = 0;
        left_view[level] = node->data;

        while (true) {
            bool break_it = false;

            if (node->left) {
                node = node->left;
                level++;
                if (left_view[level].empty()) left_view[level] = node->data;
            }
            else if (node->right) {
                node =  node->right;
                level++;
                if (left_view[level].empty()) left_view[level] = node->data;
            }
            else if (node->parent){//g
                Node* parent = node->parent;//c

                while (parent) {
                    if (node==parent->left && parent->right) {//false
                        node = parent->right;
                        break;
                    }
                    else if (parent->parent) {
                        node = parent;
                        parent = parent->parent;
                        level--;
                    }
                    else {
                        break_it = true;
                        break;
                    }
                }
            }
            else break;

            if (break_it) break;
        }

        return left_view;
    }
};

int main() {
    Node* node_A = new Node("A");
    Node* node_B = new Node("B", node_A);
    Node* node_C = new Node("C", node_A);
    Node* node_D = new Node("D", node_B);
//    Node* node_E = new Node("E", node_B);
    Node* node_F = new Node("F", node_C);
    Node* node_G = new Node("G", node_C);
    Node* node_H = new Node("H", node_D);
    Node* node_I = new Node("I", node_D);
    Node* node_J = new Node("J", node_G);
    Node* node_K = new Node("K", node_J);

    node_A->left = node_B;
    node_A->right = node_C;
    node_B->left = node_D;
//    node_B->right = node_E;
    node_C->left = node_F;
    node_C->right = node_G;
    node_D->left = node_H;
    node_D->right = node_I;
    node_G->right = node_J;
    node_J->right = node_K;

    BinaryTree::print_tree(node_A);
    cout << endl;

    string* list = BinaryTree::left_view(node_A);

    cout << "Left Side View: "; // A -> B -> D -> H -> K
    for (int i = 0; list[i]!=""; ++i) {
        cout << list[i] << " -> ";
    }


    return 0;
}
