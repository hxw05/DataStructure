#include "common.h"

typedef struct El {
    struct El* prev;
    struct El* next;
    int data;
} DoubleLinkedList;

El* Get(DoubleLinkedList list, int i) {
    El* p = list.next;
    int j = 1;

    while (j < i) {
        if (p == nullptr) break;
        p = p->next;
        j++;
    }

    return p;
}

Status Insert(DoubleLinkedList &list, int i, int e) {
    El* p;

    if ((p = Get(list, i)) == nullptr) {
        return 0;
    }

    El* newEl = new El{};
    newEl->data = e;

    // 注意，一定是四步
    newEl->prev = p->prev;
    p->prev->next = newEl;
    p->prev = newEl;
    newEl->next = p;

    return 1;
}

Status Delete(DoubleLinkedList &list, int i) {
    El* p;

    if ((p = Get(list, i)) == nullptr) {
        return 0;
    }

    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;

    return 1;
}