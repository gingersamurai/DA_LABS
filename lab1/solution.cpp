#include <iostream>
#include <ctype.h>
#include <cstring>

using namespace std;



struct myData{
    char key[33];
    unsigned long long value;
};
int MAXSIZE = 1;



int getHash(myData m, size_t pos) {
    char extra;
    if (isdigit(m.key[pos])) {
        extra = '0';
    } else {
        extra = 'a' - 10;
    }
    int hash = m.key[pos] - extra;
    // cerr << m.key << " " << hash << endl;
    return hash;
}

void insertSortDigit(myData *array, int size, int pos) {
    myData *copyArray = (myData *)malloc(sizeof(myData) * size);
    for (int i = 0; i < size; i++) copyArray[i] = array[i];

    int count[16];
    for (int i = 0; i < 16; i++) count[i] = 0;
    for (int i = 0; i < size; i++) {
        int curHash = getHash(array[i], pos);
        count[getHash(array[i], pos)]++;
    }
    
    
    for (int i = 1; i < 16; i++) {
        count[i] += count[i - 1];
    }


    for (int i = size - 1; i >= 0; i--) {
        array[count[getHash(copyArray[i], pos)] - 1] = copyArray[i];
        count[getHash(copyArray[i], pos)] -= 1;
    }

    free(copyArray);
}

void RadixSort(myData *array, size_t size) {
    for (int pos = 31; pos >= 0; pos--) { 
        insertSortDigit(array, size, pos);
    }
}


int main() {
    myData *array = (myData *)malloc(1 * sizeof(myData));
    size_t size = 0;
    while (scanf("%s\t%llu", array[size].key, &array[size].value) == 2){
        size++;
        if (size == MAXSIZE) {
            MAXSIZE *= 2;
            array = (myData *) realloc(array, MAXSIZE * sizeof(myData));
        }
    }
    RadixSort(array, size);
    // insertSortDigit(array, size, 2);
    for (int i = 0; i < size; i++) {
        cout << array[i].key << "\t" << array[i].value << "\n";
    }
}