#include <stdint.h>
#include <string.h>

/*
* Procédure affichane une matrice
*   - matrix_to_display : matrice à afficher
*/
void display_matrix(uint8_t matrix_to_display[4][4]);

/*
* Procédure lançant le test de mix_columns
*/
void test_mix_columns();

/*
* Procédure lançant le test de inv_mix_columns
*/
void test_inv_mix_columns();

/*
* Procédure effectuant le test de la fonction 'inv_mix_columns' ou 'mix_columns'
*/
void test_inv_or_mix_columns(uint8_t matrix_state[4][4], char* type_of_test);

/*
* Procédure effectuant le test de la fonction 'multiply_in_f_alpha'
*/
void test_multiply_in_f_alpha();

/*
* Procédure effetuant le test de la procédure 'shift_rows'
*/
void test_shift_rows();

/*
* Procédure effectuant le test de la procédure sub_bytes
*/
void test_sub_bytes();

/*
* Procédure effectuant le test de la procédure 'inv_sub_bytes'
*/
void test_inv_sub_bytes();

/*
* Procédure effetuant le test des procédure rotword et subword
*/
void test_rotword_subword();

/*
* Procédure effetuant le test de la procedure key_expansion
*/
void test_key_expansion_unique();

/*
* Procédure effetuant le test de la procedure key_expansion et son itération
*   - test_matrix_cipher_key : la clé à étendre
*   - test_matrix_round_key : la clé étendue
*   - test_round_number : le numéro de tour actuel
*/
void test_key_expansion_multiple(uint8_t test_matrix_cipher_key[4][4], uint8_t test_matrix_round_key[4][4], int test_round_number);

/*
* Procédure testant la fontion add_round_key
*/
void test_add_round_key();

/*
* Procédure testant la fontion cipher
*/
void test_cipher();

/*
* Procédure testant les fontion cipher et decipher d'affilés
*/
void test_cipher_and_decipher();
