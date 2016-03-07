#Makefile

ROOTPATH   =     .
SRC        =     $(ROOTPATH)/src
HEAD       =     $(ROOTPATH)/head
COM        =     $(ROOTPATH)/com
BIN        =     $(ROOTPATH)/bin

OBJ        =     $(COM)/test_make.o
TARGET     =     $(BIN)/test

all : install

install:
	@echo "-objects-"
	g++  $(SRC)/convert_comment.cpp $(SRC)/main.cpp -o $(TARGET) -I $(HEAD)

	@echo "---------"
	@date

.PHONE:
clean:
	rm -f $(OBJ) $(TARGET) 
