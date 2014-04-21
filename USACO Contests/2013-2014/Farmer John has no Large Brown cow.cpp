/*
 Created By: Malvika Joshi
 Problem: Farmer John has no Large Brown cow (November-2013 Bronze)
 Link: http://www.usaco.org/index.php?page=nov13problems
*/

#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <iostream>

#define MAXN 110
#define MAXA 32

using namespace std;

int n[MAXA];        //sizes of states for each adjectives
int pos[MAXA];      // prefix product?
vector<int> exp;    //Kth cow when the list is empty

string adjec[MAXN][MAXA];   //adjectives in each of the N items on the list
int N,K,A;

map<string,int> compr[MAXA];    //adjectives sorted and mapped to a number

vector<int> nocows[MAXN];   //same as adjec but with the correspoindind number instead of the adjective

int compare(vector<int> &a, vector<int> &b){  //comparison function for std::sort
    int i;
    for(i  = 0 ; i < (int)a.size(); ++i){
        if(a[i] != b[i]) return a[i] < b[i];
    }
    return 2;
}

void isort(){
int i,k;
for(i = 1; i < N; i++){
    for (k = i; k > 0; k--)
        if(compare(nocows[k],nocows[k-1])){
            swap(nocows[k],nocows[k-1]);
        }
    }
}



void find_exp(int adj, int k){      //find the Kth possible cow

    if(adj == A-1){
        exp.push_back(k-1); //if there is just one adjecvtive, it has to be the one numbered k-1
    }

    int i;

    for(i = 0 ; i < n[adj]; i++){       //if the current adjective is one numbered i
        if(k > pos[adj]){     //if number of possibilites is less than k then skip them
            k -= pos[adj];
            continue;
        }
        exp.push_back(i);
        find_exp(adj+1,k);
        break;
    }
}

void init(){
    int i,j;

    for(i = 0; i < N; i++){
        for(j = 0; j < A; j++){
            compr[j][adjec[i][j]] = 0;      //map every adjective...
        }
    }

    for(i = 0; i < A; i++){
        j = 0;
        for(map<string,int>::iterator it = compr[i].begin(); it != compr[i].end(); ++it){
            it->second = j++;       //...to its position when sorted alphabetically
        }
        n[i] = compr[i].size();
    }

    for(i = A-1; i >= 0; --i){
        if(i == A-1){
            pos[i] = 1;
            continue;
        }
        pos[i] = pos[i+1]*n[i+1];
    }


    for(i = 0; i < N; i++){
        for(j = 0; j < A; j++){
            nocows[i].push_back(compr[j][adjec[i][j]]);     //change the strings to corresponding numbers
        }
    }
}

int main(){
    int i,j;
    string temp;

    scanf("%d%d",&N,&K);

    for(i = 0; i < N; i++){
        j = 0;
        do {
            cin >> temp;
        } while(temp != "no");      //the strings after no are the adjectives

        cin >> temp;
        while(temp != "cow."){      //cow. is the end of input line
            adjec[i][j++] = temp;
            cin >> temp;
        }
    }

    A = j;

    init();
    //sort(nocows,nocows+N,compare);      //sort the list
    isort();
    find_exp(0,K);

    for(i = 0; i < N; i++){
        if(compare(nocows[i],exp)){    //if there is a list item less than the current cow the increment it
            ++exp[A-1];
            if(exp[A-1] < n[A-1]) continue;
            j = A-1;
            while(exp[j] >= n[j]){
                if(!j) return 0;        //no solution possible
                exp[j] = 0;
                ++exp[--j];         //carry forward
            }
            continue;
        }
        break;      //no remaining list items are less than the current cow
    }

    for(i = 0; i < A; i++){
        for(map<string,int>::iterator it = compr[i].begin(); it != compr[i].end(); ++it){
            if(it->second < exp[i]) continue;
            cout << it->first;       //print the string corresponding to the numbers
            if(i < A-1) cout << " ";
            break;
        }
    }

    cout << "\n";
    return 0;
}
