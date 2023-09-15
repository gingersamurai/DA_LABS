#include <iostream>
#include <cstring>
#include <cstdint>

using namespace std;

const int maxStringLength = 257;

struct treapNode {
    char *key;
    int priority;
    uint64_t value;
    treapNode *leftSon, *rightSon;

    treapNode(char *key, uint64_t value) {
        this->key = new char[maxStringLength];
        memcpy(this->key, key, maxStringLength);
        this->value = value;
        this->priority = rand();
        this->leftSon = nullptr;
        this->rightSon = nullptr;
    }

    ~treapNode() {
        delete[] key;
    }


};

void toLower(char *str) {
    for (int i = 0; i < strlen(str); i++) {
        str[i] = tolower(str[i]);
    }
}


void dropTreap(treapNode *node) {
    if (node == nullptr) {
        return;
    }
    dropTreap(node->leftSon);
    dropTreap(node->rightSon);
    delete node;
}

void split(treapNode *root, treapNode*& leftResult, treapNode*& rightResult, char *key) {
    if (root == nullptr) {
        leftResult = nullptr;
        rightResult = nullptr;
        return;
    }

    if (strcmp(root->key, key) <= 0) {
        leftResult = root;
        split(root->rightSon, leftResult->rightSon, rightResult, key);
    } else {
        rightResult = root;
        split(root->leftSon, leftResult, rightResult->leftSon, key);
    }
}

// left candidate's key is less or equal right candidate's key
treapNode* merge(treapNode *leftCandidate, treapNode *rightCandidate) {
    if (leftCandidate == nullptr) {
        return rightCandidate;
    }
    if (rightCandidate == nullptr) {
        return leftCandidate;
    }

    if (leftCandidate->priority > rightCandidate->priority) {
        leftCandidate->rightSon = merge(leftCandidate->rightSon, rightCandidate);
        return leftCandidate;
    } else {
        rightCandidate->leftSon = merge(leftCandidate, rightCandidate->leftSon);
        return rightCandidate;
    }
}

void removeNode(treapNode *&root, char *key) {
    if (root == nullptr) {
        return;
    }
    
    if (strcmp(root->key, key) == 0) {
        treapNode *result = merge(root->leftSon, root->rightSon);
        delete root;
        root = result;
        return;
    }

    if (strcmp(root->key, key) > 0) {
        removeNode(root->leftSon, key);
        return;
    }

    removeNode(root->rightSon, key);
}

void insertNode(treapNode *&root, treapNode *item) {
    if (root == nullptr) {
        root = item;
        return;
    }
    if (item->priority > root->priority) {
        split(root, item->leftSon, item->rightSon, item->key);
        root = item;
        return;
    }

    if (strcmp(item->key, root->key) < 0) {
        insertNode(root->leftSon, item);
    } else {
        insertNode(root->rightSon, item);
    }
}



treapNode *findNode(treapNode *root, char *key) {
    if (root == nullptr) {
        return nullptr;
    }
    
    if (strcmp(root->key, key) == 0) {
        return root;
    }
    if (strcmp(root->key, key) > 0) {
        return findNode(root->leftSon, key);
    }
    return findNode(root->rightSon, key);

}

void addDataToTreap(treapNode *&root, char *key, uint64_t value) {
    toLower(key);
    if (findNode(root, key)) {
        cout << "Exist\n";
    } else {
        insertNode(root, new treapNode(key, value));
        cout << "OK\n";
    }
}

void deleteDataFromTreap(treapNode *&root, char *key) {
    toLower(key);
    if (findNode(root, key)) {
        removeNode(root, key);
        cout << "OK\n";
    } else {
        cout << "NoSuchWord\n";
    }
}

void getValueFromTreap(treapNode *&root, char *key) {
    toLower(key);
    treapNode *result = findNode(root, key);
    if (result) {
        cout << "OK: " << result->value; 
    } else {
        cout << "NoSuchWord";
    }
    cout << "\n";
}

int main() {
    srand(time(nullptr));
    treapNode *root = nullptr;

    char *userQuery = new char[maxStringLength];
    
    char *key = new char[maxStringLength];
    uint64_t value;

    while (cin >> userQuery) {
        if (strcmp(userQuery, "+") == 0) {
            cin >> key >> value;
            addDataToTreap(root, key, value);
        } else if (strcmp(userQuery, "-") == 0) {
            cin >> key;
            deleteDataFromTreap(root, key);
        } else {
            key = userQuery;
           getValueFromTreap(root, key);
        }
    }    
}