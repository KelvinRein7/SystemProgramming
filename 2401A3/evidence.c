#include <stdio.h>
#include <string.h>
#include "defs.h"

//this function creates a DEEP COPY of old evidence and save it into newEv
void copyEvidence(EvidenceType* newEv, EvidenceType* oldEv){
	initEvidence(oldEv->id, oldEv->room, oldEv->device, oldEv->value, oldEv->timestamp, newEv);
}

//this function DOUBLES the capacity of evidence collection, temporarily store them in a new collection "newNoteBook"
void growNotebook(NotebookType* arr){
	
	//allocate memory for newNotebook
	NotebookType * newNotebook = (NotebookType*)calloc (1, sizeof(NotebookType));
	//double the capacity
	initNotebook(newNotebook, 2*arr->capacity);

	//evidencetype evidence array
	EvidenceType evArr;
	
	for(int i = 0; i < arr->size; ++i){
		copyEvidence(&evArr, &arr->elements[i]);
		newNotebook->elements[i] = evArr;
	}

	free(arr->elements);
	arr->elements = newNotebook->elements;
	arr->capacity = 2*arr->capacity;
	free(newNotebook);
}

//
void addEvidence(NotebookType* arr, EvidenceType* ev){

	int currIndex = 0;
	//2.3.1
	if(arr->size >= arr->capacity){
		growNotebook(arr);
	}


	for(int i = 0; i < arr->size; ++i){
		//if string comparison of evidence room and array room is equal
		if(strcmp(ev->room, arr->elements[i].room) == 0){
			currIndex = i;
			//if string comparison is equal, compare timestamp of the rooms
			if(ev->timestamp < arr->elements[i].timestamp){
				break;
			}
			else{
				currIndex = i + 1;
			}
		}
		//if not equal
		else if(strcmp(ev->room, arr->elements[i].room) > 0){
			currIndex = i;
			break;
		}
		else{
					currIndex = i + 1;
		}
	}


	for(int i = arr->size; i > currIndex; --i){
		copyEvidence(&arr->elements[i], &arr->elements[i - 1]);
	}

	//copy new evidence into the array at insertion point
	copyEvidence(&arr->elements[currIndex], ev);
	//increase size of arr
	arr->size += 1;

}

int  delEvidence(NotebookType* arr, int id){

	int index = -1;

	//find evidence with given id
	for(int i = 0; i < arr->size; ++i){
		if(arr->elements[i].id == id){
			index = i;
			break;
		}
	}

	//if evidence is not found, error flag
	if(index == -1){
		return C_NOK;
	}

	//copy element of evidence collection one position towards front of array
	for(int i = index; i < arr->size; ++i){
		copyEvidence(&arr->elements[i], &arr->elements[i + 1]);
	}

	//decrease size, return success flag
	arr->size -= 1;
	return C_OK;

}

//display the evidence table
void printNotebook(NotebookType* arr){

	printf("------------------------------------------------------------------------------------------------------------------\n");
	printf("     ID        |         ROOM          |      DEVICE       |           VALUE            |         TIMESTAMP\n");
	printf("------------------------------------------------------------------------------------------------------------------\n");

	for(int i = 0; i < arr->size; ++i){

		//evidence type pointer to the elements 
		EvidenceType *p = arr->elements+i;

		int h = p->timestamp / 3600;
		int m = (p->timestamp % 3600) / 60;
		int s = p->timestamp % 60;

		if(strcmp(p->device, "THERMAL") == 0){
			if(p->value < 0){
				printf("ID: %10d | ROOM: %15s | DEVICE: %10s| VALUE: %10.2f (COLD)   | TIMESTAMP: %5.2d:%.2d:%.2d\n", p->id, p->room, p->device, p->value, h, m, s);
			}
			else{
				printf("ID: %10d | ROOM: %15s | DEVICE: %10s| VALUE: %10.2f          | TIMESTAMP: %5.2d:%.2d:%.2d\n", p->id, p->room, p->device, p->value, h, m, s);
			}
		}
		else if (strcmp(p->device, "EMF") == 0){
			if(p->value > 4){
				printf("ID: %10d | ROOM: %15s | DEVICE: %10s| VALUE: %10.2f (HIGH)   | TIMESTAMP: %5.2d:%.2d:%.2d\n", p->id, p->room, p->device, p->value, h, m, s);
			}
			else{
				printf("ID: %10d | ROOM: %15s | DEVICE: %10s| VALUE: %10.2f        	| TIMESTAMP: %5.2d:%.2d:%.2d\n", p->id, p->room, p->device, p->value, h, m, s);
			}
		}
		else if(strcmp(p->device, "SOUND") == 0){
			if(p->value > 70){
			printf("ID: %10d | ROOM: %15s | DEVICE: %10s| VALUE: %10.2f (SCREAM) | TIMESTAMP: %5.2d:%.2d:%.2d\n", p->id, p->room, p->device, p->value, h, m, s);
			}
			else if(p->value < 35){
				printf("ID: %10d | ROOM: %15s | DEVICE: %10s| VALUE: %10.2f (WISPER) | TIMESTAMP: %5.2d:%.2d:%.2d\n", p->id, p->room, p->device, p->value, h, m, s);
			}
			else{
				printf("ID: %10d | ROOM: %15s | DEVICE: %10s| VALUE: %10.2f          | TIMESTAMP: %5.2d:%.2d:%.2d\n", p->id, p->room, p->device, p->value, h, m, s);
			}
		}
	}
	printf("------------------------------------------------------------------------------------------------------------------\n");

}

void cleanupNotebook(NotebookType* arr){
	free(arr->elements);	
}
