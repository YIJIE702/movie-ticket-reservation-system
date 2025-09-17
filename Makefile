# Makefile used to compile the movie reservation system
# Also includes a clean option

all: main.o movieList.o ticketList.o
	@echo '*Compiling program'
	@gcc -o movies main.o movieList.o ticketList.o

movieList.o: movieList.c 
	@echo '*Compiling movieList'
	@gcc -c movieList.c

main.o: main.c 
	@echo '*Compiling main'
	@gcc -c main.c

ticketList.o: ticketList.c
	@echo '*Compiling ticketList'
	@gcc -c ticketList.c

clean: 
	@echo '*Cleaning object and executable files'
	rm -f *.o movies