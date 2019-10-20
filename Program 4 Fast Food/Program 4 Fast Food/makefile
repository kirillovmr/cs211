prog4: main.o Manager.o Queue.o Node.o Misc.o
	gcc -o prog4 main.o Manager.o Queue.o Node.o Misc.o

main.o: main.c Manager.h
	gcc -c main.c

Manager.o: Manager.c Manager.h Misc.h
	gcc -c Manager.c
	
Queue.o: Queue.c Queue.h Node.h
	gcc -c Queue.c
	
Node.o: Node.c Node.h
	gcc -c Node.c
	
Misc.o: Misc.c Misc.h
	gcc -c Misc.c

clean:
	rm prog4 main.o Manager.o Queue.o Node.o Misc.o
