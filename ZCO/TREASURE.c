/*
 Created By: Malvika Joshi
 Problem: TREASURE
 Link: http://opc.iarcs.org.in/index.php/problems/TREASURE
*/

#include <stdio.h>

int V[200][20];
int Mac[200][20];
int Tok[200][20];
int M,T,S,N;
int MV[40000];


int main(){
	int i,j,a,b,cmac,ctok,tmac,ttok;
	scanf("%d%d%d%d",&M,&T,&S,&N);
	S--;

	for(i = 0;i < M; i++){
		for(j = 0;j < T;j++){
			scanf("%d%d",&a,&b);
			a--;
			b--;
			Tok[i][j] = a;
			Mac[i][j] = b;
			V[i][j] = 0;
		}
	}

	cmac = S;
	ctok = 0;
	int r,oc,k;

	for(i = 1;i <= N; i++){

		if(V[cmac][ctok]){
			r = V[cmac][ctok]-1;
			oc = i - V[cmac][ctok];
			k =  (N-r)%oc;
			if(k == 0){
				k = oc;
			}
			k = k+r;
			printf("%d",MV[k]+1);
			return 0;
		}

		V[cmac][ctok] = i;
		MV[i] = cmac;

		if(i == N){
			printf("%d",cmac+1);
			return 0;
		}

		tmac = Mac[cmac][ctok];
		ttok = Tok[cmac][ctok];

		cmac = tmac;
		ctok = ttok;

	}

	return 0;

}
