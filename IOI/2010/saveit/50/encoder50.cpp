#include "grader.h"
#include "encoder.h"
#include <algorithm>
#include <cassert>
#include <iostream>

#define NMAX 1010
#define HMAX 40

using namespace std;

int N,K;

int dist[HMAX][NMAX];
int adj[NMAX][NMAX];

int Q[NMAX];
int H,T;

void bfs(int src){
    int i,v;
    
    H = 0;
    T = 0;
  
    for(i = 0; i < N; ++i){
      dist[src][i] = -1;
    }
    dist[src][src]= 0;
    Q[T++] = src;
        
    while(H < T){
      v = Q[H++];
                  for(i = 0; i < N; ++i){
	if(!adj[v][i] || dist[src][i] >= 0) continue;
	dist[src][i] = dist[src][v] + 1;
	Q[T++] = i;
      }
    }
  
}

void encode(int nv, int nh, int ne, int *v1, int *v2){
  int i;
  
  N = nv;
  K = nh;
  
  for(i = 0; i < ne; ++i){
    adj[v1[i]][v2[i]] = adj[v2[i]][v1[i]] = 1;
  }
  
  for (i = 0 ; i < K; ++i){
    bfs(i);
  }
  
  for (i = 0; i < K; ++i){
    for (int k = 0; k < N; ++k){
      for (int b = 0; b < 10; ++b){
	encode_bit(!!(dist[i][k]&(1<<b)));
      }
    }
  }
  
  return;
}
