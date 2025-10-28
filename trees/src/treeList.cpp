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

void TreeList::insertarPrimero(TreeNode* treeNode){
        // Inserta un nuevo TreeListNode al inicio.
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
        // Elimina el primer elemento (si existe) y libera su memoria.
        TreeListNode* ptr = head;
        if (head != nullptr){
                head = head->obtenerSiguiente();
                delete ptr;
        }
}


void TreeList::eliminar(int val){
        // Recorre la lista y elimina todos los nodos cuyo valor coincida.
        TreeListNode* ptr = head;
        TreeListNode* ptr_prev = nullptr;
        while (ptr != nullptr){
                if ((ptr->obtenerDato())->obtenerDato() == val){
                        // Se elimina el nodo que contiene el valor buscado.
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
        // Elimina todos los elementos de la lista uno por uno.
        while (head != nullptr){
                eliminarPrimero();
        }
}

TreeNode* TreeList::buscar(int val){
        // Busca secuencialmente un TreeNode por su dato.
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
        // Imprime todos los valores almacenados en la lista.
        TreeListNode* ptr = head;
        while (ptr != nullptr){
                std::cout << ptr->obtenerDato()->obtenerDato() << " - " <<std::endl;
                ptr = ptr->obtenerSiguiente();
        }
}

TreeList::~TreeList() {
        // El destructor elimina cada nodo de la lista para evitar fugas.
        eliminarTodos();
}

} /* namespace trees */

