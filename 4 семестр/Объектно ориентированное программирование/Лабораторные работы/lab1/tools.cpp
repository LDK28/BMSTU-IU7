#include "io.h"
#include "matrix.h"
#include "points.h"
#include "figure.h"
#include "io.h"

rc_type count_points(size_t& n, stream_t f)
{
    if (!f)
        return ERR_OPEN_FILE;

    if (fscanf(f, "%zd",&n) == 1)
        return OK;

    return ERR_OPEN_FILE;
}

rc_type fill_arr(array_t arr, size_t n, stream_t f)
{
    if (!f || !n || !arr)
        return ERR_INPUT;
    point p;

    rc_type rc = OK;

    for (size_t i = 0; i < n && !rc; i++)
    {
        rc = read_line_point(f, p);
        if (rc == OK)
            arr[i] = p;
    }
    return rc;
}

rc_type fill_matrix(matrix_t& matrix, size_t n, stream_t f)
{
    if (!f || !n || !matrix)
        return ERR_INPUT;

    int mi, mj;
    while (read_line_matrix_el(f, mi, mj) == OK)
    {
        matrix[mi-1][mj-1] = true;
        matrix[mj-1][mi-1] = true;
    }
    return OK;
}

rc_type allocate_arr(array_t &arr, size_t n)
{
    array_t buf = new point[n];
    if (!buf)
        return ERR_MEMORY;
    arr = buf;
    return OK;
}

rc_type allocate_fig(figure& fig)
{
    rc_type rc = allocate_arr(fig.arr, fig.n);
    if (rc) return rc;
    rc = allocate_zero_matrix(fig.matrix, fig.n);
    if (rc)
    {
        free_fig(fig);
    }
    return rc;
}

rc_type fill_fig(figure& fig, size_t n, stream_t f)
{
    rc_type rc = OK;
    rc = fill_arr(fig.arr, n, f);
    if (rc) return rc;
    rc = fill_matrix(fig.matrix, n, f);
    return rc;
}
