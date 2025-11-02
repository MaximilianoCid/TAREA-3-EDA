#include "trees/treeNode.hpp"

namespace trees {

TreeNode::TreeNode(): parent(nullptr), data(-1), children(new TreeList()) {
}

TreeNode::TreeNode(int val): parent(nullptr), data(val), children(new TreeList()) {
}

void TreeNode::establecerPadre(TreeNode* node){
        parent = node;
}
void TreeNode::establecerDato(int val){
        data = val;
}
void TreeNode::establecerHijos(TreeList* list){
        children = list;
}
TreeNode* TreeNode::obtenerPadre(){
        return parent;
}
int TreeNode::obtenerDato(){
        return data;
}
TreeList* TreeNode::obtenerHijos(){
        return children;
}

TreeNode::~TreeNode() {
        if (children != nullptr){
                delete children;
        }
}

} /* namespace trees */
