PROJECT_SOURCE_DIR?=.
PROJECT_BINARY_DIR?=build

all: build

# http://cprieto.com/posts/2016/10/cmake-out-of-source-build.html
.PHONY: configure
configure:
	cmake -H${PROJECT_SOURCE_DIR} -B${PROJECT_BINARY_DIR}

.PHONY: build
build: configure
	cmake --build ${PROJECT_BINARY_DIR}

clean:
	make -C ${PROJECT_BINARY_DIR} clean
