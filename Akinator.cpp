#include "treelib_for_ak.h"
#include <stdio.h>
#include <locale>
#include <stdlib.h>


int main()
{
    Tree* Akin = new Tree(CAPACITY);
    FILE* database = fopen ("database.txt", "r");

    setlocale (LC_CTYPE, "Russian");


    Akin->ScanFromFile(database);


    fclose (database);

    int answer = 1;
    Node* last_guessed = 0;

    while (answer)
    {
        Node* cur_obj = Akin->head;

        while (cur_obj->right != NULL)
        {
            printf ("To�, ���� �� ��������, %s?  (1 - ��, 0 - ���)\n", cur_obj->line);
            scanf ("%d", &answer);

            if (answer)
                cur_obj = cur_obj ->right;
            else
                cur_obj = cur_obj ->left;
        }

        printf ("��� �������, �� �������� - %s, � ����? (1 - ��, 0 - ���)\n", cur_obj->line);
        scanf ("%d", &answer);

        if (answer)
        {
            printf ("� � �� ����������\n");
            cur_obj->GiveCharacteristic();
            if (last_guessed != NULL)
            {
                printf ("���������� ��� ������ ������ ���������� �� ���������� ����������? (1 - ��, 0 - ���)\n");
                scanf ("%d", &answer);
                if (answer)
                {
                    if (last_guessed != cur_obj )
                        cur_obj->CompareCharacteristicWith (last_guessed);
                    else
                        printf ("������� ��� �� �������� ��� �� ������\n");
                }
            }
            last_guessed = cur_obj;
        }
        else
            last_guessed = cur_obj->AddNewObj();
        printf ("������ ������ ��� ���? (1-��, 0 - ���)\n");
        scanf ("%d", &answer);
    }

    database = fopen ("database.txt", "w");

    Akin->PrintToFile(database);

    Akin->DotDump();

    return 0;
}
