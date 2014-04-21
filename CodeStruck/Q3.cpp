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

#define MAXP 1000010
#define POS 1000003

using namespace std;

vector<int> primes;
int comp[MAXP];

void init(){
    int i,j;

    comp[0] = comp[1] = 1;

    for(i = 2; i*i <= MAXP; ++i){
        if(comp[i]) continue;

        for(j = i*i; j < MAXP; j+=i){
            comp[j] = 1;
        }
    }

    for(i = 0; i < MAXP; ++i){
        if(comp[i]) continue;

        primes.push_back(i);
    }
}

int main(){

    int i,col_len,j;

    //freopen("triangle.out","w",stdout);

    col_len = 1;
    init();
    i = 0;
    int col = 0;

    while(i < primes.size()){
        for(j = 0; j < col_len; ++j){
            if(primes[i] == POS){
                printf("%d\n",j+1+col+1);
                return 0;
            }
            ++i;
            if(i >= primes.size()) break;
        }
        ++col_len;
        ++col;
    }

    return 0;
}
