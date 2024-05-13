CC = g++
CFLAGS  = -g -Wall -std=c++17
INCLUDES = -Isrc/include -I../include

app: main.o ESPNOW_manager.o ESPNOW_types.o
	$(CC) $(CFLAGS) -o bin/exec $(addprefix bin/,$^) -pthread

%.o: src/%.cpp
	mkdir -p bin
	$(CC) $(CFLAGS) $(INCLUDES) -o bin/$@ -c $^

clean: 
	$(RM) bin/*
