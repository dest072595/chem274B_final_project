BIN_DIR = Bin
INC_DIR = Include
TEST_DIR = Tests


.PHONY = clean all environment

environment: 
	
all:
	(cd $(TEST_DIR);make all)

clean: 
	(cd $(TEST_DIR);make clean)