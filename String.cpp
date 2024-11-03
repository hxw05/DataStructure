#define MAXLEN 255

typedef struct {
    char characters[MAXLEN+1];
    int length;
} FixedLengthString;

typedef struct {
    char *characters;
    int length;
} HeapString;