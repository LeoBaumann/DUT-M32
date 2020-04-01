#include "utils.h"
#include "aes.h"

/*
* Procédure affichane une matrice
*   - matrix_to_display : matrice à afficher
*/
void display_matrix(uint8_t matrix_to_display[4][4]) {
  printf("\n    ");
  for (size_t col = 0; col < 4; col++) {
   for (size_t line = 0; line < 4; line++) {
     if (matrix_to_display[col][line] < 0x10) {
       printf("0"); //Pour améliorer l'affichage
     }
     printf("%x ", matrix_to_display[col][line]);
   }
   printf("\n    ");
  }
}

/*
* Procédure lançant le test de mix_columns
*/
void test_mix_columns() {
  uint8_t matrix_state[4][4] = {{0x49, 0x45, 0x7f, 0x77},
                                {0xdb, 0x39, 0x02, 0xde},
                                {0x87, 0x53, 0xd2, 0x96},
                                {0x3b, 0x89, 0xf1, 0x1a}};

  test_inv_or_mix_columns(matrix_state, "de mix columns");
}

/*
* Procédure lançant le test de inv_mix_columns
*/
void test_inv_mix_columns() {
  uint8_t matrix_state[4][4] = {{0x58, 0x1b, 0xdb, 0x1b},
                                {0x4d, 0x4b, 0xe7, 0x6b},
                                {0xca, 0x5a, 0xca, 0xb0},
                                {0xf1, 0xac, 0xa8, 0xe5}};

  test_inv_or_mix_columns(matrix_state, "de l'inverse de mix columns");
}

/*
* Procédure effectuant le test de la fonction 'inv_mix_columns' ou 'mix_columns'
*/
void test_inv_or_mix_columns(uint8_t matrix_state[4][4], char* type_of_test) {
  printf("--Test %s ---------------\n",type_of_test);

  for (size_t i = 0; i < 2; i++) {
    display_matrix(matrix_state);
    printf("-----------\n    ");
    //Modification de la matrice d'état en fonction du test à réaliser
    if (strcmp(type_of_test,"de mix columns") == 0) {
      mix_columns(matrix_state);
    }
    else if (strcmp(type_of_test,"de l'inverse de mix columns") == 0){
      inv_mix_columns(matrix_state);
    }
    else {
      printf("Erreur dans type_of_test\n    ");
    }
  }
  printf("\n--Fin du test %s --------\n", type_of_test);
}

/*
* Procédure effectuant le test de la fonction 'multiply_in_f_alpha'
*/
void test_multiply_in_f_alpha() {
  uint8_t byte_x, byte_y , byte_result;

  printf("--Test de la multiplication de 2 octet dans F2(α) ---------------\n\n    ");

  byte_x = 0x57;
  byte_y = 0x13;
  printf("%x x %x = ",byte_x,byte_y);
  byte_result = multiply_in_f_alpha(byte_x,byte_y);
  printf("%x\n",byte_result);

  printf("\n--Fin du test de la multiplication de 2 octet dans F2(α) --------\n");
}


/*
* Procédure effetuant le test de la procédure 'shift_rows'
*/
void test_shift_rows() {

  uint8_t matrix_state[4][4] = { {0x19, 0xa0, 0x9a, 0xe9},
                                 {0x3d, 0xf4, 0xc6, 0xf8},
                                 {0xe3, 0xe2, 0x8d, 0x48},
                                 {0xbe, 0x2b, 0x2a, 0x08} };
  printf("--Test de la procédure shift_rows ---------------\n\n");
  printf("Affichage de l'état initial de la matrice:\n");
  display_matrix(matrix_state);

  printf("\nExécution de la procédure shift_rows\n");
  shift_rows(matrix_state);
  printf("\nAffichage de l'état après la procédure shift_rows:\n");
  display_matrix(matrix_state);
  printf("\n--Fin du test de la procédure shift_rows --------\n");

}

/*
* Procédure effetuant le test de la procédure 'inv_shift_rows'
*/
void test_inv_shift_rows() {

  uint8_t matrix_state[4][4] = { {0x19, 0xa0, 0x9a, 0xe9},
                                 {0x3d, 0xf4, 0xc6, 0xf8},
                                 {0xe3, 0xe2, 0x8d, 0x48},
                                 {0xbe, 0x2b, 0x2a, 0x08} };
  printf("--Test de la procédure inv_shift_rows ---------------\n\n");
  printf("Affichage de l'état initial de la matrice:\n");
  display_matrix(matrix_state);

  printf("\nExécution de la procédure inv_shift_rows\n");
  inv_shift_rows(matrix_state);
  printf("\nAffichage de l'état après la procédure inv_shift_rows:\n");
  display_matrix(matrix_state);
  printf("\n--Fin du test de la procédure inv_shift_rows --------\n");

}

/*
* Procédure effetuant le test de la procédure 'sub_bytes'
*/
void test_sub_bytes() {

  uint8_t matrix_state[4][4] = { {0x19, 0xa0, 0x9a, 0xe9},
                                 {0x3d, 0xf4, 0xc6, 0xf8},
                                 {0xe3, 0xe2, 0x8d, 0x48},
                                 {0xbe, 0x2b, 0x2a, 0x08} };
  printf("--Test de la procédure sub_bytes ---------------\n\n");
  printf("Affichage de l'état initial de la matrice:\n");
  display_matrix(matrix_state);

  printf("\nExécution de la procédure sub_bytes\n");
  sub_bytes(matrix_state);
  printf("\nAffichage de l'état après la procédure sub_byte:\n");
  display_matrix(matrix_state);

  printf("\n--Fin du test de la procédure sub_bytes --------\n");

}

/*
* Procédure effetuant le test de la procédure 'inv_sub_bytes'
*/
void test_inv_sub_bytes() {

  uint8_t matrix_state[4][4] = { {0xd4, 0xe0, 0xb8, 0x1e},
                                 {0x27, 0xbf, 0xb4, 0x41},
                                 {0x11, 0x98, 0x5d, 0x52},
                                 {0xae, 0xf1, 0xe5, 0x30} };
  printf("--Test de la procédure inv_sub_bytes ---------------\n\n");
  printf("Affichage de l'état initial de la matrice:\n");
  display_matrix(matrix_state);

  printf("\nExécution de la procédure inv_sub_bytes\n");
  inv_sub_bytes(matrix_state);
  printf("\nAffichage de l'état après la procédure inv_sub_bytes\n");
  display_matrix(matrix_state);
  printf("\n--Fin du test de la procédure inv_sub_bytes --------\n");
}

/*
* Procédure effetuant le test des procédure rotword et subword
*/
void test_rotword_subword() {
  printf("--Test des procédures rotword et subword---------------\n\n");
  //On génère la clef de test
  uint8_t test_matrix_cipher_key[4][4] = { {0xa0, 0x88, 0x23, 0x2a},
                                           {0xfa, 0x54, 0xa3, 0x6c},
                                           {0xfe, 0x2c, 0x39, 0x76},
                                           {0x17, 0xb1, 0x39, 0x05} };

  //On initialise une "colonne de matrice" temporaire
  uint8_t temp_column[4];

  // Exécution du rotword
  rotword(test_matrix_cipher_key, temp_column);
  printf("\n Affichage de la colonne après rotword:\n" );
  for(size_t i=0;i<4;i++) {
    printf("%x ", temp_column[i]);
  }
  printf("\n");


  // Exécution du subword
  subword(temp_column);
  printf("\n Affichage de la colonne après subword:\n" );
  for(size_t i=0;i<4;i++) {
    printf("%x ", temp_column[i]);
  }
  printf("\n");
  printf("\n--Fin des procédures rotword et subword --------\n");
}

/*
* Procédure effetuant le test de la procedure key_expansion
*/
void test_key_expansion_unique() {
  printf("--Test de la procédure key_expansion_unique---------------\n\n");

  //On génère la clef de test
  uint8_t test_matrix_cipher_key[4][4] = { {0xa0, 0x88, 0x23, 0x2a},
                                           {0xfa, 0x54, 0xa3, 0x6c},
                                           {0xfe, 0x2c, 0x39, 0x76},
                                           {0x17, 0xb1, 0x39, 0x05} };

  printf("\nAffichage de la clef initiale:\n");
  display_matrix(test_matrix_cipher_key);

  printf("\nInitialisation de la round_key à remplir et exécution de la procédure key_expansion\n");
  uint8_t round_key[4][4];
  key_expansion(test_matrix_cipher_key, round_key, 2);

  printf("\nAffichage de la clef suite à l'expansion:\n");
  display_matrix(round_key);

  printf("\n--Fin de la procédure key_expansion_unique --------\n");
}

/*
* Procédure effetuant le test de la procedure key_expansion et son itération
*   - test_matrix_cipher_key : la clé à étendre
*   - test_matrix_round_key : la clé étendue
*   - test_round_number : le numéro de tour actuel
*/
void test_key_expansion_multiple(uint8_t test_matrix_cipher_key[4][4], uint8_t test_matrix_round_key[4][4], int test_round_number) {
  printf("\nAffichage de la clef en paramètre (a étendre):\n");
  display_matrix(test_matrix_cipher_key);

  printf("\nExécution de la procédure key_expansion\n");
  key_expansion(test_matrix_cipher_key, test_matrix_round_key, test_round_number);

  printf("\nAffichage de la clef étendue:\n");
  display_matrix(test_matrix_round_key);

}

/*
* Procédure testant la fontion add_round_key
*/
void test_add_round_key() {
  //On génère la clef de base
  uint8_t test_matrix_cipher_key[4][4] = { {0x2b, 0x28, 0xab, 0x09},
                                           {0x7e, 0xae, 0xf7, 0xcf},
                                           {0x15, 0xd2, 0x15, 0x4f},
                                           {0x16, 0xa6, 0x88, 0x3c} };


  //On génère l'état de base
  uint8_t test_matrix_state[4][4] = { {0xe9, 0xcb, 0x3d, 0xaf},
                                      {0x31, 0x32, 0x2e, 0x09},
                                      {0x7d, 0x2c, 0x89, 0x07},
                                      {0xb5, 0x72, 0x5f, 0x94} };

  //On simule son appel à la fin du deuxième tour
  printf("--Test de la fonction add_round_key ---------------\n\n");

  printf("\nAffichage de l'état avant add_round_key:\n");
  display_matrix(test_matrix_state);

  add_round_key(test_matrix_state, test_matrix_cipher_key, 10);
  printf("\nAffichage de l'état après add_round_key:\n");
  display_matrix(test_matrix_state);

  printf("\n--Fin de la fonction add_round_key --------\n");
}

/*
* Procédure testant la fontion cipher
*/
void test_cipher() {
  //On génère la clef de base
  uint8_t test_matrix_cipher_key[4][4] = { {0x2b, 0x28, 0xab, 0x09},
                                           {0x7e, 0xae, 0xf7, 0xcf},
                                           {0x15, 0xd2, 0x15, 0x4f},
                                           {0x16, 0xa6, 0x88, 0x3c} };


  //On génère l'état de base
  uint8_t test_matrix_state[4][4] = { {0x32, 0x88, 0x31, 0xe0},
                                      {0x43, 0x5a, 0x31, 0x37},
                                      {0xf6, 0x30, 0x98, 0x07},
                                      {0xa8, 0x8d, 0xa2, 0x34} };

  uint8_t test_matrix_out[4][4];

  printf("--Test de la fonction cipher() ---------------\n\n");

  printf("\nAffichage de la matrice initiale:\n");
  display_matrix(test_matrix_state);

  cipher(test_matrix_state, test_matrix_out, test_matrix_cipher_key);

  printf("\nAffichage de la matrice chiffrée:\n");
  display_matrix(test_matrix_out);

  printf("\n--Fin de la fonction cipher() --------\n");
}

/*
* Procédure testant les fontion cipher et decipher d'affilés
*/
void test_cipher_and_decipher() {
  //On génère la clef de base
  uint8_t test_matrix_cipher_key[4][4] = { {0x2b, 0x28, 0xab, 0x09},
                                           {0x7e, 0xae, 0xf7, 0xcf},
                                           {0x15, 0xd2, 0x15, 0x4f},
                                           {0x16, 0xa6, 0x88, 0x3c} };


  //On génère l'état de base
  uint8_t test_matrix_state[4][4] = { {0x32, 0x88, 0x31, 0xe0},
                                      {0x43, 0x5a, 0x31, 0x37},
                                      {0xf6, 0x30, 0x98, 0x07},
                                      {0xa8, 0x8d, 0xa2, 0x34} };

  uint8_t test_matrix_out[4][4];

  printf("--Test des fonctions cipher et decipher ---------------\n\n");

  printf("\nAffichage de la matrice initiale:\n");
  display_matrix(test_matrix_state);

  printf("\nChiffrement !\n");
  cipher(test_matrix_state, test_matrix_out, test_matrix_cipher_key);

  printf("\nAffichage de la matrice chiffrée:\n");
  display_matrix(test_matrix_out);

  printf("\nDéchiffrement !\n");
  decipher(test_matrix_out, test_matrix_out, test_matrix_cipher_key);

  printf("\nAffichage de la matrice déchiffrée:\n");
  display_matrix(test_matrix_out);

  printf("\n--Fin des fonctions cipher et decipher --------\n");

}
