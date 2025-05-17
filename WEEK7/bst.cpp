#include <iostream>
#include <cmath>
#include <climits>
#include <string>

using namespace std;

struct NODE
{
    int key;
    NODE* p_left;
    NODE* p_right;
};

//khai bao ham bo tro
int max(int a, int b);
bool isBST(NODE* node, int min, int max);
bool isFull(NODE* node);
bool khongCon(NODE* node);
bool motCon(NODE* node);
void smallRemove(NODE* &deletion, int &value);

//khai bao ham chinh
NODE* Search(NODE* pRoot, int x);
void Insert(NODE* &pRoot, int x);
void Remove(NODE* &pRoot, int x);
NODE* createTree(int a[], int n);
void removeTree(NODE* &pRoot);
int Height(NODE* pRoot);
int countLess(NODE* pRoot, int x);
int countGreater(NODE* pRoot, int x);
bool isBST(NODE* pRoot);
bool isFullBST(NODE* pRoot);

//ham bo tro
int max(int a, int b)
{
    return a > b ? a : b;
}

bool khongCon(NODE* node) 
{
    return !node->p_left && !node->p_right;
}

bool motCon(NODE* node)
{
    return (!node->p_left && node->p_right) || (node->p_left && !node->p_right);
}

bool isBST(NODE* node, int min, int max)
{
    if (!node) return true;
    if (node->key <= min || node->key >= max) return false;
    return isBST(node->p_left, min, node->key) && isBST(node->p_right, node->key, max);
}

bool isFull(NODE* node)
{
    if (!node) return true;
    if (motCon(node)) return false;
    return isFull(node->p_left) && isFull(node->p_right);
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
}

//ham chinh
NODE* Search(NODE* pRoot, int x)
{
    if (!pRoot) return nullptr;
    if (pRoot->key == x) return pRoot;
    else if (x < pRoot->key) return Search(pRoot->p_left, x);
    else return Search(pRoot->p_right, x);
}

void Insert(NODE* &pRoot, int x)
{
    if (!pRoot)
    {
        pRoot = new NODE{x, nullptr, nullptr};
        return;
    }
    NODE* temp = pRoot;
    while (temp)
    {
        if (x < temp->key)
        {
            if (!temp->p_left)
            {
                temp->p_left = new NODE{x, nullptr, nullptr};
                return;
            }
            temp = temp->p_left;
        }
        else if (x > temp->key)
        {
            if (!temp->p_right)
            {
                temp->p_right = new NODE{x, nullptr, nullptr};
                return;
            }
            temp = temp->p_right;
        }
        else return;
    }
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
}

NODE* createTree(int a[], int n)
{
    NODE* result = nullptr;
    for (int i = 0; i < n; ++i)
    {
        Insert(result, a[i]);
    }
    return result;
}

void removeTree(NODE* &pRoot)
{
    if (!pRoot) return;
    NODE* deletion = pRoot;
    removeTree(pRoot->p_left);
    removeTree(pRoot->p_right);
    delete deletion;
    pRoot = deletion = nullptr;
}

int Height(NODE* pRoot)
{
    if (!pRoot) return -1;
    return max(Height(pRoot->p_left), Height(pRoot->p_right)) + 1;
}

int countLess(NODE* pRoot, int x)
{
    if (!pRoot) return 0;
    if (pRoot->key < x) return countLess(pRoot->p_left, x) + countLess(pRoot->p_right, x) + 1;
    return countLess(pRoot->p_left, x) + countLess(pRoot->p_right, x);
}

int countGreater(NODE* pRoot, int x)
{
    if (!pRoot) return 0;
    if (pRoot->key > x) return countGreater(pRoot->p_left, x) + countGreater(pRoot->p_right, x) + 1;
    return countGreater(pRoot->p_left, x) + countGreater(pRoot->p_right, x);
}

bool isBST(NODE* pRoot)
{
    return isBST(pRoot, INT_MIN, INT_MAX);
}

bool isFullBST(NODE* pRoot)
{
    return isFull(pRoot) && isBST(pRoot);
}