#include "io.h"
#include "matrix.h"
#include "points.h"
#include "figure.h"
#include "tools.h"
#include <iostream>

rc_type open_file_read(stream_t& stream, const char* filename, const char* open_type)
{
    stream_t file = fopen(filename, open_type);
    if (!file)
    {
        return ERR_OPEN_FILE;
    }
    stream  = file;
    return OK;
}

rc_type read_line_point(stream_t f, point& p)
{
   int n;
   double x, y, z;

   if (fscanf(f, "%d %lf %lf %lf", &n, &x, &y, &z) == 4)
   {
       set_point(p, x, y, z, n);
       return OK;
   }
   return ERR_INPUT;
}

rc_type read_line_matrix_el(stream_t f, int& mi, int& mj)
{
   return (fscanf(f, "%d->%d", &mi, &mj) == 2) ? OK : ERR_INPUT;
}

rc_type read_fig(figure& work, stream_t f)
{
    if (!f)
        return ERR_EMPTY;

    rc_type rc = OK;
    rc = count_points(work.n, f);
    if (rc) return rc;
    rc = allocate_fig(work);
    if (rc) return rc;

    rc = fill_fig(work, work.n, f);
    if (rc)
    {
        free_fig(work);
    }
    return rc;
}

int read_from_file(figure& fig, stream_t f)
{
    figure work = init_fig();

    rc_type rc = read_fig(work, f);

    if (rc == OK)
    {
         free_fig(fig);
         fig = work;
    }
    return rc;
}
