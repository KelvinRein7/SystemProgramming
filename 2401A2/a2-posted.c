#include <stdio.h>
#include <string.h>

#define MAX_BUF  256

#define IV  0b10110001
#define KEY 0b11001011
#define CTR 0b00110101

void encode(unsigned char*, unsigned char*, int);
void decode(unsigned char*, unsigned char*, int);

unsigned char processCtr(unsigned char, unsigned char);
unsigned char encryptByte(unsigned char, unsigned char, unsigned char);
unsigned char decryptByte(unsigned char, unsigned char, unsigned char);

unsigned char getBit(unsigned char, int);
unsigned char setBit(unsigned char, int);
unsigned char clearBit(unsigned char, int);

int main()
{
  char str[8];
  int  choice;

  printf("\nYou may:\n");
  printf("  (1) Encrypt a message \n");
  printf("  (2) Decrypt a message \n");
  printf("  (0) Exit\n");
  printf("\n  what is your selection: ");
  fgets(str, sizeof(str), stdin);
  sscanf(str, "%d", &choice);

  if (choice == 0)
    return 0;

  unsigned char plainText[MAX_BUF];
  unsigned char ct[MAX_BUF];

  switch (choice) {

    case 1:{

      printf("\nEnter your message:\n");

      fgets(plainText, sizeof(plainText), stdin);

      encode(plainText, ct, sizeof(plainText));

      for(int i = 0; i < sizeof(plainText); i++){
        printf("%d ", ct[i]);
      }

      break;
    }

    case 2:{

      printf("\nEnter your code:\n");

      int code;
      int index = 0;

    //if user input -1  the program will be terminated
      while(code != -1){
        scanf("%d", &code);
        ct[index] = code;
        ++index;
      }

      decode(ct, plainText, sizeof(ct));
      printf("%s", plainText);

      break;

    }
    //for any invalid input
    default:
      printf("\n  Enter a valid option! \n");
      main();
      break;
  }
  printf("\n");
  return 0;
}

/*
  Function:  getBit
  Purpose:   retrieve value of bit at specified position
       in:   character from which a bit will be returned
       in:   position of bit to be returned
   return:   value of bit n in character c (0 or 1)
*/
unsigned char getBit(unsigned char c, int n)
{
  return ((c & (1 << n)) >> n);
}

/*
  Function:  setBit
  Purpose:   set specified bit to 1
       in:   character in which a bit will be set to 1
       in:   position of bit to be set to 1
   return:   new value of character c with bit n set to 1
*/
unsigned char setBit(unsigned char c, int n)
{
  return c | (1 << n);
}

/*  Function:  clearBit
  Purpose:   set specified bit to 0
       in:   character in which a bit will be set to 0
       in:   position of bit to be set to 0
   return:   new value of character c with bit n set to 0
*/
unsigned char clearBit(unsigned char c, int n)
{
  return c & (~(1 << n));
}

/*
  Function:  encode
  Purpose:   encrypt user input plaintext into cipher text
       in:   plaintext user input, ciphertext array, size of the bytes   
      out:   print ciphertext
*/
void encode(unsigned char* pt, unsigned char* ct, int numBytes) {

  unsigned char temp = processCtr(temp, KEY);    

  int index;
                                 
  ct[0] = encryptByte(pt[0], temp, IV);

  for(index=1; index < numBytes; ++index){
    ct[index] = encryptByte(pt[index], temp, ct[index-1]);
    ++temp;
  }
}

/*
  Function:  decode
  Purpose:   decrypt user input ciphter into readable plain text
       in:   ciphertext user input, plaintext array, size of the bytes   
      out:   print plaintext
*/
void decode(unsigned char* ct, unsigned char* pt, int numBytes) {

  unsigned char temp = processCtr(temp, KEY);   

  int index;
                                 
  pt[0] = decryptByte(ct[0], temp, IV);

  for(index=1; index < numBytes; ++index){
    pt[index] = decryptByte(ct[index], temp, pt[index-1]);
    ++temp;
  }
}

/*
  Function:  process the given counter
  Purpose:   by processing, using the given key, we want an updated counter here
       in:   given counter input, given key  
      out:   updated counter
*/
unsigned char processCtr(unsigned char ctr, unsigned char key){

  unsigned char tempCtr = ctr;

  int bitPosition = 0;       
  
  for (int i = 0; i <= 7; ++i){  
    
    if(tempCtr % 2 == 0){
      bitPosition = i;
    }
    else{
      bitPosition = i - 1;
    }

    if(getBit(ctr, bitPosition) ^ getBit(key, bitPosition) == 1){
      tempCtr = setBit(tempCtr, bitPosition);
    }
    else{
      tempCtr = clearBit(tempCtr, bitPosition);
    }
  }
  return tempCtr;
}

/*
 Function:  encrypt byte
  Purpose:  encrypt the plaintext byte
       in:  plaintext input, counter, previous byte  
   return:  ciphertext byte
*/
unsigned char encryptByte(unsigned char pt, unsigned char ctr, unsigned char prev){

  unsigned char temp = 0;
  int index = 0;

  for(index = 0; index<=7; ++index){
    char result;
    if(getBit(ctr, index) == 1){
      result = (getBit(pt, index) ^ getBit(prev, index));
    }
    else{
      result = (getBit(pt, index) ^ getBit(prev, 7 - index));
    }

    if(result == 0){
      temp = (clearBit(temp, KEY));
    }
    else{
      temp = (setBit(temp, KEY));
    }
  }
  return temp;
}

/*
 Function:  decrypt byte
  Purpose:  decrypt the ciphertext byte
       in:  cipher input, counter, previous byte  
   return:  plaintext byte 
*/
unsigned char decryptByte(unsigned char ct, unsigned char ctr, unsigned char prev) {

  unsigned char temp = 0;
  int index = 0;

  for(index = 0; index<=7; ++index){
    char result;
    if(getBit(ctr, index) == 1){
      result = (getBit(ct, index) ^ getBit(prev, index));
    }
    else{
      result = (getBit(ct, index) ^ getBit(prev, 7 - index));
    }

    if(result == 0){
      temp = (clearBit(temp, KEY));
    }
    else{
      temp = (setBit(temp, KEY));
    }
  }
  return temp;
}

