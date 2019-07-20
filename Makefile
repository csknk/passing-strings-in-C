all: main realloc

main: main.c
	cc -fsanitize=address -g -o bin/main main.c

realloc: realloc-in-func.c
	cc -fsanitize=address -g -o bin/realloc realloc-in-func.c

#	cc -fsanitize=address -g -o $(OUT) $(OBJECTS)
	#cc -W -Wall -fsanitize=address -g -o $(OUT) $(OBJECTS)
	#cc -W -Wall -g -o $(OUT) $(OBJECTS)
