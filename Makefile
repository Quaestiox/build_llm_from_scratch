flags := -Wall -Wextra
build_dir := ./build

all: 

.PHONY: all regression util

regression: 
	mkdir -p build
	clang ${flags} ./regression.c -o ${build_dir}/regression
	${build_dir}/regression

util: 
	mkdir -p build
	clang ${flags} ./util.c -o ${build_dir}/util
	${build_dir}/util

clean: 
	rm -r ${build_dir}


