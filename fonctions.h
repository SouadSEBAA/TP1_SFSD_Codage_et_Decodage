#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

void decrypt_char (char* s, unsigned char cle, unsigned char *caract, int *som);//on lui fournit la chaine de caractères avec le caractère de la cle, et renvoie le caractère decrypte caract avec l'indice som du prochain caractere de la cle avec quoi on va coder
void comparer(FILE *f1,FILE *f2);//compare entre les deux fichiers pointés par f1 et f2
void crypt(unsigned char *cle);//crypt un fichier avec une chaine cle
void decrypt ( unsigned char *cle);//decrypt un fichier avec une chaine cle
void decorer();
void Afficher(FILE *f1);//affiche le contenu du fichier pointé par f1


#endif // FONCTIONS_H_INCLUDED
