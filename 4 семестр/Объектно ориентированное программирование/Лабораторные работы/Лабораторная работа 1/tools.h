#ifndef TOOLS_H
#define TOOLS_H

#include "points.h"
#include "rc.h"
#include "figure.h"
#include "io.h"

rc_type count_points(size_t& n, stream_t f);
rc_type allocate_fig(figure& fig);
rc_type fill_fig(figure& fig, size_t n, stream_t f);
#endif
