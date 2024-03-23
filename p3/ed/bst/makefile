run: bin
	./main
	
bin:
	gcc main.c -o main -g

test: bin
	cat test.txt | ./main
