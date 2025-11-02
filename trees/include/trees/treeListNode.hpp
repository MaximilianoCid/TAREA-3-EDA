#ifndef CHILDNODE_HPP_
#define CHILDNODE_HPP_

#include "trees/treeNode.hpp"

namespace trees {
class TreeNode;
class TreeListNode {
private:
        //valor del nodo
        TreeNode* data;
        //puntero al siguiente nodo
        TreeListNode* ptrNext;

public:
        TreeListNode();
        TreeListNode(TreeNode* _data, TreeListNode* next = nullptr);
        //cambia el valor del nodo
        void establecerDato(TreeNode* _data);
        //cambia el puntero al siguiente nodo
        void establecerSiguiente(TreeListNode* _next);
        //entreda el valor del nodo
        TreeNode* obtenerDato();
        //entrega el puntero al siguiente nodo
        TreeListNode* obtenerSiguiente();
        virtual ~TreeListNode();
};

} /* namespace trees */

#endif /* CHILDNODE_HPP_ */
