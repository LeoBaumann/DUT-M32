# Explication sujet

## Résumé fonctionnement:	
Un algorithme de cadencement de clé calcule à partir de la clé K une suite de Nr + 1 sous-clés de tour ( K 0,...,K Nr ), comportant toutes 16 octets. Le texte à chiffrer est découpé en blocs de 16 octets et, pour chaque bloc clair, on effectue les opérations suivantes pour produire un bloc chiffré de même longueur :	
	
1. On initialise un état (state)-> tableau de 4x4 avec 16 octets de texte clair (le message à coder (in)).	
2. On effectue AddRoundKey	
3. On effectue (Nr -1) tours comportant les 4 étapes SubBytes , ShiftRows, MixColumns, AddRoundKey ( K i ) dans cet ordre, pour i = 1 ,..., Nr −1	
4. Un dernier tour ne comporte plus que 3 étapes : SubBytes, ShiftRows, AddRoundKey ( K Nr ).	
5. Le contenu actuel du tableau donne les 16 octets du texte chiffré.	


## Notes importantes	
* Nb = Number  of  columns  (32-bit  words)  comprising  the  State.  For  this  standard, Nb = 4.	
* Nk = Number  of  32-bit  words  comprising  the  Cipher  Key.  For  this  standard, Nk = 4 (dans notre cas, car 128 bits)	
* Nr = Number  of  rounds,  which  is  a  function  of  Nk and  Nb (which  is  fixed). For this standard, Nr = 10 ((dans notre cas, car 128 bits)	
* XOR = OU exclusif	
* Etat: Résultat intermédiaire du chiffrement, représenté comme un tableau rectangulaires d'octets, avec 4 lignes et Nb colonnes. Dans notre cas, il n'y en a qu'un	
* Bloc: Sequence de bits comprenant l'input, l'output, l'état et la clé. Longueur d'une sequence est nombre de bits qu'il contient. Les blocs sont représentés sous forme de tableau d'octets.	
	

## Règles de programmation à suivre :	
* Makefile avec un main.c 	
* Fonction par direct au projet mettre à part utils.c	
* Fichier en .h pour toute les fonctions	
* Règles de nommages : Nom clair UNIQUEMENT en ANGLAIS, en MINUSCULE et _ (constante que MAJ), type int standard : int32, ... à priorisé 	
* Commentaire pour toutes les fonctions, tout les cas de retour, des erreurs etc (prévoir un renvoie en cas d'erreur)		
* Déclarer dès le début toutes les variables importantes des fonctions avec commentaire pour savoir l'utilité	
* Boucle pas de int que des size_t	
* Fonction courte ! Décomposer si trop long	
* OPEN READ WRITE pour E/S (si open -> close, si malloc -> free)	
* AUCUN SCANF, mettre en ligne de commande	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
