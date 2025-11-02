#include "trees/tree.hpp"
#include <iostream>

namespace trees {

Tree::Tree(): root(nullptr) {

}

void Tree::establecerRaiz(TreeNode* node){
        if (root == nullptr){
                root = node;
        }
}
void Tree::insertar(TreeNode* child, TreeNode* parent){
        if (parent != nullptr && child != nullptr){
                child->establecerPadre(parent);
                parent->obtenerHijos()->insertarPrimero(child);
        }
}

void Tree::insertar(int val, int val_parent){
        TreeNode* parent = buscar(val_parent);
        if (parent != nullptr){
                TreeNode* child = new TreeNode(val);
                insertar(child, parent);
                std::cout << "insertado " << val << " in " << val_parent << " at " << parent << std::endl;
        }
}

TreeNode* Tree::buscarRecursivo(int val, TreeNode* node){
        TreeNode* ans = nullptr;
        if (node != nullptr){
                if (node->obtenerDato() == val){
                        ans = node;
                }
                else{ // search in children
                        TreeList* childrenList = node->obtenerHijos();
                        TreeListNode* ptr = childrenList->obtenerCabeza();
                        while (ptr!=nullptr && ans == nullptr){
                                ans = buscarRecursivo(val, ptr->obtenerDato());
                                ptr = ptr->obtenerSiguiente();
                        }
                }
        }
        return ans;
}

TreeNode* Tree::buscar(int val){
        TreeNode* ans = buscarRecursivo(val, root);
        return ans;
}


void Tree::recorrerRecursivo(TreeNode* node, int level){
        if (node != nullptr){
                std::cout << std::string(level*2, '-');
                std::cout<<node->obtenerDato() << " at level " << level <<std::endl;
                TreeList* childrenList = node->obtenerHijos();
                TreeListNode* ptr = childrenList->obtenerCabeza();
                while (ptr!=nullptr){
                        recorrerRecursivo(ptr->obtenerDato(), level + 1);
                        ptr = ptr->obtenerSiguiente();
                }
        }
}

void Tree::recorrer(){
        recorrerRecursivo(root, 1);
}

Tree::~Tree() {
        delete root;
}

} /* namespace trees */
