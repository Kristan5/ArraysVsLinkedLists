/*
Name: Kristan Samaroo
iD: 1045594
Email: ksamaroo@uoguelph.ca
*/
#include "ds_list.h"
#include "ds_memory.h"

void ds_create_list(){
	long element = -1;
	ds_init("list.bin");
	ds_malloc(sizeof(element));
	ds_write(0, element, sizeof(long));
	ds_finish();
}

int ds_init_list(){
	int dsInitTest, result;
	dsInitTest = ds_init("list.bin");
	if (dsInitTest == 0){
		result = 0;
	}	
	else{
		result = 1;
	}
	return result;
}

int ds_replace( int value, long index ){

	struct ds_list_item_struct previous, new;
	long prev_loc = 0;
	int i; 
	int result;

	/*Loop goes through each element in the list until it gets to index
	once it gets there it simply writes the new value into the spot that 
	used to be held by the old value.
	*/

	previous.next = sizeof(long);

	for (i = index; i>=0; i--){
		if (previous.next == -1){
			return -1;
		}
		else{
			prev_loc = previous.next;
			ds_read(&previous.item, previous.next, sizeof(int));

		}
	}
	ds_write(previous.item, value, sizeof(int));


	if (index>MAX_BLOCKS){
		result = 1;
	}
	else{
		result = 0;
	}

	return result;
}

int ds_insert( int value, long index ){
	struct ds_list_item_struct previous, new;
	long prev_loc = 0;
	int i; 
	int result;

	previous.next = ds_read(previous.next, 0, sizeof(long));

	for (i = index; i>0; i--){
		if (previous.next == -1){
			previous.next = sizeof(long);
			prev_loc = previous.next;
			ds_read(&previous, previous.next, sizeof(previous));
		}
		else{
			prev_loc = previous.next;
			ds_read(&previous, previous.next, sizeof(previous));

		}
	
		new.item = value;

		new.next = previous.next;
	}

	previous.next = ds_malloc(sizeof(new));
	ds_write(previous.next, &new, sizeof(new));
	

	if (prev_loc == 0){
		result = 1;
	}
	else{
		result = 0;
		ds_write(prev_loc, &previous, sizeof(previous));
	}


	return result;
}

void show_list(){
	/*Test function*/

	long loc; 
	struct ds_list_item_struct li;
	ds_init_test();
	ds_read(&loc, 0, sizeof(long));
	printf("\nHead: %ld\n", loc);

	int i;
	for (i = 0; i<3;i++){
		printf("\n%ld Item: %d  Next: %ld\n", loc, li.item, li.next );

		ds_read(&li, loc, sizeof(li));
		loc = li.next;

	}

}

int ds_delete( long index ){

	struct ds_list_item_struct previous, new;
	long prev_loc = 0;
	int i; 
	int result;

	previous.next = sizeof(long);

	for (i = index; i>=0; i--){
		if (previous.next == -1){
			return -1;
		}
		else{
			prev_loc = previous.next;
			ds_read(&previous.item, previous.next, sizeof(int));

		}
	}


	prev_loc = previous.next;
	ds_read(&new.item, previous.next, sizeof(int));

	ds_write(previous.next, new.item, sizeof(int));
	ds_free(previous.next);

	if (index>MAX_BLOCKS){
		result = 1;
	}
	else{
		result = 0;
	}

	return result;
}

int ds_swap( long index1, long index2 ){

	struct ds_list_item_struct element1, element2, temp;
	long prev_loc = 0;
	int i; 
	int result;

	element1.next = sizeof(long);

	for (i = index1; i>=0; i--){
		if (element1.next == -1){
			return -1;
		}
		else{
			prev_loc = element1.next;
			ds_read(&element1.item, element1.next, sizeof(int));

		}
	}

	ds_write(element1.item, &temp.item, sizeof(int));

	prev_loc = 0;
	element2.next = sizeof(long);

	for (i = index2; i>=0; i--){
		if (element2.next == -1){
			return -1;
		}
		else{
			prev_loc = element2.next;
			ds_read(&element2.item, element2.next, sizeof(int));
		}
	}

	ds_write(element1.item, element2.item, sizeof(int));
	ds_write(temp.item, element1.item, sizeof(int));

	if (index1 > MAX_BLOCKS || index2 > MAX_BLOCKS){
		result = 1;
	}
	else{
		result = 0;
	}

	return result;
}

long ds_find( int target ){
	struct ds_list_item_struct previous, new;
	long prev_loc = 0;
	int i; 
	int result;
	int index = MAX_BLOCKS;

	previous.next = ds_read(previous.next, 0, sizeof(long));
	/*previous.next = sizeof(long);*/

	for (i = index; i>0; i--){
		if (previous.next == -1){
			previous.next = sizeof(long);
			prev_loc = previous.next;
			ds_read(&previous, previous.next, sizeof(previous));
		}
		else{
			prev_loc = previous.next;
			ds_read(&previous, previous.next, sizeof(previous));

		}
		if (previous.item == target){
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

	while (!feof(fp)){
		fscanfTest = fscanf(fp, "%d", &tempVal);
		ds_insert(tempVal, index);
		index ++;
		tempVal = 0;
	} 

	if (fscanfTest != 1){
		result = 1;
	}

	return result;
}

int ds_finish_list(){
	int testFinish;
	int result;
	testFinish = ds_finish();

	if (testFinish == 1){
		result = 0;
	}
	else{
		result = 1;
	}
	return result;
}