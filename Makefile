all:
	make -C mySimpleComputer
	make -C myTerm
	make -C myBigChars
	make -C console
	make run -C console
	make -C myReadKey
	make -C myInterputs

	gcc ./myTerm/console.c -o main.out -L./myTerm -L./mySimpleComputer -L./myBigChars -L./myReadKey -L./myInterputs -lmyTermLib -lmySimpleLib -lmyBigChars -lmyReadKey -lmyInterput -lm

clean:
	rm -f *.a *.out
	make clean -C mySimpleComputer
	make clean -C myTerm
	make clean -C myBigChars
	make clean -C console
	make clean -C myReadKey
	make clean -C myInterputs

run:
	./main.out