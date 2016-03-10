all: A3

A3: main.o drawMap.o parseLevel.o playTime.o drawHalls.o movement.o combat.o
	gcc main.o drawMap.o parseLevel.o playTime.o drawHalls.o movement.o combat.o -lncurses -o A3

main.o: src/main.c
	gcc -c -pedantic -Wall -std=c99 -Iinclude src/main.c

parseLevel.o: src/parseLevel.c
	gcc -c -pedantic -Wall -std=c99 -Iinclude src/parseLevel.c

playTime.o: src/playTime.c
	gcc -c -pedantic -Wall -std=c99 -Iinclude src/playTime.c

drawMap.o: src/drawMap.c
	gcc -c -pedantic -Wall -std=c99 -Iinclude src/drawMap.c

drawHalls.o: src/drawHalls.c
	gcc -c -pedantic -Wall -std=c99 -Iinclude src/drawHalls.c

movement.o: src/movement.c
	gcc -c -pedantic -Wall -std=c99 -Iinclude src/movement.c

combat.o: src/combat.c
	gcc -c -pedantic -Wall -std=c99 -Iinclude src/combat.c


clean:
	rm *.o A3

playHard:
	./A3 assets/hard.txt

playEasy:
	./A3 assets/easy.txt

debug:
	gcc src/main.c src/drawMap.c src/playTime.c src/parseLevel.c -lncurses -Iinclude -std=c99 -Wall -g -o de
	gdb de
	run assets/hard.txt

cleanAll:
	rm Makefile~ src/*.c~ include/*.h~ de *.o A3 src/*.c.*

