CFLAGS = -ansi -Wall -pedantic
CC = gcc

all: ds_memory.o ds_array.o ds_list.o

clean: 
		rm ds_memory.o ds_array.o ds_list.o 


ds_memory: ds_memory.c
		$(CC) $(CFLAGS) -c ds_memory.c -o ds_memory.o


ds_array: ds_array.c
		$(CC) $(CFLAGS) -c ds_array.c -o ds_array.o


ds_list: ds_list.c
		$(CC) $(CFLAGS) -c ds_list.c -o ds_list.o

