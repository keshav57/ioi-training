/*
 Created By: Malvika Joshi
 Problem: CNR
 Link: http://www.codechef.com/LTIME05/problems/CNR
*/

#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>

#define MAXN 350
#define MAXK 350
#define MAXD 150

using namespace std;

struct big_int{
	char dg[MAXD];
	int n;

	big_int(): n(0){
	}

	big_int operator+ (const big_int&) ;
	big_int operator- (const big_int&) ;
	bool operator<= (const big_int&) const;
	bool operator< (const big_int&) const;

	void print();
};

big_int big_int::operator +(const big_int &rhs){

	big_int sol;
	int i,carry,t1,t2;

	carry = 0;
	for(i = 0; i < max(n,rhs.n); i++){

		t1 = i < n ? dg[i] : 0;
		t2 = i < rhs.n ? rhs.dg[i] : 0;

		sol.dg[sol.n++] = carry + t1 + t2;
		carry = 0;

		if(sol.dg[sol.n-1] < 10) continue;
		sol.dg[sol.n-1] -= 10;
		carry = 1;
	}
	if(carry) sol.dg[sol.n++] = 1;

	return sol;
}

big_int big_int::operator -(const big_int &rhs){

	big_int sol;
	int i,carry,t1,t2;

	carry = 0;
	for(i = 0; i < max(n,rhs.n); i++){
		t1 = i < n ? dg[i] : 0;
		t2 = i < rhs.n ? rhs.dg[i] : 0;

		sol.dg[sol.n++] = t1 - t2 - carry;
		carry = 0;

		if(sol.dg[sol.n-1] >= 0) continue;
		sol.dg[sol.n-1] += 10;

		carry = 1;
	}

	assert(!carry);
	while(!sol.dg[sol.n-1]) --sol.n;
	return sol;
}

bool big_int::operator <=(const big_int &rhs) const{
	if(n != rhs.n) return n < rhs.n;
	int i;

	for(i = n-1; i >= 0; --i){
		if(dg[i] == rhs.dg[i]) continue;
		return dg[i] < rhs.dg[i];
	}

	return 1;
}

bool big_int::operator <(const big_int &rhs) const{
	if(n != rhs.n) return n < rhs.n;
	int i;

	for(i = n-1; i >= 0; --i){
		if(dg[i] == rhs.dg[i]) continue;
		return dg[i] < rhs.dg[i];
	}

	return 0;
}

void big_int::print(){
	int i;
	for(i = n-1; i >= 0; --i) printf("%d",dg[i]);
}

big_int str_ct[MAXN+5][MAXK+5];

void init(){
	int i,k;

	for(i = 0; i <= MAXN; i++) str_ct[i][0].dg[str_ct[i][0].n++] = 1;

	for(i = 1; i <= MAXN; i++){
		for(k = 1; k <= i && k <= MAXK; k++){
			str_ct[i][k] = str_ct[i-1][k] + str_ct[i-1][k-1];
		}
	}

}

void print_num(int n, int k, big_int &m){
	if(n == 0) return;
	if(m <= str_ct[n-1][k]){
		printf("0");
		print_num(n-1,k,m);
		return;
	}
	m = m-str_ct[n-1][k];
	printf("1");
	print_num(n-1,k-1,m);
}

int strrev(char *str){
      char str2[MAXD];
      strcpy(str2,str);
      int i,j,n;
      n = strlen(str);

      for(i = 0, j = n-1; i < n; i++,--j){
    	  str[i] = str2[j]-'0';
      }

      return n;
}

int main(){
	init();

	int n,k,t;
	big_int m;

	scanf("%d",&t);

	while(t--){
		scanf("%d %d %s",&n, &k, m.dg);
		m.n = strrev(m.dg);
		if(str_ct[n][k] < m){
			printf("-1\n");
			continue;
		}
		print_num(n,k,m);
		printf("\n");
	}

	return 0;
}
