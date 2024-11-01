#include "common.h"
#pragma clang diagnostic push
#pragma ide diagnostic ignored "MemoryLeak"
using namespace std;

typedef struct PNode {
    int coef; // 系数
    int expn; // 指数
    struct PNode *next;
} Polynomial;

void Create(Polynomial *head, int n) {
    head = new Polynomial;
    head->next = nullptr;

    PNode *newNode;
    PNode *targetPre;
    PNode *target;

    for (int i = 0; i < n; i++) {
        // 输入新节点的值
        newNode = new PNode;
        cin >> newNode->coef >> newNode->expn;

        // 查找，直到以下情况之一
        // - q的指数不小于s的指数，pre指向q的前一个
        // - q为nullptr，pre是表的最后一个元素
        targetPre = head;
        target = head->next;
        while (target && target->expn < newNode->expn) {
            targetPre = target;
            target = target->next;
        }

        // 将s插入到pre和q之间
        newNode->next = target;
        targetPre->next = newNode;
    }
}

void Add(Polynomial &a, Polynomial &b) {
    PNode *p1 = a.next, *p2 = b.next, *result = &a;
    while (p1 && p2) {
        if (p1->expn == p2->expn) {
            // 两项指数相等，系数相加
            int sum = p1->coef + p2->coef;
            if (sum) {
                // 相加的结果不为0，就用p1为载体，将其系数修改为相加的结果，指数不变
                // 然后将p1推入result中，准备进行下一步操作
                p1->coef = sum;
                result->next = p1;
                result = p1;
                // p1指针后移
                p1 = p1->next;
                // 存储当前的p2项（不再需要）准备删除
                PNode* toDelete = p2;
                // p2指针后移
                p2 = p2->next;
                delete toDelete;
            } else {
                // 相加的结果为0，舍弃当前的p1和p2，删除并后移
                PNode* toDelete = p1; p1 = p1->next; delete toDelete;
                toDelete = p2; p2 = p2->next; delete toDelete;
            }
        } else if (p1->expn < p2->expn) {
            // p1的指数小于p2的指数，不可相加
            // 直接将p1推入结果中，p1后移，p2不后移
            result->next = p1;
            result = p1;
            p1 = p1->next;
        } else {
            // p2的指数小于p1的指数，不可相加
            // 直接将p2推入结果中，p2后移，p1不后移
            result->next = p2;
            result = p2;
            p2 = p2->next;
        }
    }

    // 此时p1或p2已经加完，处理剩余没有相加的项
    result->next = p1 ? p1 : p2;
    // delete b;
}

#pragma clang diagnostic pop