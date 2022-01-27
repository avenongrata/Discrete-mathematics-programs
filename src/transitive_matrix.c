#include <stdio.h>
#define SIZE 10

/* variable */
int count_of_call = 0;
int flag = 0;           /* for checker */
int flag_of_way = 0;    /* for checker */

/* matrix */
int matrix[SIZE][SIZE];
int transitiv_matrix[SIZE][SIZE];
int matrix_without_backedge[SIZE][SIZE];

int visited_vertex[SIZE];

/* function */
void dfs(int a, int n);             /* my version */
void checker(int a, int b, int n);  /* will check the way to vertex */
void closing(int a, int b, int n);  /* for transitiv_matrix_closing */
void checker_for_group(int a, int n);

/* the massif of possible edge */
int tree_edge[SIZE][SIZE];
int back_edge[SIZE][SIZE];

int main()
{
    int i, j, n;
    scanf("%d", &n);

    /* delete the garbage */
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            matrix[i][j] = transitiv_matrix[i][j] = matrix_without_backedge[i][j] = '\0';
            tree_edge[i][j] = back_edge[i][j] = '\0';
        }
        visited_vertex[i] = '\0';
    }

    /* input matrix */
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%d", &matrix[i][j]);
            transitiv_matrix[i][j] = matrix_without_backedge[i][j] = matrix[i][j];
        }
    }

    /* check the matrix */
    printf("\n\n Your matrix is\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            printf("\t%d", matrix[i][j]);
        }
        printf("\n");
    }

    count_of_call = 0;
    dfs(count_of_call, n);

    /* print the edges */
    printf("\n\n In back massif is(are)\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(back_edge[i][j] == 1)
            {
                printf(" %c --> %c\n", i+65, j+65);
            }
        }
    }

    printf("\n\n Your matrix without back-edges is \n");

    /* delete the back-edges */
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(back_edge[i][j] == 1)
            {
               transitiv_matrix[i][j] = matrix_without_backedge[i][j] = 0;
            }
            printf("\t%d", transitiv_matrix[i][j]);
        }
        printf("\n");
    }

    /* will find transitiv matrix */
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            /* the diagonal we dont use */
            if(i == j)
                continue;

            /* if there is an edge */
            if(transitiv_matrix[i][j] == 1)
                closing(i, j, n);
        }
    }

    printf("\n\n Your transitiv matrix is \n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            printf("\t%d", transitiv_matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");

    /* start find source and sink */
    int all[n];
    int f, ft, t;

    /* 3 groups are possible and one(-1) - incorrect */
    f = 1; ft = 2; t = 3;

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            /* if there is (1) in string */
            if(matrix_without_backedge[i][j] == 1)
            {
                int count;
                all[i] = f;

                for(count = 0; count < n; count++)
                {
                    if(matrix_without_backedge[count][i] != 0)
                    {
                        /* to the group (ft) */
                        all[i] = ft;
                        break;
                    }
                }

                /* go to the next string */
                j = n;
            }

            /* at last call */
            if(j == n - 1)
            {
                int count;
                for(count = 0; count < n; count++)
                {
                    if(matrix_without_backedge[count][i] == 1)
                    {
                        all[i] = t;
                        break;
                    }
                    else /* if there is no line between two points */
                    {
                        all[i] = -1;
                    }
                }
            }
        }
    }

    for(i = 0; i <n; i++)
    {
        if(all[i] == 1)
        {
            printf("\t%c is source\n", i+65);
        }
        else if(all[i] == 3)
        {
            printf("\t%c is sink\n", i+65);
        }
    }
    printf("\n\n");

    return 0;
}

void dfs(int a, int n)
{
    int i, j;

    for(i = a; i <= a; i++)
    {
        /* the beginn-vertex is already visited */
        visited_vertex[i] = 1;

        for(j = 0; j < n; j++)
        {
            /* the dioganal we dont use */
            if(i == j)
                continue;

            /* if there is an edge to other vetrex */
            if(matrix[i][j] != 0)
            {
                /* check, if vertex using for the first time or not */
                if(visited_vertex[j] == 1)
                {
                    if(i > j && visited_vertex[j] == 1)
                    {
                        checker(j, i, n);

                        if(flag == 1)
                        {
                            back_edge[i][j] = 1;
                            flag = 0;
                            flag_of_way = 0;
                        }
                    }
                }
                else /* for the irst time */
                {
                    tree_edge[i][j] = 1;
                    dfs(j, n);
                }
            }
        }
    }

    /* if there is no edge to next vertex, but this vertex is not last */
    if(a == count_of_call)
    {
       int m;

       for(m = 0; m < n; m++)
       {
           if(visited_vertex[m] == 0)
           {
               count_of_call = m;
               dfs(count_of_call, n);
               break;
           }
       }
   }
}

void checker(int a, int b, int n)
{
    int i, j;

    for(i = a; i <= a; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(tree_edge[i][j] != 0)
            {
                if(j == b)
                {
                    flag = 1;
                    flag_of_way = 1;
                    break;
                }
                else if(!flag_of_way)
                {
                    checker(j, b, n);
                }
            }
        }
    }
}

void closing(int a, int b, int n)
{
    int i, j;

    for(i = b; i <= b; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(transitiv_matrix[i][j] == 1 && transitiv_matrix[a][j] == 0)
                transitiv_matrix[a][j] = 1;
        }
    }
}

