#include <cstdio>
#include <iostream>

using namespace std;

#define RED 1
#define BLACK 2

struct Node {
    int color;
    int value;
    Node *parent;
    Node *left, *right;

    Node(int v)
    {
        color = RED;
        value = v;
        parent = left = right = NULL;
    }
};

class RBTree
{
    public:
    Node *root;

    RBTree()
    {
        root = NULL;
    }
    void left_rotate(Node *);
    void right_rotate(Node *);
    void insert(int);
    void insert_fixup(Node *);
    void transplant(Node *, Node *);
    void delete_node(Node *);
    void del(int);
    void delete_fixup(Node *);
    Node *search(int);
    Node *tree_min(Node *);
    void display(Node *);
};

void RBTree::right_rotate(Node *x)
{
    if (x->left == NULL)
        return;

    Node *y = x->left;
    x->left = y->right;
    if (y->right != NULL)
        y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        root = y;
    else if(x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->right = x;
    x->parent = y;
}

void RBTree::left_rotate(Node *x)
{
    if (x->right == NULL)
        return;

    Node *y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        root = y;
    else if(x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void RBTree::insert(int value)
{
    Node *z = new Node(value);

    Node *y = NULL;
    Node *x = root;
    while (x != NULL)
    {
        y = x;
        if (z->value < x->value)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == NULL)
        root = z;
    else if (z->value < y->value)
        y->left = z;
    else
        y->right = z;
    insert_fixup(z);
}

void RBTree::insert_fixup(Node *z)
{
    while (z != NULL && z->parent != NULL && z->parent->color == RED) {
        Node *zpp = z->parent->parent;
        if(zpp != NULL && zpp->left == z->parent) {
            Node *y = zpp->right;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                zpp->color = RED;
                z = zpp;
            }
            else {
                if (z == z->parent->right) {
                    z = z->parent;
                    left_rotate(z);
                }
                z->parent->color = BLACK;
                zpp->color = RED;
                right_rotate(zpp);
            }
        }
        else {
            Node *y = zpp->left;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                zpp->color = RED;
                z = zpp;
            }
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    right_rotate(z);
                }
                z->parent->color = BLACK;
                zpp->color = RED;
                left_rotate(zpp);
            }
        }
    }
    root->color = BLACK;
}

void RBTree::transplant(Node *u, Node *v)
{
    if (u->parent == NULL)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (u != NULL && v != NULL)
        v->parent = u->parent;
}

Node *RBTree::tree_min(Node *x)
{
    while (x->left != NULL)
        x = x->left;
    return x;
}

void RBTree::delete_node(Node *z)
{
    Node *y = z;
    int original_color = y->color;
    Node *x;
    if (z->left == NULL) {
        x = z->right;
        transplant(z, z->right);
    }
    else if (z->right == NULL) {
        x = z->left;
        transplant(z, z->left);
    }
    else {
        y = tree_min(z->right);
        original_color = y->color;
        x = y->right;
        if (y->parent == z)
            x->parent = y;
        else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (original_color == BLACK)
        delete_fixup(x);
}

void RBTree::del(int value)
{
    Node *z = search(value);
    delete_node(z);
}

Node *RBTree::search(int value)
{
    Node *x = root;
    while (x != NULL && x->value != value) {
        if (value < x->value)
            x = x->left;
        else
            x = x->right;
    }
    return x;
}

void RBTree::delete_fixup(Node *x)
{
    Node *w;
    if (x == NULL)
        return;
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                left_rotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;

            }
            else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    right_rotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                left_rotate(x->parent);
                x = root;
            }
        }
        else {
            w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                right_rotate(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;

            }
            else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    left_rotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                right_rotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

void RBTree::display(Node *x)
{
    if (x == NULL)
        return;
    display(x->left);
    printf("%d ", x->value);
    display(x->right);
}

int main()
{
    RBTree t;
    t.insert(50);
    t.insert(40);
    t.insert(30);
    t.insert(45);
    t.insert(46);
    t.display(t.root);
    t.del(45);
    printf("\n");
    t.display(t.root);
    t.del(30);
    printf("\n");
    t.display(t.root);
    t.del(40);
    printf("\n");
    t.display(t.root);
    t.del(50);
    printf("\n");
    t.display(t.root);
    t.del(46);
    printf("\n");
    t.display(t.root);
    t.insert(40);
    printf("\n");
    t.display(t.root);
    t.insert(30);
    printf("\n");
    t.display(t.root);
    t.insert(86);
    t.insert(87);
    t.insert(88);
    printf("\n");
    t.display(t.root);


    return 0;
}
