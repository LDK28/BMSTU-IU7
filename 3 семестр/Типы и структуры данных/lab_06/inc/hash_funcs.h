#ifndef INC_HASH_FUNCS_H_
#define INC_HASH_FUNCS_H_
/**
 * @file hash_funcs.h
 * @author Vladimir Larin
 * @brief Hash functions
 *
 * @copyright Copyright (c) 2020
 *
 */

int hash_sum(char *str);

int hash_xor(char *str);

int hash_pearson(char *str);

int hash_djb2(char *str);


#endif  // INC_HASH_FUNCS_H_
