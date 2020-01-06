/*
Name: Kristan Samaroo
iD: 1045594
Email: ksamaroo@uoguelph.ca
*/

#include "ds_memory.h"

struct ds_file_struct ds_file;
struct ds_counts_struct ds_counts;


int ds_create( char *filename, long size ){

	int i, j; 
	int result =0; 
	char writeByte = 0;
	int fwriteTest1, fwriteTest2, fcloseTest;
	
	
	ds_file.fp = fopen(filename, "wb+");
	/*Check if file pointer is null then set start, length and alloced of first block
		first block contains size
	*/
	
	if (ds_file.fp != NULL){
		ds_file.block[0].start = 0;
		ds_file.block[0].length = size;
		ds_file.block[0].alloced = 0;

		/*Write reaminder of blocks, set equal to 0 for now*/
		for (i = 1; i<MAX_BLOCKS; i++){
			ds_file.block[i].start = 0;
			ds_file.block[i].length = 0;
			ds_file.block[i].alloced = 0;
		}
		
		fwriteTest1 = fwrite(ds_file.block, sizeof(ds_file.block), MAX_BLOCKS , ds_file.fp);		

		for (j = 0; j< size; j++){
			fwriteTest2 = fwrite(&writeByte, sizeof(writeByte), 1 , ds_file.fp);
		}
		
		fcloseTest = fclose(ds_file.fp);

		if (fwriteTest1 < 1 || fwriteTest2  < 1 || fcloseTest == 1){
			result = 1;
		}
	}
	else{
		result = 1;
	}

	return result;
}

int ds_init( char *filename ){

	int freadTest;
	int result = 0;

	/*Reopen the file, seek to the beginning and read the blocks*/
	ds_file.fp = fopen(filename, "rb+");
	fseek(ds_file.fp, 0, SEEK_SET);
	freadTest =fread(ds_file.block, sizeof(ds_file.block), MAX_BLOCKS, ds_file.fp);
	ds_counts.reads = 0;
	ds_counts.writes = 0;

	if (freadTest != 1){
		result = 1;
	}
	return result;
}

int ds_init_test(){

	/*Test function to output blocks and their information*/

	int i;
	printf("BLOCK#		start		length			alloced\n");

	for (i = 0;i<MAX_BLOCKS; i++){
		printf("%d 		%ld 		%ld 		%d\n", i, ds_file.block[i].start, ds_file.block[i].length, ds_file.block[i].alloced);
	}
	printf("read: %d\n", ds_counts.reads);
	printf("write: %d\n", ds_counts.writes);

	return 0;

}



long ds_malloc( long amount ){

	int i, j; 

	long result = -1;
	long tempLength;

	for (i = 0; i<MAX_BLOCKS; i++){
		if ((ds_file.block[i].length >= amount) && (ds_file.block[i].alloced == 0)){
			tempLength = ds_file.block[i].length;
			ds_file.block[i].length = amount;
			ds_file.block[i].alloced = 1;

	
			for (j = 0; j<MAX_BLOCKS; j++){
				if (ds_file.block[j].length == 0){
					result = ds_file.block[i].start;
					ds_file.block[j].start = ds_file.block[i].start + amount;
					ds_file.block[j].length = tempLength - amount;
					ds_file.block[j].alloced = 0;
					i = MAX_BLOCKS;
					j = MAX_BLOCKS;

				}
			}
		}

	}
	return result;
}


void ds_free( long start ){
	int i; 

	for (i = 0; i<MAX_BLOCKS; i++){
		if (ds_file.block[i].start == start){
			ds_file.block[i].alloced = 0;
		}
	}
}

void *ds_read( void *ptr, long start, long bytes ){
	int freadTest;
	
	fseek(ds_file.fp, start + sizeof(ds_file.block), SEEK_SET);
	freadTest = fread(&ptr, bytes, 1, ds_file.fp);
	ds_counts.reads = ds_counts.reads + 1;

	if (freadTest != 1){
		return NULL;
	}
	else {
		return ptr;
	}

}

long ds_write( long start, void *ptr, long bytes ){
	int fwriteTest;
	int result = start;

	fseek(ds_file.fp, start + sizeof(ds_file.block), SEEK_SET);
	fwriteTest = fwrite(&ptr, bytes, 1, ds_file.fp);
	ds_counts.writes = ds_counts.writes + 1;

	if (fwriteTest < 1 ){
		result = -1;
	}
	return result;
}

int ds_finish(){

	int fwriteTest;
	int result = 1;

	/*When finished, go to beginning of file and write all the blocks to binary file
	outputs number of reads and writes then closes the file*/

	fseek(ds_file.fp, 0, SEEK_SET);
	fwriteTest = fwrite(ds_file.block, sizeof(ds_file.block), MAX_BLOCKS, ds_file.fp);
	printf("reads: %d\n", ds_counts.reads);
	printf("writes: %d\n", ds_counts.writes);
	fclose(ds_file.fp);

	if (fwriteTest < 1){
		result = 0;
	}

	return result;
}
