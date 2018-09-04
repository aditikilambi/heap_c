#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "heap.h"


void swap(Heap* h, int index1, int index2) {
	Pair x = h->elements[index1];
	Pair y = h->elements[index2];
	h->elements[index1] = y;
	h->elements[index2] = x;
}

void expandCapacity(Heap* h) {
	Pair* newElts = malloc(sizeof(Pair) * h->capacity * 2);
	int i;
	for(i = 0; i < h->size; i++){
		newElts[i] = h->elements[i];
	}
	free(h->elements);
	h->elements = newElts;
	h->capacity *= 2;
}

void bubbleUp(Heap* h, int index) {
	int parentIndex  = (index-1)/2; 
	int childKey = h->elements[index].key;
	int parentKey = h->elements[parentIndex].key;
	if(childKey <= parentKey){
		swap(h, index, parentIndex);
	}
}

void add(Heap* h, int k, char* val) {

	if(h->size == h->capacity) {
		expandCapacity(h);
	}
	
	h->size += 1;
	int j = h->size-1;
	h->elements[j].key = k;
	h->elements[j].value = val;
	
	while(j>=1) {
		bubbleUp(h, j);
		j = (j-1)/2;
	}
	
}

void bubbleDown(Heap* h, int index) {

	h->elements[0] = h->elements[index];
	h->size -= 1;
	int i = 0;
	while(i<h->size){

		if(!hasLeft(h, i) && !hasRight(h,i)){
			return;
		}
		if(!hasLeft(h, i) && hasRight(h,i) && h->elements[(2*i)+2].key < h->elements[i].key){
			swap(h, (2*i)+2, i);
			i = (2*i)+2;
		}
                if(hasLeft(h, i) && !hasRight(h,i) && h->elements[(2*i)+1].key < h->elements[i].key){
                        swap(h, (2*i)+1, i);
                        i = (2*i)+1;
                }
		if(hasLeft(h,i) && hasRight(h,i) &&  h->elements[(2*i)+1].key < h->elements[(2*i)+2].key  && h->elements[i].key > h->elements[(2*i)+1].key){
			swap(h, (2*i)+1, i);
			i = (2*i)+1;
		}
		else if(hasLeft(h,i) && hasRight(h,i) &&  h->elements[(2*i)+2].key < h->elements[(2*i)+1].key  && h->elements[i].key > h->elements[(2*i)+2].key){
			swap(h, (2*i)+2, i);
			i = (2*i)+2;
		}
		else {
			return;
		}
	}
	
}

_Bool hasLeft(Heap* h, int index){
	int parentIndex = (2*index)+1;
	if(parentIndex >= h->size) {
		return false;
	}
	else if(h->elements[parentIndex].value == NULL){
		return false;
	}
	return true;
}

_Bool hasRight(Heap* h, int index){
        int parentIndex = (2*index)+2;
        if(parentIndex >= h->size) {
                return false;
        }
        else if(h->elements[parentIndex].value == NULL){
                return false;
        }
        return true;
}

char* removeMin(Heap* h) {
	if(h->size == 0){
		return NULL;
	}	
	char* toReturn =  h->elements[0].value;
	bubbleDown(h, h->size-1);
	return toReturn;
}


void cleanupHeap(Heap* h) {
	free(h->elements);
	free(h);
}

void printHeap(Heap* h) {
	int i;
	for(i=0; i < h->size; i++) {
		printf("Key: %d", h->elements[i].key);
		printf(" Value: %s \n", h->elements[i].value);
	}
}

Heap* makeHeap(int capacity) {
	Heap* h = malloc(sizeof(Heap));
	h->size = 0;
	h->capacity = capacity;
	h->elements = malloc(sizeof(Pair)*capacity);	
	return h;
}

int size(Heap* h) {
	return h->size;
}

char* peek(Heap* h) {
	if(h->size == 0) {
		return NULL;
	}
	return h->elements[0].value;
}

