#ifndef _HANDLING_H_
#define _HANDLING_H_

#include "queue.h"


#define QUEUE_COUNT 2

typedef struct {
  double in_min;
  double in_max;
  double proccess_min;
  double proccess_max;
} queue_config_t;

typedef struct {
  queue_config_t queue[QUEUE_COUNT];

  size_t number_of_requests_1;
  bool print_addresses;
  bool print_stats;
  bool disable_print;
} queue_handler_config_t;


int create_handle_queues(queue_type_t type, queue_handler_config_t *config);
int handle_queue(queue_t *queues[], queue_handler_config_t *config);

#endif  // _HANDLING_H_