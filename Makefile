#Opcoes para o g++:
GPPOPT = -Wall -Wextra


trabalho: fregues eventos


fregues: src/fregues.h src/fregues.cpp
	g++ $(GPPOPT) -c src/fregues.cpp -o fregues.o

eventos: src/eventos.h src/eventos.cpp
	g++ $(GPPOPT) -c src/eventos.cpp -o eventos.o

clean:
	rm -f fregues.o eventos.o
	rm -f doc_codigo.pdf

docs: relatorio doxygen

relatorio:

doxygen:
	doxygen
	make -C docs/latex pdf
	cp docs/latex/refman.pdf doc_codigo.pdf

all: clean trabalho docs
