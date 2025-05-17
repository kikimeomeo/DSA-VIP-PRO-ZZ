#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

struct NODE
{
    int key;
    NODE* p_left;
    NODE* p_right;
    int height;
};

//khai bao ham bo tro
NODE* rightRotate(NODE* a);
NODE* leftRotate(NODE* a);
bool khongCon(NODE* node);
int Height(NODE* node);
void updateHeight(NODE* node);
void fixTree(NODE* &pRoot);
void smallRemove(NODE* &deletion, int &value);
bool isBST(NODE* node, int min, int max);
bool isBST(NODE* pRoot);
bool diffHeightLessThanTwo(NODE* node);

//khai bao ham chinh
NODE* createNode(int data);
void Insert(NODE* &pRoot, int x);
void Remove(NODE* &pRoot, int x);
bool isAVL(NODE* pRoot);

//ham bo tro
bool khongCon(NODE* node) 
{
    return !node->p_left && !node->p_right;
}

int Height(NODE* node)
{
    return node ? node->height : -1;
}

void updateHeight(NODE* node)
{
    if (node) node->height = 1 + max(Height(node->p_left), Height(node->p_right));
}

NODE* rightRotate(NODE* a)
{
    NODE* x = a->p_left;
    NODE* y = x->p_right;
    a->p_left = y;
    x->p_right = a;
    updateHeight(a);
    updateHeight(x);
    return x;
}

NODE* leftRotate(NODE* a)
{
    NODE* x = a->p_right;
    NODE* y = x->p_left;
    a->p_right = y;
    x->p_left = a;
    updateHeight(a);
    updateHeight(x);
    return x;
}

void fixTree(NODE* &pRoot)
{
    int diff1 = Height(pRoot->p_left) - Height(pRoot->p_right);
    if (diff1 > 1)
    {
        int diff2 =  Height(pRoot->p_left->p_left) - Height(pRoot->p_left->p_right);
        if (diff2 >= 0)
        {
            pRoot = rightRotate(pRoot);
        }
        else
        {
            pRoot->p_left = leftRotate(pRoot->p_left);
            pRoot = rightRotate(pRoot);
        }
    }
    else if (diff1 < -1)
    {
        int diff2 =  Height(pRoot->p_right->p_left) - Height(pRoot->p_right->p_right);
        if (diff2 <= 0)
        {
            pRoot = leftRotate(pRoot);
        }
        else
        {
            pRoot->p_right = rightRotate(pRoot->p_right);
            pRoot = leftRotate(pRoot);
        }
    }
}

void smallRemove(NODE* &deletion, int &value)
{
    if (!deletion->p_right)
    {
        NODE* saved = deletion;
        deletion = deletion->p_left;
        value = saved->key;
        delete saved;
    }
    else smallRemove(deletion->p_right, value);
    updateHeight(deletion);
    if (deletion) fixTree(deletion);
}

bool isBST(NODE* node, int min, int max)
{
    if (!node) return true;
    if (node->key <= min || node->key >= max) return false;
    return isBST(node->p_left, min, node->key) && isBST(node->p_right, node->key, max);
}

bool isBST(NODE* pRoot)
{
    return isBST(pRoot, INT_MIN, INT_MAX);
}

bool diffHeightLessThanTwo(NODE* node)
{
    if (!node) return true;
    if (abs(Height(node->p_left) - Height(node->p_right)) > 1) return false;
    return diffHeightLessThanTwo(node->p_left) && diffHeightLessThanTwo(node->p_right);
}

//ham chinh
NODE* createNode(int data)
{
    return new
     NODE{data, nullptr, nullptr, 0};
}

void Insert(NODE* &pRoot, int x)
{
    if (!pRoot) 
    {
        pRoot = createNode(x);
        return;
    }
    if (pRoot->key == x) return;
    else if (x < pRoot->key) Insert(pRoot->p_left, x);
    else Insert(pRoot->p_right, x);
    updateHeight(pRoot);
    fixTree(pRoot);
}

void Remove(NODE* &pRoot, int x)
{
    if (!pRoot) return;
    if (pRoot->key == x)
    {
        NODE* deletion = pRoot;
        if (khongCon(pRoot)) 
        {
            pRoot = nullptr;
            delete deletion;
        }
        else if (!pRoot->p_left && pRoot->p_right) 
        {
            pRoot = pRoot->p_right;
            delete deletion;
        }
        else if (pRoot->p_left && !pRoot->p_right)
        {
            pRoot = pRoot->p_left;
            delete deletion;
        } 
        else
        {
            int value;
            smallRemove(pRoot->p_left, value);
            pRoot->key = value;
        }
    }
    else if (x < pRoot->key) Remove(pRoot->p_left, x);
    else Remove(pRoot->p_right, x);
    updateHeight(pRoot);
    if (pRoot) fixTree(pRoot);
}

bool isAVL(NODE* pRoot)
{
    return isBST(pRoot) && diffHeightLessThanTwo(pRoot);
}