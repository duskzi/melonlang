CC      = cc
CFLAGS  = -Wall -Wextra -std=c11 -MMD -MP
OUT     = out
TARGET  = $(OUT)/melon

SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:src/%.c=$(OUT)/%.o)
DEPS = $(OBJS:.o=.d)

build: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OUT)/%.o: src/%.c | $(OUT)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT):
	mkdir -p $@

run: build
	./$(TARGET) $(ARGS)

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)

-include $(DEPS)

.PHONY: build run clean