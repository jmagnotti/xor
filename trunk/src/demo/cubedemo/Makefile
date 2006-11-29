#Makefile for libgor.la, *nix
#
CC = g++ 
LIBS = -framework Cocoa -lSDL -lSDLMain -lGOR 

#Packages
SRCS = HelloWorld.cpp

OBJS = $(SRCS:.cpp=.o)

MAIN = HelloWorld

# 
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean
#Change this so that the executable is put in a "bin" directory of sorts
all:		$(MAIN)

HelloWorld:	$(OBJS) 
			$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

.c.o:
			$(CC) $(CFLAGS) $(INCLUDES) -c $<

clean:
			$(RM) $(OBJS) $(MAIN)

depend: $(SRCS)
			makedepend -fMakefile.osx $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it

HelloWorld.o: ../../gor.h ../../core/Controller.h /usr/include/stdlib.h
HelloWorld.o: /usr/include/sys/cdefs.h /usr/include/_types.h
HelloWorld.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
HelloWorld.o: /usr/include/ppc/_types.h /usr/include/sys/wait.h
HelloWorld.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
HelloWorld.o: /usr/include/machine/signal.h /usr/include/ppc/signal.h
HelloWorld.o: /usr/include/sys/resource.h /usr/include/machine/endian.h
HelloWorld.o: /usr/include/ppc/endian.h /usr/include/sys/_endian.h
HelloWorld.o: /usr/include/stdint.h /usr/include/libkern/OSByteOrder.h
HelloWorld.o: /usr/include/libkern/ppc/OSByteOrder.h /usr/include/alloca.h
HelloWorld.o: /usr/include/machine/types.h /usr/include/ppc/types.h
HelloWorld.o: ../../../include/SDL.h ../../../include/SDL_main.h
HelloWorld.o: ../../../include/SDL_types.h ../../../include/SDL_getenv.h
HelloWorld.o: ../../../include/SDL_error.h ../../../include/begin_code.h
HelloWorld.o: ../../../include/close_code.h ../../../include/SDL_rwops.h
HelloWorld.o: /usr/include/stdio.h ../../../include/SDL_timer.h
HelloWorld.o: ../../../include/SDL_audio.h ../../../include/SDL_byteorder.h
HelloWorld.o: ../../../include/SDL_cdrom.h ../../../include/SDL_joystick.h
HelloWorld.o: ../../../include/SDL_events.h ../../../include/SDL_active.h
HelloWorld.o: ../../../include/SDL_keyboard.h ../../../include/SDL_keysym.h
HelloWorld.o: ../../../include/SDL_mouse.h ../../../include/SDL_video.h
HelloWorld.o: ../../../include/SDL_mutex.h ../../../include/SDL_quit.h
HelloWorld.o: ../../../include/SDL_version.h ../../event/Keyboard.h
HelloWorld.o: ../../event/KeyboardListener.h ../../event/RegularKeyEvent.h
HelloWorld.o: ../../event/SpecialKeyEvent.h ../../event/Mouse.h
HelloWorld.o: ../../event/MouseListener.h ../../event/MouseClickEvent.h
HelloWorld.o: ../../event/MouseEvent.h ../../event/MouseMotionEvent.h
HelloWorld.o: ../../event/Timer.h ../../event/TimerListener.h
HelloWorld.o: ../../core/World.h ../../shape/Point3D.h /usr/include/math.h
HelloWorld.o: /usr/include/architecture/ppc/math.h ../../paint/Paint.h
HelloWorld.o: /usr/include/string.h ../../texture/Texture.h
HelloWorld.o: ../../paint/Color.h ../../shape/Renderable.h
HelloWorld.o: ../../../include/SDL_opengl.h /usr/include/stddef.h
HelloWorld.o: ../../shape/Renderable.h ../../transform/Rotate.h
HelloWorld.o: ../../transform/Transform.h ../../event/TimerListener.h
HelloWorld.o: ../../transform/Transform.h ../../transform/Translate.h
HelloWorld.o: ../../core/Viewer.h ../../geometry/Dimension2D.h
HelloWorld.o: ../../geometry/Dimension.h
HelloWorld.o: ../../util/GraphicsConversionUtility.h
HelloWorld.o: ../../transform/Orientate.h ../../transform/Translate.h
HelloWorld.o: ../../transform/Rotate.h ../../event/ReshapeListener.h
HelloWorld.o: ../../event/DefaultKeyboardListener.h ../../core/Controller.h
HelloWorld.o: ../../core/World.h ../../event/DefaultMouseListener.h
HelloWorld.o: ../../core/Viewer.h ../../core/World.h
HelloWorld.o: ../../event/DefaultKeyboardListener.h
HelloWorld.o: ../../event/DefaultMouseListener.h ../../event/Keyboard.h
HelloWorld.o: ../../event/KeyboardListener.h ../../event/Mouse.h
HelloWorld.o: ../../event/MouseClickEvent.h ../../event/MouseEvent.h
HelloWorld.o: ../../event/MouseListener.h ../../event/MouseMotionEvent.h
HelloWorld.o: ../../event/RegularKeyEvent.h ../../event/ReshapeListener.h
HelloWorld.o: ../../event/SpecialKeyEvent.h ../../event/Timer.h
HelloWorld.o: ../../event/TimerListener.h ../../geometry/CylindricalVolume.h
HelloWorld.o: ../../shape/CollisionRenderable.h ../../shape/Point3D.h
HelloWorld.o: ../../geometry/Dimension3D.h ../../geometry/Dimension.h
HelloWorld.o: ../../geometry/Dimension2D.h ../../geometry/Dimension3D.h
HelloWorld.o: ../../geometry/RectangularVolume.h ../../geometry/Dimension3D.h
HelloWorld.o: ../../paint/Color.h ../../paint/ColorConstants.h
HelloWorld.o: ../../paint/Paint.h ../../shape/AdornableCube.h
HelloWorld.o: ../../shape/Cube.h ../../shape/RectangularPrism.h
HelloWorld.o: ../../shape/Quadrilateral3D.h ../../paint/Color.h
HelloWorld.o: ../../geometry/RectangularVolume.h ../../shape/Positionable.h
HelloWorld.o: ../../shape/AdornablePrism.h ../../shape/AdornablePrism.h
HelloWorld.o: ../../shape/Arc3D.h ../../shape/CollisionRenderable.h
HelloWorld.o: ../../shape/Cube.h ../../shape/NormalPolygon3D.h
HelloWorld.o: ../../shape/Particle.h ../../shape/CollisionRenderable.h
HelloWorld.o: ../../shape/Point.h ../../shape/Point2D.h ../../shape/Point3D.h
HelloWorld.o: ../../shape/Quadrilateral3D.h
HelloWorld.o: ../../shape/Quadrilateral3DConstants.h
HelloWorld.o: ../../shape/RectangularPrism.h
HelloWorld.o: ../../shape/RectangularPrismFactory.h ../../shape/Renderable.h
HelloWorld.o: ../../shape/String2D.h ../../util/BitmapFontUtil.h
HelloWorld.o: ../../util/BitmapFontConstants.h ../../core/Viewer.h
HelloWorld.o: ../../shape/Positionable.h ../../terrain/Terrain.h
HelloWorld.o: ../../shape/Quadrilateral3D.h ../../texture/TextureFactory.h
HelloWorld.o: /sw/include/GL/glut.h ../../texture/Texture.h
HelloWorld.o: ../../texture/TexturePPM.h ../../texture/TextureBMP.h
HelloWorld.o: ../../texture/TextureTGA.h ../../texture/Texture.h
HelloWorld.o: ../../texture/TextureFactory.h ../../transform/Orientate.h
HelloWorld.o: ../../transform/Positionable.h ../../transform/Rotate.h
HelloWorld.o: ../../transform/Transform.h ../../transform/TransformFactory.h
HelloWorld.o: ../../transform/Transformable.h ../../transform/Translate.h
HelloWorld.o: ../../util/BehaviorParser.h ../../transform/TransformFactory.h
HelloWorld.o: ../../util/BitmapFontConstants.h ../../util/BitmapFontUtil.h
HelloWorld.o: ../../util/FramesPerSecondCounter.h ../../shape/String2D.h
HelloWorld.o: ../../util/GraphicsConversionUtility.h
