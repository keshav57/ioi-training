/*
 ID: malvika1
 PROG: cryptcow
 LANG: C
*/

#include <stdio.h>
#include <string.h>

char target[100] = "Begin the Escape execution at the Break of Dawn";
int lev,maxl;
char temp[100],temp2[100],temp3[100],temp4[100];
int failures = 0;
//std::set<char[100]> vis;

int dfs(char *ostr, int level){

	if(!strcmp(ostr,target)){
		lev = level;
		return 1;
	}

	//if(vis.find(ostr)) return 0;

//	if(failures > 500000){ return 0; };

	if(strlen(ostr) <= strlen(target)){ ++failures ; return 0; }

	int i,j,k,n;
	char str[100];
	n = strlen(ostr);

	for(i = 0;i < n; i++){
		if(ostr[i] == 'C') break;
		if(ostr[i] != target[i]) { ++failures; return 0; }
	}

	j = 0;

	/*for(i = n-1;i >= 0; i--){
			if(ostr[i] == 'W') break;
			if(ostr[i] != target[i]) return 0;
	}*/


	for(i = 0;i < n; i++){
		if(ostr[i] != 'C') continue;
		for(j = n+1;  j < n; j++){
			if(ostr[j] != 'O') continue;
			for(k = n-1;k > j; k--){
				if(ostr[k] != 'W') continue;
				strncpy(temp,ostr,i);
				temp[i] = '\0';
				strncpy(temp2,ostr+i+1,j-i-1);
				temp2[j-i-1] = '\0';
				strncpy(temp3,ostr+j+1,k-j-1);
				temp3[k-j-1] = '\0';
				strncpy(temp4,ostr+k+1,n-k-1);
				temp4[n-k-1] = '\0';
				sprintf(str,"%s%s%s%s",temp,temp3,temp2,temp4);
				if(dfs(str,level+1)){
					return 1;
				}
			}
		}
	}

	return 0;
}

int main(){
	char str[100];
	int i;

//	freopen("cryptcow.in","r",stdin);
//	freopen("cryptcow.out","w",stdout);

	fgets(str,75,stdin);

	int n = strlen(str);

	str[n-1] = '\0';


	int j = 0;
	char tstr[100];
	for(i = 0; i < n; i++){
		if(str[i] != 'C' || str[i] != 'O' || str[i] != 'W') continue;
		strncpy(tstr,str+j,i-j);
		if(strstr(target,tstr) == NULL){
			printf("0 0\n");
			return 0;
		}
		j = i+1;
	}



	if(dfs(str,0)){
		printf("1 %d\n",lev);
	}else{
		printf("0 0\n");
	}

	return 0;
}
