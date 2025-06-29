flags := -Wall -Wextra

build_dir := ./build
obj_dir := ${build_dir}/obj

srcs := util.c
objs := $(patsubst %.c,${obj_dir}/%.o,${srcs})

all: regression classification

regression: ${objs}
	mkdir -p ${build_dir}
	clang ${flags} regression.c ${objs} -o ${build_dir}/regression
	${build_dir}/regression

class: ${objs}
	mkdir -p ${build_dir}
	clang ${flags} classification.c ${objs} -o ${build_dir}/classification
	${build_dir}/classification

countb: ${objs}
	mkdir -p ${build_dir}
	clang ${flags} count_based.c ${objs} -o ${build_dir}/count_based
	${build_dir}/count_based

${obj_dir}/%.o: %.c
	mkdir -p ${obj_dir}
	clang ${flags} -c $< -o $@

clean:
	rm -rf ${build_dir}

.PHONY: all regression class clean countb
