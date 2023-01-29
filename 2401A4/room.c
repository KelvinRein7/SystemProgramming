#include "defs.h"

//initialize the size of the colletion to zero
void initRoomArray(RoomArrayType *arr){
  arr->size = 0;
}

//Purpose: this function dynamically allocate  meory for RoomType struct
//initialize new struct file to the parameters
//dynamically allocate new GhostListType struct to store new room's ghost list
void initRoom(int id, char *name, RoomType **room){
  *room = (RoomType*) malloc (sizeof(RoomType));
  (*room)->ghosts = (GhostListType*) malloc (sizeof(GhostListType));
  (*room)->id = id;
  strcpy((*room)->name, name);
  initGhostList((*room)->ghosts);
}

//Purpose: this function add rooms to the back of the array struct which is RoomArrayType arr
void addRoom(RoomArrayType *arr, RoomType *r){
  arr->elements[arr->size] = r;
  arr->size++;
}

//Purpose: this function prints fields of each room struct
//Ghost list of every single room will be printed
void printRooms(RoomArrayType *arr){
  for(int i=0; i < arr->size; ++i){
    printf("Room %d: %s\n", arr->elements[i]->id, arr->elements[i]->name);
    printGhosts(arr->elements[i]->ghosts, 0);
    printf("\n");
  }
}

//Purpose: this function wiil clean up the dynamically allocated memory of room collection
void cleanupRoomArray(RoomArrayType *arr){
  for(int i = 0; i < arr->size; ++i){
    cleanupGhostList(arr->elements[i]->ghosts);
    free(arr->elements[i]->ghosts);
    free(arr->elements[i]);
  }
}


//write a function that returns smallest positive integer that does not occurs in the array


//write a function that returns smallest positive integer that does not occurs in the array
//example: [1, 3, 6, 4, 1, 2] -> 5
//example: [1, 2, 3] -> 4
//example: [-1, -3] -> 1
