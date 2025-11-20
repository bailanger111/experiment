#编译器设置
CC = gcc
CFLAGES = -Wall -Wextra -std=c99
TARGET = 2220231553_mysh

#源文件
SRCS = main.c ls.c echo.c cat.c mkdir.c rm.c cd.c pwd.c wc.c
OBJS = $(SRCS:.c=.o)

#默认
all:$(TARGET)
#链接目标生成可执行文件
$(TARGET):$(OBJS)
	$(CC) $(CFLAGES) -o $(TARGET) $(OBJS)
	@echo "编译成功！可执行文件: $(TARGET)"
	@echo "运行命令: ./$(TARGET)"
#编译源文件为目标文件
%.o: %c command.h
	$(CC) $(CFLAGES) -c $< -o $@
#清理生成文件
clean:
	rm -f $(OBJS) $(TARGET)
install: $(TARGET)
	cp $cp $(TARGET) /usr/local/bin/

#重新编译
rebuild: clean all

#伪目标
.PHONY: all clean install rebuild