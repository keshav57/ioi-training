#include <algorithm>
#include <iostream>
#include <cstdio>
#include <string>
#include <cassert>

using namespace std;

int gcd(int a, int b){
	int t;
	while(b){
		t = b;
		b = a%b;
		a = t;
	}
	return a;
}

int occ[30];
int num[52];
int N;

void init(){
	int i,g,k,n,tmp;

	for(i = 0; i < N; ++i) num[i] = i+1;

	for(k = 0; k < 26; ++k){
		tmp = occ[k];
		while(tmp){
			n = tmp;
			for(i = 0; i < N; ++i){
				g = gcd(num[i],n);
				num[i] /= g;
				n /= g;
			}
			assert(n == 1);
			--tmp;
		}
	}
}

int palin(){
	int i,odd;

	odd = 0;

	for(i = 0; i < 26; ++i){
		odd += (occ[i]&1);
	}

	if(odd >= 2) return 0;

	return N/2;
}

int C;
int num2[52];

void init2(){
	int i,k,tmp,n,g;

	for(i =0 ; i < C; ++i) num2[i] = i+1;

	for(k = 0; k < 26; ++k){
		tmp = occ[k];
		tmp /= 2;

		while(tmp){
			n = tmp;
			for(i = 0; i < C; ++i){
				g = gcd(n,num2[i]);
				n /= g;
				num2[i] /= g;
			}
			assert(n == 1);
			--tmp;
		}
	}
}


double sol(){
	int i,k,g;
	init();
	C = palin();
	init2();


	if(!C) return 0;

	for(i = 0; i < C; ++i){
		for(k = 0; k < N; ++k){
			g = gcd(num2[i],num[k]);
			num2[i] /= g;
			num[k] /= g;
		}
	}

	double numer,den;

	numer = den = 1;

	for(i = 0; i < C; ++i) numer *= num2[i];
	for(i = 0; i < N; ++i) den *= num[i];

	return numer/den;
}

class PalindromePermutations{
public:

	double palindromeProbability(string word){
		int i;

		N = word.length();
		for(i = 0; i < N; ++i){
			++occ[word[i]-'a'];
		}

		return sol();
	}
};
