CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla 
EXEC = chess
OBJECTS = main.o player.o board.o textDisplay.o GraphicDisplay.o window.o bishop.o king.o knight.o pawn.o piece.o queen.o rook.o
DEPENDS = ${OBJECTS:.o=.d} 

${EXEC}: ${OBJECTS} 
	${CXX} ${OBJECTS} -o ${EXEC} ${CXXFLAG} -lX11

-include ${DEPENDS} 

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
