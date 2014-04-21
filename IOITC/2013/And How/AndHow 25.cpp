/*
 Created By: Malvika Joshi
 Problem: And how! (IOITC-2013 Final 2)

 If the complete array is set to true then the function ÄÊwill always return true because the subset of values used in computing Ä
 will be set to true as well. If setting an element to false causes Ä to return false then the element is used to compute Ä otherwise
 it is not.	We test for all elements by setting them to false and querying. This will take N calls (works only for the first subtask (10%)).
 Instead we can group sqrt(N) elements together and then query for each block by setting the entire block to false. If Ä returns true
 then we can discard the block as none of the elements in the block are used in computing Ä. Otherwise we do the previous test for
 every element in the block. As there can be atmost K elements used in computing Ä, we will have to do the brute-force test for only
 atmost K blocks and K*sqrt(N) elements. So the total number of calls will be sqrt(N) + K*sqrt(N).
 For the first subtask, total number calls in the worst case: 18 + 16*17 = 290 calls.
 For the second subtask: 30 + 9*30 = exactly 300 calls.
 So this works only for the first two subtasks (25%).
*/

#include <cassert>

#define MAX_N 900
#define SQRT_N 30

using namespace std;

bool query(const bool *);	//The library query function
bool q[MAX_N];		//The array to pass into query()

void set(int s, int e, bool val){	//To set a block of elements in q
	for(;s < e; ++s) q[s] = val;
}

void solve(int N, bool *ans){

	assert(N <= MAX_N);		//Works only the first two subtasks,

	int i,j,s;
	bool sel;

	set(0,N,true);	//Initialize q to true.
	i = s = 0;		//i will denote the end of the block, s will denote the start.

	while(i < N){
		for(j = 0; j*j < N && i < N; j++,i++); //The size of the block is aprrox sqrt(N).

		set(s,i,false);
		sel = !(query(q)); /*If setting the block to false causes the query to return false
		The the block is selected, otherwise it is not.*/
		set(s,i,true);

		for(;s < i; s++){
			if(!sel){
				ans[s] = false; //If the whole block is not selected then nothing inside the block is selected.
				continue;
			}

			q[s] = false;
			ans[s] = !(query(q)); //Otherwise we check for individual elements.
			q[s] = true;
		}
	}

}
