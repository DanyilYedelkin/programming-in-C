#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Tree{
    int number;
    struct Tree *right;
    struct Tree *left;
} Tree;

int creationTrees(int n, int k);
void newNode(Tree* trees, int point);
void firstCreation(Tree* firstPoint, int point);
void newNewNode(Tree* branch, int point);
void search(Tree* trees, int n);
int identicalNodes(Tree* rightNode, Tree* leftNode);
int identicalTrees(Tree* rightTree, Tree* leftTree);
void destroyingTrees(Tree* trees);

int main(){
    int n = 0, k = 0;
    scanf("%d %d", &n, &k);
    if((n < 1) || (n > 50) || (k < 1) || (k > 20)) return 0;

    int result = creationTrees(n, k);
    printf("%d\n", result);

    return 0;
}

void newNewNode(Tree* branch, int point){
    branch->number = point;
    branch->left = NULL;
    branch->right = NULL;
}
//https://www.geeksforgeeks.org/binary-tree-set-1-introduction/
void newNode(Tree* trees, int point){
    /*Tree* treeNode = (Tree*)malloc(sizeof(Tree));
    treeNode->number = point;
    treeNode->left = NULL;
    treeNode->right = NULL;*/
    if(point < trees->number){
        if(trees->left != NULL){
            newNode(trees->left, point);
        }
        if(trees->left == NULL){
            trees->left = (Tree*)malloc(sizeof(Tree));
            newNewNode(trees->left, point);
        }
        /*if(trees->left != NULL){
            newNode(trees->left, point);
        }*/
        /*trees->left->value = point;
        trees->left->rigth = NULL;
        trees->left->left = NULL;*/
    } else if(point >= trees->number){
        if(trees->right != NULL){
            newNode(trees->right, point);
        }
        if(trees->right == NULL){
            trees->right = (Tree*)malloc(sizeof(Tree));
            newNewNode(trees->right, point);
        }
        /*if(trees->right != NULL){
            newNode(trees->right, point);
        }*/
    }
}

void firstCreation(Tree* firstPoint, int point){
    Tree* treeNode = (Tree*)malloc(sizeof(Tree));
    treeNode->number = point;
    treeNode->left = NULL;
    treeNode->right = NULL;
    free(treeNode);
}
/*void search(Tree* trees, int n){
    int same = 0;
    for(int right = 0; right > (n - 1); right++){
        for(int left = (1 + right); left < n; left++){
            same = identicalTrees(trees[right], trees[left]);
            if(same == 0){
                continue;
            } else if(same == 1){
                destroyingTrees(trees[left]);
                trees[left] = NULL;
            }
        }
    }
}*/
int identicalNodes(Tree* rightNode, Tree* leftNode){
    int checkLeftNode = 0;
    if(rightNode == NULL && leftNode == NULL){
        return 0;
    } else if(rightNode != NULL && leftNode != NULL){
        checkLeftNode = identicalNodes(rightNode->left, leftNode->left);
        if(checkLeftNode == 0){
            return 0;
        } else{
            int returning = identicalNodes(rightNode->right, leftNode->right);
            return returning;
        }
    } else{
        return 0;
    }
}
int identicalTrees(Tree* rightTree, Tree* leftTree){
    if(rightTree == NULL && leftTree == NULL){
        return -1;
    } else if(rightTree != NULL && leftTree != NULL){
        int checkingNodes = identicalNodes(rightTree, leftTree);
        return checkingNodes;
    } else{
        return 0;
    }
}

//https://www.cprogramming.com/tutorial/c/lesson18.html
void destroyingTrees(Tree* trees){
    if(trees == NULL){
        return;
    } else if((trees->left != NULL) || (trees->right != NULL)){
        destroyingTrees(trees->left);
        destroyingTrees(trees->right);
        free(trees);
    }
}

int creationTrees(int n, int k){
    Tree **everything = calloc(n, sizeof(Tree*));
    int value = 0;
    for(int i = 0; i < n; i++){
        everything[i] = NULL;
    }

    for(int N = 0; N < n; N++){
        for(int K = 0; K < k; K++){
            value = 0;
            scanf("%d", &value);
            if((value < 1) || (value > pow(10, 6))){
                if(everything == NULL){
                    return 0;
                }
                for(int i = 0; i < n; i++){
                    destroyingTrees(everything[i]);
                }
                free(everything);
                return 0;
            }
            if(everything[N] == NULL){
                //https://www.programiz.com/dsa/binary-tree
                everything[N] = malloc(sizeof(Tree));
                everything[N]->number = value;
                everything[N]->left = NULL;
                everything[N]->right = NULL;
                firstCreation(everything[N], value);
            } else{
                newNode(everything[N], value);
            }
        }
    }
    //printf("314");
    //===================================
    int same = 0;
    for(int right = 0; right > (n - 1); right++){
        if(everything[right] == NULL) continue;
        for(int left = (1 + right); left < n; left++){
            if(everything[left] == NULL) continue;
            same = identicalTrees(everything[right], everything[left]);
            /*if(same == 0){
                continue;
            } else */if(same == 1){
                destroyingTrees(everything[left]);
                everything[left] = NULL;
            }
        }
    }
    int reiteration = 0;
    for(int i = 0; i < n; i++){
        if(everything[i] != NULL){
            reiteration++;
        }
    }
    reiteration -= 1;
    //printf("%d", reiteration);
    if(everything == NULL){
        free(everything);
        return 0;
    }
    for(int i = 0; i < n; i++){
        destroyingTrees(everything[i]);
    }
    free(everything);

    return reiteration;
}
