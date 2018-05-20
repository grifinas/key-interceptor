COMPILER=g++
MAIN=atest_intercep.cpp
OBJECT=interceptor.o
LIBDIR=-L.
LIBS=-linterception
WIN_INCLUDES=-IC:/Users/god/AppData/Local/Programs/Python/Python37/include
UIX_INCLUDES=-I/usr/include/python3.6
CFLAGS=-c -DNDEBUG -g -fwrapv -O3

OSFLAG 				:=
ifeq ($(OS),Windows_NT)
	OSFLAG =WIN32
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		OSFLAG =LINUX
	endif
	ifeq ($(UNAME_S),Darwin)
		OSFLAG =OSX
	endif
	ifneq ($(filter arm%,$(UNAME_P)),)
		OSFLAG =ARM
	endif
endif

ARCHFLAG:=
ifeq ($(OSFLAG), WIN32)
	ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
		ARCHFLAG=64
	endif
	ifeq ($(PROCESSOR_ARCHITECTURE),x86)
		ARCHFLAG=32
	endif
else
	UNAME_P := $(shell uname -p)
	ifeq ($(UNAME_P),x86_64)
		ARCHFLAG=64
	endif
	ifneq ($(filter %86,$(UNAME_P)),)
		ARCHFLAG=32
	endif
endif

ifeq ($(OSFLAG), WIN32)
	INCLUDES=$(WIN_INCLUDES)
	CLEAR=cls
	RUN=./a.exe
else
	INCLUDES=$(UIX_INCLUDES)
	CLEAR=clear
	RUN=./a.out
endif



build: clear compile link run

compile:
	$(COMPILER) $(CFLAGS) $(INCLUDES) $(MAIN) -o $(OBJECT)

link: $(OBJECT)
	$(COMPILER) $(OBJECT) $(LIBDIR) $(LIBS)

clear:
	$(CLEAR)

run:
	$(RUN)
