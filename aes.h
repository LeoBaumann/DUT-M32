#define _aes_h
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
// La table de substitution utilisée dans le cryptage AES
static const uint8_t S_BOX[256];

//Initialisation de la S-Box inversée
static const uint8_t REVERSED_S_BOX[256];

/*
* Procédure effectuant la substitution d'un état à un autre, suivant la table de substitution
*  - state : état à substituer
* Retour : Aucun, elle modifie directement la matrice (l'état)
*/
void sub_bytes (uint8_t matrix_state[4][4]);

/*
* Procédure substituant l'état donné en utilisant la table de substitution inversée d'aes, la REVERSED_S_BOX
*  - state : état à substituer
* Retour : Aucun, elle modifie directement la matrice (l'état)
*/
void inv_sub_bytes (uint8_t matrix_state[4][4]);

/*
* Procédure décalant les lignes (vers la gauche selon différent offset)
* de la matrice passée en paramètre
*  - matrix_state : matrice d'entré à modifier
*/
void shift_rows(uint8_t matrix_state[4][4]);


/*
* Procédure décalant les lignes (vers la droite selon différent offset)
* de la matrice passée en paramètre
*  - matrix_state : matrice d'entré à modifier
*/
void inv_shift_rows(uint8_t matrix_state[4][4]);

/*
* Fonction effectuant la multiplication par α dans F2(α)
*  - byte : octet à multiplier
* Retour : octet multiplié par α dans F2(α)
*/
uint8_t multiply_by_alpha(uint8_t byte);

/*
* Fonction effectuant la multiplication de 2 octets dans F2(α)
*  - byte_a : octet à multiplier par byte_b
*  - byte_b : octet à multiplier par byte_a
* Retour : résultat de la multiplication de byte_a et byte_b dans F2(α)
*/
uint8_t multiply_in_f_alpha(uint8_t byte_a, uint8_t byte_b);

/*
* Procédure appelant une fonction qui réalisera le calcul matricielle de
* l'inverse du mix columns, avec une matrice associé passée en paramètre
*  - matrix_state : matrice d'entré à multiplier qui sera modifiée
*/
void inv_mix_columns(uint8_t matrix_state[4][4]);

/*
* Procédure appelant une fonction qui réalisera le calcul matricielle du mix
* columns, avec une matrice associé passée en paramètre
*  - matrix_state : matrice d'entré à multiplier qui sera modifiée
*/
void mix_columns(uint8_t matrix_state[4][4]);

/*
* Procédure réalisant le calcul matricielle du mix columns, avec la matrice de
* multiplication correspondante au mix columns ou à son inverse passée en
* paramètre
*  - matrix_state : matrice d'entré à multiplier qui sera modifiée
*  - matrix_multiplier : matrice de multiplication du mix columns ou inverse
*/
void mix_columns_multiplication(uint8_t matrix_state[4][4], uint8_t matrix_multiplier[4][4]);

/*
* Fonction qui étend la clé donnée en paramètre en un round_key qu'elle renvoit alors
*   - matrix_cipher_key : la matrice de la clé de chiffrement à étendre
*   - matrix_round_key : l'extension de la matrix_cipher_key en paramètre
*   - round_number : le numéro de tour actuel lors de l'appel de l'extension de clé (0 étant le tour initial,
*    celui qui ne fait pas appel à l'extension car il XOR avec la clé de base)
* Retour: retourne une round_key sous forme de matrice
*/
void key_expansion(uint8_t matrix_cipher_key[4][4], uint8_t matrix_round_key[4][4], int round_number);

/*
* Procédure permettant de permuter la dernière colonne de la clé en paramètre d'une case, de bas en haut
* et place le résultat dans une "colonne" temporaire
*/
void rotword(uint8_t matrix_cipher_key[4][4], uint8_t temporary_column[4]);

/*
* Procédure qui substitue une colonne à l'aide de la S-Box, de la même manière que la procédure sub_bytes
* Mais sur une seule "colonne" de la matrice
*/
void subword(uint8_t temporary_column[4]);

/*
* Fonction qui XOR chaque colonne de l'état donné avec un une clé étendue
*   - matrix_state : matrice état à modifier
*   - matrix_cipher_key : la clé de chiffrement de base
*   - round_number : le numéro de tour actuel lors de l'appel de l'extension de clé (0 étant le tour initial,
*    celui qui ne fait pas appel à l'extension car il XOR avec la clé de base)
*/
void add_round_key(uint8_t matrix_state[4][4], uint8_t matrix_cipher_key[4][4], int round_number);


/*
* Fonction chiffrant un bloc de 128 bits selon une clef
*   - matrix_to_cipher: matrice état à modifier
*   - matrix_out : la matrice de sortie, contenant le message chiffré
*   - matrix_cipher_key : la clé de chiffrement de base, en version matrice
*/
void cipher(uint8_t matrix_to_cipher[4][4], uint8_t matrix_out[4][4], uint8_t matrix_cipher_key[4][4]);

/*
* Fonction déchiffrant un bloc de 128 bits selon une clef
*   - matrix_to_decipher: matrice état à modifier
*   - matrix_out : la matrice de sortie, contenant le message déchiffré
*   - matrix_cipher_key : la clé de chiffrement de base, en version matrice
*/
void decipher(uint8_t matrix_to_decipher[4][4], uint8_t matrix_out[4][4], uint8_t matrix_cipher_key[4][4]);

/*
* Fonction mère qui déchiffre un fichier dont le chemin est passé en argument
*   - file_path : chemin contenant le fichier à déchiffrer
*/
void decipher_file(char* file_path, char* key);

/*
* Fonction mère qui chiffre un fichier dont le chemin est passé en argument
*   - file_path : chemin contenant le fichier à chiffrer
*/
void cipher_file(char* file_path, char* key);

/*
* Transforme un bloc de 128bits (16octets) en une matrice d'octets 4x4
*   - block : le block à transformer
*   - matrix_in[4][4] : la matrice à remplir
*/
void block_to_matrix(uint8_t* block, uint8_t matrix_in[4][4]);

/*
* Fonction transformant la chaine de caratère représentant la clé en matrice
*   - key : clé de chiffrement en chaine de caractère
*   - matrix_key : la matrice de la clé à remplir avec les octets de la clé
*/
void key_conversion_matrix(char* key, uint8_t matrix_key[4][4]);
