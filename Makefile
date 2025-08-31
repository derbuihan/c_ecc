
all: ./main.c ./discrete_log.c ./discrete_log.h ./hashmap.c ./hashmap.h ./ecc.c ./ecc.h ./math.c ./math.h
	gcc -o main ./main.c ./discrete_log.c ./hashmap.c ./ecc.c ./math.c

clean:
	rm -f main

run: all
	./main
