CMAKE_FLAGS=

all: build/lsh

.PHONY: debug
debug: CMAKE_FLAGS += -DCMAKE_BUILD_TYPE=Debug
debug: clean all

.PHONY: release
release: CMAKE_FLAGS += -DCMAKE_BUILD_TYPE=Release
release: clean all

.PHONY: build/lsh
build/lsh: build/cmake-done
	make -sC build
	cp $@ .

build/cmake-done:
	mkdir -p build && cd build && cmake $(CMAKE_FLAGS) ..
	touch $@

.PHONY: clean
clean:
	rm -rf build

%:
	make -sC build $@
