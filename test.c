#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    int x;
    int base;
    char value[256];
} Root;

long long decodeValue(const char *value, int base) {
    long long result = 0;
    while (*value) {
        result = result * base + (*value >= '0' && *value <= '9' ? *value - '0' : *value - 'a' + 10);
        value++;
    }
    return result;
}

long long lagrangeInterpolation(Root roots[], long long y[], int k) {
    long long result = 0;
    for (int i = 0; i < k; i++) {
        long long numerator = 1, denominator = 1;
        for (int j = 0; j < k; j++) {
            if (i != j) {
                numerator *= -roots[j].x;
                denominator *= roots[i].x - roots[j].x;
            }
        }
        result += y[i] * (numerator / denominator);
    }
    return result;
}

int main() {
    // Test Case 1
    Root testCase1[] = {
        {1, 10, "4"},
        {2, 2, "111"},
        {3, 10, "12"},
        {6, 4, "213"}
    };
    int k1 = 3;
    long long y1[4];
    for (int i = 0; i < 4; i++) {
        y1[i] = decodeValue(testCase1[i].value, testCase1[i].base);
    }
    printf("Secret for Test Case 1: %lld\n", lagrangeInterpolation(testCase1, y1, k1));

    // Test Case 2
    Root testCase2[] = {
        {1, 6, "13444211440455345511"},
        {2, 15, "aed7015a346d63"},
        {3, 15, "6aeeb69631c227c"},
        {4, 16, "e1b5e05623d881f"},
        {5, 8, "316034514573652620673"},
        {6, 3, "2122212201122002221120200210011020220200"},
        {7, 3, "20120221122211000100210021102001201112121"},
        {8, 6, "20220554335330240002224253"},
        {9, 12, "45153788322a1255483"},
        {10, 7, "1101613130313526312514143"}
    };
    int k2 = 7;
    long long y2[10];
    for (int i = 0; i < 10; i++) {
        y2[i] = decodeValue(testCase2[i].value, testCase2[i].base);
    }
    printf("Secret for Test Case 2: %lld\n", lagrangeInterpolation(testCase2, y2, k2));

    return 0;
}
