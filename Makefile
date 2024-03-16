CC = g++

CompileParms = -c -Wall -std=c++11 -O2

OBJS = standaard.o tegelspel.o main.o

Opdr: $(OBJS)
	$(CC) $(OBJS) -o TegelSpel

clean:
	rm -f *.o TegelSpel

standaard.o: standaard.cc standaard.h
	$(CC) $(CompileParms)  standaard.cc

tegelspel.o: tegelspel.cc standaard.h constantes.h tegelspel.h
	$(CC) $(CompileParms)  tegelspel.cc

main.o: main.cc constantes.h tegelspel.h
	$(CC) $(CompileParms)  main.cc

