/*
 * tree.cpp
 *
 *  Created on: Aug 31, 2022
 *      Author: jsaavedr
 */

#include "trees/tree.hpp"
#include <iostream>

namespace trees {

Tree::Tree(): root(nullptr) {
        // El árbol parte vacío; la raíz se inicializa en nullptr.
}

void Tree::setRoot(TreeNode* node){
        // Solo permitimos fijar la raíz una vez para evitar pérdidas de memoria.
        if (root == nullptr){
                root = node;
        }
}
void Tree::insert(TreeNode* child, TreeNode* parent){
        // Inserta el nodo hijo bajo el padre siempre que ambos existan.
        if (parent != nullptr && child != nullptr){
                child->setParent(parent);
                parent->getChildren()->insertFirst(child);
        }
}

void Tree::insert(int val, int val_parent){
        // Se busca el nodo padre y, de encontrarse, se crea el nuevo hijo.
        TreeNode* parent = find(val_parent);
        if (parent != nullptr){
                TreeNode* child = new TreeNode(val);
                insert(child, parent);
                std::cout << "insertado " << val << " in " << val_parent << " at " << parent << std::endl;
        }
}

TreeNode* Tree::find_rec(int val, TreeNode* node){
        TreeNode* ans = nullptr;
        if (node != nullptr){
                if (node->getData() == val){
                        ans = node;
                }
                else{ // search in children
                        // Explora recursivamente cada hijo hasta encontrar el valor.
                        TreeList* childrenList = node->getChildren();
                        TreeListNode* ptr = childrenList->getHead();
                        while (ptr!=nullptr && ans == nullptr){
                                ans = find_rec(val, ptr->getData());
                                ptr = ptr->getNext();
                        }
                }
        }
        return ans;
}

TreeNode* Tree::find(int val){
        // Punto de entrada para la búsqueda desde la raíz.
        TreeNode* ans = find_rec(val, root);
        return ans;
}


void Tree::traverse_rec(TreeNode* node, int level){
        if (node != nullptr){
                // Se imprime el valor con una sangría proporcional al nivel.
                std::cout << std::string(level*2, '-');
                std::cout<<node->getData() << " at level " << level <<std::endl;
                TreeList* childrenList = node->getChildren();
                TreeListNode* ptr = childrenList->getHead();
                while (ptr!=nullptr){
                        traverse_rec(ptr->getData(), level + 1);
                        ptr = ptr->getNext();
                }
        }
}

void Tree::traverse(){
        // Inicia un recorrido en profundidad a partir de la raíz.
        traverse_rec(root, 1);
}

Tree::~Tree() {
        // Al eliminar el árbol se libera la raíz, lo que recursivamente borra todo.
        delete root;
}

} /* namespace trees */
