/*
 Created By: Malvika Joshi
 Problem: cowtour
 Link: http://cerberus.delos.com:791/usacoprob2?a=Kr2YuuICYFC&S=cowtour
*/
#include <stdio.h>
#include <math.h>
#define infinity 200000000

typedef struct { int x, y; } point;

int Graph[200][200];
double dist[200][200];
point V[200];
int N,min_edge = infinity;

double eucledian_dist(point p1, point p2){
	int xdist = (p1.x-p2.x)*(p1.x-p2.x);
	int ydist = (p1.y-p2.y)*(p1.y-p2.y);
	double edist = sqrt(xdist+ydist);
	return edist;
}

void floyd_warshall(){
	int i,j,k;
	double temp;

	for(i = 0; i < N; i++){
		for(j = 0;j < N; j++){
			if(i == j){
				dist[i][j] = 0;
			}else if(Graph[i][j]){
				dist[i][j] = eucledian_dist(V[i],V[j]);
			}else{
				dist[i][j] = infinity;
			}
		}
	}

	for(k = 0; k < N; k++){
		for(i = 0;i < N; i++){
			for(j = 0;j < N; j++){
				temp = dist[i][k] + dist[k][j];
				if(temp < dist[i][j]){
					dist[i][j] = temp;
				}
			}
		}
	}

}

inline double min(double a, double b){
	return a < b ? a : b;
}

inline double max(double a, double b){
	return a > b ? a : b;
}

inline double new_diameter(int i, int j){
	double diameter = 0,d1 = 0,d2 = 0,edge;
	edge = eucledian_dist(V[i],V[j]);
	int k;
	for(k = 0;k < N; k++){
		if(dist[i][k] < infinity && dist[i][k] > d1) d1 = dist[i][k];
		else if(dist[k][j] < infinity && dist[k][j] > d2) d2 = dist[k][j];
	}

	diameter = d1 + d2 + edge;
	if(d1 == 0 || d2 == 0){
		min_edge  = min(edge,min_edge);
		return infinity;
	}
	return diameter;
}

double max_diameter(){
	double max = 0;
	int i,j;
	for(i = 0;i < N; i++){
		for(j = 0;j < N; j++){
			if(dist[i][j] != infinity && dist[i][j] > max) max = dist[i][j];
		}
	}
	return max;
}

int main(){
	int i,j;
	char c;
	double mindiameter = infinity,temp;
	scanf("%d",&N);
	for(i = 0;i < N; i++){
		scanf("%d%d",&V[i].x,&V[i].y);
	}
	for(i = 0;i < N; i++){
		scanf("\n");
		for(j = 0;j < N; j++){
			scanf("%c",&c);
			Graph[i][j] = c-'0';
		}
	}

	floyd_warshall();

	for(i = 0;i < N; i++){
		for(j = 0;j < N; j++){
			if(dist[i][j] == infinity ){
				temp = new_diameter(i,j);
				mindiameter = mindiameter < temp ? mindiameter : temp;
			}
		}
	}


	if(mindiameter == infinity){
		mindiameter = max_diameter();
		if(!mindiameter  || mindiameter == infinity) mindiameter = min_edge;
	}

	printf("%.6f\n",mindiameter);

	return 0;
}
