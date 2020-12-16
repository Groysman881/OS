all : rd wr

rd : read.o
	gcc read.o -o rd
read.o : read.c
	gcc -c read.c  
wr : write.o
	gcc write.o -o wr
write.o : write.c
	gcc -c write.c
 	
clean :
	rm -rf *.o wr rd

