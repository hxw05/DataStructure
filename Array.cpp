#include "common.h"

typedef struct El {
    int *elements;
    int length;
} Array;

#define MAXSIZE 99999

Status Insert(Array &array, int i, int e) {
    if (i < 1 || i > array.length + 1) return 0;
    if (array.length == MAXSIZE) return 0;
    for (int j = array.length - 1; j >= i - 1; j--) {
        array.elements[j + 1] = array.elements[j];
    }

    array.elements[i - 1] = e;
    array.length += 1;
    return 1;
}

Status Locate(Array &array, int e) {
    for (int i = 0; i < array.length; i++) {
        if (array.elements[i] == e) return i + 1;
    }

    return 0;
}

Status Delete(Array &array, int i) {
    if ((i < 1) || (i > array.length)) return 0;
    for (int j = i; j < array.length; j++) {
        array.elements[j-1]=array.elements[j];
    }

    array.length -= 1;
    return 1;
}

// a,b,c假设按照不减顺序排列
void MergeArraySequential(Array &a, Array &b, Array &c) {
    c.length = a.length + b.length;
    c.elements = new int[c.length];
    int* pc = c.elements;
    int* pa = a.elements;
    int* pb = b.elements;
    int* pa_r = a.elements + a.length - 1;
    int* pb_r = b.elements + b.length - 1;
    while ((pa <= pa_r) && (pb <= pb_r)) {
        if (*pa <= *pb) *pc++ = *pa++; // *(pc++) = *(pa++)
        else *pc++ = *pb++;
    }
    // 由于 pa 和 pb 不一定同时到达表尾
    // 所以用下面两个语句处理没有到达表尾的那个表（无论是哪一个），将剩余元素都按照顺序加到pc中
    while (pa <= pa_r) *pc++ = *pa++;
    while (pb <= pb_r) *pc++ = *pb++;
}