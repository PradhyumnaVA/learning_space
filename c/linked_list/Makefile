main : main.o ll_lib.o
	gcc -o main main.o ll_lib.o
main.o : main.c ll_lib.h
	gcc -c -g main.c
ll_lib.o : ll_lib.c ll_lib.h
	gcc -c -g ll_lib.c
run : 
	./main > output.txt
	less output.txt
clean : 
	rm main main.o ll_lib.o
