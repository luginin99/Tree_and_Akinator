#include <stdio.h>
#include "treelib_int.h"

int main()
{
    FILE* out = fopen ("output.txt", "w");
    Tree derevo (5);
    int arr[] = {3,2,8,7,1,9,4};
    Node* nd;


    for (int i=0; i < 6; i++)
        {
            if (i == 0) nd = derevo.head->Sort_push(arr[i]);
            derevo.head->Sort_push(arr[i+1]);

        }
    nd->DeleteSubTree();
    derevo.PrintTreeInfix();
    derevo.PrintTreeInfixToFile(out);
}
