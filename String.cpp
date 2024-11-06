#define MAXLEN 255

typedef struct {
    char characters[MAXLEN + 1];
    int length;
} FixedLengthString;

typedef struct {
    char *characters;
    int length;
} HeapString;

#define CHUNKSIZE 80

typedef struct Chuck {
    char ch[CHUNKSIZE];
    Chuck *next;
} Chunk;

typedef struct {
    Chunk *head, *tail;
    int length;
} LinkedString;

/**
 * 模式匹配的BF算法
 * @param str 主串
 * @param substr 子串
 * @param pos 搜索起始位置（从1开始）
 * @return 子串在主串的位置（从1开始）
 */
int Index_BF(FixedLengthString str, FixedLengthString substr, int pos) {
    int i = pos;
    int j = 1;

    while (i <= str.length && j <= substr.length) {
        if (str.characters[i] == substr.characters[j]) {
            ++i;
            ++j;
        } else {
            // 假设 j 现在比较了 5 位失败，那么 i 会回退 3 个位置。
            i = i - j + 2;
            j = 1;
        }
    }

    // j > substr.length 表示对于子串已经比较到了串尾
    if (j > substr.length) return i - substr.length;
        // 其它情况表示比较失败
    else return 0;
}

int Index_KMP(FixedLengthString str, FixedLengthString substr, int pos, int *next) {
    int i = pos;
    int j = 1;

    while (i <= str.length && j <= substr.length) {
        if (str.characters[i] == substr.characters[j]) {
            ++i;
            ++j;
        } else {
            // KMP算法核心：i不改变，而是尝试将j移动到更省事的位置
            // 假设我们已经得到了正确的next数组
            j = next[j];
        }
    }

    // j > substr.length 表示对于子串已经比较到了串尾
    if (j > substr.length) return i - substr.length;
        // 其它情况表示比较失败
    else return 0;
}

void GetNext(FixedLengthString pattern, int *next) {
    int j = 1;
    int k = 0;
    next[1] = 0;
    while (j < pattern.length ) {
        if (k == 0 || pattern.characters[k] == pattern.characters[j]) {
            ++k;
            ++j;
            next[j] = k;
        } else {
            k = next[k];
        }
    }
}