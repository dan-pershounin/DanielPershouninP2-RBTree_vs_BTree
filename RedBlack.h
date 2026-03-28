#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "Car.h"
#include <queue>

struct RBNode {
    int val;
    Car* data;

    bool isBlack;
    RBNode* left;
    RBNode* right;
    RBNode* parent;
    RBNode(int v, Car* d) : val(v), data(d), isBlack(false), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
public:
    RedBlackTree() {root = nullptr;}
    ~RedBlackTree() {
        deleteTheTree(root);
    }


    int getHeight() {
        if (root == nullptr) {
            return 0;
        }
        return height(root);
    }
    int height(RBNode* root) {
        if (root == nullptr)
        {
            return 0;
        }
        int lh = height(root->left);
        int rh = height(root->right);
        return 1 + std::max(lh, rh);
    }

    void print() {
        if (root == nullptr) {
            return;
        }

        std::queue<RBNode*> q;
        q.push(root);

        int lev = 1;

        while (!q.empty()) {
            int size = q.size();

            for (int i = 0; i < size; i++) {
                RBNode* node = q.front();
                q.pop();

                std::cout << "Level " << lev << ": ";
                std::cout << node->val;

                if (node->isBlack) {
                    std::cout << "(B)\n";
                }
                else {
                    std::cout << "(R)\n";
                }


                if (node->left) {
                    q.push(node->left);
                }
                if (node->right) {
                    q.push(node->right);
                }
            }

            std::cout << "\n";
            lev++;
        }
    }


    void insert(int val, Car* data) {
        RBNode* node = new RBNode(val, data);

        node->left = nullptr;
        node->right = nullptr;
        node->parent = nullptr;
        node->isBlack = false;

        binsert(node);
        redBlackMagic(node);
    }
    Car* search(int val) {
        RBNode* current = root;

        while (current != nullptr) {
            if (val == current->val) {
                return current->data;
            }
            else if (val < current->val) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        return nullptr;
    }

private:
    RBNode* root;

    void rotateLeft(RBNode* node) {
        RBNode* rnode = node->right;

        node->right = rnode->left;
        if (rnode->left != nullptr) {
            rnode->left->parent = node;
        }
        rnode->parent = node->parent;

        if (node->parent == nullptr) {
            root = rnode;
        }
        else if (node == node->parent->left) {
            node->parent->left = rnode;
        }
        else {
            node->parent->right = rnode;
        }
        rnode->left = node;
        node->parent = rnode;
    }

    void rotateRight(RBNode* node) {
        RBNode* lnode = node->left;

        node->left = lnode->right;
        if (lnode->right != nullptr) {
            lnode->right->parent = node;
        }
        lnode->parent = node->parent;

        if (node->parent == nullptr) {
            root = lnode;
        }
        else if (node == node->parent->right) {
            node->parent->right = lnode;
        }
        else {
            node->parent->left = lnode;
        }
        lnode->right = node;
        node->parent = lnode;
    }

    void binsert(RBNode* node) {

        RBNode* current = root;
        RBNode* parent = nullptr;

        while (current != nullptr) {
            parent = current;
            if(node->val < current->val){
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        node->parent = parent;

        if (parent == nullptr) {
            root = node;
        }
        else if (node->val < parent->val) {
            parent->left = node;
        }
        else {
            parent->right = node;
        }

        node->left = nullptr;
        node->right = nullptr;
        node->isBlack = false;

    }
    void redBlackMagic(RBNode* node) {
        while (node != root && node->parent != nullptr && node->parent->isBlack == false) {

            RBNode* parent = node->parent;
            RBNode* gp = parent->parent;
            if (gp == nullptr) {
                break;
            }

            if (parent == gp->left) {

                RBNode* unc = gp->right;

                if (unc != nullptr && unc->isBlack == false) {
                    parent->isBlack = true;
                    unc->isBlack = true;
                    gp->isBlack = false;
                    node = gp;
                }
                else {
                    if (node == parent->right) {
                        node = parent;
                        rotateLeft(node);
                        parent = node->parent;
                        gp = parent->parent;
                    }

                    parent->isBlack = true;
                    gp->isBlack = false;
                    rotateRight(gp);
                }
            }
            else {
                RBNode* unc = gp->left;

                if (unc != nullptr && unc->isBlack == false) {
                    parent->isBlack = true;
                    unc->isBlack = true;
                    gp->isBlack = false;
                    node = gp;
                }
                else {
                    if (node == parent->left) {
                        node = parent;
                        rotateRight(node);
                        parent = node->parent;
                        gp = parent->parent;
                    }

                    parent->isBlack = true;
                    gp->isBlack = false;
                    rotateLeft(gp);
                }
            }
        }
        root->isBlack = true;
    }

    void deleteTheTree(RBNode* node){
        if(node == nullptr){
            return;
        }
        deleteTheTree(node->left);
        deleteTheTree(node->right);
        delete node;
    }
};



