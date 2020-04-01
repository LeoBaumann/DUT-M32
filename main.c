#include "utils.h"
#include "aes.h"

int main(int argc, char *argv[]){
  if (argc != 2 && argc != 4) {
    printf("Usage : %s <-option> <file name> <key>\nOR\nUsage : %s <test>\n",argv[0],argv[0]);
    exit(1);
  }
  if (argc == 2) {
    if (strcmp(argv[1], "mix_columns") == 0) {
      test_mix_columns();
    }
    else if (strcmp(argv[1], "inv_mix_columns") == 0) {
      test_inv_mix_columns();
    }
    else if (strcmp(argv[1], "multiply_in_f_alpha") == 0) {
      test_multiply_in_f_alpha();
    }
    else if (strcmp(argv[1], "shift_rows") == 0) {
      test_shift_rows();
    }
    else if (strcmp(argv[1], "sub_bytes") == 0) {
      test_sub_bytes();
    }
    else if (strcmp(argv[1], "inv_sub_bytes") == 0) {
      test_inv_sub_bytes();
    }
    else if (strcmp(argv[1], "rotword_subword") == 0) {
      test_rotword_subword();
    }
    else if (strcmp(argv[1], "key_expansion_unique") == 0) {
      test_key_expansion_unique();
    }
    else if (strcmp(argv[1], "add_round_key") == 0) {
      test_add_round_key();
    }
    else if (strcmp(argv[1], "cipher") == 0) {
      test_cipher();
    }
    else if (strcmp(argv[1], "cipher_and_decipher") == 0) {
      test_cipher_and_decipher();
    }
    else {
      printf("Usage : %s <test>\n",argv[0]);
      exit(1);
    }
  }
  if (argc == 4) {
    if (strcmp(argv[1], "-c") == 0) {
      //Chiffrement
      cipher_file(argv[2], argv[3]);
    }
    else if (strcmp(argv[1], "-d") == 0) {
      //Déchiffrement
      decipher_file(argv[2], argv[3]);
    }
    else {
      printf("Usage : %s <-option> <file name> <key>\n",argv[0]);
      printf("<-option> : '%s' should be  -c for chiper, -d for decipher\n",argv[1]);
      exit(1);
    }
  }
  return 0;
}
