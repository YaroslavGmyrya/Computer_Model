all:
	gcc -c myCache.c -o myCache.o

	gcc -c variables.c -o variables.o
	
	ar rcs libmyCacheLib.a myCache.o variables.o

clean:
	rm -f *.o *.a