/*
 Created By: Malvika Joshi
 Problem: And how! (IOITC-2013 Final 2)

 Instead of trying to find all elements at once, we can find them one by one. To find one element which is used in the computation
 of Ä, we can binary search for it. We query one half of the array, if setting all the elements not yet found to false causes Ä to
 return false then we can discard the other half, otherwise we discard that half, and continue searching on the remaining part of the
 array. In the end we will find a new element which is used in the computation of Ä. It can happen that the element does not lie in any
 of the halves, which means we have found all the elements. To prevent having to query both the halves, we can query the entire array
 at the beginning of the search.
 This will take log(N)+1 queries for each of the K elements in the worst case, which is a total of K*(log(N)+1) queries.
 This will work only upto the fourth subtask (75%) where there will be 20*(log(10000)+1) = 20*15 = 300 queries in the worst case.
*/

#include <cassert>
#include <cstring>

using namespace std;

#define MAX_N 10000

bool query(const bool *);	//The library function
bool q[MAX_N];	//The array to pass into query()
bool sel[MAX_N];	//Denotes whether an element is used in computing Ä or not. Initially everything is false.

void fill(int s, int e, bool val){	//To set a block of contiguous elements.
	for(;s <= e;++s)  q[s] = val||sel[s]; /*If that element is already found, we set it to true, because otherwise it will always cause
	the query function to return false.*/
}

int search(int N){		//Returns a new element used in computing Ä or -1, if all the elements are found.

	int low,high,mid;

	fill(0,N-1,false);
	if(query(q))  return -1;	//If setting the remaining elements to false causes query to return true, then we are done.

	low = 0;	//The beginning of the current array
	high = N-1;	//The end of the current array

	while(low < high){
		mid = (low+high)/2;	//The midpoint of the current array

		fill(low,high,true);	//Initially everything in the array is set to true.
		fill(low,mid,false);	//Set one half of the array to false.

		if(query(q)){	//If the query still returns true, then there are no elements in that part
			low = mid+1;	//So we discard the first half.
		}else{
			high = mid;	//Otherwise it there is atleast one element not yet found in the first half, so we discard the rest.
		}
	}

	return low;	//In the end both high and low will be pointing to the new element used in computing Ä.
}


void solve(int N, bool *ans){

	assert(N <= MAX_N);		//This works only upto the fourth subtask.

	int i;

	for(i = search(N); i != -1; i = search(N)){	//We keep on invoking search() until it returns -1
		sel[i] = true;	//And mark the element returned as 'selected'.
	}

	memcpy(ans,sel,sizeof(bool)*N);		//Copy the sel array into ans
}
