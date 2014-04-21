/*
 Created By: Malvika
 Problem: camelot
 Link: http://cerberus.delos.com:791/usacoprob2?a=yEGsO4WCbvX&S=camelot
*/
#include <stdio.h>

typedef struct { int i,j; } vertex;

int dist[30][30][30][30];
int knights[30][30] = {{0}};
int D[30][30] = {{0}};
int kingdist[30][30];
vertex Q[900];
int H,T,M,N;
int ki,kj;

void init(){
	int i,j,k,l;
	for(i = 0;i < M; i++){
		for(j = 0; j < N; j++){
			for(k = 0;k < M; k++){
				for(l = 0; l < N; l++){
					dist[i][j][k][l] = 810000;
				}
			}
		}
	}
}

void bfsknight(int i, int j){
	int visited[30][30] = {{0}};
	vertex v;
	H = 0;
	T = 0;
	visited[i][j] = 1;
	dist[i][j][i][j] = 0;
	Q[T].i = i;
	Q[T++].j = j;

	while(H < T){
		v = Q[H++];
		if(v.i+2 < M){
			if(v.j+1< N && !visited[v.i+2][v.j+1]){
				dist[i][j][v.i+2][v.j+1] = dist[i][j][v.i][v.j]+1;
				Q[T].i = v.i+2;
				Q[T++].j = v.j+1;
				visited[v.i+2][v.j+1] = 1;
			}
			if(v.j-1 >= 0 && !visited[v.i+2][v.j-1]){
				dist[i][j][v.i+2][v.j-1] = dist[i][j][v.i][v.j]+1;
				Q[T].i = v.i+2;
				Q[T++].j = v.j-1;
				visited[v.i+2][v.j-1] = 1;
			}
		}
		if(v.i-2 >= 0){
			if(v.j+1< N && !visited[v.i-2][v.j+1]){
				dist[i][j][v.i-2][v.j+1] = dist[i][j][v.i][v.j]+1;
				Q[T].i = v.i-2;
				Q[T++].j = v.j+1;
				visited[v.i-2][v.j+1] = 1;
			}
			if(v.j-1 >= 0 && !visited[v.i-2][v.j-1]){
				dist[i][j][v.i-2][v.j-1] = dist[i][j][v.i][v.j]+1;
				Q[T].i = v.i-2;
				Q[T++].j = v.j-1;
				visited[v.i-2][v.j-1] = 1;
			}
		}
		if(v.j+2 < N){
			if(v.i+1 < M && !visited[v.i+1][v.j+2]){
				dist[i][j][v.i+1][v.j+2] = dist[i][j][v.i][v.j]+1;
				Q[T].i = v.i+1;
				Q[T++].j = v.j+2;
				visited[v.i+1][v.j+2] = 1;
			}
			if(v.i-1 >= 0 && !visited[v.i-1][v.j+2]){
				dist[i][j][v.i-1][v.j+2] = dist[i][j][v.i][v.j]+1;
				Q[T].i = v.i-1;
				Q[T++].j = v.j+2;
				visited[v.i-1][v.j+2] = 1;
			}
		}

		if(v.j-2 >= 0){
			if(v.i+1 < M && !visited[v.i+1][v.j-2]){
				dist[i][j][v.i+1][v.j-2] = dist[i][j][v.i][v.j]+1;
				Q[T].i = v.i+1;
				Q[T++].j = v.j-2;
				visited[v.i+1][v.j-2] = 1;
			}
			if(v.i-1 >= 0 && !visited[v.i-1][v.j-2]){
				dist[i][j][v.i-1][v.j-2] = dist[i][j][v.i][v.j]+1;
				Q[T].i = v.i-1;
				Q[T++].j = v.j-2;
				visited[v.i-1][v.j-2] = 1;
			}
		}
	}

}

void bfsking(int i, int j){
	int visited[30][30]= {{0}};
	vertex v;
	int k,l;
	H = 0;
	T = 0;
	Q[T].i =i;
	Q[T++].j = j;
	visited[i][j] = 1;
	kingdist[i][j] = 0;

	while(H < T){
		v = Q[H++];
		for(k = -1; k < 2; k++){
			for(l = -1; l < 2; l++){
				if(!k && !l) continue;
				if(v.i+k < M && v.i+k >= 0 && v.j+l < N && v.j+l >= 0 && !visited[v.i+k][v.j+l]){
					kingdist[v.i+k][v.j+l] = kingdist[v.i][v.j]+1;
					Q[T].i =v.i+k;
					Q[T++].j = v.j+l;
					visited[v.i+k][v.j+l] = 1;
				}
			}
		}
	}
}

int initCaseA(){
	int i,j,k,l,min = -1;

	for(i = 0;i < M; i++){
		for(j = 0;j < N; j++){
			for(k = 0; k < M; k++){
				for(l = 0; l < N;l ++){
					if(!knights[k][l]) continue;
					D[i][j] += dist[i][j][k][l];
				}
			}
			if(min == -1 || D[i][j] +kingdist[i][j]< min){ min = D[i][j]+kingdist[i][j]; }
		}
	}

	return min;
}

int CaseB(){
	int closest = -1,i,j,min = -1;
	for(i = 0;i < M; i++){
		for(j = 0; j < N; j++){
			if(!knights[i][j]) continue;
			if(closest == -1 || kingdist[i][j] < closest) closest = kingdist[i][j];
		}
	}

	for(i = 0;i < M; i++){
		for(j = 0; j < N; j++){
			if(D[i][j]+closest < min || min == -1) min = D[i][j] + closest;
		}
	}

	return min;

}

int CaseC(int ni,int nj){
	int toking = dist[ni][nj][ki][kj],min = -1, temp,i,j;
	for(i = 0; i < M ;i++){
		for(j = 0; j < N; j++){
			temp = D[i][j] - dist[ni][nj][i][j] + dist[ki][kj][i][j] + toking;
			if(temp < min || min == -1){
				min = temp;
			}
		}
	}

	return min;
}

int CaseCfull(){
	int i,j,temp,min = -1;
	for(i =0;i < M; i++){
		for(j = 0;j < N; j++){
			if(!knights[i][j]) continue;
			temp = CaseC(i,j);
			if(min == -1 || temp < min) min = temp;
		}
	}
	return min;
}

int minof3(){
	init();

	int i,j,temp,min;
	for(i = 0;i < M; i++){
		for(j = 0; j < N; j++){
			bfsknight(i,j);
		}
	}
	bfsking(ki,kj);

	min = initCaseA();
	temp = CaseB();
	if(temp < min && temp != -1){ min = temp; }
	temp = CaseCfull();
	if(temp < min && temp != -1){ min= temp; }

	return min;
}

int main(){

	int k;
	char n[2];


	scanf("%d%d",&N,&M);
	scanf("%s%d",n,&kj);
	ki = n[0]-'A';
	kj--;

	while(scanf("%s%d",n,&k) != EOF){
		k--;
		knights[n[0]-'A'][k] = 1;
	}

	int min;

	min = minof3();

	printf("%d\n",min);

	return 0;
}
