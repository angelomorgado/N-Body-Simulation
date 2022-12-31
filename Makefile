.SUFFIXES: .cpp .hpp .o .c .h

CC	= g++
INCLDIR	= Include/
BINDIR	= bin/
SRCDIR	= Src/

_BIN	= a.out
BIN	= $(addprefix $(BINDIR), $(_BIN))

SRC	= $(wildcard Src/*.cpp ./Dependencies/Src/*.c)

CFLAGS = -Wall -pedantic -g -std=c++17 -I$(INCLDIR) -I./Dependencies/Include/ -lm -pthread -lglfw -lGL -lX11 -lrt -ldl -lstdc++fs -lassimp

$(BINDIR)/$(_BIN): $(SRC)
	@$(CC) $(SRC) $(CFLAGS) -o $@

gendir: 
	@mkdir include bin src

clean: 
	@rm bin/a.out

.PHONY: gendir
.PHONY: clean
