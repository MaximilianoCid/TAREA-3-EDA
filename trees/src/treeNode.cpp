/*
 * treeNode.cpp
 *
 *  Created on: Aug 30, 2022
 *      Author: jsaavedr
 */

#include "trees/treeNode.hpp"

namespace trees {

TreeNode::TreeNode(): parent(nullptr), data(-1), children(new TreeList()) {
        // Crea un nodo sin valor inicial y con lista de hijos vacía.
}

TreeNode::TreeNode(int val): parent(nullptr), data(val), children(new TreeList()) {
        // Variante que establece el dato almacenado desde el inicio.
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
        // Cuando se elimina un nodo se libera recursivamente su subárbol.
        if (children != nullptr){
                delete children;
        }
}

} /* namespace trees */
