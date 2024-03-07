override PREFIX = c:\Users\Pavel\.vscode\extensions\anarcom.evcpp-0.0.10/../tools/toolchain/bin/arm-evcpp-linux-gnueabi-
includePath = c:\Users\Pavel\.vscode\extensions\anarcom.evcpp-0.0.10/../tools/include
apiPath = c:\Users\Pavel\.vscode\extensions\anarcom.evcpp-0.0.10/../tools/api

PREFIX ?= $(CROSS_COMPILE)
CC=$(PREFIX)g++
CFLAGS= -mcpu=arm9 -marm -O3 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -I"$(includePath)" -std=c++0x -MMD -MP -c
LDFLAGS=-static-libstdc++ -pthread -mcpu=arm9 -marm -O3 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -Xlinker --gc-sections -s 
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=program.elf
all: $(SOURCES) $(EXECUTABLE)
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(addprefix obj/,$(OBJECTS))  -o $@ -L"$(apiPath)" -lev3api -lm

.cpp.o:
	$(CC) $(CFLAGS) $< -o obj/$@
