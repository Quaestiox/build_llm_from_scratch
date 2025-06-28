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
