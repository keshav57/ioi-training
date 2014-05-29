#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <map>
#include <utility>
#include <cassert>

#define NMAX 52
#define TYP 12
#define ROT 64

using namespace std;

struct cube{
	int x,y,z;

	void rotate_z(){
		swap(x,y);
		x = -x;
	}

	void rotate_x(){
		swap(y,z);
		y = -y;
	}

	void rotate_y(){
		swap(x,z);
		z = -z;
	}
};

typedef vector<cube> block;
typedef vector<int> group;

block all[TYP+2][ROT+2];
block start[TYP+2];

void create_blocks(){
	int xr,yr,zr,i,k,c;

	for(i = 0; i < TYP; ++i){

		k = 0;
		for(xr = 0; xr < 4; ++xr){
			for(yr = 0; yr < 4; ++yr){
				for(zr = 0; zr < 4; ++zr){

					all[i][k++] = start[i];

					for(c = 0; c < (int)start[i].size(); ++c){
						start[i][c].rotate_z();
					}
				}

				for(c = 0; c < (int)start[i].size(); ++c){
					start[i][c].rotate_y();
				}
			}

			//comes back to the start
			for(c = 0; c < (int)start[i].size(); ++c){
				start[i][c].rotate_x();
			}
		}

		assert(k == ROT);
	}

}

int id[10][10][10];
group groups[NMAX][TYP*ROT+2];
int typ[NMAX][TYP*ROT+2];
int n[NMAX];

cube pos[NMAX];
int N;

void create_groups(){
	int i,b,k,dx,dy,dz,st,j,v;

	for(i = 0; i < N; ++i){
		for(b = 0; b < TYP; ++b){

			for(k = 0; k < ROT; ++k){

				for(st = 0; st < (int)all[b][k].size(); ++st){
					dx = pos[i].x-all[b][k][st].x;
					dy = pos[i].y-all[b][k][st].y;
					dz = pos[i].z-all[b][k][st].z;

					for(j = 0; j < (int)all[b][k].size(); ++j){
						v = id[all[b][k][j].x+dx][all[b][k][j].y+dy][all[b][k][j].z+dz];
						if(v < 0) break;
						groups[i][n[i]].push_back(v);
					}

					if(j < (int)all[b][k].size()){
						groups[i][n[i]].clear();
						continue;
					}

					typ[i][n[i]] = b;
					++n[i];
				}
			}
		}
	}
}

int sol[NMAX];
int S;

int V;
long long int rem;
int D;

map<long long, int> vis;
int M;

long long next[1000000];
int next_typ[1000000];
int bl[1000000];

int dfs(int i){
	if(M >= 1000000) return N;

	int k,j,cur;
	map<long long , int>::iterator it;

	if(D+(V+1)/4 >= S) return N;

	it = vis.find(rem);
	if(it != vis.end()){
		S = min(S,bl[it->second]+D);
		return bl[it->second];
	}

	if(rem&(1LL<<i)) return dfs(i+1);

	vis[rem] = M++;
	cur = M-1;
	next_typ[cur] = -1;
	next[cur] = -1;
	bl[cur] = N+1;

	if(!V){
		S = min(S,D);
		bl[cur] = 0;
		return 0;
	}

	int tmp;

	for(k = n[i]-1; k >= 0; --k){
		for(j = 0; j < (int)groups[i][k].size(); ++j){
			if(rem&(1LL<<groups[i][k][j])) break;
		}
		if(j < (int)groups[i][k].size()) continue;

		for(j = 0; j < (int)groups[i][k].size(); ++j){
			rem |= (1LL<<groups[i][k][j]);
			--V;
		}
		++D;
		tmp = 1+dfs(i+1);

		if(tmp < bl[cur]){
			bl[cur] = tmp;
			next[cur] = rem;
			next_typ[cur] = typ[i][k];
		}

		--D;
		for(j = 0; j < (int)groups[i][k].size(); ++j){
			rem ^= (1LL<<groups[i][k][j]);
			++V;
		}
	}

	return bl[cur];
}

int main(){
	int i,sz,t;
	cube c;

	memset(id,-1,sizeof(id));
	FILE *r = fopen("TYPES.IN","r");

	for(i = 0; i < TYP; ++i){
		fscanf(r,"%d%d",&t,&sz);
		--t;
		assert(i == t);
		while(sz--){
			fscanf(r,"%d%d%d",&c.x,&c.y,&c.z);
			start[t].push_back(c);
		}
	}

	scanf("%d",&N);

	for(i = 0; i < N; ++i){
		scanf("%d%d%d",&pos[i].x,&pos[i].y,&pos[i].z);
		id[pos[i].x][pos[i].y][pos[i].z] = i;
	}

	create_blocks();
	create_groups();
	S = N;
	V = N;
	dfs(0);

	printf("%d\n",bl[0]);

	long long v;
	v = 0;

	while(v >= 0){
		v = vis[v];
		if(next[v] < 0) break;
		printf("%d ",next_typ[v]+1);
		v = next[v];
	}
	printf("\n");

	return 0;
}
