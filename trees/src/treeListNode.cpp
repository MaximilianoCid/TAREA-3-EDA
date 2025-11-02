#include "trees/treeListNode.hpp"

namespace trees {

TreeListNode::TreeListNode(): data(), ptrNext(nullptr) {
}

TreeListNode::TreeListNode(TreeNode* _data,
                TreeListNode* next) : data(_data), ptrNext(next){
}
void TreeListNode::establecerDato(TreeNode* _data){
        data = _data;
}
void TreeListNode::establecerSiguiente(TreeListNode* _next){
        ptrNext = _next;
}
TreeNode* TreeListNode::obtenerDato(){
        return data;
}
TreeListNode* TreeListNode::obtenerSiguiente(){
        return ptrNext;
}

TreeListNode::~TreeListNode() {
        delete data;
}

} /* namespace trees */
