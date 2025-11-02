#include "trees/treeList.hpp"
#include <iostream>
namespace trees {

TreeList::TreeList(): head(nullptr) {
}

void TreeList::insertarPrimero(TreeNode* treeNode){
        TreeListNode* node = new TreeListNode(treeNode);
        if (head == nullptr) {
                head = node;
        }
        else{
                node->establecerSiguiente(head);
                head = node;
        }
}

TreeListNode* TreeList::obtenerCabeza(){
        return head;
}

void TreeList::eliminarPrimero(){
        TreeListNode* ptr = head;
        if (head != nullptr){
                head = head->obtenerSiguiente();
                delete ptr;
        }
}


void TreeList::eliminar(int val){
        TreeListNode* ptr = head;
        TreeListNode* ptr_prev = nullptr;
        while (ptr != nullptr){
                if ((ptr->obtenerDato())->obtenerDato() == val){
                        if (ptr_prev == nullptr) {
                                head = ptr->obtenerSiguiente();
                                delete ptr;
                                ptr = head;
                        }
                        else{
                                ptr_prev->establecerSiguiente(ptr->obtenerSiguiente());
                                delete ptr;
                                ptr = ptr_prev->obtenerSiguiente();
                        }
                }
                else{
                        ptr_prev = ptr;
                        ptr = ptr->obtenerSiguiente();
                }
        }
}

void TreeList::eliminarTodos(){
        while (head != nullptr){
                eliminarPrimero();
        }
}

TreeNode* TreeList::buscar(int val){
        TreeListNode* ptr = head;
        while ((ptr != nullptr) && ((ptr->obtenerDato())->obtenerDato() != val)){
                ptr = ptr->obtenerSiguiente();
        }
        if (ptr == nullptr){
                return nullptr;
        }
        return ptr->obtenerDato();
}

bool TreeList::estaVacia(){
        return (head == nullptr);
}

void TreeList::imprimir(){
        TreeListNode* ptr = head;
        while (ptr != nullptr){
                std::cout << ptr->obtenerDato()->obtenerDato() << " - " <<std::endl;
                ptr = ptr->obtenerSiguiente();
        }
}

TreeList::~TreeList() {
        eliminarTodos();
}

} /* namespace trees */

