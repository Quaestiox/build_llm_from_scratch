#include "../include/mtx.h"
#include <time.h>

int main(){
    srand(time(0));
    Mtx *mtx = init_mtx(3, 3);
    rand_mtx(mtx);
    print_mtx(*mtx, "try");
    print_mtx(*mtx, NULL);
    free(mtx);
}
