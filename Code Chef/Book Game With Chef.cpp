#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>

#define DMAX 20

using namespace std;

long long ct[DMAX][2];
long long N;
char dig[DMAX];

long long occ(int d){
	int i,k,b;
	long long pref;
	long long val;

	pref = N;
	val = d ? 0 : -1;

	for(i = 0; pref && i < 18; ++i){
		pref /= 10;

//		if(d == 1) cout << i << " " << val << endl;

		if(!i){
			val += pref+1;
			if(d > dig[i]) --val;
//			if(d == 1) cout << i << " " << val << endl;
			continue;
		}

		for(k = i-1; k >= 0; --k){
			for(b = 0; b <= 1; ++b){

				if(!k){
					if(!b) ct[k][b] = 9;
					else ct[k][b] = (dig[k]+1-(d <= dig[k]));
					continue;
				}

				ct[k][b] = 0;

				if(!b){
					ct[k][b] = ct[k-1][b]*9;
					continue;
				}

				if(d != dig[k]) ct[k][b] = ct[k-1][b];

				ct[k][b] += ct[k-1][0]*(dig[k]-(d < dig[k]));
			}
		}

		if(d == dig[i]) val += ct[i-1][1];		//match all
		val += ct[i-1][0]*(pref+(!!d)-(d >= dig[i]));

//		if(d == 1) cout << ct[i-1][0] << " " << ct[i-1][1] << " " << pref << endl;

//		if(d == 1) cout << i << " " << val << endl;
	}

//	cout << d << " " << val << endl;

	return val;
}

long long gcd(long long a, long long b){
	long long t;

	while(b){
		t = b;
		b = a%b;
		a = t;
	}

	return a;
}

int T;

int main(){
	int i;
	long long tmp;
	long long win;

	scanf("%d",&T);

	while(T--){
		scanf("%lld",&N);

		memset(dig,0,sizeof(dig));

		tmp = N, i =0;
		win = 0;

		while(tmp){
			dig[i++] = tmp%10;
			tmp /= 10;
		}

		for(i = 0; i <= 9; ++i){
			win += occ(i);
		}

		N *= 10;
		tmp = gcd(win,N);

		printf("%lld/%lld\n",win/tmp,N/tmp);
	}

	return 0;
}
