#include <stdio.h>
#include <string.h>
#include "defs.h"

int main()
{
  NotebookType * display = (NotebookType*) calloc (1, sizeof(NotebookType));
  initNotebook(display, MAX_CAP);
  loadEvidenceData(display);
  // printNotebook(display);

  int userChoice;
  int *ptr;
  ptr = &userChoice;

  do{
    printMenu(ptr);

    if(userChoice == 1) {

      EvidenceType newEv;

      int id, evDevice, newHours, newMinutes, newSeconds, time;

      char room[MAX_STR], *device;

      printf("Enter the evidence ID: ");
      scanf("%d", &id);

      printf("Enter the room name: ");
      getchar();
      fgets(room, MAX_STR, stdin);

      room[strcspn(room, "\n")] = 0;

      do{
        printf("Enter the device code [EMF: 1, THERMAL: 2, SOUND: 3]: ");
        scanf("%d", &evDevice);
      }
      while(evDevice < 1 || evDevice > 3);

      float value;
      printf("Enter the value: ");
      scanf("%f", &value);

      printf("Enter timestamp (hours minutes seconds, m, space separated): ");
      scanf("%d %d %d", &newHours, &newMinutes, &newSeconds);

      time = newHours * 3600;
      time = time + (newMinutes * 60);
      time = time + newSeconds;

      if(evDevice == 1){
        device = "EMF";
      }
      else if(evDevice == 2){
        device = "THERMAL";
      }
      else{
        device  = "SOUND";
      }
      initEvidence(id, room, device, value, time, &newEv);
      addEvidence(display, &newEv);

    }
    else if(userChoice == 2){
      int id;
      printf("Enter the evidence ID you wish to remove: ");
      scanf("%d", &id);

      if (delEvidence(display, id) == C_OK){
        printf("The evidence ID has been removed.\n");
      }
      else if(delEvidence(display, id) == C_NOK){
        printf("Invalid ID Input!\n");
      }
    }
    else if(userChoice == 3){
      printNotebook(display);
    }
    else if(userChoice == 0){
      cleanupNotebook(display);
    }
  } while(userChoice != 0);
  


}

void printMenu(int *choice)
{
  int c = -1;
  int numOptions = 3;

  printf("\nMAIN MENU\n");
  printf("  (1) Add evidence\n");
  printf("  (2) Delete evidence\n");
  printf("  (3) Print evidence\n");
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

