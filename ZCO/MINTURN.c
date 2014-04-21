/*
 Created By: Malvika Joshi
 Problem: MINTURN
 Link: http://opc.iarcs.org.in/index.php/problems/MINTURN
*/

#include <stdio.h>
#include <limits.h>

#define infinity 20000
#define nil -1

typedef struct {char top,bottom,left,right;} disk;
typedef struct {int i,j;} vertex;

disk Park[1000][1000];
int D[1000][1000];
int M,N;
int visited[1000][1000];

vertex A[1000000];
int heap_size;
int pointers[1000][1000];

int parent(int i){
	return ((i+1)/2)-1;
}

int left(int i){
	return (2*(i+1))-1;
}

int right(int i){
	return 2*(i+1);
}

void heaplify(int i){
	int l = left(i);
	int r = right(i);
	int smallest;
	vertex temp;

	if(l < heap_size && D[A[l].i][A[l].j] < D[A[i].i][A[i].j]){
		smallest = l;
	}else {
		smallest = i;
	}
	if(r < heap_size && D[A[r].i][A[r].j] < D[A[smallest].i][A[smallest].j]){
		smallest= r;
	}
	if(smallest != i){
		temp = A[i];
		A[i] = A[smallest];
		A[smallest] = temp;
		pointers[A[i].i][A[i].j] = i;
		pointers[A[smallest].i][A[smallest].j] = smallest;
		heaplify(smallest);
	}
}

void build_heap(){
	int n = heap_size;
	int i;
	for(i = (n/2)-1;i >= 0;i--){
		heaplify(i);
	}
}

vertex extract_min(){
	int j = heap_size-1;
	vertex temp;
	temp = A[0];
	A[0] = A[j];
	pointers[A[0].i][A[0].j] = 0;
	heap_size--;
	heaplify(0);
	return temp;
}

void decrease_key(int x){
	int	p = parent(x);
	vertex temp;
	if(D[A[x].i][A[x].j] < D[A[p].i][A[p].j]){
		temp = A[x];
		A[x] = A[p];
		A[p] = temp;
		pointers[A[p].i][A[p].j] = p;
		pointers[A[x].i][A[x].j] = x;
		decrease_key(p);
	}
}

int ddown(int i, int j){
    char des = Park[i+1][j].top;
    if(Park[i][j].bottom == des){
        return 0;
    }else if(Park[i][j].right == des){
        return 1;
    }else if(Park[i][j].top == des){
        return 2;
    }else {
        return 3;
    }
}

int dright(int i, int j){
    char des = Park[i][j+1].left;
    if(Park[i][j].right == des){
        return 0;
    }else if(Park[i][j].top == des){
        return 1;
    }else if(Park[i][j].left == des){
        return 2;
    }else {
        return 3;
    }
}

int dtop(int i, int j){
    char des = Park[i-1][j].bottom;
    if(Park[i][j].top == des){
        return 0;
    }else if(Park[i][j].left == des){
        return 1;
    }else if(Park[i][j].bottom == des){
        return 2;
    }else {
        return 3;
    }
}

int dleft(int  i, int j){
    char des = Park[i][j-1].right;
    if(Park[i][j].left == des){
        return 0;
    }else if(Park[i][j].bottom == des){
        return 1;
    }else if(Park[i][j].right == des){
        return 2;
    }else {
        return 3;
    }
}

void dijsktra(int i, int j){
	visited[i][j] = 1;
    int dist;
    if(i+1 < M && !visited[i+1][j]){
       dist = ddown(i,j);
       dist += D[i][j];
       if(D[i+1][j] > dist){
            D[i+1][j] = dist;
            decrease_key(pointers[i+1][j]);
       }
    }
    if(j+1 < N && !visited[i][j+1]){
        dist = dright(i,j);
        dist += D[i][j];
        if(D[i][j+1] > dist){
            D[i][j+1] = dist;
            decrease_key(pointers[i][j+1]);
        }
    }

    if(i-1 >= 0 && !visited[i-1][j]){
        dist = dtop(i,j);
        dist += D[i][j];
        if(D[i-1][j] > dist){
            D[i-1][j] = dist;
            decrease_key(pointers[i-1][j]);
        }
    }

    if(j-1 >= 0 && !visited[i][j-1]){
        dist = dleft(i,j);
        dist += D[i][j];
        if(D[i][j-1] > dist){
            D[i][j-1] = dist;
            decrease_key(pointers[i][j-1]);
        }
    }
}

int main(void){

    int i,j;
    scanf("%d%d",&M,&N);

    for(i = 0;i < M; i++){
        for(j = 0;j < N; j++){
            scanf("\n%c %c %c %c",&Park[i][j].top,&Park[i][j].right,&Park[i][j].bottom,&Park[i][j].left);
        }
    }

    for(i = 0;i < M;i ++){
        for(j = 0;j < N;j++){
            D[i][j] = infinity;
            visited[i][j] = 0;
        }
    }

    D[0][0] = 0;
    heap_size = 0;

    for(i = 0;i < M ;i ++){
        for(j = 0;j < N;j ++){
            A[heap_size].i = i;
            A[heap_size].j = j;
            pointers[i][j] = heap_size;
            heap_size++;
        }
    }

    build_heap();
    vertex min;
    while(heap_size > 0){
        min = extract_min();
        dijsktra(min.i,min.j);
    }

    printf("%d",D[M-1][N-1]);

    return 0;
}









