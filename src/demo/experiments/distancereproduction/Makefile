#Makefile for helloworld demo, *nix
#
CC = g++

LIBS = -lSDL -lGL -lGLU -lm -lXOR

#Packages
SRCS = AutoPilotState.cpp Experiment.cpp SampleWithoutReplacement.cpp

OBJS = $(SRCS:.cpp=.o)

MAIN = Experiment

# 
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean
#Change this so that the executable is put in a "bin" directory of sorts
all:		$(MAIN)

Experiment:	$(OBJS) 
			$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

.c.o:
			$(CC) $(CFLAGS) $(INCLUDES) -c $<

clean:
			$(RM) $(OBJS) $(MAIN)

depend: $(SRCS)
			makedepend -fMakefile.unix 2>/dev/null $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it

Experiment.o: ../../xor.h ../../core/Camera.h ../../../include/SDL.h
Experiment.o: ../../../include/SDL_main.h ../../../include/SDL_types.h
Experiment.o: ../../../include/SDL_getenv.h ../../../include/SDL_error.h
Experiment.o: ../../../include/begin_code.h ../../../include/close_code.h
Experiment.o: ../../../include/SDL_rwops.h /usr/include/stdio.h
Experiment.o: /usr/include/features.h /usr/include/sys/cdefs.h
Experiment.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Experiment.o: /usr/include/gnu/stubs-32.h /usr/include/bits/types.h
Experiment.o: /usr/include/bits/typesizes.h /usr/include/libio.h
Experiment.o: /usr/include/_G_config.h /usr/include/wchar.h
Experiment.o: /usr/include/bits/wchar.h /usr/include/gconv.h
Experiment.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
Experiment.o: ../../../include/SDL_timer.h ../../../include/SDL_audio.h
Experiment.o: ../../../include/SDL_byteorder.h ../../../include/SDL_cdrom.h
Experiment.o: ../../../include/SDL_joystick.h ../../../include/SDL_events.h
Experiment.o: ../../../include/SDL_active.h ../../../include/SDL_keyboard.h
Experiment.o: ../../../include/SDL_keysym.h ../../../include/SDL_mouse.h
Experiment.o: ../../../include/SDL_video.h ../../../include/SDL_mutex.h
Experiment.o: ../../../include/SDL_quit.h ../../../include/SDL_version.h
Experiment.o: ../../../include/SDL_opengl.h /usr/include/GL/gl.h
Experiment.o: /usr/include/GL/glext.h /usr/include/GL/glu.h
Experiment.o: ../../core/World.h /usr/include/stdlib.h
Experiment.o: /usr/include/sys/types.h /usr/include/time.h
Experiment.o: /usr/include/endian.h /usr/include/bits/endian.h
Experiment.o: /usr/include/sys/select.h /usr/include/bits/select.h
Experiment.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
Experiment.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
Experiment.o: /usr/include/alloca.h ../../util/Logger.h
Experiment.o: ../../core/Renderable.h ../../object3D/Object3D.h
Experiment.o: ../../geometry/Vector3D.h ../../geometry/Dimension3D.h
Experiment.o: ../../geometry/Dimension.h ../../geometry/Vector3D.h
Experiment.o: ../../paint/Paint.h /usr/include/string.h
Experiment.o: ../../texture/Texture.h ../../../include/SDL_image.h
Experiment.o: ../../../include/SDL.h ../../geometry/Vector2D.h
Experiment.o: ../../paint/Color.h ../../core/Renderable.h ../../core/Window.h
Experiment.o: ../../event/reshape/ReshapeListener.h
Experiment.o: ../../event/reshape/ReshapeEvent.h ../../../include/SDL.h
Experiment.o: ../../geometry/Dimension2D.h ../../geometry/Dimension2D.h
Experiment.o: ../../core/CameraListener.h ../../paint/Color.h
Experiment.o: ../../transform/Orientation.h ../../transform/Transform.h
Experiment.o: ../../transform/Translate.h ../../event/timer/Timer.h
Experiment.o: /usr/include/math.h /usr/include/bits/huge_val.h
Experiment.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
Experiment.o: ../../event/timer/TimerListener.h ../../event/Action.h
Experiment.o: ../../interpolation/InterpolatorFactory.h
Experiment.o: ../../interpolation/Interpolator.h
Experiment.o: ../../interpolation/LinearInterpolator.h
Experiment.o: ../../util/GraphicsConversionUtility.h
Experiment.o: ../../interpolation/Interpolator.h ../../transform/Rotate.h
Experiment.o: ../../event/ContinuousAction.h ../../event/Action.h
Experiment.o: ../../event/timer/TimerListener.h
Experiment.o: ../../event/timer/TimerListenerManager.h
Experiment.o: ../../event/timer/Timer.h ../../core/Controller.h
Experiment.o: ../../event/EventFactory.h ../../event/keyboard/Keyboard.h
Experiment.o: ../../event/keyboard/KeyboardListener.h
Experiment.o: ../../event/keyboard/KeyEvent.h
Experiment.o: ../../event/keyboard/KeyEventFactory.h
Experiment.o: ../../event/keyboard/KeyDownEvent.h
Experiment.o: ../../event/keyboard/KeyUpEvent.h ../../event/mouse/Mouse.h
Experiment.o: ../../event/mouse/MouseListener.h
Experiment.o: ../../event/mouse/MouseEvent.h
Experiment.o: ../../event/mouse/MouseEventFactory.h
Experiment.o: ../../event/mouse/MouseButtonDown.h
Experiment.o: ../../event/mouse/MouseClickEvent.h
Experiment.o: ../../event/mouse/MouseButtonUp.h
Experiment.o: ../../event/mouse/MouseMotionEvent.h ../../event/timer/Timer.h
Experiment.o: ../../event/keyboard/Keyboard.h ../../event/mouse/Mouse.h
Experiment.o: ../../object3D/Point3D.h ../../object3D/Object3D.h
Experiment.o: ../../core/XavierConfiguration.h
Experiment.o: ../../transform/CoordinateSystem.h ../../transform/Scale.h
Experiment.o: ../../interpolation/InterpolationEngine.h
Experiment.o: ../../interpolation/InterpolationListener.h
Experiment.o: ../../interpolation/InterpolatorFactory.h
Experiment.o: ../../event/InputEventProxyFactory.h ../../event/EventFactory.h
Experiment.o: ../../event/keyboard/KeyboardStub.h
Experiment.o: ../../multicast/MulticastSocket.h ../../multicast/Multicast.h
Experiment.o: /usr/include/sys/socket.h /usr/include/sys/uio.h
Experiment.o: /usr/include/bits/uio.h /usr/include/bits/socket.h
Experiment.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
Experiment.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
Experiment.o: /usr/include/bits/posix2_lim.h /usr/include/bits/sockaddr.h
Experiment.o: /usr/include/asm/socket.h /usr/include/asm-i386/socket.h
Experiment.o: /usr/include/asm/sockios.h /usr/include/asm-i386/sockios.h
Experiment.o: /usr/include/netinet/in.h /usr/include/stdint.h
Experiment.o: /usr/include/bits/in.h /usr/include/bits/byteswap.h
Experiment.o: /usr/include/arpa/inet.h /usr/include/unistd.h
Experiment.o: /usr/include/bits/posix_opt.h /usr/include/bits/confname.h
Experiment.o: /usr/include/getopt.h ../../multicast/MulticastSocketPool.h
Experiment.o: ../../multicast/MulticastSocket.h
Experiment.o: ../../event/keyboard/Keyboard.h ../../event/mouse/MouseStub.h
Experiment.o: ../../event/mouse/Mouse.h ../../event/timer/TimerStub.h
Experiment.o: ../../core/Camera.h ../../transform/CoordinateSystemFactory.h
Experiment.o: ../../transform/CoordinateSystem.h
Experiment.o: ../../transform/OpenGLCoordinateSystem.h
Experiment.o: ../../transform/MacCoordinateSystem.h
Experiment.o: ../../transform/MathCoordinateSystem.h
Experiment.o: ../../transform/LeftOpenGLCoordinateSystem.h
Experiment.o: ../../transform/EngineerCoordinateSystem.h
Experiment.o: ../../event/timer/TimerListener.h
Experiment.o: ../../event/reshape/ReshapeEvent.h ../../core/CameraListener.h
Experiment.o: ../../core/Controller.h ../../core/DebugCamera.h
Experiment.o: ../../core/Controller.h ../../core/Renderable.h
Experiment.o: ../../core/Window.h ../../core/World.h
Experiment.o: ../../core/XavierConfiguration.h ../../event/Action.h
Experiment.o: ../../event/DelayedAction.h ../../event/timer/IntervalTimer.h
Experiment.o: ../../event/EventFactory.h
Experiment.o: ../../event/FullEventHandlerFactory.h
Experiment.o: ../../event/keyboard/KeyboardSkeleton.h
Experiment.o: ../../../include/SDL_thread.h ../../event/mouse/MouseSkeleton.h
Experiment.o: ../../event/timer/TimerSkeleton.h
Experiment.o: ../../event/FullEventProxyFactory.h
Experiment.o: ../../event/InputEventHandlerFactory.h
Experiment.o: ../../event/InputEventProxyFactory.h
Experiment.o: ../../event/ContinuousAction.h
Experiment.o: ../../event/keyboard/DefaultKeyboardListener.h
Experiment.o: ../../interpolation/TimedInterpolation.h
Experiment.o: ../../core/Controller.h
Experiment.o: ../../interpolation/InterpolationEngine.h ../../core/World.h
Experiment.o: ../../event/keyboard/Keyboard.h
Experiment.o: ../../event/keyboard/KeyboardListener.h
Experiment.o: ../../event/keyboard/KeyboardSkeleton.h
Experiment.o: ../../event/keyboard/KeyboardStub.h
Experiment.o: ../../event/keyboard/KeyDownEvent.h
Experiment.o: ../../event/keyboard/KeyEvent.h
Experiment.o: ../../event/keyboard/KeyEventFactory.h
Experiment.o: ../../event/keyboard/KeyUpEvent.h
Experiment.o: ../../event/keyboard/RegularKeyEvent.h
Experiment.o: ../../event/keyboard/SpecialKeyEvent.h
Experiment.o: ../../event/mouse/DefaultMouseListener.h
Experiment.o: ../../event/mouse/Mouse.h ../../event/mouse/MouseButtonDown.h
Experiment.o: ../../event/mouse/MouseButtonUp.h
Experiment.o: ../../event/mouse/MouseClickEvent.h
Experiment.o: ../../event/mouse/MouseEvent.h
Experiment.o: ../../event/mouse/MouseEventFactory.h
Experiment.o: ../../event/mouse/MouseListener.h
Experiment.o: ../../event/mouse/MouseMotionEvent.h
Experiment.o: ../../event/mouse/MouseSkeleton.h ../../event/mouse/MouseStub.h
Experiment.o: ../../event/reshape/ReshapeEvent.h
Experiment.o: ../../event/reshape/ReshapeListener.h
Experiment.o: ../../event/timer/IntervalTimer.h ../../event/timer/Timer.h
Experiment.o: ../../event/timer/TimerListener.h
Experiment.o: ../../event/timer/TimerSkeleton.h ../../event/timer/TimerStub.h
Experiment.o: ../../event/timer/TimerListenerManager.h
Experiment.o: ../../geometry/CylindricalVolume.h ../../geometry/Dimension.h
Experiment.o: ../../geometry/Dimension2D.h ../../geometry/Dimension3D.h
Experiment.o: ../../geometry/RectangularVolume.h ../../geometry/Dimension3D.h
Experiment.o: ../../geometry/Vector2D.h ../../geometry/Vector3D.h
Experiment.o: ../../interpolation/CameraRoller.h
Experiment.o: ../../interpolation/ContinuousInterpolation.h
Experiment.o: ../../interpolation/TimedInterpolation.h
Experiment.o: ../../interpolation/InterpolationEngine.h
Experiment.o: ../../interpolation/InterpolationListener.h
Experiment.o: ../../interpolation/Interpolator.h
Experiment.o: ../../interpolation/InterpolatorFactory.h
Experiment.o: ../../interpolation/LinearInterpolator.h
Experiment.o: ../../interpolation/TimedInterpolation.h
Experiment.o: ../../interpolation/Waypoint.h
Experiment.o: ../../interpolation/WaypointCollection.h
Experiment.o: ../../interpolation/Waypoint.h ../../model/MilkshapeModel.h
Experiment.o: ../../model/Model.h ../../texture/TextureFactory.h
Experiment.o: ../../texture/Texture.h ../../model/Model.h
Experiment.o: ../../model/ModelFactory.h ../../model/MilkshapeModel.h
Experiment.o: ../../multicast/mcreceive.h ../../multicast/mcsend.h
Experiment.o: ../../multicast/Multicast.h ../../multicast/MulticastSocket.h
Experiment.o: ../../multicast/MulticastSocketPool.h ../../object2D/Object2D.h
Experiment.o: ../../core/Window.h ../../object2D/Point2D.h
Experiment.o: ../../object2D/Rectangle2D.h ../../object2D/Object2D.h
Experiment.o: ../../object2D/String2D.h ../../util/BitmapFontUtil.h
Experiment.o: ../../util/BitmapFontConstants.h
Experiment.o: ../../object2D/Transformable2D.h
Experiment.o: ../../transform/Transformable.h ../../transform/Transform.h
Experiment.o: ../../object3D/AdornablePrism.h
Experiment.o: ../../object3D/RectangularPrism.h ../../util/PointScale.h
Experiment.o: ../../object3D/Quadrilateral3D.h ../../texture/TextureScale.h
Experiment.o: ../../geometry/RectangularVolume.h
Experiment.o: ../../object3D/Object3DCollection.h
Experiment.o: ../../object3D/CompiledObject3D.h ../../object3D/Arc3D.h
Experiment.o: ../../object3D/Point3D.h ../../object3D/CompiledObject3D.h
Experiment.o: ../../object3D/Cube.h ../../object3D/ExtrudedNormalPolygon3D.h
Experiment.o: ../../object3D/NormalPolygon3D.h
Experiment.o: ../../object3D/NoDepthTestQuadrilateral3D.h
Experiment.o: ../../object3D/NormalPolygon3D.h ../../object3D/Object3D.h
Experiment.o: ../../object3D/Object3DCollection.h ../../object3D/Particle.h
Experiment.o: ../../object3D/Point3D.h ../../object3D/Quadrilateral3D.h
Experiment.o: ../../object3D/RectangularPrism.h
Experiment.o: ../../object3D/RectangularPrismFactory.h
Experiment.o: ../../object3D/Sprite3D.h ../../object3D/Sprite3DListener.h
Experiment.o: ../../object3D/Sprite3DListener.h
Experiment.o: ../../object3D/Transformable3D.h ../../object3D/Triangle3D.h
Experiment.o: ../../paint/Color.h ../../paint/Paint.h
Experiment.o: ../../shape/CollisionRenderable.h
Experiment.o: ../../terrain/FunctionHeightFieldStrategy.h
Experiment.o: ../../terrain/HeightFieldStrategy.h ../../terrain/HeightField.h
Experiment.o: ../../object3D/Quadrilateral3D.h ../../terrain/HeightField.h
Experiment.o: ../../terrain/HeightFieldFactory.h
Experiment.o: ../../terrain/HeightFieldStrategy.h
Experiment.o: ../../terrain/ImageHeightFieldStrategy.h
Experiment.o: ../../terrain/MatrixHeightFieldStrategy.h
Experiment.o: ../../terrain/NullHeightFieldStrategy.h ../../texture/Texture.h
Experiment.o: ../../texture/TextureFactory.h ../../texture/TextureScale.h
Experiment.o: ../../transform/CoordinateSystem.h
Experiment.o: ../../transform/CoordinateSystemFactory.h
Experiment.o: ../../transform/EngineerCoordinateSystem.h
Experiment.o: ../../transform/IdentityTransform.h
Experiment.o: ../../transform/LeftOpenGLCoordinateSystem.h
Experiment.o: ../../transform/MacCoordinateSystem.h
Experiment.o: ../../transform/MathCoordinateSystem.h
Experiment.o: ../../transform/OpenGLCoordinateSystem.h
Experiment.o: ../../transform/Orientation.h ../../transform/Rotate.h
Experiment.o: ../../transform/Scale.h ../../transform/Stretch.h
Experiment.o: ../../transform/Transform.h ../../transform/Transformable.h
Experiment.o: ../../transform/TransformFactory.h ../../transform/Translate.h
Experiment.o: ../../util/BehaviorParser.h ../../transform/TransformFactory.h
Experiment.o: ../../util/BitmapFontConstants.h ../../util/BitmapFontUtil.h
Experiment.o: ../../util/FramesPerSecondCounter.h ../../object2D/String2D.h
Experiment.o: ../../util/GraphicsConversionUtility.h ../../util/Logger.h
Experiment.o: ../../util/PointScale.h ../../util/xmlParser.h
