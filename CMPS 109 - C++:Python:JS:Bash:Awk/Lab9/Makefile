#######################################################################
#
# Copyright (C) 2018 David C. Harrison. All right reserved.
#
# You may not use, distribute, publish, or modify this code without 
# the express written permission of the copyright holder.
#
#######################################################################

CFLAGS = -Wall -Isrc -lpthread -lcrypt -g
CC = g++ -std=c++17

SRC=$(wildcard src/*.cc)

all: crack test

grade: clean crack test
	@./grade.sh 1000

clean:
	@rm -f radix make.out

submit: clean 
	@tar czvf ~/CMPS109-Lab9.tar.gz \
	    --exclude Makefile.h \
	    src/*.cc src/*.h
crack: src/main.cc crack.o
	$(CC) -o $@ $^ $(CFLAGS)
test: src/test.cc crack.o
	$(CC) -o $@ $^ $(CFLAGS) 
