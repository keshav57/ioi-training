/*
 Created By: Malvika Joshi
 Problem: Scrambled Letters (December-2012 Bronze)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=206
*/

#include <stdio.h>
#include <string>
#include <string.h>
#include <algorithm>

using namespace std;

string worst[50000];
string best[50000];
string max_l[50000];
string min_l[50000];
int N;

int worst_search(string target){
	int low,mid,high;
	low = 0;
	high = N-1;

	while(low <= high){
		mid = low + (high-low)/2;
		if(worst[mid] < target){
			low = mid+1;
		}else{
			high = mid-1;
		}
	}

	return low;
}

int best_search(string target){
	int low,mid,high;
	low = 0;
	high = N-1;

	while(low <= high){
		mid = low + (high-low)/2;
		if(best[mid] <= target){
			low = mid+1;
		}else{
			high = mid-1;
		}
	}

	return low;
}
int main(){

	int i;
	char name[20];
	string str;

	scanf("%d" , &N);

	for(i = 0;i < N;i ++){
		scanf("%s", name);
		str = name;
		sort(str.begin(),str.end());
		min_l[i] = str;
		best[i] = str;
		str = string ( str.rbegin(), str.rend() );
		max_l[i] = str;
		worst[i] = str;
	}

	sort(best,best+N);
	sort(worst,worst+N);

	for(i = 0;i < N;i ++){
		printf("%d ", worst_search(min_l[i])+1);
		printf("%d\n", best_search(max_l[i]));
	}

	return 0;
}

/*
  a b c f m


 */


