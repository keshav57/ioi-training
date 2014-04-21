/*
 Created By: Malvika Joshi
 Problem: METRO
 Link: http://opc.iarcs.org.in/index.php/problems/METRO
*/

#include <stdio.h>
#include <limits.h>
#define inf INT_MAX;

typedef struct {int x,y;}vertex;

int Sr[100];
int Sc[100];
char Tr[100];
char Tc[100];
vertex Q[30000];
int M,N;
int D[100][100];

int extract_min(int H, int T){
        int min,i;
        min = H;
        for(i = H+1; i <= T; i++){
                if(D[Q[min].x][Q[min].y] > D[Q[i].x][Q[i].y]){
                        min = i;
                }
        }
        return min;
}

int get_time(int sta,int mint,int stime,char type,int n){
        int gap,r,s,time,n2;

        if(type == 'S' || type == 's'){ gap = 3;}
        else if(type == 'F' || type == 'f'){gap = 1; }
        else if(type == 'O' || type == 'o'){gap = 2;}

        r = (sta*gap)+stime;
        s = mint - r;
        if(s < 0){
                return r;
        }

        n2 = (n*2)-2;

        n2 = n2 * gap;

        time = s/n2;
        time++;

        time = time*n2 + r;
        return time;
}

void relax(int i,int j){
        int time,v2;
        if(i+1 < M){
                time = get_time(i+1,D[i][j],Sc[j],Tc[j],M);
                if(D[i+1][j] > time){
                        D[i+1][j] = time;
                }
        }
        if(i-1 >= 0){
                if(i-1 == 0){
                        time = get_time(i-1,D[i][j],Sc[j],Tc[j],M);
                }else{
                        v2 = M-1 + (M-i);
                        time = get_time(v2,D[i][j],Sc[j],Tc[j],M);
                }
                if(D[i-1][j] > time){
                        D[i-1][j] = time;
                }
        }

        if(j+1 < N){
                time = get_time(j+1,D[i][j],Sr[i],Tr[i],N);
                if(D[i][j+1] > time){
                        D[i][j+1] = time;
                }
        }

        if(j-1 >= 0){
                if(j-1 == 0){
                        time = get_time(j-1,D[i][j],Sr[i],Tr[i],N);
                }else {
                        v2 = N-1 + (N-j);
                        time = get_time(v2,D[i][j],Sr[i],Tr[i],N);
                }
                if(D[i][j-1] > time){
                        D[i][j-1] = time;
                }
        }
}

int main(void){

        int i,j,s1,s2,st,d1,d2;
        scanf("%d%d",&M,&N);

        for(i = 0;i < M;i++){
                scanf("\n%c %d",&Tr[i],&Sr[i]);
        }

        for(j = 0;j < N;j ++){
                scanf("\n%c %d",&Tc[j],&Sc[j]);
        }

        scanf("%d%d%d%d%d",&s1,&s2,&st,&d1,&d2);

        for(i  = 0;i < M; i++){
                for(j = 0;j < N; j++){
                        D[i][j] = inf;
                }
        }

        D[s1-1][s2-1] = st;

        int H = 0, T = 0;

        for(i = 0;i < M;i++){
                for(j  = 0;j < N; j++){
                        Q[T].x = i;
                        Q[T].y = j;
                        T++;
                }
        }

        while(H < T){
                i = extract_min(H,T);
                relax(Q[i].x,Q[i].y);
                Q[i] = Q[H];
                H++;
        }

        printf("%d\n",D[d1-1][d2-1]);

        return 0;
}
