/*
 Created By: Malvika Joshi
 Problem: DRAWFIX
 Link: http://opc.iarcs.org.in/index.php/problems/DRAWFIX
*/

#include <iostream>
#include <algorithm>

using namespace std;

struct player{
	int ELO_rating;
	int index;
};

player S[50000];
player N[50000];
int solution[50000];

bool compare(player a, player b){
	return a.ELO_rating > b.ELO_rating;
}

int main(){

	int n;
	cin >> n;

	for(int i = 0;i < n ;i ++){
		cin >> S[i].ELO_rating;
		S[i].index = i;
	}

	for(int i = 0; i< n ;i++){
		cin >> N[i].ELO_rating;
		N[i].index = i;
	}

	sort(S, S+n,compare);
	sort(N,N+n,compare);

	int count = 0;
	int nindex = 0;
	int sindex = 0;
	int sis = n-1;

	while(nindex < n){
		if(S[sindex].ELO_rating < N[nindex].ELO_rating){
			solution[S[sis].index] = N[nindex].index;
			nindex = nindex+1;
			sis--;
		}else{
			count++;
			solution[S[sindex].index] = N[nindex].index;
			nindex++;
			sindex++;
		}
	}

	cout << count << endl;
	for(int i = 0;i < n; i++){
		cout << solution[i] + 1 << endl;
	}
}
