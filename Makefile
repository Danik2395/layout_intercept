NAME   := layout_intercept
LAYOUT ?= graphite

CC     := gcc
CFLAGS := -O2 -Wall -Wextra -pedantic -Wconversion -Wshadow -Werror

BUILD_DIR := ./bin
SRCS      := $(wildcard *.c) ./layouts/${LAYOUT}_layout.c
OBJS      := $(patsubst %.c, ${OBJ_DIR}/%.o, ${SRCS})

.PHONY: clean all debug release

all: debug

debug:   CFLAGS  += -fsanitize=address,undefined -g
debug:   EXEC    := ${BUILD_DIR}/${NAME}-test
debug:   OBJ_DIR := ${BUILD_DIR}/debug
debug:   build

release: EXEC    := ./${NAME}
release: OBJ_DIR := ${BUILD_DIR}/release
release: build

build:
	@$(MAKE) --no-print-directory build_proxy EXEC="${EXEC}" CFLAGS="${CFLAGS}" OBJ_DIR="${OBJ_DIR}"

build_proxy: ${EXEC}

${EXEC}: ${OBJS}
	${CC} ${CFLAGS} $^ -o $@

${OBJ_DIR}/%.o: %.c
	@mkdir -p ${BIN_DIR} ${OBJ_DIR}
	${CC} ${CFLAGS} $< -c -o $@

clean:
	@rm -rf ${BUILD_DIR}
