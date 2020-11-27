#include <stdio.h>
#define SIZE 10

/* value */
int count_of_color = 0;
int flag = 0;

/* function */
void paint(int a, int n);

int visited_vertex[SIZE];

/* matrix */
int matrix[SIZE][SIZE];

int main()
{
    int i, j;
    for(i = 0; i < SIZE; i++){ /* delete the garbage */
        for(j = 0; j < SIZE; j++){
            matrix[i][j] = '\0';
        }
        visited_vertex[i] = -1;
    }

    int n;
    scanf("%d", &n); /* the size of matrix */

    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            scanf("%d", &matrix[i][j]);
        }
    }

    printf("\n\n Your matrix is\n\n");
    for(i = 0; i < n; i++){ /* wanna see the matrix? */
        for(j = 0; j < n; j++){
            printf("\t%d", matrix[i][j]);
        }
        printf("\n");
    }

    paint(0, n);

    printf("\n\n The color are ");
    for(i = 0; i < n; i++){
        printf("%d ", visited_vertex[i]);
    }
    printf("\n\n");




    return 0;
}

void paint(int a, int n){

    int i,j;
    for(i = a + 1; i < n; i++){
        for(j = a; j <= a; j++){
            if(matrix[i][j] == 1){
                matrix[j][i] = 1;
            }
        }
    }

    if(++a < n){
        paint(a, n);
    }


     if(!flag)
    {

        for(i = 0; i < n; i++){
            if(visited_vertex[i] == -1) /* if vertex is unvisited */
            visited_vertex[i] = count_of_color;
            count_of_color++; /* for vertex, which have an edge to present vertex, we will use new color */

            for(j = 1 + i; j < n; j++){
                if(matrix[i][j] == 1 && visited_vertex[j] == -1){ /* for the first call for each vertex */
                    visited_vertex[j] = count_of_color; /* there is an edge -> use new color */
                    continue;
                } else if(matrix[i][j] == 0 && visited_vertex[j] == -1) /* for the first call and there is no edge */
                    visited_vertex[j] = count_of_color - 1 - i; /* use color from first vertex */

               if(matrix[i][j] == 1 && visited_vertex[j] == count_of_color - 1){ /* if from last vertex there is an edge to 'C'
                                                                                  * and from present vertex there is an edge to 'C'
                                                                                  * this edge will have new color
                                                                                  * not color from last vertex and not
                                                                                  * color from present vertex */
                    visited_vertex[j] = count_of_color;
               }

            }

        }
        flag = 1; /* we can do it for one cycle -> close flag */

    }

}
