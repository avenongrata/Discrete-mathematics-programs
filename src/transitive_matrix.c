#include <stdio.h>
#define SIZE 10

/* variable */
int count_of_call = 0;
int flag = 0; /* for checker */
int flag_of_way = 0; /* for checker */

/* matrix */
int matrix[SIZE][SIZE];
int transitiv_matrix[SIZE][SIZE];
int matrix_without_backedge[SIZE][SIZE];

int visited_vertex[SIZE];

/* function */
void dfs(int a, int n); /* my version */
void checker(int a, int b, int n); /* will check the way to vertex */
void closing(int a, int b, int n); /* for transitiv_matrix_closing */
void checker_for_group(int a, int n);

/* the massif of possible edge */
int tree_edge[SIZE][SIZE];
int back_edge[SIZE][SIZE];

int main()
{
    int n;
    scanf("%d", &n);

    /* delete the garbage */
    int i, j;
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            matrix[i][j] = transitiv_matrix[i][j] = matrix_without_backedge[i][j] = '\0';
            tree_edge[i][j] = back_edge[i][j] = '\0';
        }
        visited_vertex[i] = '\0';
    }

    /* input matrix */
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++){
            scanf("%d", &matrix[i][j]);
            transitiv_matrix[i][j] = matrix_without_backedge[i][j] = matrix[i][j];
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



    /* wanna see the back edges? */
    printf("\n\n In back massif is(are)\n");
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(back_edge[i][j] == 1){
                printf(" %c --> %c\n", i+65, j+65);
            }
        }
    }


       printf("\n\n Your matrix without back-edges is \n");
       /* delete the back-edges */
       for(i = 0; i < n; i++){
           for(j = 0; j < n; j++){
               if(back_edge[i][j] == 1){
                   transitiv_matrix[i][j] = matrix_without_backedge[i][j] = 0;
               }
               printf("\t%d", transitiv_matrix[i][j]);
           }
           printf("\n");
       }

       /* will find transitiv matrix */
       for(i = 0; i < n; i++){
           for(j = 0; j < n; j++){
               if(i == j) /* the diagonal we dont use */
                   continue;

               if(transitiv_matrix[i][j] == 1) /* if there is an edge */
               closing(i, j, n); /* call function */
           }
       }

      printf("\n\n Your transitiv matrix is \n");
      for(i = 0; i < n; i++){
           for(j = 0; j < n; j++){
               printf("\t%d", transitiv_matrix[i][j]);
           }
           printf("\n");
       }

       printf("\n\n");


       /* start find source and sink */
       int all[n];
       int f, ft, t;
       f = 1; ft = 2; t = 3; /* 3 groups are possible and one(-1) - incorrect */

       for(i = 0; i < n; i++){
          for(j = 0; j < n; j++){
               if(matrix_without_backedge[i][j] == 1){ /* if there is (1) in string */
               int count;
               all[i] = f;
               for(count = 0; count < n; count++){
                   if(matrix_without_backedge[count][i] != 0){
                       all[i] = ft; /* to the group (ft) */
                       break;
                       }
                 }
                 j = n; /* go to the next string */
           }

           if(j == n - 1){ /* at last call */
               int count;
           for(count = 0; count < n; count++){
               if(matrix_without_backedge[count][i] == 1){
                   all[i] = t;
                   break;
               }
               else all[i] = -1; /* if there is no line between two points */
           }
           }
       }
   }
   for(i = 0; i <n; i++){
       if(all[i] == 1){
           printf("\t%c is source\n", i+65);
       }
       else if(all[i] == 3){
           printf("\t%c is sink\n", i+65);
       }
   }

   printf("\n\n");


    return 0;
}

void dfs(int a, int n){

    int i, j;
    for(i = a; i <= a; i++){
        visited_vertex[i] = 1; /* the beginn-vertex is already visited */

        for(j = 0; j < n; j++){
            if(i == j) /* the dioganal we dont use */
                continue;

            if(matrix[i][j] != 0){ /* if there is an edge to other vetrex */
                /* check, if vertex using for the first time or not */
                    if(visited_vertex[j] == 1){ /* not for the first time */
                        /* check, this is the back edge or the cross edge*/
                        if(i > j && visited_vertex[j] == 1){
                            checker(j, i, n);
                              if(flag == 1){
                               back_edge[i][j] = 1;
                               flag = 0;
                               flag_of_way = 0;
                             }
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


void closing(int a, int b, int n){

    int i, j;
    for(i = b; i <= b; i++){
        for(j = 0; j < n; j++){
            if(transitiv_matrix[i][j] == 1 && transitiv_matrix[a][j] == 0)
            transitiv_matrix[a][j] = 1;
        }
    }
}








