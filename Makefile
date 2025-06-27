flags := -Wall -Wextra
build_dir := ./build

all: 

.PHONY: all linear

linear: 
	mkdir -p build
	clang ${flags} ./linear.c -o ${build_dir}/linear
	${build_dir}/linear

clean: 
	rm -r ${build_dir}


