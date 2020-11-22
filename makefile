CC = g++
CPPFLAGS = -Wall -g

OBJECTS = mainProgram.o processadorTexto.o grafo.o estatisticas.o

PROGRAM = mainProgram

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o: 
	$(CC) $(CPPFLAGS) -c $<

clean: 
	rm -vf *.o
