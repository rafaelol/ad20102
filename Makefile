#Opcoes para o g++:
GPPOPT = -Wall -Wextra


trabalho: fregues


fregues: src/fregues.h src/fregues.cpp
	g++ $(GPPOPT) -c src/fregues.cpp -o fregues.o

clean:
	rm -f fregues.o
	rm -f doc_codigo.pdf

docs: relatorio doxygen

relatorio:

doxygen:
	doxygen
	make -C docs/latex pdf
	cp docs/latex/refman.pdf doc_codigo.pdf

all: clean trabalho docs
