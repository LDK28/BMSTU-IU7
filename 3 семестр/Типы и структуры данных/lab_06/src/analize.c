/**
 * @file analize.c
 * @author Vladimir Larin
 * @brief Analize module
 *
 * @copyright Copyright (c) 2020
 *
 */
#include "inc/analize.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "inc/avl_tree.h"
#include "inc/btree.h"
#include "inc/hash_funcs.h"
#include "inc/hash_table.h"
#include "inc/utils.h"

#define MAX_ARRAY_SIZE 1000000

static int counts = 500;
extern char *filename_data_global;
#define HASH_FUNC hash_pearson


int fill_array(char **array) {
  int size = 0;
  FILE *file = fopen(filename_data_global, "r");
  if (!file) return -1;
  while (size < MAX_ARRAY_SIZE && !feof(file)) {
    char *str = NULL;
    size_t n = 0;
    size_t len = getline(&str, &n, file);
    str[len - 1] = 0;
    if (len <= 1) {
      free(str);
      continue;
    }
    array[size] = str;
    size++;
  }
  fclose(file);

  return size;
}

void free_array(char **array, int size) {
  for (int i = 0; i < size; i++) free(array[i]);
}

static FILE *table_file = NULL;

int analyze_export_csv_initter(char **names, int num, char *message) {
  table_file = fopen("temp.html", "w");
  if (message) fprintf(table_file, "<p> %s </p>", message);
  fprintf(table_file, "<table class='table table-bordered'> <thead> <tr>");
  fprintf(table_file, "<th rowspan=2>Размерность СД </td>");
  for (size_t i = 0; i < num; i++) {
    fprintf(table_file, "<th colspan=3> %s </td>", names[i]);
  }
  fprintf(table_file, "</tr> <tr>");

  for (size_t i = 0; i < num; i++) {
    fprintf(table_file, "<td> Время, тики </td>");
    fprintf(table_file, "<td> Кол-во сравнений </td>");
    fprintf(table_file, "<td> Объём СД, Байты </td>");
  }
  fprintf(table_file, "</tr></thead><tbody>");

  return 0;
}

int analyze_export_csv_line(analyze_report_t *reports, int num, size_t size,
                            size_t counts) {
  fprintf(table_file, "<tr><th> %zu </th>", size);

  for (size_t i = 0; i < num; i++) {
    fprintf(table_file, "<td>%.3lf</td>",
            1. * reports[i].time / (counts * size));
    fprintf(table_file, "<td>%.3lf</td>",
            1. * reports[i].cmps / (counts * size));
    fprintf(table_file, "<td>%zu</td>", reports[i].memory);
  }
  fprintf(table_file, "</tr>");

  return 0;
}

int analyze_export_csv_finisher() {
  fprintf(table_file, "</tbody></table>");
  fprintf(table_file,
          "<link "
          "href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.0.0-beta1/dist/css/"
          "bootstrap.min.css\" rel=\"stylesheet\" crossorigin=\"anonymous\">");
  fclose(table_file);

  system("open -a \"Google Chrome\" ./temp.html");

  return 0;
}

int analyze_wrapper() {
  char *names[] = {"Двоичное дерево поиска", "АВЛ дерево", "Хэш таблица"};

  analyze_export_csv_initter(
      names, 3,
      "Анализ был проведен для добавления элемента в дерево. В таблице "
      "приведено среднее значения для 1000 повторений");

  char *array[MAX_ARRAY_SIZE] = {0};
  int data_size = fill_array(array);

  for (int size = 16; size <= data_size; size *= 2) {
    analyze_report_t reports[3] = {0};

    size_t hash_table_size = next_prime(size * 0.85);

    for (size_t i = 0; i < counts; i++) {
      btree_t *btree = init_btree(strcmp_connector);
      avl_tree_t *avl_tree = init_avl_tree(strcmp_connector);
      hash_table_t *table =
          init_hash_table(hash_table_size, HASH_FUNC, strcmp_connector);

      clock_t start = clock();
      for (size_t i = 0; i < size; i++)
        add_btree_cmps(btree, strdup(array[i]), &(reports[0].cmps));
      reports[0].time += clock() - start;

      start = clock();
      for (size_t i = 0; i < size; i++)
        add_avl_tree_cmps(avl_tree, strdup(array[i]), &(reports[1].cmps));
      reports[1].time += clock() - start;

      start = clock();
      for (size_t i = 0; i < size; i++)
        add_element_hash_table_cmps(table, strdup(array[i]),
                                    &(reports[2].cmps));
      reports[2].time += clock() - start;

      btree_free(btree);
      free_avl_tree(avl_tree);
      free_hash_table(table);
    }

    reports[0].memory = sizeof(btree_node_t) * size + sizeof(btree_t);

    reports[1].memory = sizeof(avl_tree_node_t) * size + sizeof(avl_tree_t);

    reports[2].memory = sizeof(hash_table_node_t *) * hash_table_size +
                        sizeof(hash_table_t) + sizeof(hash_table_node_t) * size;

    analyze_export_csv_line(reports, 3, size, counts);
  }

  free_array(array, data_size);

  analyze_export_csv_finisher();

  return 0;
}

int find_in_file_cmps(FILE *file, char *elem, int size, avl_tree_cmp_t cmp,
                      size_t *cmps) {
  rewind(file);
  char *str = calloc(100, 1);
  size_t n = 100;
  int cur_s = 0;
  while (cmp(str, elem) && !feof(file) && cur_s <= size) {
    if (cmps) (*cmps)++;
    size_t len = getline(&str, &n, file);
    str[len - 1] = 0;
    cur_s++;
  }
  free(str);

  return 0;
}

int analyze_has_wrapper() {
  char *array[MAX_ARRAY_SIZE] = {0};
  int size_data = fill_array(array);

  char *names[] = {"Двоичное дерево поиска", "АВЛ дерево", "Хэш таблица",
                   "Файл"};

  analyze_export_csv_initter(
      names, 4,
      "Анализ был проведен для поиска элемента в дереве. В таблице"
      "приведено среднее значения для 1000 повторений");

  for (size_t size = 16; size <= size_data; size *= 2) {
    analyze_report_t reports[4] = {0};

    size_t hash_table_size = next_prime(size * 0.85);

    btree_t *btree = init_btree(strcmp_connector);
    avl_tree_t *avl_tree = init_avl_tree(strcmp_connector);
    hash_table_t *table =
        init_hash_table(hash_table_size, HASH_FUNC, strcmp_connector);

    for (size_t i = 0; i < size; i++) {
      add_avl_tree(avl_tree, strdup(array[i]));
      add_btree(btree, strdup(array[i]));
      add_element_hash_table(table, strdup(array[i]));
    }

    FILE *file = fopen(filename_data_global, "r");

    for (size_t i = 0; i < counts; i++) {
      clock_t start = clock();
      for (size_t i = 0; i < size; i++)
        has_element_btree_cmps(btree, array[i], &(reports[0].cmps));
      reports[0].time += clock() - start;

      start = clock();
      for (size_t i = 0; i < size; i++)
        has_avl_tree_cmps(avl_tree, array[i], &(reports[1].cmps));
      reports[1].time += clock() - start;

      start = clock();
      for (size_t i = 0; i < size; i++)
        has_element_hash_table_cmps(table, array[i], &(reports[2].cmps));
      reports[2].time += clock() - start;

      start = clock();
      for (size_t i = 0; i < size; i++)
        find_in_file_cmps(file, array[i], size, strcmp_connector,
                          &(reports[3].cmps));
      reports[3].time += clock() - start;
    }

    fclose(file);
    btree_free(btree);
    free_avl_tree(avl_tree);
    free_hash_table(table);

    reports[0].memory = sizeof(btree_node_t) * size + sizeof(btree_t);

    reports[1].memory = sizeof(avl_tree_node_t) * size + sizeof(avl_tree_t);

    reports[2].memory = sizeof(hash_table_node_t *) * hash_table_size +
                        sizeof(hash_table_t) + sizeof(hash_table_node_t) * size;
    reports[3].memory = 0;

    analyze_export_csv_line(reports, 4, size, counts);
  }

  free_array(array, size_data);

  analyze_export_csv_finisher();

  return 0;
}
