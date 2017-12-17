#include <stdio.h>

Node::Node()
{
    right = left = NULL;
    value = 0;
}

Node::Node(T val)
{
    right = left = NULL;
    value = val;
}
Node::~Node()
{
    if (right)
        delete right;
    if (left)
        delete left;
}

int Node::OK ()
{
    if (!this)
        {
            printf ("ERROR pointer is NULL\n");
            return 0;
        }
}


Node* Node::R_push (T val)
{
    assert (OK());

    Node* nd  = new Node();
    right = nd;
    nd->value = val;
    nd->root_r = this;
    return nd;
}

Node* Node::L_push (T val)
{
    assert (OK());

    Node* nd = new Node();
    left = nd;
    nd->value = val;
    nd->root_l = this;
    return nd;

}

void Node::DeleteSubTree ()
{
    assert (OK());

    if (left)
        left->DeleteSubTree();
    if (right)
        right->DeleteSubTree();

    if (root_l)
        root_l->left = NULL;
    if (root_r)
        root_r->right = NULL;
}

Node* Node::Sort_push(T val)
{

    if (val >= value)
    {
        if (!right)
            R_push(val);
        else
            right->Sort_push (val);
    }
    if (val < value)
    {
        if (!left)
            L_push(val);
        else
            left->Sort_push (val);
    }
}

void Node::PrintInfix()
{
    assert (OK());

    if (left)
        left->PrintInfix();
    printf ("%d ", value);
    if (right)
        right->PrintInfix();
}

void Node::PrintPostfix()
{
    assert (OK());

    printf ("%d", value);
    if (left)
        left->PrintInfix();
    if (right)
        right->PrintInfix();
}

void Node::PrintInfixToFile (FILE* file)
{
    assert (OK());

    if (left)
        left->PrintInfixToFile(file);
    fprintf (file,"%d ", value);
    if (right)
        right->PrintInfixToFile(file);

}

Tree::Tree(T val)
{
    head = new Node();
    head->value = val;
}


void Tree::PrintTreeInfix()
{

    if (head->left)
        head->left->PrintInfix();
    printf ("%d ", head->value);
    if (head->right)
        head->right->PrintInfix();
}
void Tree::PrintTreeInfixToFile(FILE* file)
{
    if (head->left)
        head->left->PrintInfixToFile(file);
    fprintf (file, "%d ", head->value);
    if (head->right)
        head->right->PrintInfixToFile(file);
}

Tree::~Tree()
{
    if (head)
        delete head;
}




