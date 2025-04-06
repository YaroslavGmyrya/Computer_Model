all:
	make -C mySimpleComputer
	make -C myTerm
	make -C myBigChars
	make -C console
	make run -C console

	gcc ./myTerm/console.c -o main.out -L./myTerm -L./mySimpleComputer -L./myBigChars -lmyTermLib -lmySimpleLib -lmyBigChars -lm

clean:
	rm -f *.a *.out
	make clean -C mySimpleComputer
	make clean -C myTerm
	make clean -C myBigChars
	make clean -C console

run:
	./main.out