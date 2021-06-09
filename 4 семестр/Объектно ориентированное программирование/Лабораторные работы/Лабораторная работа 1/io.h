#ifndef IO_H
#define IO_H

#include <stdlib.h>
#include <stdio.h>

#include "points.h"
#include "rc.h"

#define FILE_OPEN_TYPE "r"

typedef FILE * stream_t;

rc_type open_file_read(stream_t &stream, const char* filename, const char* open_type);
int read_from_file(struct figure &fig, stream_t f);
rc_type read_line_point(stream_t f, point& p);
rc_type read_line_matrix_el(stream_t f, int& mi, int& mj);

#endif
