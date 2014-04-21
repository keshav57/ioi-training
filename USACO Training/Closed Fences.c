/*
 Created By: Unknown
 Problem: fence4
 Link: http://cerberus.delos.com:791/usacoprob2?a=61KMSqSZrhc&S=fence4
*/

#include <stdio.h>

int N;
double pts[201][2];
double vx,vy;
int can_see[201] = {0};

int get_side(double sx, double sy, double ex, double ey, int p){
	double dx,dy,px,py,t;
	dx = ex-sx;
	dy = ey-sy;

	px = pts[p][0]-sx;
	py = pts[p][1]-sy;

	t = dx*py-dy*px;

	if(t > 0.00001) return 0;
	if(t < -0.00001) return 1;
	return 2;
}

int first_ints(double sx, double sy, double ex, double ey){
	int k,s1,s2,t1,t2,mloc;
	double ax,ay,bx,by,t,cof,cst,i,j,x,y,lbr,rbr,min;

	min = 1e10;
	mloc = N;

	lbr = rbr = 1e10;

	for(k = 0; k < N; k++){
		ax = pts[k][0];
		ay = pts[k][1];
		bx = pts[k+1][0];
		by = pts[k+1][1];

		t = (ex-sx) * (ay-by) - (ey-sy) * (ax-bx);

		if(t > -0.00001 && t < 0.00001) continue;

		cst = (ax-sx) * (by-ay) - (ay-sy)*(bx-ax);
		cof = (ex-sx) * (by-ay) - (ey-sy)*(bx-ax);

		if(cof > -0.00001 && cof < 0.00001) {
			if(bx - ax > -0.00001 && bx-ax < 0.00001){
				cst = ax-sx;
				cof = ex-sx;
			}else{
				cst = ay-sy;
				cof = ey-sy;
			}
		}

		j = cst/cof;

		if(j < -0.00001) continue;

		cst = sx + (ex-sx) * j - ax;
		cof = bx - ax;

		if(cof > -0.00001 && cof < 0.00001){
			cst = sy + (ey -sy) * j - ay;
			cof = by - ay;
		}

		i = cst/cof;

		if(i < -0.00001 || i > 1.00001) continue;

		x = ax + (bx-ax) * i;
		y = ay + (by-ay) * i;

		t = (x-sx) * (ex-sx) + (y-sy) * (ey-sy);

		if(t < -0.00001 || t > min) continue;

		if(i < 0.00001 || i > 0.99999){
			if(i < 0.00001){
				t1 = k-1;

				if(t1 < 0) t1 += N;

				t2 = k+1;
			}else{
				t1 = k;
				t2 = k+2;

				if(t2 >= N) t2 -= N;
			}

			s1 = get_side(sx,sy,ex,ey,t1);
			s2 = get_side(sx,sy,ex,ey,t2);

			if(s1 == s2){
				if(s1 == 0 && t < lbr) lbr = t;
				if(s1 == 1 && t < rbr) rbr = t;

				continue;
			}
		}

		min = t;
		mloc = k;

	}

	if(min > lbr && min > rbr) return N;

	return mloc;
}

int do_intersect(int f1, int f2){

	double sx,sy;
	double ex,ey;

	sx = pts[f1][0];
	sy = pts[f1][1];
	ex = pts[f1+1][0];
	ey = pts[f1+1][1];

	if(get_side(sx,sy,ex,ey,f2) == get_side(sx,sy,ex,ey,f2+1)) return 0;

	sx = pts[f2][0];
	sy = pts[f2][1];
	ex = pts[f2+1][0];
	ey = pts[f2+1][1];

	if(get_side(sx,sy,ex,ey,f1) == get_side(sx,sy,ex,ey,f1+1)) return 0;

	return 1;
}

int main(){

	int i,j,count;

	scanf("%d",&N);
	scanf("%lf %lf",&vx,&vy);

	for(i = 0;i < N; i++){
		scanf("%lf %lf",&pts[i][0],&pts[i][1]);
	}

	pts[N][0] = pts[0][0];
	pts[N][1] = pts[0][1];

	for(i = 0;i < N; i++){
		for(j = i+2;j < N; j++){
			if(do_intersect(i,j)){
				if(i == 0 && j == N-1) continue;
				printf("NOFENCE\n");
				return 0;
			}
		}
	}

	for(i = 0;i < N; i++){
		can_see[first_ints(vx,vy,pts[i][0],pts[i][1])] = 1;
		can_see[first_ints(vx,vy,(pts[i][0]+pts[i+1][0])*0.5,(pts[i][1] + pts[i+1][1]) * 0.5)] = 1;
	}

	count = 0;

	for(i = 0;i < N; i++){
		count += can_see[i];
	}

	printf("%i\n",count);

	for(i = 0;i < N-2; i++){
		if(can_see[i]){
			printf("%.0f %.0f %.0f %.0f\n",pts[i][0],pts[i][1],pts[i+1][0],pts[i+1][1]);
		}
	}

	if(can_see[N-1]){
		printf("%.0f %.0f %.0f %.0f\n",pts[0][0],pts[0][1],pts[N-1][0],pts[N-1][1]);
	}

	if(can_see[N-2]){
		printf("%.0f %.0f %.0f %.0f\n", pts[N-2][0],pts[N-2][1],pts[N-1][0],pts[N-1][1]);
	}
	return 0;
}
