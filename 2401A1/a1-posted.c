#include <stdio.h>

#define MAX_SIZE  32

#define C_OK             0	// Success flag
#define C_ERR_ARR_FULL  -1	// Error code for array is full
#define C_ERR_BAD_EMF   -2	// Error code for an invalid EMF value
#define C_ERR_BAD_UUID  -3	// Error code for an invalid UUID value
#define C_ERR_BAD_ARR   -4	// Error code for an array error

int  getEmfData(int*, float*);
void printEmfData(int*, float*, int);
int  orderEmfData(int*, float*, int);

int  validateUUID(int); 
int  validateEMF(float);
void printErrorMsg(int);        // Hint: Write modular code using helper functions for repeated functionality
int  findMaxIndex(float* , int);

//main funtion
//Declared two arrays as local vairables and they are populated with EMF and UUID values
//Take user inputs and store them in array
//Print out the data pairs in expected format (on one single line with a space between and by columns)
//reorder the data pairs
//print the valid data pairs entered by the user
//print the data pairs in decending order of EMF values
int main()
{

int uuidArr[MAX_SIZE];
float emfArr[MAX_SIZE];

getEmfData(uuidArr, emfArr);

int entries = getEmfData(uuidArr, emfArr);

printEmfData(uuidArr, emfArr, entries);

if (orderEmfData(uuidArr, emfArr, entries) == C_OK) {
	
	printf("\nTotal data pairs in decending EMF order: \n");

	for (int i = 0; i < entries; i++) {

		if(validateEMF(emfArr[i]) == C_OK && validateUUID(uuidArr[i]) == C_OK) {
		printf("%d ", uuidArr[i]);
		printf("%.1f \n", emfArr[i]) ;
		}
	}
} else { 
 		printErrorMsg(C_ERR_BAD_ARR);
}

  return(0);
}

//this function ask for the user to input EMF values and UUID values
//if user enter -1 for either EMF or UUID the program will terminate
//if user enter invalid EMF or UUID, the user will get an appropriate error message and will be asked to enter the inputs again
//in-> user inputs EMF and UUID
//out-> return number of valid data pairs if successful
int getEmfData(int *uuid, float *emf)
{

int i = 0;
int successfulDataPairs = 0;
int valU;
float valE;

do
{
printf("Enter UUID and EMF pair (e.g. 32850021 4.2214): ");
scanf("%d %f", &valU, &valE);
printf("\n");

if (validateUUID(valU) == C_OK && validateEMF(valE) == C_OK) { 
	uuid[i] = valU;
	emf[i] = valE;
	successfulDataPairs++;
} 
 else	{

	if(validateUUID(valU) == C_ERR_BAD_UUID) {
		printErrorMsg(C_ERR_BAD_UUID);
	} 
	else if(validateEMF(valE) == C_ERR_BAD_EMF) {
		printErrorMsg(C_ERR_BAD_EMF);
	}
	else if(i > MAX_SIZE) {
		printErrorMsg(C_ERR_ARR_FULL);
	}

}
	i++;
}
while(valU != -1 && valE != -1 && i < MAX_SIZE);
	
	return successfulDataPairs;

}

void printEmfData(int* uuid, float* emf, int num)
{
	int count = 0;
	int i = 0;

	printf("\n");
	printf("Valid data pairs entered by the user:");
	printf("\n");

	for (i = 0; i < num; i++) {
	if (validateUUID(uuid[i]) == C_OK && validateEMF(emf[i]) == C_OK) { 
			printf("%d ",  uuid[i]);
			printf("%.1f", emf[i]);
			printf("\n");
			count++;
		} 
	}
	num = count;

	printf("Total number of valid pairs: ");
	printf("%d", num);
	printf("\n");

}

//this function sorts the input EMF values by the users in decending order
//in -> uuid array, emf array and number of valid data pairs
//process -> create a deep copy of the original array
//process -> loop through the copy array and sort the array in decending order of EMF values (Largest to Smallest)
//out -> successful flag (0) if it works ELSE error flag for bad array (-4) 
//whether it is successul or fail will be checked in the main
int orderEmfData(int* uuid, float* emf, int num)
{

	int localUUID[MAX_SIZE];
	float localEMF[MAX_SIZE];

	int i, j;

	for (i = 0; i < num; i++) {
		localUUID[i] = uuid[i];
		localEMF[i] = emf[i];
	}

	float emfValue;
	int uuidValue;
	for (i = 0; i < num; i++) {
        
      for (j = i + 1; j < num; j++) {
            
            if (localEMF[i] < localEMF[j]) {

                emfValue = localEMF[i];
								uuidValue = localUUID[i];

								emfValue = emf[i];
								uuidValue = uuid[i];

                localEMF[i] = localEMF[j];
								localUUID[i] = localUUID[j];

								emf[i] = emf[j];
								uuid[i] = uuid[j];

                localEMF[j] = -1;
								localUUID[j] = -1;

								emf[j] = emfValue;
								uuid[j] = uuidValue;
            } 
        }
    }

	return C_OK;
}

//this function checks where the user input UUID value is in the expected range
//expected range -> ( 32850000 - 32859999 inclusively)
//in -> input UUID value
//out -> successful flag (0) if in the range ELSE error flag bad uuid (-3)
int validateUUID(int uuid)
{
if(uuid >= 32850000 && uuid <= 32859999)
{
	return C_OK;
}
else
{
	return C_ERR_BAD_UUID;
}
}

//this function checks where the user input EMF value is in the expected range
//expected range -> ( 0 - 5 inclusively)
//in -> input EMF value
//out -> successful flag (0) if in the range ELSE error flag bad emf (-2)
int validateEMF(float emf)
{

if(emf >= 0.0 && emf <= 5.0) 
{
	return C_OK;
}
else
{
	return C_ERR_BAD_EMF;
}
}

//this function helps reduce printf() statements
//in -> input integers that indicates different error flags
//out -> friendly message to the user which states the error the breaks the program
void printErrorMsg(int errorMsg)
{
  if (errorMsg == C_ERR_BAD_EMF) {
		printf("Check your input EMF. It should be at least 0.0 and at most 5.0.");
		printf("\n");
	}
	else if (errorMsg == C_ERR_BAD_UUID) {
		printf("Check your input UUID. It should be at least 32850000 and at most 32859999.");
		printf("\n");
	}
	else if (errorMsg == C_ERR_BAD_ARR) {
		printf("There was a problem sorting the values in the array.");
		printf("\n");
	}
	else if (errorMsg == C_ERR_ARR_FULL) {
		printf("Unfortunately, your array is full.");
		printf("\n");
	}
}

//this funtion finds index of max value
//in -> array of data pairs and number of data pairs
//out -> successful flag (0) if the index is found ELSE error flag for array (-4)
int findMaxIndex(float* arr, int num)
{
	int i, maxInd;
	for (i = 0; i < num; i++) {
		if(arr[i] > arr[maxInd]) {
				arr[maxInd] = arr[i];
				maxInd = i;
		}
	}
	return C_OK;

}

/***********************************************
 * This and the below comments can be removed
 * but are provided to give you an example of
 * how to write comments for your functions.
***********************************************/
/*  
  Function: myFunction()
  Purpose:  Do that thing this function does
       in:   this is the point of the first parameter
       out:  this is the point of the second parameter
  return:   the thing we're looking for, or C_APPROPRIATE_ERROR if not found
*/
