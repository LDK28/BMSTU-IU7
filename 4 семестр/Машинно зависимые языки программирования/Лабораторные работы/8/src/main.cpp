#include <stdio.h>

extern "C"
{
    void strcopy(char *dst, char *src, int size);
}
int strlen(char *str)
{
    int count = 0;
    __asm__("xor %%rcx, %%rcx\n" 
            "mov $100, %%ecx\n"       // ecx будет декрементироваться каждый раз при "прочтении"
            "mov %1, %%rdi\n"
            "xor %%al, %%al\n"        // код символа с которым идёт сравнение должен храниться в AL
            "repne scasb\n"           /* repne повторит поиск по строке пока не найдет символ из регистра al. строка находится по edi. проходясь по байтам, декрементирует ecx. 
                                         scasb - сравнить строку байтов*/
            "mov $100, %%eax\n"
            "sub %%ecx, %%eax\n"      // получение реального размера
            "dec %%eax\n"
            "mov %%eax, %0\n"         // перенос к 0ой(индекс) переменной
            : "=r"(count)             // список выходных параметров
            : "r"(str)                // список входных параметров
            : "%rcx", "%rdi", "%rax"  // разрушение регистров
    );
    return count;
}
int main() {
    int i;
    char a[100] = "abcde";
    char b[100] = "aff";
    int l = strlen(a);
    printf("strlen(%s) = %d\n", a, l);
    strcopy(&a[2], a, l);
    printf("%s\n", a);
    printf("%s\n", &a[2]);
    return 0;
}

