#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef char* elString;

typedef struct elementsdef{
	elString* wordDest;
	struct elementsdef* prevptr;
	struct elementsdef* nextptr;
} elements;

elements* createElement(){
	elements* retptr = NULL;
	retptr = (elements*)calloc(1, sizeof(elements));
	if (retptr == NULL){
		return NULL;
	}
}

void parseText(elString targrtText){
	int32_t nStr = 0;
	int32_t ctr1 = 0;
	
	nStr = 0;
	while(targrtText[nStr] != '\0'){
		nStr++;
	}

	
}

void main(void){
	elements head;

	head.nextptr = NULL;
	head.prevptr = NULL;
	head.wordDest = (elString*)calloc(1, sizeof(elString));
	if (head.wordDest == NULL){
		return;
	}
	
}
