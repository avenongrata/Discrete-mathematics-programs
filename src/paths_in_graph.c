#include <stdio.h>
#define SIZE 10

/* variable */
int count_of_call = 0;
int flag = 0; /* for checker */
int flag_of_way = 0; /* for checker */

/* matrix */
int matrix[SIZE][SIZE];
int work_matrix[SIZE][SIZE];
int control_matrix[SIZE][SIZE];

/* temporary massif */
int visited_vertex[SIZE];

/* function */
void dfs(int a, int n); /* my version */
void checker(int a, int b, int n); /* will check the way to vertex */

int tree_edge[SIZE][SIZE];
int back_edge[SIZE][SIZE];
int forward_edge[SIZE][SIZE];
int cross_edge[SIZE][SIZE];

int main()
{
    /* there is 4 possible edge in graph
     * 1) tree edge
     * 2) back edge
     * 3) forward edge
     * 4) cross edge */

    int n;
    scanf("%d", &n);

    /* delete the garbage */
    int i, j;
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            matrix[i][j] = work_matrix[i][j] = control_matrix[i][j] = '\0';
            tree_edge[i][j] = back_edge[i][j] = forward_edge[i][j] = cross_edge[i][j] = '\0';
        }
        visited_vertex[i] = '\0';
    }

    /* input matrix */
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++){
            scanf("%d", &matrix[i][j]);
            work_matrix[i][j] = control_matrix[i][j] = matrix[i][j];
        }

    /*check the matrix */
    printf("\n\n Your matrix is\n");
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            printf("\t%d", matrix[i][j]);
        }
        printf("\n");
    }



    count_of_call = 0;
    dfs(count_of_call, n);


    /* wanna see the tree edges? */
    printf("\n\n In tree massif is(are)\n");
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(tree_edge[i][j] == 1){
                printf(" %c --> %c\n", i+65, j+65);
            }
        }
    }

    /* wanna see the back edges? */
    printf("\n\n In back massif is(are)\n");
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(back_edge[i][j] == 1){
                printf(" %c --> %c\n", i+65, j+65);
            }
        }
    }

    /* wanna see the forward edges? */
    printf("\n\n In forward massif is(are)\n");
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(forward_edge[i][j] == 1){
                printf(" %c --> %c\n", i+65, j+65);
            }
        }
    }

    /* wanna see the cross edges? */
    printf("\n\n In cross massif is(are)\n");
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(cross_edge[i][j] == 1){
                printf(" %c --> %c\n", i+65, j+65);
            }
        }
    }
    printf("\n\n");


    return 0;
}

void dfs(int a, int n){

    int i, j;
    for(i = a; i <= a; i++){
        visited_vertex[i] = 1; /* the beginn-vertex is already vivsted */

        for(j = 0; j < n; j++){
            if(i == j) /* the dioganal we dont use */
                continue;

            if(matrix[i][j] != 0){ /* if there is an edge to other vetrex */
                /* check, if vertex using for the first time or not */
                    if(visited_vertex[j] == 1){ /* not for the first time */
                        /* there are possible 3 edges
                         * 1) forward
                         * 2) back
                         * 3) cross */

                        /* check if this is the forward edge */
                        if(i < j && visited_vertex[j] == 1){
                            forward_edge[i][j] = 1;
                        }

                        /* check, this is the back edge or the cross edge*/
                        else if(i > j && visited_vertex[j] == 1){
                            checker(j, i, n);
                              if(flag == 1){
                               back_edge[i][j] = 1;
                               flag = 0;
                               flag_of_way = 0;
                             }

                            /* the other edge is 100% cross edge */
                            else cross_edge[i][j] = 1;

                        }

                    }

                    else { /* for the irst time */
                        tree_edge[i][j] = 1;
                        dfs(j, n);
                    }

                }
        }
    }

   if(a == count_of_call){ /* if there is no edge to next vertex, but this vertex is not last */
       int m;
       for(m = 0; m < n; m++){
           if(visited_vertex[m] == 0){
               count_of_call = m;
               dfs(count_of_call, n);
               break;
           }
       }
   }


}


void checker(int a, int b, int n){

    int i, j;
    for(i = a; i <= a; i++){
        for(j = 0; j < n; j++){
            if(tree_edge[i][j] != 0){
                if(j == b){
                    flag = 1;
                    flag_of_way = 1;
                    break;
                }
                else if(!flag_of_way)
                    checker(j, b, n);

            }
        }
    }
}

