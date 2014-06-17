#include "grader.h"
#include "memory.h"
#include <algorithm>
#include <cstdio>

int pos[30][2];
int n[30];

void play() {
	int i;
	char c;

	for(i = 1; i <= 50; ++i){
		c = faceup(i);
		pos[c-'A'][n[c-'A']++] = i;
	}

	for(i = 0; i < 25; ++i){
		faceup(pos[i][0]);
		faceup(pos[i][1]);
	}
}
