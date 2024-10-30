#include <iostream>
#include "common.h"

using namespace std;

typedef struct El {
    struct El *next{};
    int data{};
} List;

Status Insert(List &list, int i, int value) {
    if (i < 1) return 0;

    El *p = &list;
    int j = 0;

    /**
     * 写法1
     * 寻找第i-1个元素，如果i的值大于n+1，
     * 为了避免执行无效循环，当p为null（最后一个元素）的时候就直接跳出循环
     */
    while (p && (j < i - 1)) {
        p = p->next;
        ++j;
    }

    if (!p) return 0;

    /**
     * 写法2
     * 寻找第i-1个元素，如果找到最后p是null，就直接返回0，
     */
    while (j < i - 1) {
        p = p->next;
        ++j;
        if (p == nullptr) return 0; // 此时已经查找到尾部，插入位置不正确
    }

    El *s = new El{};
    s->data = value;
    s->next = p->next;
    p->next = s;
    return 1;
}

Status Get(List list, int i, int &target) {
    if (i < 1) return 0;
    El *p = list.next;
    int j = 1;
    while (j < i) {
        if (p == nullptr) return 0;
        p = p->next;
        ++j;
    }
    target = p->data;
    return 1;
}

Status Delete(List &list, int i) {
    if (i < 1) return 0;
    El *p = list.next;
    int j = 0;

    while (j < i - 1) {
        // 未找到合适的i-1结点：删除位置不正确
        if (p->next == nullptr) return 0;
        p = p->next;
        ++j;
    }

    El *q = p->next; // 需要删除的结点
    p->next = q->next; // 相当于 p->next = p->next->next;
    delete q;
    return 1;
}

int len(List list) {
    El *p = list.next;
    int cnt = 0;

    while (p) {
        p = p->next;
        cnt++;
    }

    return cnt;
}

int Locate(List list, int e) {
    int j = 1;
    El* p = list.next;

    while (p) {
        if (p->data == e) return j;
        p = p->next;
        j++;
    }

    return 0;
}

void CreateList_Head(List *list, int n) {
    list->next = nullptr;

    for (int i = 0; i < n; i++) {
        El *p = new El{};
        cin >> p->data;
        p->next = list->next;
        list->next = p;
    }
}

void CreateList_Rear(List *list, int n) {
    list->next = nullptr;
    // 辅助指针，用于标记当前链表尾部元素（rear）
    List* r = list;
    for (int i = 0; i < n; i++) {
        El *p = new El{};
        cin >> p->data;
        p->next = nullptr;
        r->next = p;
        r = p;
    }
}

void Merge(List &la, List &lb) {
    int m = len(la);
    int n = len(lb);

    int e;
    for (int i = 0; i < n; i++) {
        Get(la, i, e);

        // 判断 la 中是否包含 lb 中的某些元素
        // 如果不包含，就将其插入到 la 的尾部（++m 位置）
        if (!Locate(la, e)) {
            Insert(la, ++m, e);
        }
    }
}

// la,lb,lc假设按照不减顺序排列
void MergeListSequential(List &la, List &lb, List &lc) {
    El* pa = la.next;
    El* pb = lb.next;
    // 任意为 lc 指定一个头结点
    // 此处选择 la 的头结点
    lc = la;
    El* pc = &lc;

    while (pa && pb) { // 当两个表都没有遍历到最后
        if (pa->data <= pb->data) {
            pc->next = pa; // 插入pa
            pc = pa; // pc指针移动到pa上
            pa = pa->next; // pa指针移动到pa表的下一个
        } else {
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
    }

    pc->next = pa ? pa : pb; // 剩余部分处理
    // delete lb;
}

List Reverse(List L) {
    El* current = L.next, *nextTargetReverse = nullptr, *nextTarget = nullptr;
    // L head -> head.next -> head.next.next -> ...
    //           ↑current
    // current从L的第一个元素开始

    while (current) {
        // nextTarget指向current的下一个元素
        nextTarget = current->next;
        // [R] null
        //    ↑nextTargetReverse
        // [L] head -> head.next -> head.next.next -> ...
        //              ↑current      ↑nextTarget

        // 将current移入反向后的链表尾部
        current->next = nextTargetReverse;
        // [R] head -> head.next -> null
        //              ↑current    ↑nextTargetReverse
        // [L] head.next.next -> ...
        //      ↑nextTarget

        // 将nextTargetReverse指向反向链表的下一个指向目标
        nextTargetReverse = current;
        // 将current指向原链表的下一个要移动的目标
        current = nextTarget;
        // [R] head -> head.next -> null
        //           ↑nextTargetReverse
        // [L] head.next.next -> ...
        //   ↑current,nextTarget
    }
}