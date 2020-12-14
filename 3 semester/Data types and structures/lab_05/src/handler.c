#include "handler.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "queue.h"
#include "utils.h"

static double tick(double request_time[QUEUE_COUNT], double process_end_time) {
  double min = process_end_time;
  for (size_t i = 0; i < QUEUE_COUNT; i++)
    if (min > request_time[i]) min = request_time[i];

  return min;
}

static double calculated_process_time(queue_handler_config_t *c) {
  double d1 = c->queue[0].in_max + c->queue[0].in_min;
  double d2 = c->queue[0].proccess_max + c->queue[0].proccess_min;
  double max = d1;
  if (d2 > max) max = d2;

  return c->number_of_requests_1 * max / 2;
}

int create_handle_queues(queue_type_t type, queue_handler_config_t *config) {
  queue_t *queues[QUEUE_COUNT] = {0};
  for (size_t i = 0; i < QUEUE_COUNT; i++) queues[i] = create_queue(type);

  int err = handle_queue(queues, config);
  for (size_t i = 0; i < QUEUE_COUNT; i++) free_queue(queues[i]);

  return err;
}


int handle_queue(queue_t *queues[], queue_handler_config_t *config) {
  FILE *file = NULL;

  if (config->print_addresses) file = fopen("address.txt", "w");

  double request_time[QUEUE_COUNT] = {0};
  double req_num_on_time[QUEUE_COUNT] = {0};
  size_t req_num_processed[QUEUE_COUNT] = {0};
  size_t req_num_processed_all = 0;
  size_t req_num_generated_all = 0;

  double process_end_time = 0;
  double current_time = 0, last_time = 0;

  for (size_t i = 0; i < QUEUE_COUNT; i++)
  {
    queue_config_t c = config->queue[i];
    request_time[i] = random_double(c.in_min, c.in_max);
  }

  while (req_num_processed[0] < config->number_of_requests_1)
  {
    for (size_t i = 0; i < QUEUE_COUNT; i++) {
      if (current_time >= request_time[i]) {
        request_t req = {req_num_generated_all++};
        push_queue(queues[i], &req);
        if (config->print_addresses && queues[i]->type == QUEUE_LIST)
          fprintf(file, "Created: %p \n", queues[i]->queue.list->tail);
        queue_config_t c = config->queue[i];
        request_time[i] = current_time + random_double(c.in_min, c.in_max);
      }
    }

    if (current_time >= process_end_time) {
      int cur_queue = 0;
      if (is_empty_queue(queues[cur_queue])) cur_queue++;

      if (is_empty_queue(queues[cur_queue])) {
        // If no requests in queues
        current_time = tick(request_time, request_time[0] + request_time[1]);
        continue;
      }
      request_t req;
      pop_queue(queues[cur_queue], &req);
      req_num_processed[cur_queue]++;
      req_num_processed_all++;

      if (file && queues[0]->type == QUEUE_LIST)
        fprintf(file, "Closed:  %p \n", req.address);

      queue_config_t c = config->queue[cur_queue];
      
      process_end_time =
          current_time + random_double(c.proccess_min, c.proccess_max);

      if (config->print_stats && cur_queue == 0 &&
          req_num_processed[0] % 100 == 0) {
        printf("Processed: ");
        size_t sum = 0;
        for (size_t i = 0; i < QUEUE_COUNT; i++) {
          printf("%zu + ", req_num_processed[i]);
          sum += req_num_processed[i];
        }
        printf("\b\b= %zu (out of %zu logged in)\n", sum, req_num_generated_all);

        printf("Current length of the queue:\n");
        for (size_t i = 0; i < QUEUE_COUNT; i++) {
          printf("- requests %zu type: %zu\n", i + 1, length_queue(queues[i]));
        }
        printf("Average length of the queue:\n");
        for (size_t i = 0; i < QUEUE_COUNT; i++) {
          printf("- requests %zu type: %lf\n", i + 1,
                 req_num_on_time[i] / current_time);
        }
        // printf("Поступило заявок: %zu\n", req_num_generated_all);
        printf("Spent time: %lf е.в.\n", current_time);
        printf("==============\n");
      }
    }

    double diff = current_time - last_time;

    for (size_t i = 0; i < QUEUE_COUNT; i++)
      req_num_on_time[i] += length_queue(queues[i]) * diff;
    
    
    last_time = current_time;
    current_time = tick(request_time, process_end_time);
  }

  double calc_time = calculated_process_time(config);

  double perc_pogr = fabs((1 - current_time / calc_time)) * 100;

  if (!config->disable_print) {
    printf("Processed:\n");
    size_t sum = 0;
    for (size_t i = 0; i < QUEUE_COUNT; i++) {
      printf("- requests %zu type: %zu\n", i + 1, req_num_processed[i]);
      sum += req_num_processed[i];
    }
    // perc_pogr *= 0.7;
    printf("Total processed: %zu \n", sum);
    printf("Requests received: %zu \n", req_num_generated_all);

    printf("Calculated operating time:   %lf \n", calc_time);
    printf("Simulated operating time: %lf \n", current_time);
    printf("Inaccuracy: %lf%% \n", perc_pogr);
  }
  if (file) fclose(file);
  if (config->print_addresses && queues[0]->type == QUEUE_LIST)
    system("open address.txt");

  return 0;
}
