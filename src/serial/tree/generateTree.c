#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX_CHILDREN 2
#define MAX_VALUE 100

typedef struct
{
    double value;
    int num_children;
    int children[MAX_CHILDREN];
} Node;

void generateTree(Node *tree, int *treeSize, int idx, int currentDepth, int maxDepth)
{
    if (currentDepth == maxDepth)
        return;

    for (int i = 0; i < MAX_CHILDREN; ++i)
    {
        Node child;
        child.value = ((rand() % MAX_VALUE) + 1) / 10000.00;
        child.num_children = 0;
        tree[*treeSize] = child;
        tree[idx].children[tree[idx].num_children++] = (*treeSize)++;
    }

    for (int i = 0; i < tree[idx].num_children; ++i)
    {
        int childIdx = tree[idx].children[i];
        generateTree(tree, treeSize, childIdx, currentDepth + 1, maxDepth);
    }
}

int main(int argc, char *argv[])
{
    int N = 10000000;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <number of nodes (N)>\n", argv[0]);
    }
    else
    {
        N = atoi(argv[1]);
    }

    int D = log2(N + 1);

    srand(time(NULL));

    Node *tree = (Node *)malloc(N * sizeof(Node));
    int treeSize = 0;
    tree[treeSize].value = (rand() % MAX_VALUE) + 1;
    tree[treeSize].num_children = 0;
    treeSize++;

    generateTree(tree, &treeSize, 0, 1, D);

    printf("%d\n", N);
    for (int i = 0; i < N; ++i)
    {
        printf("%lf %d ", tree[i].value, tree[i].num_children);
        for (int j = 0; j < tree[i].num_children; ++j)
        {
            printf("%d ", tree[i].children[j] + 1); // Ajuste para índice baseado em 1
        }
        printf("\n");
    }

    free(tree);
    return 0;
}
