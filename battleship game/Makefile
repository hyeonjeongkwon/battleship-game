CXX=gcc
CXXFLAGS=-std=c14 -MMD
OBJECTS=main.o grid.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=battleship

${EXEC}: ${OBJECTS} 
    ${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean
clean: 
    rm ${OBJECTS} ${DEPENDS} ${EXEC}
