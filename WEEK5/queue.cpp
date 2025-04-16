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

struct Queue
{
    NODE* head;
    NODE* tail;
};

Queue* initializeQueue()
{
    return new Queue{nullptr, nullptr};
}

void enqueue(Queue *&q, int key)
{
    if (q == nullptr)
    {
        q = initializeQueue();
        q->head = q->tail = new NODE{key, nullptr};
    }
    else if (q->head == nullptr)
    {
        q->head = q->tail = new NODE{key, nullptr};
    }
    else
    {
        q->tail->p_next = new NODE{key, nullptr};
        q->tail = q->tail->p_next;
    }
}

int dequeue(Queue *&q)
{
    if (q != nullptr && q->head != nullptr)
    {
        int value = q->head->key;
        NODE* xoa = q->head;
        if (xoa->p_next == nullptr)
        {
            q->head = q->tail = nullptr;
        }
        else
        {
            q->head = q->head->p_next;
        }
        delete xoa;
        return value;
    }
    return -1;
}

int size(Queue *q)
{
    int dem = 0;
    if (q != nullptr)
    {
        NODE* count = q->head;
        while (count != nullptr)
        {
            count = count->p_next;
            ++dem;
        }
    }
    return dem;
}

bool isEmpty(Queue *q)
{
    return q == nullptr || q->head == nullptr;
}

void display(Queue *q, ofstream &os)
{
    if (isEmpty(q)) os << "EMPTY";
    else
    {
        NODE* in = q->head;
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
    Queue *q = nullptr;
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
            q = initializeQueue();
            display(q, os);
        }
        else if (line == "enqueue")
        {
            is >> value;
            enqueue(q, value);
            display(q, os);
        }
        else if (line == "dequeue") 
        {
            dequeue(q);
            display(q, os);
        }
        else if (line == "size") 
        {
            os << "Queue size: " << size(q) << endl;
        }
        else if (line == "isEmpty") 
        {
            os << "EMPTY: ";
            if (isEmpty(q)) os << "YES" << endl;
            else os << "NO" << endl;
        }
    }
    is.close();
    os.close();
    return 0;
}