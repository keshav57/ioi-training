/*
 Created By: Malvika Joshi
 Problem: Perimeter (February-2013 Silver)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=244
*/

#include <stdio.h>
#include <set>

std::set<std::pair<int,int> > points,visited;
int perimeter;

int isempty(int x, int y){
	int i,j;
	for(i = -1;i < 2;i ++){
		for(j = -1;j < 2; j++){
			if(points.count(std::make_pair(x+i,y+j))){
				return 0;
			}
		}
	}
	return 1;
}

void fill(int x, int y){
	if(isempty(x,y)){ return; }
	if(visited.count(std::make_pair(x,y))){ return; }

	if(points.count(std::make_pair(x,y))){
		perimeter++;
		return;
	}

	visited.insert(std::make_pair(x,y));

	fill(x,y+1);
	fill(x+1,y);
	fill(x-1,y);
	fill(x,y-1);
}

int main(){

	int n,i,x,y;

	freopen("perimeter.in","r",stdin);
	freopen("perimeter.out","w",stdout);

	scanf("%d",&n);

	for(i = 0;i < n; i++){
		scanf("%d%d",&x,&y);
		points.insert(std::make_pair(x,y));
	}

	fill(points.begin()->first-1,points.begin()->second);

	printf("%d",perimeter);

	return 0;

}
