#include <stdio.h>

const int CAPACITY = 50;
const int BRACKET_SHIFT = 2;
const int BEFORESTART = -1;

Node::Node()
{
    root_l = root_r = right = left = NULL;
    line = NULL;
}

Node::Node(int capacity)
{
    root_r = root_l = right = left = NULL;
    line = new char(capacity);   // возможно ошибка будет здесь
}

Node::Node(char* new_line)
{
    root_r = root_l = right = left = NULL;
    line = new_line;
}

Node::~Node()
{
    if (right)
        delete right;
    if (left)
        delete left;
    delete line;
}

int Node::OK ()
{
    if (!this)
        {
            printf ("ERROR pointer is NULL\n");
            return 0;
        }
}


Node* Node::R_push (T new_line)
{
    assert (OK());

    Node* nd  = new Node();
    right = nd;
    nd->line = new_line;
    nd->root_r = this;
    return nd;
}

Node* Node::L_push (T question)
{
    assert (OK());

    Node* nd = new Node();
    left = nd;
    nd->line = line;
    nd->root_l = this;
    line = question;
    return nd;

}

void Node::L_push_node (Node* nd)
{
    left = nd;
    nd->root_l = this;
}

void Node::R_push_node (Node* nd)
{
    right = nd;
    nd->root_r = this;
}

void Node::PrintToFile (FILE* file)
{
//    assert (OK());

    fprintf (file, "(\n");
    fprintf (file, "%s\n", line);
    if (left)
        left->PrintToFile (file);
    if (right)
        right->PrintToFile (file);
    fprintf (file,")\n");
}

void Node::ScanFromBuf (char** buffer, int* i)
{
    char* buf = *buffer;

    int j = 0;
    while (buf[*i] != '\n')
    {
        line[j] = buf[(*i)];
        (*i)++;
        j++;
    }
    line [j] = '\0';
    (*i)++;
 //   printf ("%s\n", line);

    if (buf[*i] == '(')
    {
        (*i) += BRACKET_SHIFT;
        Node* nd_l = new Node (CAPACITY);
        nd_l->ScanFromBuf (buffer, i);
        L_push_node (nd_l);
        (*i) += BRACKET_SHIFT;
        Node* nd_r = new Node (CAPACITY);
        nd_r->ScanFromBuf (buffer, i);
        R_push_node (nd_r);
    }
    else
    {
        left = right = NULL;
        (*i) += BRACKET_SHIFT;
    }




}

Tree::Tree ()
{
    head = NULL;
}

Tree::Tree(char* question)
{
    head = new Node(question);
}



Tree::Tree (int capacity)
{
    head = new Node (capacity);
}

void Tree::PrintToFile(FILE* file)
{
    head->PrintToFile (file);
}

void Tree::ScanFromFile (FILE* file)
{
    fseek (file, 0, SEEK_END);
    long file_size = ftell (file);
    rewind (file);
    int i = BRACKET_SHIFT;

    char* buffer = (char*) calloc (file_size + 1, sizeof(char));
    fread (buffer, sizeof(char), file_size, file);


    int j = 0;
    if (buffer[0] == '(')
    {

        while (buffer[i] != '\n')
        {
            head->line[j] = buffer[i];
            i++;
            j++;
        }
        head->line [j] = '\0';
        i++;
//        printf ("%s\n", head->line);
    }
    else
        {
            head = NULL;
            return;
        }
    if (buffer[i] == '(')
    {
        i += BRACKET_SHIFT;
        Node* nd_l = new Node (CAPACITY);
        nd_l->ScanFromBuf (&buffer, &i);
        head->L_push_node (nd_l);
        i += BRACKET_SHIFT;
        i += BRACKET_SHIFT;
        Node* nd_r = new Node (CAPACITY);
        nd_r->ScanFromBuf (&buffer, &i);
        head->R_push_node (nd_r);
    }

}

Tree::~Tree()
{
    if (head)
        delete head;
}

int strlen (char *  buf)
{
    if (buf == NULL)
        return 0;

    int Num_symb = 0;

    for (Num_symb=0; buf[Num_symb]!=0 ; Num_symb++);

    return Num_symb;
}
//   Function only for Akinator

Node* Node::AddNewObj ()
{
    Node* nd;
    char* answer = new char(CAPACITY);

    printf ("Даже гении совершают ошибки\nКого вы загадали?\n");

    scanf ("%s", answer);

    int i = strlen(answer);

    while ((answer[i++] = getchar())!='\n');

    answer[i-1] = '\0';

    R_push  (answer);
    char* question = new char (CAPACITY);

    printf ("Чем %s отличается от %s?\n", answer, line);

    i = 0;
    while ((question[i++] = getchar())!='\n');


    question[i-1] = '\0';

    L_push (line);
    line = question;

    return left;
}

void Node::GiveCharacteristic()
{
    Node* cur = this;
    printf ("%s обладает следующими свойствами: ", line);
    while (cur->root_l != 0 || cur->root_r != 0)
    {
        if (cur->root_l != 0)
        {
            printf ("не %s, ", cur->root_l->line);
            cur = cur->root_l;
        }
        if (cur->root_r != 0)
        {
            printf ("%s, ", cur->root_r->line);
            cur = cur->root_r;
        }
    }
    printf ("был загадан вами))\n");
}


void Node::CompareCharacteristicWith  (Node* node2)
{
    GiveCharacteristic ();
    printf ("a ");
    node2->GiveCharacteristic ();
}


void Tree::DotDump ()
{
    FILE* file = fopen ("graph_dump.txt", "w");
    fprintf (file, "digraph G{\n");
    Node* cur= head;
    fprintf (file, "%d [shape = box, style = rounded, color = blue, label = \"%s\"]\n", cur, cur -> line);
    cur->Dumper (file);
    fprintf (file, "}");
    fclose (file);
    system ("C:\\Progtam\\bin\\dot.exe -Tpng C:\\Users\\Snax\\Desktop\\c++\\Дерево\\graph_dump.txt -o C:\\Users\\Snax\\Desktop\\c++\\Дерево\\dump.png");
    system ("del graph_dump.txt");
    system ("dump.png");
}


int Node::Dumper (FILE* file)
{
    if (left)
    {
        fprintf (file, "%d [shape = box, style = rounded, color = blue, label = \"%s\"]\n", left, left -> line);
        fprintf (file, "%d -> %d [color = blue]\n", this, left);
        left->Dumper (file);
    }

    if (right)
    {
        fprintf (file, "%d [shape = box, style = rounded, color = blue, label = \"%s\"]\n", right, right -> line);
        fprintf (file, "%d -> %d [color = blue]\n", this, right);
        right->Dumper (file);
    }

    return 0;
}
