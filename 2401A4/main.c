#include "defs.h"

int main()
{
  BuildingType building;
  initBuilding(&building);
  loadBuildingData(&building);
  int userChoice = 1;
  do{
    printMenu(&userChoice);
    
    if(userChoice == 1){
      printRooms(&building.rooms);
    }
    else if(userChoice == 2){
      printGhosts(&building.ghosts, C_FALSE);
    }
    else if(userChoice == 3){
      printByLikelihood(&building.ghosts, C_FALSE);
    }
    else if(userChoice == 0){
      cleanupBuilding(&building);
    }

  }while(userChoice != 0);
}

void printMenu(int *choice)
{
  int c = -1;
  int numOptions = 3;

  printf("\nMAIN MENU\n");
  printf("  (1) Print rooms\n");
  printf("  (2) Print ghosts\n");
  printf("  (3) Print ghosts by likelihood\n");
  printf("  (0) Exit\n\n");

  printf("Please enter your selection: ");
  scanf("%d", &c);

  if (c == 0) {
    *choice = c;
    return;
  }

  while (c < 0 || c > numOptions) {
    printf("Please enter your selection: ");
    scanf("%d", &c);
  }

  *choice = c;
}

