#ifndef TREE_HPP_
#define TREE_HPP_

#include "trees/treeNode.hpp"


namespace trees {

class Tree {
private:
        //puntero a la raíz
        TreeNode* root;

public:
        //constructor
        Tree();
        //asigna la raíz del árbol
        void establecerRaiz(TreeNode* node);
        //inserta un nodo hijo
        void insertar(TreeNode* node, TreeNode* parent);
        //crea un nodo hijo con el valor y lo inserta
        void insertar(int child, int parent);
        //busca un nodo recursivamente
        TreeNode* buscarRecursivo(int val, TreeNode* node);
        //busca un nodo
        TreeNode* buscar(int val);
        //recorre y hace print el arbol recursivamente
        void recorrerRecursivo(TreeNode* node, int level);
        //recorre y hace print el arbol recursivamente
        void recorrer();
        virtual ~Tree();
};

} /* namespace trees */

#endif /* TREE_HPP_ */
