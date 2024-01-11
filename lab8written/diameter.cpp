#include "diameter.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;
int height(const BinaryTreeNode* tree);
void filler(vector<int> &container,const BinaryTreeNode* tree);

int diameter(const BinaryTreeNode* tree) {
  // TODO
    if(!tree){
        return 0;
    }
    vector<int> container;
    filler(container, tree);
    return *max_element(container.begin(), container.end());
}

int height(const BinaryTreeNode* tree){
    if(!tree){
        return 0;
    }
    
    int left = height(tree->left);
    int right = height(tree->right);
    
    return max(left, right)+1;
}

void filler(vector<int> &container,const BinaryTreeNode* tree){
    if (!tree){
        return;
    }
    int left = height(tree->left);
    int right = height(tree->right);
    container.push_back(left+right);
    filler(container, tree->left);
    filler(container, tree->right);
}
