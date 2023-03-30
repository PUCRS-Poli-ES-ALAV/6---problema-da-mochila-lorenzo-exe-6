#include <stdio.h>

int fiboRec(int n);
int fibo(int n);
int memoizedFibo(int f[], int n);
int lookupFibo(int f[], int n);

void reset();
void fiboRecTest1(int n[], int s);
void fiboTest1(int v[], int s);
void memoizedFiboTest1(int v[], int s);

int count = 0;
int instructions = 0;

int main() {
    int v[5] = { 10, 15, 20, 25, 30 };
    
    printf("\n");
    printf("Valores = [ ");

    for (int i = 0; i < 5; i++) {
        if (i == 4) printf("%d ]", v[i]);
        else printf("%d, ", v[i]);
    }

    printf("\n");

    fiboRecTest1(v, 5);
    fiboTest1(v, 5);
    memoizedFiboTest1(v, 5);

    printf("\n");

    return 0;
}

void fiboRecTest1(int v[], int s) {
    printf("\nfiboRec | ");

    for (int i = 0; i < s; i++) {
        reset();
        int r = fiboRec(v[i]);
        printf("r=%d it=%d in=%d | ", r, count, instructions);
    }

    printf("\n");

    reset();
}

void fiboTest1(int v[], int s) {
    printf("\nfibo | ");

    for (int i = 0; i < s; i++) {
        reset();
        int r = fibo(v[i]);
        printf("r=%d it=%d in=%d | ", r, count, instructions);
    }

    printf("\n");

    reset();
}

void memoizedFiboTest1(int v[], int s) {
    printf("\nmemoizedFiboTest1 | ");

    for (int i = 0; i < s; i++) {
        reset();
        int f[v[i]];
        int r = memoizedFibo(f, v[i]);
        printf("r=%d it=%d in=%d | ", r, count, instructions);
    }

    printf("\n");

    reset();
}

int fiboRec(int n) {
    count++;
    instructions++;

    if (n <= 1) return n;
    int a = fiboRec(n - 1);
    int b = fiboRec(n - 2);
    
    instructions += 2;
    return a + b;
}

int fibo(int n) {
    instructions += 3;

    int f[n];
    f[0] = 0;
    f[1] = 1;
    
    for (int i = 2; i <= n; i++) {    
        count++;
        instructions++;
        f[i] = f[i - 1] + f[i - 2];
    }

    return f[n];
}

int memoizedFibo(int f[], int n) {
    for (int i = 0; i <= n; i++) {
        count++;
        instructions++;
        f[i] = -1;
    }
    
    return lookupFibo(f, n);
}

int lookupFibo(int f[], int n) {
    count++;
    instructions++;
    
    if (f[n] >= 0) return f[n];
    if (n <= 1) f[n] = n;
    else f[n] = lookupFibo(f, n - 1) + lookupFibo(f, n - 2);
    
    instructions += 2;

    return f[n];
}

void reset() {
    count = 0;
    instructions = 0;
}