/*
 Created By: Malvika Joshi
 Problem: RANK;
 Link: http://opc.iarcs.org.in/index.php/problems/RANK
*/

#include <iostream>
using namespace std;

int main(void){

int N;
cin >> N;
int merchants_wealth[N];
for(int i = 0;i < N; i++){
    cin >> merchants_wealth[i];
}

for(int j = 0; j < N; j++){
        int key = merchants_wealth[j];
        int i = j-1;

    while(i + 1 > 0 && merchants_wealth[i] < key){
        merchants_wealth[i+1] = merchants_wealth[i];
        --i;
        }
        merchants_wealth[i+1] = key;
        cout << i+2 << endl;
}

    return 0;

}
