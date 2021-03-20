#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct Node{
    int head;
    struct Node* left;
    struct Node* right;
} Node;

Node* creatingNodes(Node* tree, int head);
void creatingTrees(Node* tree, int n, int k);
void destroyNode(Node* tree);
int comparing(Node* firstTree, Node* SecondTree);

int main() {
    int n = 0, k = 0, value = 0, identical = 1, number = 0, identicalTrees = 0;;
    scanf("%d %d", &n, &k);
    if((n < 1) || (n > 50) || (k < 1) || (k > 20)) return 0;

    Node *trees[n];
    creatingTrees(trees[n], n, k);

    for(int num = 0; num < n; num++){
        Node *tree = NULL;
        for(int Nodes = 0; Nodes < k; Nodes++){
            value = 0;
            scanf("%d", &value);
            if ((value < 1) || (value > pow(10, 6))) return 0;
            tree = creatingNodes(tree, value);
        }
        trees[num] = tree;
    }

    for(int num = 0; num < n; num++){
        identical = 1;
        for(number = num + 1; number < n; number++){
            if (comparing(trees[num], trees[number]) == 1) identical = 0;
        }
        if (identical == 1) identicalTrees++;       
    }
    for(int num = 0; num < n; num++) destroyNode(trees[num]);
    printf("%d\n", identicalTrees);

    return 0;
}

void creatingTrees(Node* trees, int n, int k){
    int value = 0;
    for(int num = 0; num < n; num++){
        Node *tree = NULL;
        for(int counterNodes = 0; counterNodes < k; counterNodes++){
            value = 0;
            //scanf("%d", &value);
            if ((value < 1) || (value > pow(10, 6))) {
                return;
            }
            tree = creatingNodes(tree, value);
        }
        trees[num] = tree[num];
    }
}
//https://www.geeksforgeeks.org/write-c-code-to-determine-if-two-trees-are-identical/
Node* creatingNodes(Node* tree, int head) {
    if (tree == NULL){
        tree = (Node*)malloc(sizeof(Node));
        tree->head = head;
        tree->right = NULL;
        tree->left = NULL;
    } else if(head > tree->head) tree->right = creatingNodes(tree->right, head);
    else if(head < tree->head) tree->left = creatingNodes(tree->left, head);
    return tree;
}
//https://www.cprogramming.com/tutorial/c/lesson18.html
void destroyNode(Node* tree){
    if(tree == NULL){
        return;
    } else if(tree != NULL){
        destroyNode(tree->right);
        destroyNode(tree->left);
        free(tree);
    }
}
//https://www.geeksforgeeks.org/write-c-code-to-determine-if-two-trees-are-identical/
int comparing(Node* firstTree, Node* SecondTree) {
    if ((firstTree == NULL) && (SecondTree == NULL))  return 1;
    else if((firstTree == NULL) || (SecondTree == NULL)) return 0;
    else{
        int compare = comparing(firstTree->left, SecondTree->left) && comparing(firstTree->right, SecondTree->right);
        return compare;
    }
}
