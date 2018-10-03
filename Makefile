
# Makefile for linux only.

CPP = gcc

CCOPT = -m32 -march=i686 -mcpu=i686 -O3 -static-libstdc++ -ffast-math -funroll-loops \
	-fomit-frame-pointer -fexpensive-optimizations -malign-loops=2 \
	-malign-jumps=2 -malign-functions=2 -fno-exceptions -fno-rtti -s

CPPFLAGS = ${CCOPT} -m32 -march=i686 -mcpu=i686 -w -I. -Ilibs/hlsdk/engine -Ilibs/hlsdk/common -Ilibs/hlsdk/pm_shared -Ilibs/hlsdk/dlls -Ilibs/metamod -static-libstdc++

OBJ = dllapi.o engine_api.o h_export.o meta_api.o sdk_util.o

tebex_metamod_i686.so: ${OBJ}
	${CPP} -m32 -march=i686 -mcpu=i686 -static-libstdc++ -static-libgcc -fPIC -shared -o $@ ${OBJ}
	-rm -f *.o

clean:
	-rm -f *.o
	-rm -f *.so	

%.o:	%.cpp
	${CPP} ${CPPFLAGS} -c $< -o $@

%.o:	%.c
	${CPP} ${CPPFLAGS} -c $< -o $@

