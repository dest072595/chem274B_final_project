CPP = g++ 

CPPFLAGS = -std=c++20 -Og

BIN_OBJS = CA_Test

BIN_DIR = ../BIN

INC_DIR = ../INCLUDE

.PHONY: all

# Makes the CA Testing Program
CA_Test: CA_Test.cpp
	$(CPP) $(CPPFLAGS) CA_Test.cpp -o CA_Test -I$(INC_DIR)

all: $(BIN_OBJS)
	mv $(BIN_OBJS) $(BIN_DIR)

clean: 
	(cd $(BIN_DIR); rm $(BIN_OBJS))