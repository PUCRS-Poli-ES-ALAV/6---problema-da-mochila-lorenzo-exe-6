#include <iostream>
#include <time.h>

using namespace std;

void test1();
void test2();

int backPackRec(int n, int c, pair<int, int> items[]);
int backPackPD(int n, int c, pair<int, int> items[]);

void reset();
void generateItems(int itemsQuantity, pair<int, int> items[]);
void backPackRecTest(int itemsQuantity, int backpackCapacity, pair<int, int> baseItems[], int test);
void backPackPDTest(int itemsQuantity, int backpackCapacity, pair<int, int> baseItems[], int test);

int count = 0;

int main()
{
    /*int itemsQuantity = 10;
    int backpackCapacity = 25;

    pair<int, int> baseItems[itemsQuantity];

    generateItems(itemsQuantity, baseItems);

    backPackRecTest(itemsQuantity, backpackCapacity, baseItems, 1);
    backPackPDTest(itemsQuantity, backpackCapacity, baseItems, 1);*/

    test1();
    test2();
    
    return 0;
}

void test1() {
    int itemsQuantity = 10;
    int backpackCapacity = 165;

    pair<int, int> baseItems[itemsQuantity];

    baseItems[0].first = 23;
    baseItems[0].second = 92;

    baseItems[1].first = 31;
    baseItems[1].second = 57;

    baseItems[2].first = 29;
    baseItems[2].second = 49;

    baseItems[3].first = 44;
    baseItems[3].second = 68;

    baseItems[4].first = 53;
    baseItems[4].second = 60;

    baseItems[5].first = 38;
    baseItems[5].second = 43;

    baseItems[6].first = 63;
    baseItems[6].second = 67;

    baseItems[7].first = 85;
    baseItems[7].second = 84;

    baseItems[8].first = 89;
    baseItems[8].second = 87;

    baseItems[9].first = 82;
    baseItems[9].second = 72;

    backPackRecTest(itemsQuantity, backpackCapacity, baseItems, 1);
    backPackPDTest(itemsQuantity, backpackCapacity, baseItems, 1);
}

void test2() {
    int itemsQuantity = 6;
    int backpackCapacity = 190;

    pair<int, int> baseItems[itemsQuantity];
    
    baseItems[0].first = 56;
    baseItems[0].second = 50;

    baseItems[1].first = 59;
    baseItems[1].second = 50;

    baseItems[2].first = 80;
    baseItems[2].second = 64;

    baseItems[3].first = 64;
    baseItems[3].second = 46;

    baseItems[4].first = 75;
    baseItems[4].second = 50;

    baseItems[5].first = 17;
    baseItems[5].second = 5;

    backPackRecTest(itemsQuantity, backpackCapacity, baseItems, 2);
    backPackPDTest(itemsQuantity, backpackCapacity, baseItems, 2);
}

void backPackRecTest(int itemsQuantity, int backpackCapacity, pair<int, int> baseItems[], int test) {
    cout << "backPackRec - test " << test << endl << endl;
    cout << "Best combination: " << backPackRec(itemsQuantity, backpackCapacity, baseItems) << endl;
    cout << "Number of instructions: " << count << endl << endl;
    reset();
}

void backPackPDTest(int itemsQuantity, int backpackCapacity, pair<int, int> baseItems[], int test) {
    pair<int, int> items[itemsQuantity + 1];

    for (int i = 1; i < itemsQuantity + 1; i++) {
        items[i].first = baseItems[i - 1].first;
        items[i].second = baseItems[i - 1].second;
    }
    
    cout << "backPackPD - test " << test << endl << endl;
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