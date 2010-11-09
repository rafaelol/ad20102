#Opcoes para o g++:
GPPOPT = -Wall -Wextra


trabalho: fregues eventos exponencial simulador
	g++ $(GPPOPT) src/main.cpp fregues.o eventos.o exponencial.o simulador.o -o cmulator

fregues: src/fregues.h src/fregues.cpp
	g++ $(GPPOPT) -c src/fregues.cpp -o fregues.o

eventos: src/eventos.h src/eventos.cpp
	g++ $(GPPOPT) -c src/eventos.cpp -o eventos.o

exponencial: src/exponencial.h src/exponencial.cpp
	g++ $(GPPOPT) -c src/exponencial.cpp -o exponencial.o

simulador: src/simulador.h src/simulador.cpp
	g++ $(GPPOPT) -c src/simulador.cpp -o simulador.o

clean:
	rm -f fregues.o eventos.o exponencial.o simulador.o cmulator
	rm -f doc_codigo.pdf

docs: relatorio doxygen

relatorio:

doxygen:
	doxygen
	make -C docs/latex pdf
	cp docs/latex/refman.pdf doc_codigo.pdf

all: clean trabalho docs
