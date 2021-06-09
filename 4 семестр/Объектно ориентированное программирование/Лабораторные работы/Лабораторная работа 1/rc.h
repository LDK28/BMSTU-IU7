#ifndef RC_H
#define RC_H

#define OK 0
#define ERR_OPEN_FILE 1
#define ERR_EMPTY 2
#define ERR_INPUT 3
#define ERR_MEMORY 4
#define ERR_PARAMETR 5

typedef int rc_type;

void print_warning(rc_type rc);

#endif
