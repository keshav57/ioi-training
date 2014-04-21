/*
User ID: 34114
Team ID: CSWC1223
Email: castusmail@gmail.com
*/

#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <map>
#include <set>
#include <utility>

#define MOD 1000000007

#define MINRED 2300
#define MINBLUE 1100
#define MINGREEN 2700

#define N 10000

using namespace std;

int choose[N+2][N+2];

void init(){
    int i,k;

    choose[0][0] = 1;

    for(i = 1; i <= N; ++i){
        choose[i][0] = 1;
        for(k = 1; k <= i; ++k){
            choose[i][k] = choose[i-1][k] + choose[i-1][k-1];
            choose[i][k] %= MOD;
        }
    }
}

int main(){
    int red,blue;
    long long tmp;
    int pos;

    init();

    pos =0;

    for(red = MINRED; (red+MINBLUE+MINGREEN) <= N; ++red){
        for(blue = MINBLUE; (red+blue+MINGREEN) <= N; ++blue){
            tmp = choose[N][red];
            tmp *= choose[N-red][blue];
            tmp %= MOD;
            pos += tmp;
            pos %= MOD;
        }
    }

    printf("%d\n",pos);

    return 0;
}
