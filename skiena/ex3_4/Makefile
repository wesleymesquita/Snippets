bin_dict.o : bin_dict.c bin_dict.h
	gcc -Wall -c bin_dict.c -o bin_dict.o
test_bin_dict.o: test_bin_dict.c bin_dict.o 
	gcc -Wall -c test_bin_dict.c -o test_bin_dict.o
test_bin_dict: test_bin_dict.o
	gcc test_bin_dict.o bin_dict.o -o test_bin_dict -lm
test: test_bin_dict
	./test_bin_dict
memcheck: test_bin_dict
	valgrind --tool=memcheck ./test_bin_dict
