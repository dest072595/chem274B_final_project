CPP = g++ 

CPPFLAGS = -std=c++20 -Og

BIN_OBJS = CA_Test_People CA_Test_Majority CA_Test_Straight_Conditional CA_Test_Neighbor_Conditional

BIN_DIR = ../BIN

INC_DIR = ../INCLUDE

.PHONY: all

# Makes the CA Test People Program which demostrates custom functionality
CA_Test_People: CA_Test_People.cpp
	$(CPP) $(CPPFLAGS) CA_Test_People.cpp -o CA_Test_People -I$(INC_DIR)

# Makes the CA Test Majority Program which demostrates the Straight Conditional Rule
CA_Test_Straight_Conditional: CA_Test_Straight_Conditional.cpp
	$(CPP) $(CPPFLAGS) CA_Test_Straight_Conditional.cpp -o CA_Test_Straight_Conditional -I$(INC_DIR)

# Makes the CA Test Majority Program which demostrates the Straight Conditional Rule
CA_Test_Neighbor_Conditional: CA_Test_Neighbor_Conditional.cpp
	$(CPP) $(CPPFLAGS) CA_Test_Neighbor_Conditional.cpp -o CA_Test_Neighbor_Conditional -I$(INC_DIR)

# Makes the CA Test Majority Program which demostrates the Majority Rule
CA_Test_Majority: CA_Test_Majority.cpp
	$(CPP) $(CPPFLAGS) CA_Test_Majority.cpp -o CA_Test_Majority -I$(INC_DIR)


all: $(BIN_OBJS)
	mv $(BIN_OBJS) $(BIN_DIR)

clean: 
	(cd $(BIN_DIR); rm $(BIN_OBJS))