/*
Name: Kristan Samaroo
iD: 1045594
Email: ksamaroo@uoguelph.ca
*/

#include "ds_memory.h"
#include "ds_array.h"

long elements;

int ds_create_array(){
	/*Creates array and mallocs memory for the max amount of elements*/

	long ds_mallocTest;
	int result = 0;
	ds_init("array.bin");
	elements = 0;
	ds_mallocTest = ds_malloc(MAX_ELEMENTS);

	if(ds_mallocTest != elements){
		result = 1;
	}

	ds_finish();

	return result;
}

int ds_init_array(){

	/*Intializes array by reading amount of elements that are in the binary file*/
	long test;
	int result;
	ds_init("array.bin");

	int dsreadtest;
	dsreadtest = ds_read( test, 0, sizeof(long));

	if(dsreadtest != elements){
		result = -1;
	}
	else{
		result = 0;
	}

	return result;
}


int ds_replace( int value, long index ){
	int result;

	/*(index*sizeof(int))+ sizeof(long):
	This line finds the index of an element in the array by multiplying the index number
	of the element by the size of an integer to get to the locaton and then adds the size 
	of the global variable elements which is stored at the beginning of the binary file
	*/

	if (index<elements || index > -1 ){
		ds_write((index*sizeof(int))+ sizeof(long), value, sizeof(int));
		result = 0;
	}
	else{
		result = 1;
	}

	return result;
}


int ds_insert( int value, long index ){

	int tempOld, tempNew;
	int i;
	int result;

	/*Function inserts by looping through the array until it gets to the index specified
	and then reads the value there into a temporary variable, then writes the value. It then
	shifts each element after it one spot over. 
	*/

	if (index<elements || index > -1 ){
		result = 0;
		tempOld = ds_read(tempOld, (index*sizeof(int))+ sizeof(long), sizeof(int));
		ds_write((index*sizeof(int))+ sizeof(long), value, sizeof(int));

		elements = elements + 1;
		for (i = (index+1); i<elements; i++){
			tempNew = ds_read( tempNew, (i*sizeof(int))+ sizeof(long), sizeof(int));
			ds_write((i*sizeof(int))+ sizeof(long), tempOld, sizeof(int));
			tempOld = tempNew;
		}
	}
	else{
		result = 1;
	}

	return result;
}


int ds_delete( long index ){
	int i; 
	int temp;
	int result;
	int tempNew, tempOld;

	if (index<elements || index > -1 ){
		for (i = (index); i<elements; i++){
			tempNew = ds_read( tempNew, ((i+1)*sizeof(int))+ sizeof(long), sizeof(int));
			ds_write((i*sizeof(int))+ sizeof(long), tempNew, sizeof(int));
		}
		elements--;


		result = 0;
	}
	else{
		result = 1;
	}

	return result;
}

int ds_swap( long index1, long index2 ){
	int result;
	int temp1, temp2;

	if ((index1<elements || index1 > -1)  || (index2<elements || index2 > -1) ){
		temp1 = ds_read(temp1, index1*sizeof(int)+ sizeof(long), sizeof(int));
		temp2 = ds_read(temp2, index2*sizeof(int)+ sizeof(long), sizeof(int));
		ds_write((index2*sizeof(int))+ sizeof(long), temp1, sizeof(int));
		ds_write((index1*sizeof(int))+ sizeof(long), temp2, sizeof(int));

		result = 0;
	}
	else{
		result = 1;
	}

	return result;

}

long ds_find( int target ){
	long result;
	int i; 
	int temp; 

	/*Loops through all the elements until the target element is found, returns that element*/

	for (i = 0; i<elements; i++){
		temp = ds_read(temp, i*sizeof(int)+ sizeof(long), sizeof(int) );
		if (temp == target){
			result = i;
			break;
		}
		else{
			result = -1;
		}

	}

	return result;
}


int ds_read_elements( char *filename ){
  int fscanfTest;
  int tempVal;
  int result = 0;
  int index = 0;

  FILE *fp;
  fp = fopen(filename, "r");

  /*Loops through until the end of the file to look for each integer
	it then calls ds_insert to put each integer into memory
  */

  while (!feof(fp)){
    fscanfTest = fscanf(fp, "%d", &tempVal);
    ds_insert(tempVal, index);
    index ++;
    tempVal = 0;
  } 

  if (index>MAX_ELEMENTS || fscanfTest != 1){
    result = 1;
  }
  
  return result;
}

int ds_finish_array(){

	int ds_writeTest;
	int result;

	ds_writeTest = ds_write(0, elements, sizeof(long));

	ds_finish();

	if (ds_writeTest == -1){
		result = 1;
	}
	else {
		result = 0;
	}

	return result;
}