/*
 Created By: Malvika Joshi
 Problem: MEDUVADA
 Link: http://opc.iarcs.org.in/index.php/problems/MEDUVADA
*/

#include <stdio.h>

void printmaze();
void printpath();
void dfs(int,int);

int M,N;
int maze[1001][1001];
int savemaze[1001][1001];

int mx,my,dx,dy;
int left='l';
int right='r';
int up='u';
int down='d';
int beg='b';
int blank='.';
int done=0;
int found=0;

int answer=0;

char buf[100];

int main() {


	int i,j;

	scanf("%d %d", &M, &N);
	getchar();
	for (i=1;i<=M;i++) {
		for (j=1;j<=N;j++) {
			maze[i][j]=getchar();
			savemaze[i][j]=maze[i][j];
      		switch (maze[i][j]) {
				case 'M': mx=i;
					  my=j;
					  break;
				case 'D': dx=i;
					  dy=j;
					  break;
			}
		}

		getchar();  /* Skip the new line */
	}

	maze[mx][my]=beg;
	dfs(mx,my);
	if (done) answer=1;

  printpath();

}

int cdec(int i) {
	if (i>1) return (i-1);
	return N;
}

int rdec(int i) {
	if (i>1) return (i-1);
	return M;
}

int cinc(int i) {
	if (i<N) return (i+1);
	return 1;
}

int rinc(int i) {
	if (i<M) return (i+1);
	return 1;
}

int unvisited(int i,int j) {
	if ((maze[i][j]==blank)||(maze[i][j]=='D')) return 1;
	else return 0;
}

void dfs(int cx,int cy) {

    if (done) return;

	if ((cx==dx)&&(cy==dy)) {
		done=1;
		return;
	}
	if (unvisited(rdec(cx),cy)) {
		maze[rdec(cx)][cy]=down;
		dfs(rdec(cx),cy);
	}
	if (unvisited(rinc(cx),cy)) {
		maze[rinc(cx)][cy]=up;
		dfs(rinc(cx),cy);
	}
	if (unvisited(cx,cdec(cy))) {
		maze[cx][cdec(cy)]=right;
		dfs(cx,cdec(cy));
	}
	if (unvisited(cx,cinc(cy))) {
		maze[cx][cinc(cy)]=left;
		dfs(cx,cinc(cy));
	}
}
void printpath() {
	int cx,cy;
	int tx,ty;
	if (done) printf("YES\n");
	else printf("NO\n");
	if (done) {
		cx=dx;
		cy=dy;
		while ((cx!=mx) || (cy!=my)) {
			tx=cx;ty=cy;
			if (maze[cx][cy]==left) cy=cdec(cy);
			else if (maze[cx][cy]==right) cy=cinc(cy);
			else if (maze[cx][cy]==up) cx=rdec(cx);
			else if (maze[cx][cy]==down) cx=rinc(cx);
			maze[tx][ty]='x';
		}
		maze[dx][dy]='D';
		printmaze();
	}
}



void printmaze() {
	int i,j;

	for (i=1;i<=M;i++) {
		for (j=1;j<=N;j++)  {
			switch (maze[i][j]) {
				case 'd':
				case 'u':
				case 'r':
				case 'l': putchar('.');
					  break;
				case 'b': putchar('M');
					  break;
				default:  putchar(maze[i][j]);
			}
		}
		printf("\n");
	}

}
