SingleMass: SingleMass.o GLPendulum.o ../../sva/sva.o
	g++ -o ../bin/SingleMass -Wall SingleMass.o GLPendulum.o ../../sva/sva.o -framework GLUT -framework OpenGL

GenerateThetas: SinglePendulum.o
	g++ -o ../bin/GenerateThetas -Wall SinglePendulum.o

SinglePendulum.o: SinglePendulum.c qpicard.h
	g++ -c SinglePendulum.c

GLPendulum.o: GLPendulum.cpp GLPendulum.h
	g++ -c GLPendulum.cpp

SingleMass.o: SingleMass.cpp
	g++ -c SingleMass.cpp