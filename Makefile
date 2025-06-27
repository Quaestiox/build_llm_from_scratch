#flags := -Wall -Wextra
#build_dir := ./build
#obj_dir := ${build_dir}/obj
#NEED := ${obj_dir}/util.o
#
#all: 
#
#.PHONY: all regression util
#
#regression: ${NEED}
#	mkdir -p build
#	clang ${flags} ./regression.c ${NEED} -o ${build_dir}/regression
#	${build_dir}/regression
#
#class: ${NEED}
#	mkdir -p build
#	clang ${flags} ./classification.c ${NEED} -o ${build_dir}/classification
#	${build_dir}/classification
#
#util: 
#	mkdir -p build
#	clang ${flags} ./util.c -o ${build_dir}/util
#	${build_dir}/util
#
#${obj_dir}/%.o: %.c
#	mkdir -p ${obj_dir}
#	clang ${flags} -c $< -o ${obj_dir}/$@
#
#clean: 
#	rm -r ${build_dir}
#

flags := -Wall -Wextra

build_dir := ./build
obj_dir := ${build_dir}/obj

SRCS := util.c
OBJS := $(patsubst %.c,${obj_dir}/%.o,${SRCS})

all: regression classification

regression: ${OBJS}
	mkdir -p ${build_dir}
	clang ${flags} regression.c ${OBJS} -o ${build_dir}/regression
	${build_dir}/regression

class: ${OBJS}
	mkdir -p ${build_dir}
	clang ${flags} classification.c ${OBJS} -o ${build_dir}/classification
	${build_dir}/classification

${obj_dir}/%.o: %.c
	mkdir -p ${obj_dir}
	clang ${flags} -c $< -o $@

clean:
	rm -rf ${build_dir}

.PHONY: all regression classification clean
