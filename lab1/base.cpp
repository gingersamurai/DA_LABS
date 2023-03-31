#include <iostream>
#include <algorithm>
#include <ctype.h>
#include <cstring>

using namespace std;



struct myData{
    char key[33];
    unsigned long long value;
};
int MAXSIZE = 1;



bool comp(myData a, myData b){
    return strcmp(a.key, b.key) < 0;
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
    sort(array, array + size, comp);
    for (int i = 0; i < size; i++) {
        cout << array[i].key << "\t" << array[i].value << "\n";
    }
}