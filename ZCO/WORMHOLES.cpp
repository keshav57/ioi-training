/*
 Created By: Malvika Joshi
 Problem: WORMHOLES
 Link: http://www.iarcs.org.in/zco2013/index.php/problems/WORMHOLES
*/

#include <iostream>
using namespace std;

int seq[100000];

int main(){

        int n,i;
        cin >> n;

        for(i = 0;i < n; i++){
                cin >> seq[i];
        }

        int maxd = 0;
        int fpd = 0;
        int open = 0;

        for(int i = 0;i < n ;i ++){
                if(seq[i] == 1){
                        open++;
                        if(open > maxd){
                                maxd = open;
                                fpd = i;
                        }
                }else{
                        open--;
                }
        }


        cout << maxd << " " << fpd+1 << " ";

        int max = 0;
        int fp = 0;

        for(i = 0;i < n;i++){
                int cur = i;
                int j = 1;
                int count = 1;
                while(j > 0 && i < n-1){
                        count++;
                        i++;
                        if(seq[i] == 1){
                                j++;
                        }else {
                                j--;
                        }
                }
                if(count > max){
                        max = count;
                        fp = cur;
                }
        }

        cout << max << " " << fp+1;

        return 0;
}
