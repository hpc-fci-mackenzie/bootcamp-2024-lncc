#include <stdio.h>
#include <stdlib.h>

#define MAX_CHILDREN 2
#define MAX_VALUE 100
#define MAX_NODES 1000

typedef struct
{
    double value;
    int num_children;
    int children[MAX_CHILDREN];
} Node;

typedef struct
{
    double sum;
    int path[MAX_NODES];
    int pathLength;
} Result;

Result computePaths(Node *tree, int idx)
{
    Result res = {0, {0}, 0};

    if (idx == -1)
        return res;

    if (tree[idx].num_children == 0)
    {
        res.sum = tree[idx].value;
        res.path[res.pathLength++] = idx;
        return res;
    }

    double maxSum = -1;
    Result maxChildRes;

    for (int i = 0; i < tree[idx].num_children; ++i)
    {
        Result childRes = computePaths(tree, tree[idx].children[i]);
        if (childRes.sum > maxSum)
        {
            maxSum = childRes.sum;
            maxChildRes = childRes;
        }
    }

    res.sum = tree[idx].value + maxSum;
    res.path[0] = idx;
    for (int i = 0; i < maxChildRes.pathLength; ++i)
    {
        res.path[i + 1] = maxChildRes.path[i];
    }
    res.pathLength = maxChildRes.pathLength + 1;

    return res;
}

int main()
{
    int N;
    scanf("%d", &N);

    Node *tree = (Node *)malloc(N * sizeof(Node));
    for (int i = 0; i < N; ++i)
    {
        scanf("%lf %d", &tree[i].value, &tree[i].num_children);
        for (int j = 0; j < tree[i].num_children; ++j)
        {
            scanf("%d", &tree[i].children[j]);
            tree[i].children[j]--;
        }
    }

    Result finalRes = computePaths(tree, 0);
    printf("Max Sum: %.2lf\n", finalRes.sum);
    printf("Path: ");
    for (int i = 0; i < finalRes.pathLength; ++i)
    {
        printf("%d ", finalRes.path[i] + 1);
    }
    printf("\n");
    free(tree);
    return 0;
}
