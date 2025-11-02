#ifndef TREENODE_HPP_
#define TREENODE_HPP_

#include "trees/treeList.hpp"

namespace trees {

class TreeList;
class TreeNode {
private:
        //nodo padre
        TreeNode* parent;
        //valor nodo
        int data; // data can be of any type
        //lista de hijos
        TreeList* children;

public:
        TreeNode();
        explicit TreeNode(int val);
        //cambia el valor del nodo padre
        void establecerPadre(TreeNode* node);
        //cambia el valor del nodo
        void establecerDato(int val);
        //cambia la lista de hijos
        void establecerHijos(TreeList* list);
        //entrega el nodo padre
        TreeNode* obtenerPadre();
        //entrega el valor del nodo
        int obtenerDato();
        //entrega la lista de hijos
        TreeList* obtenerHijos();
        virtual ~TreeNode();
};

} /* namespace trees */

#endif /* TREENODE_HPP_ */
