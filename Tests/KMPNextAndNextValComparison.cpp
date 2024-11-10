/**
 * 生成一个字符串的next数组和nextval数组
 * 用于比较
 */
#include "../String.cpp"
#include "iostream"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++11-extensions"
using namespace std;

int main() {
    auto* str = new FixedLengthString;
    // 函数处理时的下标都从1开始，第一个字符设为0
    strcpy(str->characters, "0AAABCAABCA");
    str->length = 10;

    int* next = new int[999];
    int* nextval = new int[999];

    GetNext(*str, next);
    GetNextVal(*str, nextval);

    for (int i = 1; i <= str->length; i++) cout << str->characters[i] << " ";
    cout << endl;
    for (int i = 1; i <= str->length; i++) cout << next[i] << " ";
    cout << endl;
    for (int i = 1; i <= str->length; i++) cout << nextval[i] << " ";
}
#pragma clang diagnostic pop