#include <stdio.h>
#define SIZE 10

/* functions */
void bfs(int a, int n);

/* values */
int height_of_tree = 0;
int count_of_vertex = 0;
int count_of_call = 0;
int flag = 0;

/* matrix */
int matrix[SIZE][SIZE];

int visited_vertex[SIZE];
int w8ing_vertex[SIZE];

int main()
{
    int n, i, j;

    /* delete the garbage */
    for(i = 0; i < SIZE; i++)
    {
        for(j = 0; j < SIZE; j++)
        {
            matrix[i][j] = '\0';
        }
        visited_vertex[i] = 0;
        w8ing_vertex[i] = 0;
    }

    /* get size of the matrix */
    scanf("%d", &n);

    /* input the matrix */
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }

    /* print the matrix */
    printf("\n\n Your matrix is\n\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            printf("\t%d", matrix[i][j]);
        }
        printf("\n");
    }

    /* begin from this vertex */
    bfs(0, n);

    printf("\n\n Height of tree = %d\n\n", height_of_tree);

    return 0;
}

void bfs(int a, int n)
{
    int i, j;

    for(i = a; i <= a; i++)
    {
        visited_vertex[i] = 1;

        for(j = 0; j <= n; j++)
        {
            if(matrix[i][j] != 0)
            {
                 if(visited_vertex[j] == 0)
                 {
                     if(!flag)
                        height_of_tree++;

                     flag = 1;
                     w8ing_vertex[count_of_vertex++] = j;
                     visited_vertex[j] = 1;
                 }
            }
        }
    }

    flag = 0;

    /* if there is vertex */
    if(count_of_call < count_of_vertex)
        bfs(w8ing_vertex[count_of_call++], n);
}

