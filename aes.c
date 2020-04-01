#include "aes.h"
#include "utils.h"
#include <stdio.h>

//Initialization of the S_BOX
static const uint8_t S_BOX[256] = {
//  /* 0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F  */
     0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
     0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
     0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
     0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
     0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
     0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
     0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
     0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
     0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
     0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
     0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
     0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
     0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
     0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
     0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
     0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

//Initialisation de la S-Box inversée
static const uint8_t REVERSED_S_BOX[256] = {
 //  /* 0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F  */
      0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
      0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
      0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
      0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
      0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
      0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
      0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
      0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
      0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
      0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
      0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
      0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
      0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
      0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
      0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
      0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
};

//Initialisation de la RCON
static const uint8_t RCON[10] = {
0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36
};

/*
* Procédure substituant l'état donné en utilisant la table de substitution d'aes, la S_BOX
*  - state : état à substituer
* Retour : Aucun, elle modifie directement la matrice (l'état)
*/
void sub_bytes (uint8_t matrix_state[4][4]) {
 size_t i, j;
 //Nous parcourons tout le tableau, pour substituer chaque élément(octet)
  for(i=0; i<4; i++) {
     for(j=0;j<4;j++) {
       //Le nombre n contenu dans la case est remplacé par le nombre de la S-Box, à l'indice n
       int index = (int)matrix_state[i][j];;
       matrix_state[i][j]=S_BOX[index];
     }
  }
}

/*
* Procédure substituant l'état donné en utilisant la table de substitution inversée d'aes, la REVERSED_S_BOX
*  - state : état à substituer
* Retour : Aucun, elle modifie directement la matrice (l'état)
*/
void inv_sub_bytes (uint8_t matrix_state[4][4]) {
 size_t i, j;
 //Nous parcourons tout le tableau, pour substituer chaque élément(octet)
  for(i=0; i<4; i++) {
     for(j=0;j<4;j++) {
       //Le nombre n contenu dans la case est remplacé par le nombre de la S-Box inverse, à l'indice n
       int index = (int)matrix_state[i][j];;
       matrix_state[i][j]=REVERSED_S_BOX[index];
     }
  }
}


/*
* Procédure décalant les lignes (vers la gauche selon différent offset)
* de la matrice passée en paramètre
*  - matrix_state : matrice d'entré à modifier
*/
void shift_rows(uint8_t matrix_state[4][4]) {
  //Variable temporaire
  uint8_t temp_byte;

  //Decalage sur la premiere ligne avec un offset de 1
  temp_byte = matrix_state[1][0];
  matrix_state[1][0] = matrix_state[1][1];
  matrix_state[1][1] = matrix_state[1][2];
  matrix_state[1][2] = matrix_state[1][3];
  matrix_state[1][3] = temp_byte;

  //Decalage sur la deuxieme ligne avec un offset de 2
  temp_byte = matrix_state[2][0];
  matrix_state[2][0] = matrix_state[2][2];
  matrix_state[2][2] = temp_byte;
  temp_byte = matrix_state[2][1];
  matrix_state[2][1] = matrix_state[2][3];
  matrix_state[2][3] = temp_byte;

  //Decalage sur la troisieme ligne avec un offset de 3
  temp_byte = matrix_state[3][1];
  matrix_state[3][1] = matrix_state[3][0];
  matrix_state[3][0] = matrix_state[3][3];
  matrix_state[3][3] = matrix_state[3][2];
  matrix_state[3][2] = temp_byte;
}

/*
* Procédure décalant les lignes (vers la droite selon différent offset)
* de la matrice passée en paramètre
*  - matrix_state : matrice d'entré à modifier
*/
void inv_shift_rows(uint8_t matrix_state[4][4]) {
    //Variable temporaire
    uint8_t temp_byte;

    //Decalage sur la premiere ligne
    temp_byte = matrix_state[1][3];
    matrix_state[1][3] = matrix_state[1][2];
    matrix_state[1][2] = matrix_state[1][1];
    matrix_state[1][1] = matrix_state[1][0];
    matrix_state[1][0] = temp_byte;

    //Decalage sur la deuxieme ligne
    temp_byte = matrix_state[2][0];
    matrix_state[2][0] = matrix_state[2][2];
    matrix_state[2][2] = temp_byte;
    temp_byte = matrix_state[2][1];
    matrix_state[2][1] = matrix_state[2][3];
    matrix_state[2][3] = temp_byte;

    //Decalage sur la troisieme ligne
    temp_byte = matrix_state[3][0];
    matrix_state[3][0] = matrix_state[3][1];
    matrix_state[3][1] = matrix_state[3][2];
    matrix_state[3][2] = matrix_state[3][3];
    matrix_state[3][3] = temp_byte;
}

/*
* Fonction effectuant la multiplication par α dans F2(α)
*  - byte : octet à multiplier
* Retour : octet multiplié par α dans F2(α)
*/
uint8_t multiply_by_alpha(uint8_t byte) {
  uint8_t new_byte;
  if (byte > 127) {
    //X⁸ remlacé par X⁴ + X³ + X +1
    new_byte = (byte<<1)^ 0X1B;
  }
  else {
    new_byte = byte<<1;
  }
  return new_byte;
}

/*
* Fonction effectuant la multiplication de 2 octets dans F2(α)
*  - byte_a : octet à multiplier par byte_b
*  - byte_b : octet à multiplier par byte_a
* Retour : résultat de la multiplication de byte_a et byte_b dans F2(α)
*/
uint8_t multiply_in_f_alpha(uint8_t byte_a, uint8_t byte_b) {
  uint8_t multiplied_byte = 0;
  //Variable temporaire
  uint8_t temp_byte;

  //Parcous bit à bit de l'octet
  for (size_t i = 0; i<8;i++){
    temp_byte = byte_b;

    //Si le bit est de 1, on multiplie i fois
    if (byte_a % 2 == 1) {

      //Déplacement en fonction de la position du bit
      for (size_t j = i; j>0;j--){
        temp_byte = multiply_by_alpha(temp_byte);
      }
      multiplied_byte ^= temp_byte;
    }

    //Shift droite pour récupérer le bit suivant
    byte_a = byte_a>>1;
  }
  return multiplied_byte;
}

/*
* Procédure appelant une fonction qui réalisera le calcul matricielle du mix
* columns, avec une matrice associé passée en paramètre
*  - matrix_state : matrice d'entré à multiplier qui sera modifiée
*/
void mix_columns(uint8_t matrix_state[4][4]) {
  //Matrice qui devra multiplier la matrice en entrée
  uint8_t matrix_multiplier[4][4] = {{0x02, 0x03, 0x01, 0x01},
                                     {0x01, 0x02, 0x03, 0x01},
                                     {0x01, 0x01, 0x02, 0x03},
                                     {0x03, 0x01, 0x01, 0x02}};

   //Effectuer le calcul matricielle avec la matrice ce dessus
   mix_columns_multiplication(matrix_state, matrix_multiplier);
}

/*
* Procédure réalisant le calcul matricielle du mix columns, avec la matrice de
* multiplication correspondante au mix columns ou à son inverse passée en
* paramètre
*  - matrix_state : matrice d'entré à multiplier qui sera modifiée
*  - matrix_multiplier : matrice de multiplication du mix columns ou inverse
*/
void mix_columns_multiplication(uint8_t matrix_state[4][4], uint8_t matrix_multiplier[4][4]) {
  //Matrice qui stockera les données calculées avant de les replacer dans
  //la matrice de l'état passée en paramètre
  uint8_t matrix_tmp[4][4];

  //Parcours par colonnes de la matrice d'entrée puis par ligne
  for (size_t col = 0; col < 4; col++) {
    for (size_t line = 0; line < 4; line++) {
      //Multiplication dans F2(α) et XOR
      matrix_tmp[line][col] =
        multiply_in_f_alpha(matrix_multiplier[line][0],matrix_state[0][col]) ^
        multiply_in_f_alpha(matrix_multiplier[line][1],matrix_state[1][col]) ^
        multiply_in_f_alpha(matrix_multiplier[line][2],matrix_state[2][col]) ^
        multiply_in_f_alpha(matrix_multiplier[line][3],matrix_state[3][col]);
    }
  }

  for (size_t i = 0; i < 4; i++) {
    for (size_t j = 0; j < 4; j++) {
      //Récupérer les données dans la bonne matrice
      matrix_state[j][i] = matrix_tmp[j][i];
    }
  }
}



/*
* Procédure appelant une fonction qui réalisera le calcul matricielle de
* l'inverse du mix columns, avec une matrice associé passée en paramètre
*  - matrix_state : matrice d'entré à multiplier qui sera modifiée
*/
void inv_mix_columns(uint8_t matrix_state[4][4]) {
  //Matrice qui devra multiplier la matrice en entrée
  uint8_t matrix_multiplier[4][4] = {{0x0e, 0x0b, 0x0d, 0x09},
                                     {0x09, 0x0e, 0x0b, 0x0d},
                                     {0x0d, 0x09, 0x0e, 0x0b},
                                     {0x0b, 0x0d, 0x09, 0x0e}};

   //Effectuer le calcul matricielle avec la matrice ce dessus
   mix_columns_multiplication(matrix_state, matrix_multiplier);
}

/*
* Fonction qui étend la clé donnée en paramètre en un round_key
*   - matrix_cipher_key : la matrice de la clé de chiffrement à étendre
*   - matrix_round_key : l'extension de la matrix_cipher_key en paramètre
*   - round_number : le numéro de tour actuel lors de l'appel de l'extension de clé (0 étant le tour initial,
*    celui qui ne fait pas appel à l'extension car il XOR avec la clé de base)
*/
void key_expansion(uint8_t matrix_cipher_key[4][4], uint8_t matrix_round_key[4][4], int round_number) {
  //On réinitialise la matrix_round_key pour facilier l'utilisation de la fonction en boucle
  for(size_t i=0; i<4; i++) {
     for(size_t j=0;j<4;j++) {
       matrix_round_key[i][j] = 0x00;
     }
  }

  //On initialise une "colonne de matrice" temporaire
  uint8_t temp_column[4];

  // Exécution du rotword
  rotword(matrix_cipher_key, temp_column);

  // Exécution du subword
  subword(temp_column);

  // On XOR la première valeur de temp_column avec le RCON(nb d'itérat.)
  temp_column[0] = temp_column[0] ^ RCON[round_number-1];

  // On XOR la temp_column avec la première colonne da la clé en paramètre
  for(size_t i=0; i<4; i++){
    temp_column[i] = temp_column[i] ^ matrix_cipher_key[i][0];
  }

  //On ajoute alors la colonne temporaire dans la round_key
  for(size_t i=0; i<4; i++){
    matrix_round_key[i][0] = temp_column[i];
  }
  //On remplit le reste des autres colonnes du round_key avec un XOR
  for(size_t i=1; i<4; i++){
    // XOR de la  colonne i-1 de la round_key avec la colonne i de la clé en paramètre
    for(size_t j=0; j<4; j++){
      temp_column[j] = matrix_round_key[j][i-1] ^ matrix_cipher_key[j][i];
    }
    //On ajoute alors la colonne temporaire dans la round_key
    for(size_t k=0; k<4; k++){
      matrix_round_key[k][i] = temp_column[k];
    }
  }

}

/*
* Procédure permettant de permuter la dernière colonne de la clé en paramètre d'une case, de bas en haut
* et place le résultat dans une "colonne" temporaire
*/
void rotword(uint8_t matrix_cipher_key[4][4], uint8_t temporary_column[4]) {

  temporary_column[0] = matrix_cipher_key[1][3];
  temporary_column[1] = matrix_cipher_key[2][3];
  temporary_column[2] = matrix_cipher_key[3][3];
  temporary_column[3] = matrix_cipher_key[0][3];

}

/*
* Procédure qui substitue une colonne à l'aide de la S-Box, de la même manière que la procédure sub_bytes
* Mais sur une seule "colonne" de la matrice
*/
void subword(uint8_t temporary_column[4]) {
  for(size_t j=0;j<4;j++) {
    //Le nombre n contenu dans la case est remplacé par le nombre de la S-Box à l'indice n
    int index = (int)temporary_column[j];
    temporary_column[j]=S_BOX[index];
  }

}

/*
* Fonction qui XOR chaque colonne de l'état donné avec un une clé étendue
*   - matrix_state : matrice état à modifier
*   - matrix_cipher_key : la clé de chiffrement de base
*   - round_number : le numéro de tour actuel lors de l'appel de l'extension de clé (0 étant le tour initial,
*    celui qui ne fait pas appel à l'extension car il XOR avec la clé de base)
*/
void add_round_key(uint8_t matrix_state[4][4], uint8_t matrix_cipher_key[4][4], int round_number) {
  //Créer une copie locale de la cipher_key pour éviter toute modification
  uint8_t matrix_local_cipher_key[4][4];
  for(size_t i=0; i<4; i++) {
     for(size_t j=0;j<4;j++) {
       matrix_local_cipher_key[i][j] = matrix_cipher_key[i][j];
     }
  }

  //Si premier appel de la round_key : on XOR l'état avec la clé de base
  if(round_number==0) {
    for(size_t i=0; i<4; i++) {
       for(size_t j=0;j<4;j++) {
         matrix_state[i][j] = matrix_state[i][j] ^ matrix_local_cipher_key[i][j];
       }
    }
  }

  //Sinon, on étend la clé grâce à key_expansion autant de fois que nécessaire
  else {
    uint8_t matrix_round_key[4][4];
    for(size_t i=1; i<round_number+1; i++) {
      key_expansion(matrix_local_cipher_key, matrix_round_key, i);
      //On copie la round_key obtenue précédemment dans la cipher_key pour la prochaine itération s'il y a
      for(size_t i=0; i<4; i++) {
         for(size_t j=0;j<4;j++) {
           matrix_local_cipher_key[i][j] = matrix_round_key[i][j];
         }
      }
    }

    //XOR entre la clé étendue (round_key) et l'état
    for(size_t i=0; i<4; i++) {
       for(size_t j=0;j<4;j++) {
         matrix_state[i][j] = matrix_state[i][j] ^ matrix_round_key[i][j];
       }
    }
  }
}

/*
* Fonction mère qui chiffre un fichier dont le chemin est passé en argument
*   - file_path : chemin contenant le fichier à chiffrer
*/
void cipher_file(char* file_path, char* key) {
  int file_descriptor = open(file_path, O_RDONLY);
  if (file_descriptor == -1) {
    printf("Erreur open failed\n");
    exit(-1);
  }
  int size_file = lseek(file_descriptor, 0, SEEK_END);
  lseek(file_descriptor, 0, SEEK_SET);
  char* content = malloc(size_file);
  read( file_descriptor , content , size_file );

  printf("Message à chiffrer : \n");
  for (size_t i = 0; i < size_file; i++) {
    printf("%c", content[i]);
  }
  printf("\n");

  //Remplir le dernier bloc avec des 0 si il n'est pas assez grand
  if (size_file%16 != 0) {
    char* padding = malloc(16-(size_file%16));
    memset(padding, 0, (size_file%16));
    strcat(content,padding);
    free(padding);
  }

  uint8_t matrix_out[4][4];
  uint8_t matrix_in[4][4];
  uint8_t matrix_cipher_key[4][4];
  //Convertir la clé en une matrice
  key_conversion_matrix(key,matrix_cipher_key);

  int file = open("cipher_msg", O_RDWR|O_CREAT|O_TRUNC,S_IRWXU);
  int position = 0;
  while (size_file > position) {
    char* message = malloc(16);
    for (size_t i = 0; i < 16; i++) {
      message[i] = content[position+i];
    }

    block_to_matrix((uint8_t*)message, matrix_in);
    cipher(matrix_in, matrix_out, matrix_cipher_key);

    size_t number_cell = 0;
    char decoded_message[16];
    for(size_t column = 0; column < 4; column++){
      decoded_message[number_cell] = matrix_out[0][column];
      decoded_message[number_cell+1] = matrix_out[1][column];
      decoded_message[number_cell+2] = matrix_out[2][column];
      decoded_message[number_cell+3] = matrix_out[3][column];
      number_cell += 4;
    }
    write(file,decoded_message,16);
    free(message);
    position += 16;
  }
  close(file);
  printf("Message codé, créé dans le fichier 'cipher_msg'\n");
  free(content);
  close(file_descriptor);
}

/*
* Fonction mère qui déchiffre un fichier dont le chemin est passé en argument
*   - file_path : chemin contenant le fichier à déchiffrer
*/
void decipher_file(char* file_path, char* key) {
  int file_descriptor = open(file_path, O_RDONLY);
  if (file_descriptor == -1) {
    printf("Erreur open failed\n");
    exit(-1);
  }
  int size_file = lseek(file_descriptor, 0, SEEK_END);
  lseek(file_descriptor, 0, SEEK_SET);
  char* content = malloc(size_file);
  read( file_descriptor , content , size_file );

  //Remplir le dernier bloc avec des 0 si il n'est pas assez grand
  if (size_file%16 != 0) {
    char* padding = malloc(16-(size_file%16));
    memset(padding, 0, (size_file%16));
    strcat(content,padding);
    free(padding);
  }

  uint8_t matrix_out[4][4];
  uint8_t matrix_in[4][4];
  uint8_t matrix_cipher_key[4][4];
  //Convertir la clé en une matrice
  key_conversion_matrix(key,matrix_cipher_key);

  int file = open("decipher_msg", O_RDWR|O_CREAT|O_TRUNC,S_IRWXU);
  int position = 0;
  while (size_file > position) {
    char* message = malloc(16);
    for (size_t i = 0; i < 16; i++) {
      message[i] = content[position+i];
    }

    block_to_matrix((uint8_t*)message, matrix_in);
    decipher(matrix_in, matrix_out, matrix_cipher_key);

    size_t number_cell = 0;
    char decoded_message[16];
    for(size_t column = 0; column < 4; column++){
      decoded_message[number_cell] = matrix_out[0][column];
      decoded_message[number_cell+1] = matrix_out[1][column];
      decoded_message[number_cell+2] = matrix_out[2][column];
      decoded_message[number_cell+3] = matrix_out[3][column];
      number_cell += 4;
    }
    for (size_t i = 0; i < 16; i++) {
      printf("%c", decoded_message[i]);
    }
    write(file,decoded_message,16);
    free(message);
    position += 16;
  }
  printf("\n");
  printf("Message décodé, créé dans le fichier 'decipher_msg'\n");
  free(content);
  close(file_descriptor);
}

/*
* Transforme un bloc de 128bits (16octets) en une matrice d'octets 4x4
*   - block : le block à transformer
*   - matrix_in[4][4] : la matrice à remplir
*/
void block_to_matrix(uint8_t* block, uint8_t matrix_in[4][4]) {
  size_t number_cell = 0;
  //Colonne par colonne
  for(size_t column = 0; column < 4; column++){
    matrix_in[0][column] = *(block + (number_cell));
    matrix_in[1][column] = *(block + (number_cell+1));
    matrix_in[2][column] = *(block + (number_cell+2));
    matrix_in[3][column] = *(block + (number_cell+3));
    number_cell += 4;
  }
}

/*
* Fonction chiffrant un bloc de 128 bits selon une clef
*   - matrix_to_cipher: matrice état à modifier
*   - matrix_out : la matrice de sortie, contenant le message chiffré
*   - matrix_cipher_key : la clé de chiffrement de base, en version matrice
*/
void cipher(uint8_t matrix_to_cipher[4][4], uint8_t matrix_out[4][4], uint8_t matrix_cipher_key[4][4]) {
  uint8_t round_number = 0;

  uint8_t matrix_state[4][4];

  //On copie la matrice à chiffrer en paramètre dans l'état
    for(size_t i=0; i<4; i++) {
       for(size_t j=0;j<4;j++) {
         matrix_state[i][j] = matrix_to_cipher[i][j];
       }
    }

  add_round_key(matrix_state, matrix_cipher_key, round_number);

  //Dans notre cas, il y a 9 rounds où on doit effectuer ces étapes
  for(round_number = 1; round_number < 10; round_number++){
    sub_bytes(matrix_state);
    shift_rows(matrix_state);
    mix_columns(matrix_state);
    add_round_key(matrix_state, matrix_cipher_key, round_number);
  }
  //Dernier tour

  sub_bytes(matrix_state);
  shift_rows(matrix_state);
  add_round_key(matrix_state, matrix_cipher_key, (round_number));

  //On place dans matrix_out le bloc crypté
  for(size_t i=0; i<4; i++) {
     for(size_t j=0;j<4;j++) {
       matrix_out[i][j] = matrix_state[i][j];
     }
  }
}

/*
* Fonction déchiffrant un bloc de 128 bits selon une clef
*   - matrix_to_decipher: matrice état à modifier
*   - matrix_out : la matrice de sortie, contenant le message déchiffré
*   - matrix_cipher_key : la clé de chiffrement de base, en version matrice
*/
void decipher(uint8_t matrix_to_decipher[4][4], uint8_t matrix_out[4][4], uint8_t matrix_cipher_key[4][4]) {
  uint8_t round_number = 0;

  uint8_t matrix_state[4][4];

  //On copie la matrice à déchiffrer en paramètre dans l'état
    for(size_t i=0; i<4; i++) {
       for(size_t j=0;j<4;j++) {
         matrix_state[i][j] = matrix_to_decipher[i][j];
       }
    }

  add_round_key(matrix_state, matrix_cipher_key, 10-round_number);

  //Dans notre cas, il y a 9 rounds où on doit effectuer ces étapes
  for(round_number = 1; round_number < 10; round_number++){
    inv_shift_rows(matrix_state);
    inv_sub_bytes(matrix_state);
    add_round_key(matrix_state, matrix_cipher_key, 10-round_number);
    inv_mix_columns(matrix_state);

  }
  //Dernier tour
  inv_shift_rows(matrix_state);
  inv_sub_bytes(matrix_state);
  add_round_key(matrix_state, matrix_cipher_key, (10-round_number));

  //On place dans matrix_out le bloc décrypté
  for(size_t i=0; i<4; i++) {
     for(size_t j=0;j<4;j++) {
       matrix_out[i][j] = matrix_state[i][j];
     }
  }
}

/*
* Fonction transformant la chaine de caratère représentant la clé en matrice
*   - key : clé de chiffrement en chaine de caractère
*   - matrix_key : la matrice de la clé à remplir avec les octets de la clé
*/
void key_conversion_matrix(char* key, uint8_t matrix_key[4][4]) {
  //0x000102030405060708090a0b0c0d0e0f
  uint8_t bloc_key[16];
  for (size_t i =0; i<16;i++){
    char courant[5] = "0x";
    strncat(courant,(char*)&key[2*i+2],2);
    bloc_key[i] = strtol(courant, NULL, 16);
  }
  block_to_matrix(bloc_key, matrix_key);
}
