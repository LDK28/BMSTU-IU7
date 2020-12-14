#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

#include "io_matrix.h"
#include "matrix.h"
#include "random_matrix.h"

#define TEMP_FILE "./temp.out"
#define ACTIONS_COUNT 11

static matrix_t *full_matrix = NULL;
static sparse_matrix_t *sparse_matrix = NULL;

static matrix_t *full_vector = NULL;
static sparse_matrix_t *sparse_vector = NULL;

int input_matrix() {
  free_matrix(full_matrix);
  full_matrix = create_matrix_from_coord(stdin);
  if (!full_matrix) {
    return 1;
  }
  free_sparse_matrix(sparse_matrix);
  sparse_matrix = matrix_to_sparse(full_matrix);
  return 0;
}

int print_matrix_wrapper() {
  if (!full_matrix) {
    printf("Matrix is still empty. ");
    return 0;
  }
  print_matrix(stdout, full_matrix);
  print_sparse_matrix(stdout, full_matrix);

  return 0;
}

int random_matrix_wrapper() {
  size_t rows = 0, cols = 0, occupancy = 0;
  printf("Enter the matrix dimensions and fill percentage: ");

  if (scanf("%zu%zu%zu", &rows, &cols, &occupancy) != 3 || !rows || !cols ||
      occupancy > 100) {
    wait_and_clear();
    return 1;
  }

  free_matrix(full_matrix);
  full_matrix = create_random_matrix_by_occupancy(rows, cols, occupancy);
  free_sparse_matrix(sparse_matrix);
  sparse_matrix = matrix_to_sparse(full_matrix);

  wait_and_clear();
  return 0;
}

int random_vector_wrapper() {
  size_t cols = 0, occupancy = 0;
  printf("Enter the vector dimension and fill percentage: ");

  if (scanf("%zu%zu", &cols, &occupancy) != 2 || !cols || occupancy > 100) {
    wait_and_clear();
    return 1;
  }

  free_matrix(full_vector);
  full_vector = create_random_matrix_by_occupancy(1, cols, occupancy);
  free_sparse_matrix(sparse_vector);
  sparse_vector = matrix_to_sparse(full_vector);

  wait_and_clear();
  return 0;
}

int print_vector_wrapper() {
  if (!full_vector) {
    printf("Vector is still empty.  ");
    return 0;
  }
  print_matrix(stdout, full_vector);
  print_sparse_matrix(stdout, full_vector);

  return 0;
}

matrix_t *create_vector_from_coord(FILE *stream) {
  int err = 0;

  size_t cols = 0;
  size_t count = 0;
  if (stream == stdin)
    printf("Enter the number of columns and non-zero elements: ");

  if (!err) err = fscanf(stream, "%zu%zu", &cols, &count) != 2;

  if (!err && cols < count) err = 1;

  matrix_t *matrix = NULL;
  if (!err) matrix = init_matrix(1, cols);

  if (!err && !matrix) err = 1;

  for (size_t k = 0; k < count && !err; k++) {
    size_t j = 0;
    double element = 0;
    if (stream == stdin)
      printf("%3zu) Enter the column and element: ", k + 1);
    err = fscanf(stream, "%zu%" MATRIX_TYPE_SPECIF, &j, &element) != 2;
    if (!err && (j == 0)) err = 1;
    if (!err && (j > cols)) err = 1;
    if (!err) matrix->data[0][j - 1] = element;
  }

  if (err && matrix) {
    free_matrix(matrix);
    matrix = NULL;
  }

  return matrix;
}

int input_vector() {
  free_matrix(full_vector);
  full_vector = create_vector_from_coord(stdin);
  if (!full_vector) {
    return 1;
  }
  free_sparse_matrix(sparse_vector);
  sparse_vector = matrix_to_sparse(full_vector);
  return 0;
}

int mul_wrapper() {
  if (!full_matrix) {
    printf("Matrix is still empty. ");
    return 0;
  }

  if (!full_vector) {
    printf("Vector is still empty. ");
    return 0;
  }

  if (full_vector->cols != full_matrix->rows) {
    printf("Matrix %zuX%zu cannot be multiplied by a vector %zuX%zu.",
           full_matrix->rows, full_matrix->cols, full_vector->rows,
           full_vector->cols);
    return 0;
  }

  clock_t time_full = 0, time_sparse = 0;
  matrix_t *result_vector = mul(full_vector, full_matrix, &time_full);
  sparse_matrix_t *result_sparse =
      mul_sparse(sparse_vector, sparse_matrix, &time_sparse);

  matrix_t *temp = sparse_to_matrix(result_sparse);

  printf("### Result (standart).\n");
  print_matrix(stdout, result_vector);
  printf("\n### Result (advanced).\n");
  print_sparse_matrix(stdout, temp);

  printf("\nMultiplication of standart matrixes was in %ld tacts\n", time_full);
  printf("Multiplication of advanced matrixes was in %ld tacts\n",
         time_sparse);

  free_matrix(temp);
  free_matrix(result_vector);
  free_sparse_matrix(result_sparse);

  return 0;
}

size_t matrix_size(size_t rows, size_t cols) {
  return sizeof(matrix_t) + sizeof(matrix_type_t) * cols * rows;
}

size_t sparse_matrix_size(size_t cols, size_t count) {
  return (sizeof(matrix_type_t) + sizeof(size_t)) * count +
         sizeof(size_t) * (cols + 1);
}

int mul_analize() {
  size_t repeats = 10;
  printf("\n\nTime is indicated as a tact.\n");
  printf("Matrix memory is indicated as a byte.\n");
  printf("Fill is indicated as a percentage.\n\n");

  printf("| Size of   | Fill |        Time         |   Occupied memory   |\n");
  printf("| matrix    |      | standart | advenced | standart | advenced |\n");
  printf("|-----------|------|----------|----------|----------|----------|\n");

  for (size_t j = 10; j < 1001; j *= 10) {
    for (size_t i = 10; i <= 100; i += 10) {
      clock_t time_1 = 0, time_2 = 0;
      for (size_t k = 0; k < repeats; k++) {
        matrix_t *matrix = create_random_matrix_by_occupancy(j, j, i);
        matrix_t *vector = create_random_matrix_by_occupancy(1, j, i);
        sparse_matrix_t *sparse = matrix_to_sparse(matrix);
        sparse_matrix_t *svector = matrix_to_sparse(vector);

        clock_t cur_1 = 0;
        clock_t cur_2 = 0;

        free_matrix(mul(vector, matrix, &cur_1));
        free_sparse_matrix(mul_sparse(svector, sparse, &cur_2));
        time_1 += cur_1;
        time_2 += cur_2;

        free_matrix(matrix);
        free_matrix(vector);
        free_sparse_matrix(sparse);
        free_sparse_matrix(svector);
      }

      printf("|%4zu X %-4zu|  %3zu |%10ld|%10ld|%10zu|%10zu|\n", j, j, i,
             time_1 / repeats, time_2 / repeats,
             matrix_size(j, j) + matrix_size(1, j),
             sparse_matrix_size(j, j * j * i / 100) +
                 sparse_matrix_size(j, j * i / 100));
    }
  }
  return 0;
}

int clear_input() {
  int ch = 0;

  do {
    ch = getc(stdin);
  } while ((char)ch != '\n');

  return 0;
}

int wait_and_clear() {
  printf("Press any button to continue.\n");
  clear_input();
  system("clear");
  return 0;
}

void exit_handler() {
  exit(0);
}

void print_menu() {
  static struct {
    char *name;
    int (*action)(void);
  } actions[ACTIONS_COUNT] = {
      {.name = "Matrix", .action = NULL},
      {.name = "Input matrix", .action = input_matrix},
      {.name = "Generate random matrix", .action = random_matrix_wrapper},
      {.name = "Print matrix", .action = print_matrix_wrapper},
      {.name = "Vector", .action = NULL},
      {.name = "Input vector", .action = input_vector},
      {.name = "Generate random vector", .action = random_vector_wrapper},
      {.name = "Print vector", .action = print_vector_wrapper},
      {.name = "Multiplication", .action = NULL},
      {.name = "Multiply", .action = mul_wrapper},
      {.name = "Time comparison", .action = mul_analize},
  };

  printf("Menu \n\n");

  size_t diff = 0;
  for (size_t i = 0; i < ACTIONS_COUNT; i++) {
    if (actions[i].action) {
      printf("%3zu) %s\n", i + 1 - diff, actions[i].name);
    } else {
      diff++;
      printf("===== %s\n", actions[i].name);
    }
  }

  printf("\n  0) Exit \n");

  printf("Select action: ");
  int action = 0;
  if (scanf("%d", &action) == 0 || action > ACTIONS_COUNT - diff ||
      action < 0) {
    wait_and_clear();
    printf("Invalid input\n");
    return print_menu();
  }

  wait_and_clear();
  if (!action) return exit_handler();

  size_t i = 0;
  for (size_t j = 0; j < action; i++)
    if (actions[i].action) j++;

  if (actions[i - 1].action()) {
    wait_and_clear();
    printf("Error\n");
  }

  wait_and_clear();
  print_menu();
}