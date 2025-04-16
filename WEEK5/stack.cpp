#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

struct NODE 
{
    int key;
    NODE* p_next;
};

struct Stack
{
    NODE* top;
};

Stack* initializeStack()
{
    return new Stack{nullptr};
}

void push(Stack *&s, int key)
{
    if (s == nullptr)
    {
        s = initializeStack();
        s->top = new NODE{key, nullptr};
    }
    else if (s->top == nullptr)
    {
        s->top = new NODE{key, nullptr};
    }
    else
    {
        NODE* add = s->top;
        while (add->p_next != nullptr)
        {
            add = add->p_next;
        }
        add->p_next = new NODE{key, nullptr};
    }
}

int pop(Stack *&s)
{
    if (s != nullptr && s->top != nullptr)
    {
        NODE* xoa = s->top;
        if (xoa->p_next == nullptr)
        {
            s->top = nullptr;
        }
        else
        {
            while (xoa->p_next->p_next != nullptr)
            {
                xoa = xoa->p_next;
            }
            NODE* temp = xoa;
            xoa = xoa->p_next;
            temp->p_next = temp->p_next->p_next;
        }
        int value = xoa->key;
        delete xoa;
        return value;
    }
    return -1;
}

int size(Stack *s)
{
    int dem = 0;
    if (s != nullptr)
    {
        NODE* count = s->top;
        while (count != nullptr)
        {
            count = count->p_next;
            ++dem;
        }
    }
    return dem;
}

bool isEmpty(Stack *s)
{
    return s == nullptr || s->top == nullptr;
}

void display(Stack *s, ofstream &os)
{
    if (isEmpty(s)) os << "EMPTY";
    else
    {
        NODE* in = s->top;
        while (in != nullptr)
        {
            os << in->key << ' ';
            in = in->p_next;
        }
    }
    os << endl;
}

int main()
{
    Stack *s = nullptr;
    ifstream is("input.txt");
    ofstream os("output.txt");
    if (!is) 
    {
        cout << "cannot open input file!" << endl;
        return 1;
    }
    if (!os) 
    {
        cout << "cannot open output file!" << endl;
        return 1;
    }
    string line;
    int value;
    while (is >> line)
    {
        if (line == "init") 
        {
            s = initializeStack();
            display(s, os);
        }
        else if (line == "push")
        {
            is >> value;
            push(s, value);
            display(s, os);
        }
        else if (line == "pop") 
        {
            pop(s);
            display(s, os);
        }
        else if (line == "size") 
        {
            os << "stack size: " << size(s) << endl;
        }
        else if (line == "isEmpty") 
        {
            os << "EMPTY: ";
            if (isEmpty(s)) os << "YES" << endl;
            else os << "NO" << endl;
        }
    }
    is.close();
    os.close();
    return 0;
}