#ifndef REDBLACKBCARS_BTREE_H
#define REDBLACKBCARS_BTREE_H

#include <iostream>
#include <vector>
#include "Car.h"
#include <queue>
//Degree = 16
//Maxkeys = 31 (2d-1)
//Maxchild = 32 (2d)

struct BNode {
    int nkeys;
    int keys[31];
    Car* data[31];
    BNode* children[32];
    bool isLeaf;

    BNode(bool l) : nkeys(0), isLeaf(l) {
        for (int i = 0; i < 32; i++) {
            children[i] = nullptr;
        }
        for (int i = 0; i < 31; i++) {
            data[i] = nullptr;
        }
    }
};

class BTree {
public:
    BTree() {root = new BNode(true);}
    ~BTree() {
        deleteBTree(root);
    }

    int getHeight() {
        if (root == nullptr) {
            return 0;
        }
        return height(root);
    }
    int height(BNode* root) {
        if (root == nullptr)
        {
            return 0;
        }
        if (root->isLeaf == true)
        {
            return 1;
        }
        return 1 + height(root->children[0]);
    }

    void print() {
        if (root == nullptr) {
            return;
        }
        std::queue<BNode*> q;
        q.push(root);

        int lev = 1;

        while (!q.empty()) {
            int size = q.size();


            for (int i = 0; i < size; i++) {
                BNode* node = q.front();
                q.pop();

                std::cout << "Level " << lev << ": ";
                std::cout << "[";
                for (int j = 0; j < node->nkeys; j++) {
                    std::cout << node->keys[j];
                    if (j < node->nkeys - 1) std::cout << ",";
                }
                std::cout << "]\n";

                if (!node->isLeaf) {
                    for (int j = 0; j <= node->nkeys; j++) {
                        if (node->children[j] != nullptr) {
                            q.push(node->children[j]);
                        }
                    }
                }
            }

            std::cout << "\n";
            lev++;
        }
    }

    void insert(int key, Car* car) {
        if (root->nkeys == 31) {
            BNode* newRoot = new BNode(false);
            newRoot->children[0] = root;
            splitChild(newRoot, 0, root);
            root = newRoot;
        }

        insnotfull(root, key, car);
    }
    Car* search(int key){return searchNode(root, key);}
private:
    BNode* root;

    void insnotfull(BNode* node, int key, Car* car) {
        int i = node->nkeys - 1;

        if (node->isLeaf) {
            while (i >= 0 && key < node->keys[i]) {
                node->keys[i + 1] = node->keys[i];
                node->data[i + 1] = node->data[i];
                i-=1;
            }
            node->keys[i + 1] = key;
            node->data[i + 1] = car;
            node->nkeys += 1;
        } else {
            while (i >= 0 && key < node->keys[i])
                i-=1;
            i+=1;

            if (node->children[i] != nullptr && node->children[i]->nkeys == 31) {
                splitChild(node, i, node->children[i]);
                if (key > node->keys[i])
                    i+=1;
            }


            insnotfull(node->children[i], key, car);
        }
    }
    void splitChild(BNode* parent, int index, BNode* child) {
        BNode* newChild = new BNode(child->isLeaf);

        newChild->nkeys = 15;

        for (int j = 0; j < 15; j++) {
            newChild->keys[j] = child->keys[j + 16];
            newChild->data[j] = child->data[j + 16];

            child->data[j + 16] = nullptr;
        }

        if (!child->isLeaf) {
            for (int j = 0; j < 16; j++) {
                newChild->children[j] = child->children[j + 16];
                child->children[j + 16] = nullptr;
            }
        }

        child->nkeys = 15;

        for (int j = parent->nkeys; j >= index + 1; j--) {
            parent->children[j + 1] = parent->children[j];
        }
        parent->children[index + 1] = newChild;

        for (int j = parent->nkeys - 1; j >= index; j--) {
            parent->keys[j + 1] = parent->keys[j];
            parent->data[j + 1] = parent->data[j];
        }

        parent->keys[index] = child->keys[15];
        parent->data[index] = child->data[15];
        child->data[15] = nullptr;
        parent->nkeys += 1;
    }
    Car* searchNode(BNode* node, int key) {
        int l = 0;
        while (l < node->nkeys && key > node->keys[l]) {
            l += 1;
        }

        if (l < node->nkeys && key == node->keys[l]) {
            return node->data[l];
        }

        if (node->isLeaf) {
            return nullptr;
        }

        if (node->children[l] == nullptr) {
            return nullptr;
        }

        return searchNode(node->children[l], key);
    }
    void deleteBTree(BNode* node) {
        if (node == nullptr) {
            return;
        }
        if (node->isLeaf == false) {
            for (int i = 0; i <= node->nkeys; i++) {
                deleteBTree(node->children[i]);
            }
        }
        delete node;
    }
};




#endif //REDBLACKBCARS_BTREE_H
