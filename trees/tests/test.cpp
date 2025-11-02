#include <iostream>
#include "trees/tree.hpp"
#include <cstring>

int main(int nargs, char** vargs){
        (void)nargs;
        (void)vargs;
        trees::Tree tree;
        tree.establecerRaiz(new trees::TreeNode(10));
        tree.insertar(5,10);
        tree.insertar(6,5);
        tree.insertar(7,10);
        tree.insertar(17,7);
        tree.insertar(71,7);
        tree.insertar(41,7);
        tree.recorrer();
        std::cout<<"Mostrar los hijos de 10" << std::endl;
        trees::TreeNode* node = tree.buscar(10);
        if (node != nullptr){
                node->obtenerHijos()->imprimir();
        }
        return 0;
}
