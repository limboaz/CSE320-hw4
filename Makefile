all:
	gcc	-g	main.c	-o	part1
	gcc	-g	-c	part2.c	-o	part2.o
	gcc	-pthread	-g	test.c	part2.o		-o	test
	gcc -pthread	-g 	test2.c	part2.o		-o	test2

