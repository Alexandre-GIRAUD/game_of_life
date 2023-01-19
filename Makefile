CC = gcc
EXEC = game_of_life

all : $(EXEC)

$(EXEC): main.o grid.o cell.o global.o
	$(CC) -o $(EXEC) main.o cell.o grid.o global.o

main.o: main.c 
	$(CC) -o main.o main.c

grid.o: grid.c 
	$(CC) -o grid.o grid.c 

cell.o: cell.c 
	$(CC) -o cell.o cell.c 

clean : 
	@echo "clean project"
    -rm -f $(EXEC).exe *.o
    @echo "clean completed"