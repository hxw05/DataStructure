#include "common.h"

typedef struct QNode {
    int data;
    QNode *next;
} QNode;

typedef struct {
    QNode *front;
    QNode *rear;
} LinkedQueue;

void Init(LinkedQueue &q) {
    q.front = q.rear = new QNode; // 注：此时q.front和q.rear指向的是同一个node
    q.front->next = nullptr;
}

void Enqueue(LinkedQueue &q, int e) {
    QNode *node = new QNode;
    node->data = e;
    node->next = nullptr;
    q.rear->next = node;
    q.rear = node;
}

Status Dequeue(LinkedQueue &q, int &e) {
    if (q.front == q.rear) return 0;
    QNode *p = q.front->next; // 获取队头元素（头指针next）
    e = p->data;
    q.front->next = p->next; // 头指针next指向下一个元素

    // 如果p也是队尾的元素，那么上面的语句将p.front.next设为了nullptr，q.rear仍然指向即将要被释放的p
    // 需要将其设置和q.front相同
    if (q.rear == p) {
        q.rear = q.front;
    }
    delete p; // 释放原队头元素

    return 1;
}

Status GetFront(LinkedQueue q, int &e) {
    if (q.front == q.rear) return 0;
    e = q.front->next->data;
}