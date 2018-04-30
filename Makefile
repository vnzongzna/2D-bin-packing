#Makefile

OBJ = BinPack.o  headers/MaxRectsBinPack.o  headers/rectangle.o
CXX = g++

all:  $(OBJ)
	$(CXX) $(OBJS) -o BinPack
clean:
	rm -r *.o headers/*.o
