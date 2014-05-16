#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>

#define NMAX 210
#define MOD 100000

using namespace std;

char seq[NMAX];
int dp[NMAX][NMAX];

int pos(int i, int j){
	if(i >= j) return 0;
	if(!(seq[i] || seq[j])) return 3;
	if(seq[j] < 0 && !seq[i]) return 1;
	if(seq[i] > 0 && !seq[j]) return 1;
	if(seq[i] < seq[j] || seq[i]+seq[j]) return 0;
	return 1;
}

int N;

void print(int d, int num){
	if(!d || !num) return;
	print(d-1,num/10);
	printf("%d",num%10);
}

int compute(){
	int i,j,k,n;
	long long tmp,tmp2;

	for(i = 0; i < N; ++i){
		dp[i+1][i] = 1;
	}

	for(n = 2; n <= N; ++n){
		for(i = 0; i+n <= N; ++i){
			j = i+n-1;
			if(n%2){
				dp[i][j] = 0;
				continue;
			}

			tmp = (pos(i,j)*1LL*dp[i+1][j-1]);

			if(tmp > MOD){
				tmp %= MOD;
				tmp += MOD;
			}

			dp[i][j] = tmp;

			for(k = i+1; k < j; ++k){
				tmp = (1LL*dp[i+1][k-1]*pos(i,k));

				if(tmp > MOD){
					tmp %= MOD;
					tmp += MOD;
				}

				tmp2 = tmp*dp[k+1][j];
				if(tmp2 > MOD){
					tmp2 %= MOD;
					tmp2 += MOD;
				}

				dp[i][j] += tmp2;

				if(dp[i][j] > MOD){
					dp[i][j] %= MOD;
					dp[i][j] += MOD;
				}

//				cout << k << " " << tmp << endl;
			}

//			cout << i << " " << j << " " << dp[i][j] << endl;
		}
	}

//	assert(dp[0][N-1] >= 0);
	return dp[0][N-1];
}

int main(){
	int i;

	scanf("%d",&N);

	for(i = 0; i < N; ++i){
		scanf(" %c",&seq[i]);

		if(seq[i] == '?'){
			seq[i] = 0;
			continue;
		}

		if(seq[i] == '(' || seq[i] == ')'){
			seq[i] = seq[i] == '(' ? 1 : -1;
		}
		else if(seq[i] == '{' || seq[i] == '}'){
			seq[i] = seq[i] == '{' ? 2 : -2;
		}
		else if(seq[i] == '[' || seq[i] == ']'){
			seq[i] = seq[i] == '[' ? 3 : -3;
		}
	}
//	cout << compute() << endl;
	print(5,compute());
	printf("\n");

	return 0;
}
