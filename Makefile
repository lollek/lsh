
all: lsh

lsh: build/cmake-done
	$(MAKE) -C build

build/cmake-done:
	mkdir -p build && cd build && cmake ..
	touch $@

clean: build/cmake-done
	$(MAKE) -C build clean
