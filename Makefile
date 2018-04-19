all:
	gcc	-g	-c	part2.c	-o	part2.o
	gcc	-pthread	-g	test.c	part2.o		-o	test

