all : daytimecli

daytimecli : daytimecli.o
	gcc -o daytimecli daytimecli.o 

daytimecli.o : daytimecli.c
	gcc -c daytimecli.c

clean :
	rm daytimecli *.o
