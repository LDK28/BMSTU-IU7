/**
 * @file io.c
 * @author Vladimir Larin (volodyalarin@bk.ru)
 * @brief Input output interface
 *
 * @copyright Copyright (c) 2020
 *
 */
#include "inc/io.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "inc/analize.h"
#include "inc/avl_tree.h"
#include "inc/btree.h"
#include "inc/hash_funcs.h"
#include "inc/hash_table.h"
#include "inc/utils.h"
extern char *filename_data_global;

static btree_t *btree_global = NULL;
static avl_tree_t *avl_tree_global = NULL;
static hash_table_t *hash_table_global = NULL;

char *read_element() {
  printf("Введите элемент строку: ");
  char *str = NULL;
  size_t n = 0;
  size_t len = getline(&str, &n, stdin);
  if (len < 2) {
    free(str);
    return NULL;
  }
  str[len - 1] = 0;
  return str;
}

int create_tree_wrapper() {
  btree_free(btree_global);
  btree_global = init_btree(strcmp_connector);
  avl_tree_global = init_avl_tree(strcmp_connector);

  FILE *file = fopen(filename_data_global, "r");
  if (!file) return -1;
  while (!feof(file)) {
    char *str = NULL;
    size_t n = 0;
    size_t len = getline(&str, &n, file);
    str[len - 1] = 0;
    if (len <= 1) {
      free(str);
      continue;
    }
    add_btree(btree_global, str);
    add_avl_tree(avl_tree_global, strdup(str));
  }
  fclose(file);
  return 0;
}

int add_element_wrapper() {
  char *str = read_element();
  if (!str) return -1;

  static char *statuses[] = {"Успешно", "Произошла ошибка"};

  int b_status = add_btree(btree_global, str) ? 0 : 1;
  int avl_status = add_avl_tree(avl_tree_global, strdup(str)) ? 0 : 1;
  int hash_status =
      hash_table_global
          ? add_element_hash_table(hash_table_global, strdup(str)) ? 0 : 1
          : 1;

  printf("Добавление в ДДП: %s\n", statuses[b_status]);
  printf("Добавление в АВЛ: %s\n", statuses[avl_status]);
  printf("Добавление в хэш-таблицу: %s\n", statuses[hash_status]);

  return 0;
}
int add_element_btree_wrapper() {
  char *str = read_element();
  if (!str) return -1;
  return add_btree(btree_global, str) ? 0 : -1;
}

int add_element_avl_tree_wrapper() {
  char *str = read_element();
  if (!str) return -1;
  return add_avl_tree(avl_tree_global, str) ? 0 : -1;
}

int add_element_hash_table_wrapper() {
  if (!hash_table_global) {
    printf("Хэш таблица не создана\n");
    return 0;
  }
  char *str = read_element();
  if (!str) return -1;
  return add_element_hash_table(hash_table_global, str) ? 0 : -1;
}

int has_element_wrapper() {
  char *str = read_element();
  if (!str) return -1;

  static char *statuses[] = {"Найден", "Не найден"};

  int b_status = has_element_btree(btree_global, str) ? 0 : 1;
  int avl_status = has_avl_tree(avl_tree_global, str) ? 0 : 1;
  int hash_status = hash_table_global
                        ? has_element_hash_table(hash_table_global, str) ? 0 : 1
                        : 1;
  free(str);

  printf("Поиск в ДДП: %s\n", statuses[b_status]);
  printf("Поиск в АВЛ: %s\n", statuses[avl_status]);
  if (hash_table_global)
    printf("Поиск в хэш-таблице: %s\n", statuses[hash_status]);

  return 0;
}

static FILE *file_dot_output = NULL;
void print_dot_btree_walker(btree_node_t *parent, btree_node_t *current) {
  int side = 0;
  char *sides[] = {"L", "R"};
  if (parent->right == current) side = 1;
  fprintf(file_dot_output, "\"%s\" -> \"%s\" [label=\"%s\"]; \n", parent->data,
          current->data, sides[side]);
}

void print_dot_avl_tree_walker(avl_tree_node_t *parent,
                               avl_tree_node_t *current) {
  int side = 0;
  char *sides[] = {"L", "R"};
  if (parent->right == current) side = 1;
  fprintf(file_dot_output, "\"%s %d\" -> \"%s %d\" [label=\"%s\"]; \n",
          parent->data, get_balance_avl_tree(parent), current->data,
          get_balance_avl_tree(current), sides[side]);
}

int print_btree_wrapper() {
  file_dot_output = fopen("temp.txt", "w");
  fprintf(file_dot_output, "digraph graphname {");
  btree_walker(btree_global, print_dot_btree_walker);
  fprintf(file_dot_output, "}");
  fclose(file_dot_output);
  file_dot_output = NULL;

  system("dot -Tpng temp.txt -otemp.png");
  system("open temp.png");
  system("clear");
  return 0;
}

int print_avl_tree_wrapper() {
  file_dot_output = fopen("temp.txt", "w");
  fprintf(file_dot_output, "digraph graphname {");
  avl_tree_walker(avl_tree_global, print_dot_avl_tree_walker);
  fprintf(file_dot_output, "}");
  fclose(file_dot_output);
  file_dot_output = NULL;

  system("dot -Tpng temp.txt -otemp.png");
  system("open temp.png");
  system("clear");
  return 0;
}

int read_hash_func(hash_func_t *hash) {
  printf("Выберите хэш функцию: \n");
  printf("  1. Сумма\n");
  printf("  2. XOR\n");
  printf("  3. Хеширование Пирсона\n");
  printf("  4. Хеширование djb2\n");

  int option = 0;
  if (scanf("%d", &option) != 1) return -1;

  switch (option) {
    case 1:
      *hash = hash_sum;
      break;
    case 2:
      *hash = hash_xor;
      break;
    case 3:
      *hash = hash_pearson;
      break;
    case 4:
      *hash = hash_djb2;
      break;
    default:
      return -1;
  }
  return 0;
}

int hash_table_info_wrapper() {
  if (!hash_table_global) {
    printf("Хэш таблица не создана\n");
    return 0;
  }

  printf("Используемая хэш функция: ");

  if (hash_table_global->hasher == hash_sum)
    printf("сумма\n");
  else if (hash_table_global->hasher == hash_xor)
    printf("xor\n");
  else if (hash_table_global->hasher == hash_pearson)
    printf("Пирсона\n");
  else if (hash_table_global->hasher == hash_djb2)
    printf("djb2\n");

  printf("Максимальное кол-во коллизий в таблице: %zu\n",
         hash_table_global->max_collision_num);

  printf("Размерность таблицы: %zu\n", hash_table_global->table_size);

  printf("Кол-во элементов в таблице: %zu\n",
         hash_table_global->elements_count);
  return 0;
}
int restruct_hash_table_wrapper() {
  if (!hash_table_global) {
    printf("Хэш таблица не создана\n");
    return 0;
  }
  hash_table_info_wrapper();
  size_t recomend_size = hash_table_global->elements_count * 0.72;
  if (recomend_size <= hash_table_global->table_size)
    recomend_size = hash_table_global->table_size * 1.2;

  recomend_size = next_prime(recomend_size);

  printf("Рекомендуемые параметры реструкторизации: \n");
  printf(" - хэширование Пирсона\n");
  printf(" - размерность таблицы: %zu\n", recomend_size);

  printf("Применить? (1-да , 0-ввести параметры вручную): \n");

  int option = -1;
  if (scanf("%d", &option) != 1) return -1;

  switch (option) {
    case 1:
      restruct_hash_table(&hash_table_global, recomend_size, hash_pearson);
      break;
    case 0: {
      hash_func_t hash = NULL;

      if (read_hash_func(&hash)) return -1;
      printf("Введите размерность таблицы: ");
      int size = 0;
      if (scanf("%d", &size) != 1 || size < 1) return -1;

      restruct_hash_table(&hash_table_global, size, hash);

      break;
    }
    default:
      return -1;
  }

  clear_input();

  printf("Текущее максимальное кол-во коллизий в таблице: %zu\n",
         hash_table_global->max_collision_num);

  return 0;
}

int restruct_hash_table_automatic_wrapper() {
  if (!hash_table_global) {
    printf("Хэш таблица не создана\n");
    return 0;
  }

  printf("Введите максимальное кол-во допустимых коллизий (-1 для пропуска): ");
  int collision_num = 0;
  if (scanf("%d", &collision_num) != 1 || collision_num < 1) return 0;
  size_t tryes = 0;
  while (tryes < 40 && hash_table_global->max_collision_num > collision_num) {
    hash_func_t hash = hash_table_global->hasher;
    size_t recomend_size = hash_table_global->elements_count * 0.72;
    if (hash != hash_pearson &&
        recomend_size * 3 <= hash_table_global->table_size)
      hash = hash_pearson;
    else if (recomend_size <= hash_table_global->table_size)
      recomend_size = hash_table_global->table_size * 1.2;

    recomend_size = next_prime(recomend_size);

    restruct_hash_table(&hash_table_global, recomend_size, hash);
    tryes++;
  }
  if (tryes >= 40) printf("Подобрать параметры хэш-таблицы не удалось\n");

  clear_input();
  hash_table_info_wrapper();

  return 0;
}

int create_hash_table_wrapper() {
  hash_func_t hash = NULL;

  if (read_hash_func(&hash)) return -1;
  printf("Введите размерность таблицы: ");
  int size = 0;
  if (scanf("%d", &size) != 1 || size < 1) return -1;

  free_hash_table(hash_table_global);
  hash_table_global = init_hash_table(size, hash, strcmp_connector);

  FILE *file = fopen(filename_data_global, "r");
  if (!file) return -1;
  while (!feof(file)) {
    char *str = NULL;
    size_t n = 0;
    size_t len = getline(&str, &n, file);
    str[len - 1] = 0;
    if (len <= 1) {
      free(str);
      continue;
    }
    add_element_hash_table(hash_table_global, str);
  }
  fclose(file);

  restruct_hash_table_automatic_wrapper();

  return 0;
}
int show_hash_table_wrapper() {
  if (!hash_table_global) {
    printf("Хэш таблица не создана\n");
    return 0;
  }
  file_dot_output = fopen("temp.txt", "w");
  fprintf(file_dot_output, "digraph graphname {");

  for (size_t i = 0; i < hash_table_global->table_size; i++) {
    if (!hash_table_global->table[i]) continue;
    fprintf(file_dot_output, "%zu [shape=box]; \n", i);
    if (!hash_table_global->table[i]) continue;

    fprintf(file_dot_output, "%zu", i);

    hash_table_node_t *cur = hash_table_global->table[i];

    while (cur) {
      fprintf(file_dot_output, " -> \"%s\"", cur->data);
      cur = cur->next;
    }
    fprintf(file_dot_output, ";\n");
  }

  fprintf(file_dot_output, "}");
  fclose(file_dot_output);
  file_dot_output = NULL;

  system("dot -Tpng temp.txt -otemp.png");
  system("open temp.png");
  system("clear");
  return 0;
}

void print_menu() {
  static struct {
    char *name;
    int (*action)(void);
  } actions[] = {
      {.name = "Перестроить деревья из файла", .action = create_tree_wrapper},

      {.name = "ДДП", .action = NULL},
      {.name = "показать", .action = print_btree_wrapper},
      {.name = "добавить элемент", .action = add_element_btree_wrapper},

      {.name = "АВЛ дерево", .action = NULL},
      {.name = "показать", .action = print_avl_tree_wrapper},
      {.name = "добавить элемент", .action = add_element_avl_tree_wrapper},

      {.name = "Хеш-таблица", .action = NULL},
      {.name = "создать из файла", .action = create_hash_table_wrapper},
      {.name = "добавить элемент", .action = add_element_hash_table_wrapper},
      {.name = "показать", .action = show_hash_table_wrapper},
      {.name = "состояние", .action = hash_table_info_wrapper},
      {.name = "\b== переструктурировать", .action = NULL},
      {.name = "самостоятельно", .action = restruct_hash_table_wrapper},
      {.name = "автоматически",
       .action = restruct_hash_table_automatic_wrapper},

      {.name = "Все структуры", .action = NULL},
      {.name = "добавить элемент", .action = add_element_wrapper},
      {.name = "поиск элемента", .action = has_element_wrapper},

      {.name = "Анализ", .action = NULL},
      {.name = "добавления элемента", .action = analyze_wrapper},
      {.name = "поиска элемента", .action = analyze_has_wrapper},
      {.name = NULL, .action = NULL},
  };

  if (create_tree_wrapper()) {
    printf("Ошибка открытия файла\n");
    return;
  }
  while (1) {
    printf("Меню \n\n");

    size_t diff = 0;
    size_t act_count = 0;
    for (size_t i = 0; actions[i].name; i++) {
      if (actions[i].action) {
        printf("%3zu) %s\n", i + 1 - diff, actions[i].name);
      } else {
        diff++;
        printf("===== %s\n", actions[i].name);
      }
      act_count++;
    }

    printf("\n  0) Выход \n");

    printf("Введите номер команды: ");
    int action = 0;
    if (scanf("%d", &action) == 0 || action > act_count - diff || action < 0) {
      wait_and_clear();
      printf("Неправильный номер команды.");
      return print_menu();
    }

    wait_and_clear();
    if (!action) return exit_handler();

    size_t i = 0;
    for (size_t j = 0; j < action; i++)
      if (actions[i].action) j++;

    if (actions[i - 1].action()) {
      wait_and_clear();
      printf("Произошла ошибка\n");
    }

    wait_and_clear();
  }
}
