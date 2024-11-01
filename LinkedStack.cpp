#include "common.h"

using namespace std;

typedef struct Node {
    int e;
    Node *next;
} LinkedStack;

// st为栈顶指针，它指向栈顶的元素（与顺序存储有些许不同）
Status Push(LinkedStack *&st, int e) {
    Node *node = new Node;
    // 类似于前插法
    node->e = e;
    node->next = st;
    st = node;
    return 1;
}

Status Pop(LinkedStack *&st, int &e) {
    if (st == nullptr) return 0;
    e = st->e;
    Node *toDelete = st;
    st = st->next;
    delete toDelete;
    return 1;
}

Status GetTop(LinkedStack *st, int &e) {
    if (st == nullptr) return 0;
    e = st->e;
    return 1;
}

int main() {
    LinkedStack *newStack = new LinkedStack;

    for (int i = 1; i <= 10; i++) {
        cout << "push " << i << endl;
        Push(newStack, i);
    }

    for (int i = 1; i <= 10; i++) {
        int e;
        Status status = GetTop(newStack, e);
        if (status) {
            cout << "get top TRUE, e=" << e << endl;
        } else {
            cout << "get top FALSE";
        }
        status = Pop(newStack, e);
        if (status) {
            cout << "pop TRUE, e=" << e << endl;
        } else {
            cout << "pop FALSE" << endl;
        }
    }

    delete newStack;

    return 0;
}