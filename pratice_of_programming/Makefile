hash.o: hash.c hash.h
	gcc -c -g hash.c
test_hash_table.o: test_hash_table.c
	gcc -c -g test_hash_table.c
test: hash.o test_hash_table.o
	gcc hash.o test_hash_table.o -o test
run: test
	./test
clean:
	rm *.o
	rm test
