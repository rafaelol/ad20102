#Opcoes para o g++:
GPPOPT = -Wall -Wextra


trabalho: fregues


fregues: fregues.h fregues.cpp
	g++ $(GPPOPT) -c fregues.cpp -o fregues.o

clean:
	rm -f fregues.o

all: clean trabalho
