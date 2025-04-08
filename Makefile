all:
	make -C mySimpleComputer
	make -C myTerm
	make -C myBigChars
	make -C console
	make run -C console
	make -C myReadKey

	gcc ./myTerm/console.c -o main.out -L./myTerm -L./mySimpleComputer -L./myBigChars -L./myReadKey -lmyTermLib -lmySimpleLib -lmyBigChars -lmyReadKey -lm

clean:
	rm -f *.a *.out
	make clean -C mySimpleComputer
	make clean -C myTerm
	make clean -C myBigChars
	make clean -C console
	make clean -C myReadKey

run:
	./main.out