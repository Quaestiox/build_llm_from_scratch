flags := -Wall -Wextra

build_dir := ./build
obj_dir := ${build_dir}/obj

srcs := util.c mtx.c
test_dir := ./test
tests := $(wildcard ${test_dir}/*.c)
objs := $(patsubst %.c,${obj_dir}/%.o,${srcs})

all: 

regression: ${objs}
	mkdir -p ${build_dir}
	clang ${flags} regression.c ${objs} -o ${build_dir}/regression
	${build_dir}/regression

class: ${objs}
	mkdir -p ${build_dir}
	clang ${flags} classification.c ${objs} -o ${build_dir}/classification
	${build_dir}/classification

countb: ${obj_dir}/util.o
	mkdir -p ${build_dir}
	clang ${flags} count_based.c ${obj_dir}/util.o -o ${build_dir}/count_based
	${build_dir}/count_based

cbow: ${objs}
	mkdir -p ${build_dir}
	clang ${flags} cbow.c ${objs} -o ${build_dir}/cbow
	${build_dir}/cbow

${obj_dir}/%.o: %.c
	mkdir -p ${obj_dir}
	clang ${flags} -c $< -o $@

util_test: ${objs}
	mkdir -p ${build_dir}
	clang ${flags} ${test_dir}/util_test.c ${objs} -o ${build_dir}/util_test
	${build_dir}/util_test

mtx_test: ${objs}
	mkdir -p ${build_dir}
	clang ${flags} ${test_dir}/mtx_test.c ${objs} -o ${build_dir}/mtx_test
	${build_dir}/mtx_test

clean:
	rm -rf ${build_dir}

.PHONY: all regression class clean countb test
