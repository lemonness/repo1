SRC = $(wildcard *.c)  
OBJ = $(patsubst %.c,%.o, ${SRC}) 
CC=gcc
CFLAGS = -g -Wall   -pthread
 
# 目标文件
TARGET:pthread_more pthread_test
$(TARGET):${OBJ}
	$(CC)    $^  -o  $@    $(CFLAGS) 

%.o:%.c
	$(CC) $(CFLAGS) -c  $< -o $@

.PHONY:clean
clean:
	rm -rf *.o

