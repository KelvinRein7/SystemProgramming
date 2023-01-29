#include "defs.h"

//Purpose: initialize the collection to an empty one
//head and tail set to NULL value
void initGhostList(GhostListType *list){
  list->head = NULL;
  list->tail = NULL;
}

//Purpose: dynamically allocate memory for GhostType struct
//initialize parameters appropriately
void initGhost(int id, GhostEnumType gt, RoomType *r, float like, GhostType**ghost){
  *ghost = (GhostType*) malloc (sizeof(GhostType));
  (*ghost)->id = id;
  (*ghost)->ghostType = gt;
  (*ghost)->room = r;
  (*ghost)->likelihood = like;
}

//Purpose: this function will add the ghost to the list from the BACK of it
void addGhost(GhostListType *list, GhostType *ghost){

  NodeType *nodeT;
  nodeT = (NodeType*) malloc (sizeof(NodeType));
  nodeT->data = ghost;
  nodeT->next = NULL;

  if(list->head == NULL){
    list->head = nodeT;
    list->tail = nodeT;
  }
  else{
    list->tail->next = nodeT;
    list->tail = nodeT;
  }
}

//Purpose: this function will add the ghost to the correct position
//in decending order by likelihood
void addGhostByLikelihood(GhostListType *list, GhostType *ghost){

  NodeType *nodeT = (NodeType*) malloc (sizeof(NodeType));
  nodeT->data = ghost;
  nodeT->next = NULL;

  //NodeType* curr = list->head;
  //NodeType* prev = NULL;

  if(list->head == NULL){
    list->head = nodeT; 
    list->tail = nodeT;
  }
  else{
  
  NodeType* currNode = list->head;
  NodeType* prevNode = NULL;

    //make sure if node is not NULL, compare data of current node vs existing likelihood data in the list 
    while(currNode != NULL && (currNode->data->likelihood > ghost->likelihood)){
      prevNode = currNode;
      currNode = currNode->next;
    }
    if(prevNode == NULL){
      nodeT->next = list->head;
      list->head = nodeT;
    }
    else{
      nodeT->next = currNode;
      prevNode->next = nodeT;
    }
  }
}

//Purpose: this function will deallocate ONLY data from the list
void cleanupGhostData(GhostListType *list){

  NodeType *currNode = list->head;
  
  while(currNode != NULL){
    free(currNode->data);
    currNode = currNode->next;
  }
}

//Purpose: this function will deallocate ONLY nodes from the list
void cleanupGhostList(GhostListType *list){

  NodeType* currNode = list->head;
  NodeType* next;

  while(currNode != NULL){
    next = currNode->next;
    free(currNode);
    currNode = next; 
  }
}

//Purpose: this function will print ghost id, ghost type, the room and the likelihood
void printGhost(GhostType *ghost){

  printf("GHOST ID: %d", ghost->id);
  printf("\tGHOST TYPE: ");

  switch (ghost->ghostType)
  {
  case PHANTOM:
  printf("Phantom");
  break;
  case WRAITH:
  printf("Wraith");
  break;
  case BULLIES:
  printf("Bullies");
  break;
  case POLTERGEIST:
  printf("Poltergeist");
  break;
  case OTHER:
  printf("Other Ghost");
  break;
  default:
  printf("Unknown Ghost Type");
    break;
  }
  printf("\t\t ROOM : ");
  if(ghost->room == NULL){
    printf("%-10s", "Unknown Room");
  }
  else{
    printf("%-10s", ghost->room->name);
  }
  printf("\t\t GHOST BY LIKELIHOOD: %f\n", ghost->likelihood);
}

//Purpose: this function prints ghost from the list by using printGhost function
//if ends = C_TRUE, head and tail of the list will be printed second time after all the ghost outputs
//if ends = C_FALSE, head and tail wont appear the second time like C_TRUE
void printGhosts(GhostListType *list, int ends){

  NodeType *currNode = list->head;
  while(currNode != NULL){
    printGhost(currNode->data);
    currNode = currNode->next;
  }
  //make sure if ends is C_TRUE
  //if so, print head and tail the second time
  if(ends == C_TRUE){
    printGhost(list->head->data);
    printGhost(list->tail->data);
  }

}

//Purpose: this function prints ghosts in decreaing order by likelihood
void printByLikelihood(GhostListType *origList, int ends){

  NodeType *currNode = origList->head;

  GhostListType *tempList;
  tempList = malloc(sizeof(GhostListType));
  tempList->head = NULL;
  tempList->tail = NULL;

  while(currNode != NULL){
    addGhostByLikelihood(tempList, currNode->data);
    currNode = currNode->next;
  }
  printGhosts(tempList, ends);
  cleanupGhostList(tempList);
  free(tempList);
}
