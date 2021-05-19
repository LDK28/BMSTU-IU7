#ifndef FIGURE_H
#define FIGURE_H

#include "points.h"
#include "matrix.h"
#include "rc.h"


struct figure
{
    point *arr;
    size_t n = 0;
    bool **matrix;
};

size_t get_fig_n(const figure& fig);
bool is_empty(const figure& fig);
rc_type free_fig(figure& fig);
figure init_fig();
bool get_matrix_el(const figure& fig, size_t i, size_t j);
void set_fig_n(figure& fig, size_t n);
void set_fig_arr(figure& fig, array_t arr);
void set_fig_matrix(figure& fig, matrix_t matrix);

#endif
