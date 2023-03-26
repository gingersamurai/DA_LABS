#include <iostream>
#include <cstring>

using namespace std;

struct myData{
    char key[33];
    unsigned long long value;
};
const int MAXSIZE = 100000;

bool comp(myData a, myData b) {
    return strcmp(a.key, b.key) <= 0;
}

void BubbleSort(myData array[], size_t size) {
    for (int iter = 0; iter < size; iter++) {
        for (int i = 1; i < size; i++) {
            if (!comp(array[i-1], array[i])) {
                swap(array[i-1], array[i]);
            }
        }
    }
}


int main() {
    myData array[MAXSIZE];
    size_t size = 0;
    while (scanf("%s %llu", array[size].key, &array[size].value) == 2){
        size++;
    }
    BubbleSort(array, size);
    for (int i = 0; i < size; i++) {
        cout << array[i].key << "\t" << array[i].value << "\n";
    }
}