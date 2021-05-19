#include "figure.h"
#include "points.h"

size_t get_fig_n(const figure& fig)
{
    return fig.n;
}

bool is_empty(const figure& fig)
{
    return !(fig.arr && fig.matrix && get_fig_n(fig));
}

rc_type free_fig(figure& fig)
{
    if (fig.arr)
        delete [] fig.arr;

    if (fig.matrix)
        delete_matrix(fig.matrix, fig.n);

    fig.n = 0;
    fig.matrix = NULL;
    fig.arr = NULL;

    return OK;
}

figure init_fig()
{
    figure fig;
    fig.n = 0;
    fig.matrix = NULL;
    fig.arr = NULL;
    return fig;
}

bool get_matrix_el(const figure& fig, size_t i, size_t j)
{
    return fig.matrix[i][j];
}

void set_fig_matrix(figure& fig, matrix_t matrix)
{
    fig.matrix = matrix;
}

void set_fig_arr(figure& fig, array_t arr)
{
    fig.arr = arr;
}

void set_fig_n(figure& fig, size_t n)
{
    fig.n = n;
}
