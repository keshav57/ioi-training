/*
 Created By: Malvika Joshi
 Problem: SORTROWS
 Link: http://opc.iarcs.org.in/index.php/problems/SORTROWS
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct { int row[100]; }col;

col M[2000];
int N;

int compare(const void  *a, const void *b){
    int i = 0;
    col *c1 = (col *) a;
    col *c2 = (col *) b;

    while(c1->row[i] == c2->row[i]){
        if(c1->row[i] == -1){
            return 1;
        }

        if(c2->row[i] == -1){
            return 0;
        }

        i++;
    }

    return c1->row[i] - c2->row[i];
}

int main(void){

    int i,j;

    scanf("%d",&N);

    for(i = 0;i < N;i ++){
        j = -1;
        do {
            j++;
            scanf("%d",&M[i].row[j]);
        } while(M[i].row[j] != -1);
    }

    qsort(M,N,sizeof(col),compare);


    for(i = 0;i < N ; i++){
        j = 0;
        while(M[i].row[j] != -1){
            printf("%d ",M[i].row[j]);
            j++;
        }
        printf("\n");
    }

    return 0;
}
