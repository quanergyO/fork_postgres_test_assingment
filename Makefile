CXX = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
FILES = cmd/main.c types/statData/Error.c types/statData/Result.c types/statData/StatData.c
OUTPUT = forkPostgres
TEST_FLAGS = -lcheck -pthread -lrt -lm -I/usr/include

build: clean
	mkdir build || true
	${CXX} -o ./build/${OUTPUT} ${CFLAGS} ${FILES}

run: build
	./build/${OUTPUT}

clean:
	rm -rf build

test:
	${CXX} ${CFLAGS} ${TEST_FLAGS} types/StatData.c tests/testStatData.c -o test
	./test
