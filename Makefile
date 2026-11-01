NAME   := layout_intercept
LAYOUT ?= graphite

CC     := gcc
CFLAGS := -O2 -Wall -Wextra -pedantic -Wconversion -Wshadow -Werror

BUILD_DIR := ./bin
SRC_DIR   := ./src
SRCS      = $(wildcard ${SRC_DIR}/*.c) layouts/${LAYOUT}_layout.c configs/${CONFIG}_config.c
OBJS      = $(patsubst %.c, ${OBJ_DIR}/%.o, ${SRCS})

.PHONY: clean all debug release test testall

all: debug

testall: TFLAGS := --all --stream_suspend --bad_macro_suspend --stream_count 100000 --stream_sleep 1
testall: test

test: debug
	python test/main.py --path ${BUILD_DIR}/${NAME}-test --logic ${TFLAGS}

debug:   CFLAGS  += -fsanitize=address,undefined -g -D DEBUG
debug:   EXEC    := ${BUILD_DIR}/${NAME}-test
debug:   OBJ_DIR := ${BUILD_DIR}/debug
debug:   CONFIG  := test
debug:   build

release: EXEC    := /usr/local/bin/${NAME}
release: OBJ_DIR := ${BUILD_DIR}/release
release: CONFIG  := test # plug; rename when config done
release: build

build:
	@$(MAKE) --no-print-directory build_proxy EXEC="${EXEC}" CFLAGS="${CFLAGS}" OBJ_DIR="${OBJ_DIR}" SRCS="${SRCS}" OBJS="${OBJS}"

build_proxy: ${EXEC}

${EXEC}: ${OBJS}
	${CC} ${CFLAGS} $^ -o $@

${OBJ_DIR}/%.o: %.c
	@mkdir -p $(dir $@)
	${CC} ${CFLAGS} $< -c -o $@

clean:
	@rm -rf ${BUILD_DIR}
