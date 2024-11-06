#include "string"
#include "iostream"

using namespace std;

int main() {
    string str = "ABCDABDE";
    int *next = new int[9999];
    unsigned int pLen = str.length();
    next[0] = -1;
    int k = -1;
    int j = 0;
    while (j < pLen - 1) {
        //p[k]表示前缀，p[j]表示后缀
        if (k == -1 || str[j] == str[k]) {
            ++k;
            ++j;
            next[j] = k;
            cout << "next[j=" << j << "] = k=" << k << endl;
        } else {
            cout << "k=" << k << " = next[k=" << k << "]" << endl;
            k = next[k];
            cout << "k=" << k << endl;
        }
    }

    for (int i = 0; i < pLen; i++) {
        cout << i << ": " << next[i] << endl;
    }
}