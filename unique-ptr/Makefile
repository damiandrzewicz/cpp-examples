.PHONY: all build cmake clean format

BUILD_DIR := build
BUILD_TYPE ?= debug
BUILD_DIR_TYPE=${BUILD_DIR}/${BUILD_TYPE}
PROJECT_DIR := src

all: build run

${BUILD_DIR_TYPE}/Makefile:
	cmake \
		-B${BUILD_DIR_TYPE} \
		-DCMAKE_BUILD_TYPE=${BUILD_TYPE}

cmake: ${BUILD_DIR_TYPE}/Makefile

build: cmake
	$(MAKE) -C ${BUILD_DIR_TYPE} --no-print-directory

SRCS := $(shell find ./${PROJECT_DIR} -name '*.[ch]' -or -name '*.[ch]pp')
%.format: %
	clang-format -i $<
format: $(addsuffix .format, ${SRCS})

clean:
	rm -rf $(BUILD_DIR_TYPE)

run:
	$(BUILD_DIR_TYPE)/bin/main

