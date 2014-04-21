/*
 Created By: Malvika Joshi
 Problem: heritage
 Link: http://cerberus.delos.com:791/usacoprob2?S=heritage&a=ooa9E43NmTps
*/

#include <stdio.h>
#include <string.h>

#define maxN 30

typedef struct {
	int left,right,parent;
}node;

node tree[30];
int Q[30];
int H =0;

void init_tree(){
	int i;
	for(i = 0;i < maxN;i++){
		tree[i].left = -1;
		tree[i].right = -1;
		tree[i].parent = -1;
	}
}

int find(int *A,int n,int x){
	int i;
	for(i = 0; i < n; i++){
		if(A[i] == x){
			return i;
		}
	}
	return -1;
}

int get_tree(int *A, int n){
	if(n == 0) return -1;
	int root = Q[H++],k;

	k = find(A,n,root);
	tree[root].left = get_tree(A,k);
	tree[root].right = get_tree(&A[k+1],n-k-1);

	return root;
}

void post_order(int root){
	if(root == -1) return;

	post_order(tree[root].left);
	post_order(tree[root].right);
	printf("%c",root+'A');
}

int main(){
	int A[30];
	int n,i;
	char str[30];

	scanf("%s",str);
	n = strlen(str);

	for(i = 0;i < n; i++){ A[i] = str[i]-'A'; }

	scanf("%s",str);

	for(i = 0;i < n; i++){ Q[i] = str[i]-'A'; }

	int root = get_tree(A,n);

	post_order(root);
	printf("\n");

	return 0;
}
