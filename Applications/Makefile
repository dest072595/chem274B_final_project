CPP = g++ 

CPPFLAGS = -std=c++20 -Og -o

BIN_OBJS = COVID-19_Simulation

BIN_DIR = ../Bin

INC_DIR = ../INCLUDE

.PHONY: all

# Makes the CA Test People Program which demostrates custom functionality
COVID-19_Simulation: COVID-19_Simulation.cpp
	$(CPP) COVID-19_Simulation.cpp $(CPPFLAGS) COVID-19_Simulation -I$(INC_DIR)

all: $(BIN_OBJS)
	mv $(BIN_OBJS) $(BIN_DIR)

clean: 
	(cd $(BIN_DIR); rm $(BIN_OBJS))