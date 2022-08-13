CC = /usr/bin/g++
PROJECT = new_output
SRC = main.cpp
THREAD = -ldl -lm -lpthread -lrt
LIBS = `pkg-config --cflags --libs opencv4`
THREAD_OLD = `gcc lightmanager.c -lusb-1.0 -lpthread -olightmanager`
$(PROJECT): -ldl -lm -lpthread -lrt` : $(SRC)
	$(CC) $(SRC) -o $(PROJECT) ${THREAD} $(LIBS)