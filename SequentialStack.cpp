#include "common.h"

#define MAXSIZE 100
typedef struct {
    int *base;
    int *top;
    int stacksize;
} SequentialStack;

Status Init(SequentialStack &st) {
    // 栈底指向数组的第一个元素，此后不改变
    st.base = new int[MAXSIZE];
    st.top = st.base;
    st.stacksize = 0;
    return 1;
}

Status Push(SequentialStack &st, int e) {
    if (st.top - st.base == MAXSIZE) return 0; // 栈长 = st.top-st.base
    *(st.top++) = e;
    return 1;
}

Status Pop(SequentialStack &st, int &e) {
    if (st.top == st.base) return 0;
    e = *(--st.top); // 注意：栈顶指针指向的是栈顶元素的后一个位置，需要先-1再返回
    return 1;
}

Status GetTop(SequentialStack st, int &e) {
    if (st.top == st.base) return 0;
    e = *(st.top - 1);
    return 1;
}

