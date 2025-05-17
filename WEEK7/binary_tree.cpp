#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct NODE
{
    int key;
    NODE* p_left;
    NODE* p_right;
};

//khai bao ham
NODE* createNode(int data);
vector <int> NLR(NODE* pRoot);
vector <int> LNR(NODE* pRoot);
vector <int> LRN(NODE* pRoot);
vector <vector <int>> LevelOrder(NODE* pRoot);
int countNode(NODE* pRoot);
int sumNode(NODE* pRoot);
int Level(NODE* pRoot, NODE* p);
int treeHeight(NODE* pRoot);
int heightNode(NODE* pRoot, int value);
int countLeaf(NODE* pRoot);
int max(int a, int b);

//ham bo tro
int max(int a, int b)
{
    return (a < b) ? b : a;
}

int treeHeight(NODE* pRoot)
{
    if (!pRoot) return -1;
    return max(treeHeight(pRoot->p_left), treeHeight(pRoot->p_right)) + 1;
}

//ham chinh
NODE* createNode(int data)
{
    return new NODE{data, nullptr, nullptr};
}

vector <int> NLR(NODE* pRoot)
{
    vector <int> result_NLR;
    if (!pRoot) return vector <int> {};
    result_NLR.push_back(pRoot->key);
    vector <int> left = NLR(pRoot->p_left);
    result_NLR.insert(result_NLR.end(), left.begin(), left.end());
    vector <int> right = NLR(pRoot->p_right);
    result_NLR.insert(result_NLR.end(), right.begin(), right.end());
    return result_NLR;
}

vector <int> LNR(NODE* pRoot)
{
    vector <int> result_LNR;
    if (!pRoot) return vector <int> {};
    vector <int> left = LNR(pRoot->p_left);
    result_LNR.insert(result_LNR.end(), left.begin(), left.end());
    result_LNR.push_back(pRoot->key);
    vector <int> right = LNR(pRoot->p_right);
    result_LNR.insert(result_LNR.end(), right.begin(), right.end());
    return result_LNR;
}

vector <int> LRN(NODE* pRoot)
{
    vector <int> result_LRN;
    if (!pRoot) return vector <int> {};
    vector <int> left = LRN(pRoot->p_left);
    result_LRN.insert(result_LRN.end(), left.begin(), left.end());
    vector <int> right = LRN(pRoot->p_right);
    result_LRN.insert(result_LRN.end(), right.begin(), right.end());
    result_LRN.push_back(pRoot->key);
    return result_LRN;
}

vector <vector <int>> LevelOrder(NODE* pRoot)
{
    queue <NODE*> node; //luu lan luot cac node theo level tu trai sang phai
    int treeheight = treeHeight(pRoot), count_at_level = 1, count = 0;//bien dem so phan tu o tung level
    vector <vector <int>> result_Level(treeheight + 1); //ket qua
    if (pRoot) node.push(pRoot); //neu cay khong rong
    for (int i = 0; i <= treeheight; ++i) //vong lap level
    {
        //bien dem tong so con cua cac phan tu tai level i
        for (int j = 0; j < count_at_level; ++j) //vong lap so phan tu tai level do
        {
            //them con trai va con phai, dong thoi tang bien dem tong so con tai level i
            if (node.front()->p_left)
            {
                node.push(node.front()->p_left);
                ++count;
            }
            if (node.front()->p_right) 
            {
                node.push(node.front()->p_right);
                ++count;
            }
            result_Level[i].push_back(node.front()->key);//them gia tri cua node vao dung level cua mang
            node.pop();//xoa node o dau
        }
        count_at_level = count;//gan lai bien dem
        count = 0; //reset
    }
    return result_Level;
}

int countNode(NODE* pRoot)
{
    if (!pRoot) return 0;
    return countNode(pRoot->p_left) + countNode(pRoot->p_right) + 1;
}

int sumNode(NODE* pRoot)
{
    if (!pRoot) return 0;
    return sumNode(pRoot->p_left) + sumNode(pRoot->p_right) + pRoot->key;
}

int Level(NODE* pRoot, NODE* p)
{
    int level = 0;
    while (pRoot)
    {
        if (p->key < pRoot->key) 
        {
            pRoot = pRoot->p_left;
            ++level;
        }
        else if (p->key > pRoot->key) 
        {
            pRoot = pRoot->p_right;
            ++level;
        }
        else return level;
    }
    return -1;
}

int heightNode(NODE* pRoot, int value)
{
    int level = 0;
    NODE* saved = pRoot;
    while (pRoot)
    {
        if (value < pRoot->key) 
        {
            pRoot = pRoot->p_left;
            ++level;
        }
        else if (value > pRoot->key) 
        {
            pRoot = pRoot->p_right;
            ++level;
        }
        else return treeHeight(saved) - level;
    }
    return -1;
}

int countLeaf(NODE* pRoot)
{
    if (!pRoot) return 0;
    if (!pRoot->p_left && !pRoot->p_right) return 1;
    return countLeaf(pRoot->p_left) + countLeaf(pRoot->p_right);
}