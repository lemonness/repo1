SRC = $(wildcard *.c)  
OBJ = $(patsubst %.c,%.o, ${SRC}) 
CC=gcc
CFLAGS = -g -Wall   -pthread
 
# 目标文件
TARGET:ptd_sync ptd_rwlock cond_consumer_producer multicons_producer
$(TARGET):${OBJ}
	$(CC)    $^  -o  $@    $(CFLAGS) 

%.o:%.c
	$(CC) $(CFLAGS) -c  $< -o $@

.PHONY:clean
clean:
	rm -rf *.o

