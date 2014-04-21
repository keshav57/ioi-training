/*
 Created By: Malvika Joshi
 Problem: Record Keeping (December-2013 Bronze)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=358
*/


#include <string>
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <cstdio>

using namespace std;

map <vector<string> , int> occ;
int N;

int main(){
    int i,k;
    vector<string> group;
    group.resize(3);

    cin >> N;
    for(i = 0; i < N; ++i){
        for(k = 0; k < 3; ++k) cin >> group[k];
        sort(group.begin(),group.end());
        occ[group]++;
    }

    int maxocc;

    maxocc = 0;
    for(map<vector<string> ,int>::iterator it = occ.begin(); it != occ.end(); ++it){
        maxocc = max(maxocc,it->second);
    }

    cout << maxocc << "\n";

    return 0;
}
