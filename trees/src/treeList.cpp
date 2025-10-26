/*
 * childrenList.cpp
 *
 *  Created on: Aug 31, 2022
 *      Author: jsaavedr
 */

#include "trees/treeList.hpp"
#include <iostream>
namespace trees {

TreeList::TreeList(): head(nullptr) {
        // La lista comienza vacía.
}

void TreeList::insertFirst(TreeNode* treeNode){
        // Inserta un nuevo TreeListNode al inicio.
        TreeListNode* node = new TreeListNode(treeNode);
        if (head == nullptr) {
                head = node;
        }
        else{
                node->setNext(head);
                head = node;
        }
}

TreeListNode* TreeList::getHead(){
        return head;
}

void TreeList::removeFirst(){
        // Elimina el primer elemento (si existe) y libera su memoria.
        TreeListNode* ptr = head;
        if (head != nullptr){
                head = head->getNext();
                delete ptr;
        }
}


void TreeList::remove(int val){
        // Recorre la lista y elimina todos los nodos cuyo valor coincida.
        TreeListNode* ptr = head;
        TreeListNode* ptr_prev = nullptr;
        while (ptr != nullptr){
                if ((ptr->getData())->getData() == val){
                        // Se elimina el nodo que contiene el valor buscado.
                        if (ptr_prev == nullptr) {
                                head = ptr->getNext();
                                delete ptr;
                                ptr = head;
                        }
                        else{
                                ptr_prev->setNext(ptr->getNext());
                                delete ptr;
                                ptr = ptr_prev->getNext();
                        }
                }
                else{
                        ptr_prev = ptr;
                        ptr = ptr->getNext();
                }
        }
}

void TreeList::removeAll(){
        // Elimina todos los elementos de la lista uno por uno.
        while (head != nullptr){
                removeFirst();
        }
}

TreeNode* TreeList::find(int val){
        // Busca secuencialmente un TreeNode por su dato.
        TreeListNode* ptr = head;
        while ((ptr != nullptr) && ((ptr->getData())->getData() != val)){
                ptr = ptr->getNext();
        }
        if (ptr == nullptr){
                return nullptr;
        }
        return ptr->getData();
}

bool TreeList::isEmpty(){
        return (head == nullptr);
}

void TreeList::print(){
        // Imprime todos los valores almacenados en la lista.
        TreeListNode* ptr = head;
        while (ptr != nullptr){
                std::cout << ptr->getData()->getData() << " - " <<std::endl;
                ptr = ptr->getNext();
        }
}

TreeList::~TreeList() {
        // El destructor elimina cada nodo de la lista para evitar fugas.
        removeAll();
}

} /* namespace trees */

