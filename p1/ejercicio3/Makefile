DIRSRC := src/
DIROBJ := obj/
DIRHEA := include/
DIREXE := exec/
DIRDAT := data/

CFLAGS := -I$(DIRHEA) -c -Wall -ansi
LDLIBS := -lpthread -lrt
CC := gcc

all: dirs manager sumador restador

dirs:
	mkdir -p $(DIROBJ) $(DIREXE)

manager: $(DIROBJ)manager.o
	$(CC) -o $(DIREXE)$@ $^ $(LDLIBS)

sumador: $(DIROBJ)sumador.o
	$(CC) -o $(DIREXE)$@ $^ $(LDLIBS)

restador: $(DIROBJ)restador.o
	$(CC) -o $(DIREXE)$@ $^ $(LDLIBS)

$(DIROBJ)%.o: $(DIRSRC)%.c
	$(CC) $(CFLAGS) $^ -o $@

test:
	./$(DIREXE)manager $(DIRDAT)ejemplo 5

clean:
	rm -rf *~ core $(DIROBJ) $(DIREXE) $(DIRHEA)*~ $(DIRSRC)*~

