/*
 Created By: Malvika Joshi
 Problem: packrec
 Link: http://cerberus.delos.com:791/usacoanal2?a=NqUIopnM9br&S=packrec
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct { int w,h; }rectangle;

int sol[150];
rectangle L[4];
rectangle A[4];
int vis[4] = {0};
int S = 0;
int min_ar = 10000;

int max(int a,int b,int c,int d){
	int m = d;
	m = a > m ? a : m;
	m = b > m ? b : m;
	m = c > m ? c : m;
	return m;
}

inline int min(int a,int b){ return a < b ? a : b; }

void minarea(){

	int h,w,area;

	h = max(L[0].h,L[1].h,L[2].h,L[3].h);
	w = L[0].w+L[1].w+L[2].w+L[3].w;

	area = h*w;
	if(area == min_ar){
		sol[S++] = min(h,w);
	}
	if(area < min_ar){
		S = 0;
		min_ar = area;
		sol[S++] = min(h,w);
	}

	h = L[3].h + max(L[0].h,L[1].h,L[2].h,0);
	w = max(L[3].w, L[0].w+L[1].w+L[2].w,0,0);

	area = h*w;
	if(area == min_ar){
			sol[S++] = min(h,w);
		}
	if(area < min_ar){
		S = 0;
		min_ar = area;
		sol[S++] = min(h,w);
	}

	h = L[2].w + max(L[3].w,L[0].w+L[1].w,0,0);
	w = max(L[2].h,L[3].h + max(L[0].h,L[1].h,0,0),0,0);

	area = h*w;
	if(area == min_ar){
			sol[S++] = min(h,w);
		}
	if(area < min_ar){
		S = 0;
		min_ar = area;
		sol[S++] = min(h,w);
	}
	h = max(L[0].h,L[1].h+L[2].h,L[3].h,0);
	w = L[0].w + L[3].w + max(L[1].w,L[2].w,0,0);

	area = h*w;
	if(area == min_ar){
			sol[S++] = min(h,w);
		}
	if(area < min_ar){
		S = 0;
		min_ar = area;
		sol[S++] = min(h,w);
	}

	if (L[2].w>=L[0].w+L[1].w)
         h =max(L[3].h,max(L[0].h+L[2].h,L[1].h+L[2].h,0,0),0,0);
    else if (L[2].w>L[1].w && L[2].w<L[0].w+L[1].w)
         h = max(L[0].h+max(L[2].h,L[3].h,0,0),L[1].h+L[2].h,0,0);
    else if (L[1].w>L[2].w && L[1].w<L[2].w+L[3].w)
         h=max(L[1].h+max(L[2].h,L[3].h,0,0),L[0].h+L[3].h,0,0);
    else if (L[1].w>=L[2].w+L[3].w)
         h=max(L[1].h+max(L[2].h,L[3].h,0,0),L[0].h,0,0);
    else
         h=max(L[0].h+L[3].h,L[1].h+L[2].h,0,0);
    w=max(L[0].w+L[1].w,L[2].w+L[3].w,0,0);


	area = h*w;
	if(area == min_ar){
			sol[S++] = min(h,w);
	}
	if(area < min_ar){
		S = 0;
		min_ar = area;
		sol[S++] = min(h,w);
	}

}


void get_area(int r){
	if(r < 0) return;
	if(r == 0){
		minarea();
		return;
	}
	int i;
	for(i = 0; i < 4; i++){
		if(!vis[i]){
			vis[i] = 1;
			L[r-1].h = A[i].w;
			L[r-1].w = A[i].h;
			get_area(r-1);
			L[r-1] = A[i];
			get_area(r-1);
			vis[i] = 0;
		}
	}
}

int compare(const void* a, const void* b){
	return *(int *)a - *(int*)b;
}

int main(){

	scanf("%d%d",&A[0].w,&A[0].h);
	scanf("%d%d",&A[1].w,&A[1].h);
	scanf("%d%d",&A[2].w,&A[2].h);
	scanf("%d%d",&A[3].w,&A[3].h);
	get_area(4);

	printf("%d\n",min_ar);
	int i;

	qsort(sol,S,sizeof(int),compare);
	for(i = 0;i < S; i++){
		if(i > 0 && sol[i] == sol[i-1]) continue;
		printf("%d %d\n",sol[i],min_ar/sol[i]);
	}

	return 0;
}
