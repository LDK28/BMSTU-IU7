#include "stdio.h"
#include "utils.h"

int main() {
  setbuf(stdout, NULL);
  setbuf(stdin, NULL);
  print_menu();
}