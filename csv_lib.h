#ifndef CSV_LIB_H
#define CSV_LIB_H

#include "global.h"
#include <csv.h>

#define MAX_ROWS 150
#define MAX_COLS 10
#define MAX_FIELD_LEN 64

typedef struct {
    char ***matrix;
    size_t row;
    size_t col;
    size_t max_cols;
} CSVData;





#endif