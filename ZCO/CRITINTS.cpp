/*
 Created By: Malvika Joshi
 Problem: CRITINTS
 Link: http://opc.iarcs.org.in/index.php/problems/CRITINTS
*/

#include <iostream>
using namespace std;

bool Graph[300][300];
int n;

void runDFS(int u, int state[], int s, int &ct) {
      state[u] = 2;
      for (int v = 0; v < n; v++)
            if (Graph[u][v]  && state[v] == 0 && v!=s && u !=s)
                  runDFS(v, state,s,ct);
      state[u] = 1;
      ct++;
}
int DFS(int s) {
      int *state = new int[n];
      for (int i = 0; i < n; i++)
            state[i] = 0;
      int u = 0;
      if(s == 0){
    	  u = 1;
      }
      int ct = 0;
      runDFS(u, state, s, ct);
      delete [] state;
      return ct;
}




int main(){
	int m;
	cin >> n >> m;
	for(int i = 0;i < n; i++){
		for(int j = 0;j < n; j++){
			Graph[i][j] = false;
		}
	}
	for(int i = 0;i < m; i++){
		int a,b;
		cin >> a >> b;
		a--,b--;
		Graph[a][b] = true;
		Graph[b][a] = true;
	}

	int output[n];
	int count = 0;

	for(int i = 0;i < n; i++){
		int k = DFS(i);
		if(k!= n-1){
			output[count] = i+1;
			count++;
		}
	}

	cout << count << endl;
	for(int i = 0;i < count;i ++){
		cout << output[i] << endl;
	}
}
