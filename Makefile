CC =gcc
DEBUG=yes

# définition des cibles particulières
.PHONY: clean, mrproper

ifeq ($(DEBUG),yes)
	CFLAGS = -Wall -ansi -pedantic -g
else
	CFLAGS = -Wall -ansi -pedantic
endif

SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

LIB=i2c_tmp102.so
EXEC=tmp102
SEXEC=stmp102
MAIN=i2c_tmp102_out

# Regle principale
all: $(OBJ) $(LIB) $(EXEC)

$(LIB): $(OBJ)
	$(CC) $(CFLAGS) -shared -o $@ $^

$(EXEC): $(OBJ) $(LIB)
	$(CXX) $(CFLAGS) -o $@ $^

# Compilation des sources c
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

# Dependance avec les headers
%.o: %.h

install:
	cp $(LIB) /usr/local/lib/
	cp $(EXEC) /usr/local/bin/
	cp $(SEXEC) /usr/local/bin/

# Netoyage
clean:
	rm -f *.o

mrproper: clean
	rm -f $(EXEC) $(LIB)

