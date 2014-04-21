/*
 Created By: Malvika Joshi
 Problem: FINDPERM
 Link: http://opc.iarcs.org.in/index.php/problems/FINDPERM
*/

#include <iostream>
using namespace std;

int n;
int M[100010];

void add(int i,int v){
	while(i <= n){
		M[i] = M[i] + v;
		i += i & -i;
	}
}

int sum(int i){
	int s = 0;
	while(i > 0){
		s = s+ M [i];
		i -= i & -i;
	}
	return s;
}

int lower_bound(int s){
	int l  = 1, r = n;
	while(l < r){
		int c = (l+r)/2;
		if(sum(c) < s){
			l = c+1;
		}else{
			r = c;
		}
	}
	return l;
}

int main(){
	cin >> n;
	for(int i = 0;i <= n ;i ++){
		M[i] = 0;
	}

	int Q[n];
	for(int i = 0;i < n; i++){
		cin >> Q[i];
	}

	for(int i = 1; i <= n;i ++){
		add(i,1);
	}

	int ans[n];

	for(int i = n-1;i >= 0;i --){
		int k = lower_bound(Q[i]+1);
		ans[n-k] = i+1;
		add(k,-1);
	}

	for(int i = 0;i < n; i++){
		cout << ans[i] << " ";
	}

	return 0;
}
