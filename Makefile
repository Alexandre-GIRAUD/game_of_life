CC = gcc
EXEC = game_of_life
DEP = src/grid.c src/cell.c

all : bin/$(EXEC) bin/client bin/server

bin/$(EXEC): src/main.c src/grid.c src/cell.c 
	$(CC) -I include -o bin/$(EXEC) src/main.c $(DEP) 

bin/client: src/client.c $(DEP) 
	$(CC) -I include -o bin/client src/client.c $(DEP) -lws2_32

bin/server: src/server.c $(DEP) 
	$(CC) -I include -o bin/server src/server.c $(DEP) -lws2_32

clean : 
	@echo "clean project"
	-rm -f bin/$(EXEC) obj/*.o
	@echo "clean completed"