#include "common.h"

typedef struct Node {
    int *base;
    int front;
    int rear;
} SequentialQueue;

#define MAXSIZE 100

/**
 * 预设：
 * 使用循环队列实现
 * 且如果尾指针在循环意义上加一等于头指针就认定队满
 */

void Init(SequentialQueue &q) {
    q.base = new int[MAXSIZE];
    q.front = q.rear = 0;
}

int Len(SequentialQueue q) {
    return (q.rear - q.front + MAXSIZE) % MAXSIZE; // 固定算法，+MAXSIZE是为了避免相减出现负数
}

Status Enqueue(SequentialQueue &q, int e) {
    if ((q.rear + 1) % MAXSIZE == q.front) return 0; // 队满
    q.base[q.rear] = e; // 队尾元素
    q.rear = (q.rear + 1) % MAXSIZE; // 循环队列：当 q.rear+1 恰好为 MAXSIZE 时，取余回到0（第一个位置）
    return 1;
}

Status Dequeue(SequentialQueue &q, int &e) {
    if (q.front == q.rear) return 0;
    e = q.base[q.front]; // 队头元素
    q.front = (q.front + 1) % MAXSIZE;
    return 1;
}

// 获取队头元素
int GetHead(SequentialQueue q) {
    if (q.front != q.rear) { // 队非空
        return q.base[q.front];
    }
}