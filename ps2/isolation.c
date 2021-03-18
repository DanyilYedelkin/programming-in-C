#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    int number;
    struct Tree *right;
    struct Tree *left;
} Tree;

//int creationTrees(int n, int k);

int main(){
    int n = 0, k = 0;
    scanf("%d %d", &n, &k);
    if((n < 1) || (n > 50) || (k < 1) || (k > 20)) return 0;

    return 0;
}

