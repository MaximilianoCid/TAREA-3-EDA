#include <iostream>
#include "trees/tree.hpp"
#include <cstring>

int main(int nargs, char** vargs){
        (void)nargs;
        (void)vargs;
        // Construimos un árbol de ejemplo con varios niveles.
        trees::Tree tree;
        tree.establecerRaiz(new trees::TreeNode(10));
        tree.insertar(5,10);
        tree.insertar(6,5);
        tree.insertar(7,10);
        tree.insertar(17,7);
        tree.insertar(71,7);
        tree.insertar(41,7);

        // Recorremos el árbol mostrando la jerarquía.
        tree.recorrer();
        std::cout<<"Mostrar los hijos de 10" << std::endl;
        trees::TreeNode* node = tree.buscar(10);
        if (node != nullptr){
                // Imprimimos todos los hijos directos del nodo raíz.
                node->obtenerHijos()->imprimir();
        }
        return 0;
}
