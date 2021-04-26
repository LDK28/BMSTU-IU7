#ifndef INC_ANALIZE_H_
#define INC_ANALIZE_H_
/**
 * @file analize.h
 * @author Vladimir Larin
 * @brief Analize mpdule
 *
 * @copyright Copyright (c) 2020
 *
 */
#include <time.h>

typedef struct {
  clock_t time;
  size_t memory;
  size_t cmps;
} analyze_report_t;

int analyze_wrapper();
int analyze_has_wrapper();

#endif  // INC_ANALIZE_H_
