#ifndef _TREELIB_FOR_AK_
#define _TREELIB_FOR_AK_
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <locale.h>


typedef char*  T;

class Node
{
public:
    Node* right = NULL;
    Node* left = NULL;
    Node* root_l = NULL;
    Node* root_r = NULL;
    T line = NULL;

    Node* R_push (T new_line);
    Node* L_push (T question);
    void  L_push_node (Node* nd);
    void  R_push_node (Node* nd);
    OK();

    void PrintToFile (FILE* file);
    void ScanFromBuf (char** buffer, int* i);
    Node();
    Node (int capacity);
    Node(char* new_line);
    ~Node ();


    //   Function only for Akinator

    Node* AddNewObj();

    void GiveCharacteristic();
    void CompareCharacteristicWith  (Node* node2);
    int  Dumper (FILE* file);
};

class Tree
{
public:

    Node* head;

    void PrintToFile(FILE* file);
    void ScanFromFile (FILE* file);
    void DotDump ();
    Tree();
    Tree (char* question);
    Tree (int capacity);
    ~Tree();

};



#include "tree_ak.cpp"
#endif // _TREELIB_FOR_AK_
