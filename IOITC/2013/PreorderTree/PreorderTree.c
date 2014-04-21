#include <stdio.h>

long long T[25][25] = {{0}};
int N;

void init(){

	int i,k;

	T[0][0] = 1;
	T[1][1] = 1;

	for(i = 2; i <= N; i++){
		for(k = 1; k <= N; k++){
			T[i][k] = T[i][k-1] + (T[k-1][k-1]*T[i-k][i-k]);
		}
	}

}

void query(int i,long long n,char s){
	if(i == 0 || n == 0){
		return;
	}

	int k= 1;

	for(k = 1; k <= i; k++){
		if(T[i][k] >= n) break;
	}

	printf("%c",s+k-1);
//	printf("%d %lld %d\n",k,T[i][k],n);

	long long q = n-T[i][k-1];
	//printf("%d\n",q);

	query(k-1,(q-1)/T[i-k][i-k]+1,s);
	query(i-k,1 + (q-1)%T[i-k][i-k],s+k);

}

int main(){
	long long k;
	scanf("%d%lld",&N,&k);

	init();

	if(k > T[N][N]){
		printf("-1");
		return 0;
	}

	query(N,k,'a');

	return 0;
}
