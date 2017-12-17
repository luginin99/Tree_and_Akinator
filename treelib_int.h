#ifndef _TREELIB_H_
#define _TREELIB_H_
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef int  T;

class Node
{
public:
    Node* right = NULL;
    Node* left = NULL;
    Node* root_l = NULL;
    Node* root_r = NULL;

    T value;
    Node* R_push (T val);
    Node* L_push (T val);
    Node* Sort_push (T val);
    OK();
    void PrintInfix ();
    void PrintInfixToFile (FILE* file);
    void PrintPostfix ();
    void DeleteSubTree();

    Node();
    Node (T val);
    ~Node ();
};

class Tree
{
public:

    Node* head;

    void PrintTreeInfix();
    void PrintTreeInfixToFile(FILE* file);
    Tree (T val);
    ~Tree();

};

#include "tree_int.cpp"
#endif // TREELIB_H_
