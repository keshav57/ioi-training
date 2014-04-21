/*
 Created By: Malvika Joshi
 Problem: buylow
 Link: http://cerberus.delos.com:791/usacoprob2?a=OvvJ4ufeu8C&S=buylow
*/

#include <stdio.h>
#include <map>
#include <limits.h>

int price[5000];
int A[5000];
int length[5000];
int N;
int visited[200000] = {0};

struct bignum{
	int dig[200];
	int n;
	bignum();
	bignum operator + (bignum);
};

bignum::bignum(){
	n = 0;
	int i;
	for(i = 0;i < 200; i++) dig[i] = 0;
}

bignum bignum::operator+(bignum param){
	bignum c;
	int i,carry = 0;
	int max = param.n > n ? param.n : n;
	for(i = 0; i < max; i++){
		c.dig[i] = param.dig[i] + dig[i] + carry;
		carry = 0;
		if(c.dig[i] >= 10){
			c.dig[i] -= 10;
			carry = 1;
		}
	}

	c.n = i;
	if(carry) c.dig[c.n++] = carry;

	return c;
}
bignum total[5000];

int bin_search(int target,int n){

	int low,high,mid;
	low = 0;
	high = n-1;

	while(low <= high){
		mid = low + (high-low)/2;
		if(A[mid] > target){
			low = mid+1;
		}else{
			high = mid-1;
		}
	}

	return low;
}

int main(){
	int i,k,n;

	scanf("%d",&N);

	i = 0;
	bignum count;
	n = 0;
	int j;

	count.n =0;
	count.dig[0] = 0;

	while(i < N){
		scanf("%d",&price[i]);
		visited[price[i]] = 0;
		k = bin_search(price[i],n);
		A[k] = price[i];
		if(k == n)	n++;
		length[i] = k+1;
		i++;
	}

	for(i = 0;i < N; i++){
		if(length[i] == 1){
			total[i].dig[0] = 1;
			total[i].n = 1;
		}
		else{
			total[i].dig[0] = 0;
			total[i].n = 0;
			for(j = i-1; j >= 0;j --){
				if(price[j] > price[i] && length[j] == length[i]-1 && !visited[price[j]]){
					total[i] = total[i] +total[j];
					visited[price[j]] = 1;
				}
			}
			for(j = i-1; j >= 0;j --){
			visited[price[j]] = 0;
			}
		}

	}

	for(i = N-1;i >= 0; i-- ){
		if(visited[price[i]]) continue;
		visited[price[i]] = 1;
		if(length[i] == n) count = count + total[i];
	}

	printf("%d ",n);
	for(i = count.n-1;i >= 0; i--){
		printf("%d",count.dig[i]);
	}
	printf("\n");

	return 0;
}
