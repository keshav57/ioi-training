/*
 Created By: Malvika Joshi
 Problem: ENDCORR
 Link: http://opc.iarcs.org.in/index.php/problems/ENDCORR
*/

#include <iostream>

using namespace std;
void remove_root(int*, int);
void add_element(int, int*, int);

int main(){

	int N,M;
	int k;

	cin >> N >> M;
	int wealth[N];

	for(int i =0 , c =0;i < M+N;i ++){
			cin >> k;
			if(k != -1){
			add_element(k , wealth, c);
			c++;
		}else{
		cout << wealth[0] << endl;
		remove_root(wealth , c+1);
		--c;
		}
	}
	return 0;
}

int get_left(int i){
	return ((i << 1) + 1);
}

int get_right(int i){
	return ((i << 1) + 2);
}

int get_parent(int i){
	return ((i - 1) >> 1);
}

void swap(int &a, int &b){
	int c = a;
	a = b;
	b = c;
}

int swap_with_child(int i, int *heap, int size){
	int left = get_left(i);
	int right = get_right(i);
	int largest = i;

	if(right < size){
		if(heap[left] < heap[right]){
			largest = right;
		} else {
			largest = left;
		}
		if (heap[i] > heap[largest]){
			largest = i;
		}
	} else if (left < size){
		if (heap[i] > heap[left]){
			largest = left;
		}
	}

	if(heap[i] < heap[largest]){
		swap(heap[i] , heap[largest]);
	}
	return largest;
}

int swap_with_parent(int i, int *heap){
	if(i < 1){
		return 0;
	}
	int parent = get_parent(i);
	if(heap[i] > heap[parent]){
		swap(heap[i], heap[parent]);
		return parent;
	} else {
		return i;
	}
}

void add_element(int new_entry , int *heap , int size){
	heap[size] = new_entry;
	int i = swap_with_parent(size, heap);
	while ( size != i){
		size = i;
		i = swap_with_parent(i , heap);
	}
}

void remove_root(int *heap, int size){
	heap[0] = heap[size-1];
	--size;
	int index = 0;
	int i = swap_with_child(0, heap, size);
	while (i != index){
		index = i;
		i = swap_with_child(i , heap, size);
	}
}



