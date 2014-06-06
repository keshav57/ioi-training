#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstring>

#define NMAX 1000010

using namespace std;

int order[NMAX];
int rev[NMAX];

int N;

pair<int,int> ranges[NMAX];
pair<int,int> add[NMAX];
int R;

int is_pos(int K, int *perm){
	int i,s1,e1,inc;

	i = 0;
	s1 = (perm[i]-K+N)%N;
	e1 = (perm[i]+K)%N;

	R = 0;
	ranges[R++] = make_pair(s1,e1);

	int k;

	for(i = 1; i < N; ++i){
		inc = 0;
		for(k = 0; k < R; ++k){
			int &s = ranges[k].first;
			int &e = ranges[k].second;
			s1 = (perm[i]-K+N)%N, e1 = (perm[i]+K)%N;
			s = (s+1)%N,e = (e+1)%N;

			if(s > e && s1 > e1){
				e = min(e,e1);
				s = max(s,s1);
				continue;
			}

			if(s <= e && s1 <= e1){
				e = min(e,e1);
				s = max(s,s1);
				if(s > e){
					swap(ranges[R-1],ranges[k]);
					--R;
					--k;
				}
				continue;
			}

			if(s1 > e1){
				swap(s,s1);
				swap(e,e1);
			}

			assert(s1 <= e1);

			if(e1 >= s && s1 <= e){
				add[inc++] = make_pair(s1,e);
				ranges[k] = make_pair(s,e1);
				continue;
			}

			if(e1 >= s){
				s = max(s1,s);
				e = e1;
				continue;
			}

			if(s1 <= e){
				s = s1;
				e = min(e,e1);
				continue;
			}

			swap(ranges[R-1],ranges[k]);
			--R;
			--k;
		}

		while(inc--) ranges[R++] = add[inc];
		if(!R) return 0;
	}

	return 1;
}

int search(){
	int low,high,mid;

	low = 0;
	high = (N)/2;


	while(low < high){
		mid = (low+high)/2;
		if(is_pos(mid,order) || is_pos(mid,rev)){
			high = mid;
		}else{
			low = mid+1;
		}
	}

	return low;
}

int get_cost(int *perm){
	int i,m;

	m = 0;
	for(i = 0; i < N; ++i){
		m = max(m,min(abs(perm[i]-i),N-abs(perm[i]-i)));
	}

	return m;
}

int main(){
	int i;

	scanf("%d",&N);

	for(i = 0; i < N; ++i){
		scanf("%d",&order[i]);
		--order[i];
		rev[N-i-1] = order[i];
 	}

	printf("%d\n",search());
//
//	int tmp = search();
//
//	int sol,t1,t2;
//	sol = N;
//	for(i = 0; i <= N; ++i){
//		sol = min(sol,get_cost(order));
//		sol = min(sol,get_cost(rev));
//
//		t1 = order[N-1];
//		t2 = rev[N-1];
//
//		for(int k = N-1; k ; --k){
//			order[k] = order[k-1];
//			rev[k] = rev[k-1];
//		}
//
//
//		order[0] = t1;
//		rev[0] = t2;
//	}

//
//	if(sol != tmp){
//		sol /= 0;
//	}
//	cout << sol << endl;
//
//	cout << is_pos(3,rev) << endl;;
//	cout << is_pos(4,rev) << endl;;

	return 0;
}
