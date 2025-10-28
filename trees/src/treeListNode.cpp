/*
 * childNode.cpp
 *
 *  Created on: Aug 30, 2022
 *      Author: jsaavedr
 */

#include "trees/treeListNode.hpp"

namespace trees {

TreeListNode::TreeListNode(): data(), ptrNext(nullptr) {
        // Inicializa el nodo de lista sin dato ni enlace.
}

TreeListNode::TreeListNode(TreeNode* _data,
                TreeListNode* next) : data(_data), ptrNext(next){
        // Constructor que permite dejar preconfigurados dato y siguiente.
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
        // Al liberar el nodo, también se libera el TreeNode que contiene.
        delete data;
}

} /* namespace trees */
