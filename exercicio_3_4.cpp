#include <iostream>
#include <time.h>

using namespace std;

int backPackRec(int n, int c, pair<int, int> items[]);
int backPackPD(int n, int c, pair<int, int> items[]);

void reset();
void generateItems(int itemsQuantity, pair<int, int> items[]);
void backPackRecTest1(int itemsQuantity, int backpackCapacity, pair<int, int> baseItems[]);
void backPackPDTest1(int itemsQuantity, int backpackCapacity, pair<int, int> baseItems[]);

int count = 0;

int main()
{
    int itemsQuantity = 10;
    int backpackCapacity = 25;

    pair<int, int> baseItems[itemsQuantity];

    generateItems(itemsQuantity, baseItems);

    backPackRecTest1(itemsQuantity, backpackCapacity, baseItems);
    backPackPDTest1(itemsQuantity, backpackCapacity, baseItems);
    
    return 0;
}

void backPackRecTest1(int itemsQuantity, int backpackCapacity, pair<int, int> baseItems[]) {
    cout << "backPackRec - test 1" << endl << endl;
    cout << "Best combination: " << backPackRec(itemsQuantity, backpackCapacity, baseItems) << endl;
    cout << "Number of instructions: " << count << endl << endl;
    reset();
}

void backPackPDTest1(int itemsQuantity, int backpackCapacity, pair<int, int> baseItems[]) {
    pair<int, int> items[itemsQuantity + 1];

    for (int i = 1; i < itemsQuantity + 1; i++) {
        items[i].first = baseItems[i - 1].first;
        items[i].second = baseItems[i - 1].second;
    }
    
    cout << "backPackPD - test 1" << endl << endl;
    cout << "Best combination: " << backPackPD(itemsQuantity, backpackCapacity, items) << endl;
    cout << "Number of instructions: " << count << endl << endl;
    reset();
}

// n = products quantity
// c = backpack capacity
// items = <weight, value> tuple
int backPackRec(int n, int c, pair<int, int> items[]) {
    count++;

    if (n == 0 || c == 0) return 0;
    
    if (items[n - 1].first > c) {
        return backPackRec(n - 1, c, items);
    } else {
        return max(
            items[n - 1].second + backPackRec(n - 1, c - items[n - 1].first, items), 
            backPackRec(n - 1, c, items));
    }
}

// n = products quantity
// c = backpack capacity
// items = <weight, value> tuple
int backPackPD(int n, int c, pair<int, int> items[]) {
    int maxTab[n + 1][c + 1];

    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < c + 1; j++) {
            maxTab[i][j] = 0;
            count++;
        }
    }
    
    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < c + 1; j++) {
            // if the current item fits in the backpack
            if (items[i].first <= j) {
                maxTab[i][j] = max(maxTab[i - 1][j], items[i].second + maxTab[i - 1][j - items[i].first]);
            } else {
                maxTab[i][j] = maxTab[i - 1][j];
            }
            count++;
        }
    }

    // max value will be at the [n][c] position
    return maxTab[n][c];
}

void generateItems(int itemsQuantity, pair<int, int> items[]) {
    srand(time(NULL));

    cout << endl << "Items: { ";

    for (int i = 1; i < itemsQuantity + 1; i++) {
        items[i].first = 1 + (rand() % 100);
        items[i].second = 1 + (rand() % 100);

        if (i != itemsQuantity) {
            cout << "[ " << items[i].first << ", " << items[i].second << " ], ";
        } else {
            cout << "[ " << items[i].first << ", " << items[i].second << " ] }" << endl << endl;
        }
    }
}

void reset() {
    count = 0;
}