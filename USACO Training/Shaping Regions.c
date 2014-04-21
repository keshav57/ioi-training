/*
 Created By: Malvika Joshi
 Problem: rect1
 Link: http://cerberus.delos.com:791/usacoprob2?S=rect1&a=cAqVK0yAeBZ
*/

#include <stdio.h>
#include <string.h>

typedef struct { int x1,y1,x2,y2,col; } rectangle;

int get_intersection(rectangle *splits,rectangle a, rectangle b){
	if(a.x2 <= b.x1 || b.x2 <= a.x1) return 0;
	if(a.y2 <= b.y1 || b.y2 <= a.y1) return 0;

	if(b.x1 <= a.x1 && b.y1 <= a.y1 && b.x2 >= a.x2 && b.y2 >= a.y2) return -1;

	int k = 0;
	rectangle c;

	if(b.x1 > a.x1){
		c = a;
		c.x2 = b.x1;
		splits[k++] = c;
		a.x1 = b.x1;
	}

	if(b.x2 < a.x2){
		c = a;
		c.x1 = b.x2;
		splits[k++] = c;
		a.x2 = b.x2;
	}

	if(b.y1 > a.y1){
		c = a;
		c.y2 = b.y1;
		splits[k++] = c;
		a.y1 = b.y1;
	}

	if(b.y2 < a.y2){
		c = a;
		c.y1 = b.y2;
		splits[k++] = c;
		a.y2 = b.y2;
	}

	return k;
}

rectangle Rect[4000];
int colours[2501] = {0};
int N;
int main(){

	int i,j,t,rn,cs;
	rectangle splits[4];
	rectangle top;

	scanf("%d%d%d",&Rect[0].x2,&Rect[0].y2,&N);
	Rect[0].x1 = Rect[0].y1 = 0;
	Rect[0].col = 1;

	rn = 1;
	for(i = 1;i <= N; i++){
		scanf("%d%d%d%d%d",&Rect[rn].x1,&Rect[rn].y1,&Rect[rn].x2,&Rect[rn].y2,&Rect[rn].col);
		cs = rn;
		top = Rect[rn++];
		for(j = 0;j < cs; j++){
		//	printf("%d\n",i);
			t = get_intersection(splits,Rect[j],top);
			if(!t){  continue;  };
			if(t == -1){
                memmove(Rect+j,Rect+j+1,sizeof(rectangle)*(rn-j-1));
			//	Rect[j] = Rect[rn--];
				rn --;
				cs--;
                j--;
				continue;
			}
			Rect[j] = splits[--t];
			while(t-- > 0){
				Rect[rn++] = splits[t];
			}
		}
	}

	for(i = 0;i < rn; i++){
		colours[Rect[i].col] += (Rect[i].x2-Rect[i].x1) * (Rect[i].y2 - Rect[i].y1);
	}

	for(i = 0; i < 2501; i++){
		if(colours[i])
		printf("%d %d\n",i,colours[i]);
	}

	return 0;
}
