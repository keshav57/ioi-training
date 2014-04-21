#include <stdio.h>

typedef struct {
	int digits[40];
	int n;
} bignum;

void createbignum(bignum x){
	int i;
	for(i = 0;i < 40; i++) x.digits[i] = 0;
	x.n = 0;
}

bignum parent(bignum x){
	int i,d,q,k,n;
	k = 0;
	i = 0;
	d = 0;
	n = x.n;

	bignum sol;

	if(x.digits[i] < 2){
		d = x.digits[i];
		i++;
	}

	while(i < n){
		d *= 10;
		d +=  x.digits[i];
		q = d/2;
		d %= 2;
		sol.digits[k++] = q;
		i++;
	}

	sol.n = k;

	return sol;
}

int bigcmp(bignum a, bignum b){
	int i;

	if(a.n != b.n) return a.n-b.n;

	for(i = 0;i < a.n; i++){
		if(a.digits[i] != b.digits[i]){
			return a.digits[i]-b.digits[i];
		}
	}

	return 0;
}

bignum root_u[200];
bignum root_v[200];
int U,V,Q;

int init(bignum u, bignum v){

	int i,j;
	U = 0;
	V = 0;
	bignum one;
	one.n = 1;
	one.digits[0] = 1;

	root_u[U++] = u;

	while(bigcmp(root_u[U-1],one)){
		root_u[U] = parent(root_u[U-1]);
		U++;
	}

	root_v[V++] = v;

	while(bigcmp(root_v[V-1],one)){
		root_v[V] = parent(root_v[V-1]);
		V++;
	}

	i = 0;
	j = 0;
	int cmp;
	while(i < U && j < V){
		cmp = bigcmp(root_u[i],root_v[j]);

		if(!cmp){
			break;
		}

		if(cmp > 0){
			i++;
		}else{
			j++;
		}
	}

	return i+j;
}

int main(){
	bignum u,v;
	int i;
	char c;
	scanf("%d\n",&Q);

	for(i = 0 ;i < Q; i++){
		u.n = 0;
		v.n = 0;
		c = getchar();
		while(c != ' '){
			u.digits[u.n++] = c-'0';
			c = getchar();
		}

		c = getchar();

		while(c != '\n'){
			v.digits[v.n++] = c-'0';
			c = getchar();
		}

		printf("%d\n",init(u,v));
	}

	return 0;
}

