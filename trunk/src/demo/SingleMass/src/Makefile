PenTest: SimTest.o PenSim.o ThetaReader.o GLPendulum.o
	g++ -o PenTest -Wall SimTest.o PenSim.o ThetaReader.o GLPendulum.o -L/sw/lib -framework Cocoa -framework OpenGL -framework SDL -framework SDL_image -lXOR -lSDLmain

SimTest.o: SimTest.cpp ../../../xor.h
	g++ -c -Wno-deprecated SimTest.cpp

PenSim.o: PenSim.cpp PenSim.h ../../../xor.h
	g++ -c PenSim.cpp

GLPendulum.o: GLPendulum.cpp GLPendulum.h ../../../xor.h
	g++ -c GLPendulum.cpp

ThetaReader.o: ThetaReader.cpp ThetaReader.h
	g++ -c ThetaReader.cpp