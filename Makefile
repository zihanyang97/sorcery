CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror=vla -MMD
EXEC = sorcery
OBJECTS = main.o ascii_graphics.o board.o card.o deck.o enchantment.o graveyard.o hand.o minion.o player.o ritual.o spell.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}


.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
