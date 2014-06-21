
#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <cstdlib>

#define MOD ((int)(1e9+7))

using namespace std;

void sort(vector<int> &A){

    int i,j,key;

	for(i = 1; i < (int)A.size(); ++i){
		j = i;
		key = A[i];
		while(j && A[j-1] > key){	//Find the position to insert key
			A[j] = A[j-1];
			--j;
		}
		A[j] = key;
	}
}

map<vector<int>,int > F;	//We use memoization and store the values already computed.
int N,K;	//N is the number of seats, K is the number of toys


int num(vector<int> S){		//S contains the lengths of all the groups of children.
	if(S.empty())	return 1;	//If there are no children, then there is only one way.

	if((int)S.size() > K)	return 0;	//If there are more than K groups, there are no ways.

	sort(S);	/*We sort the array, because even if the groups are given in any order the answer will be same.	So, we can
	convert all the permutations of the groups to one unique permutation and can avoid a lot of wasteful recomputation.*/

	int t = F[S];	//Check if we have already computed for that S (or its permutation)
	if(t) return t;	/*If F[S] does not exits it is created and set to 0 (or default value of the mapped type). If there
	are no ways to create S, we are taking care of that previously, so we won't confuse this 0 with the no-possibilities 0.*/

	int i,j,s1,s2;
	vector<int> X;

	t = 0;

	for(i = 0; i < (int)S.size(); ++i){		//i is group where we seat the current child.
		for(j = 1; j <= S[i]; ++j){			//j is the place to seat the current child from the S[i] seats.
			s1 = j-1;	//s1 is the size of the group to the left of the seat, before this child sits.
			s2 = S[i]-j;	//s2 is the size of the group to the right.
			X = S;	//X are the sizes of all the groups before the current child sat.

			//We should'nt have any 0s in the array as they are unnecessary
			if(s1 && s2){
				X[i] = s1;
				X.push_back(s2);	/*If both are zero, the array size will increase by 1. This means the current child
				is joining two groups making them into one.*/
			}else if(s1){	//Otherwise it remains the same, which means the child is sitting on one of the endpoints of the group.
				X[i] = s1;
			}else if(s2){
				X[i] = s2;
			}else{
				X[i] = X.back();	/*If both of them are zero, the array size reduces by 1. This means the child had no
				neighbours and was thus creating a new group.*/
				X.pop_back();
			}

			t += num(X);
			t %= MOD;
		}
	}

	F[S] = t;
	return t;
}

int main(){
	scanf("%d%d",&N,&K);

	long long sol;

	sol = num(vector<int>(1,N-1));	//We count the number of ways to seat N-1 children on a line.
	sol *= N;	//The Nth child can sit into any of the N seats and join the two endpoints of the line to create a circle.
	sol %= MOD;

	printf("%lld",sol);
	return 0;
}
