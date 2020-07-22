#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

void crypt(unsigned char *cle)
{   //crypter un fichier
    int c1,chiffre[3],c[3],code,cpt,taille_cle;

    FILE *f2,*f1;
    f1=fopen("acrypter.txt","r");
    f2=fopen("crypter.txt","w");
    if(f1==NULL){printf("le fichier est vide\n");}

    cpt=0;
    c1=fgetc(f1);
    taille_cle = strlen(cle);
    while(c1 != EOF)
    {
        //extraire les chiffre du caractere de la cle
        code=cle[cpt % taille_cle];
        c[0]=code/100;
        c[1]=(code-c[0]*100)/10;
        c[2]=(code-c[0]*100-c[1]*10);
        if (c[2] != 0)
        {
            c1 = c1 * c[2];
        }
        //extraire les chiffres du caractere a chiffre
        chiffre[0]=c1/100;
        chiffre[1]=(c1-chiffre[0]*100)/10;
        chiffre[2]=(c1-chiffre[0]*100-chiffre[1]*10);
        // sommer chiffre par chiffre
        chiffre[0]=chiffre[0]+c[0];
        chiffre[1]=chiffre[1]+c[1];
        chiffre[2]=chiffre[2]+c[2];
        //le code du prochain caractere de la cle avec quoi coder
        cpt= (chiffre[0]+chiffre[1]+chiffre[2]) % taille_cle;
        //mettre dans l'intervalle des caractères affihables
        chiffre[0]=(chiffre[0]+126-32);
        chiffre[1]=chiffre[1]+126-32;
        chiffre[2]=chiffre[2]+126-32;
        //crypter
        fprintf(f2,"%c%c%c",chiffre[0],chiffre[1],chiffre[2]);
        c1=fgetc(f1);
    }
        fclose(f1);
        fclose(f2);
}
//*************************************************************
void decrypt_char (char* s, unsigned char cl, unsigned char *caract, int *som)
{
    int nb=0, c[3],chiffre,i; *som = 0;
    //extraire les chiffre du caractere de la cle
    c[0]=cl/100;
    c[1]=(cl-c[0]*100)/10;
    c[2]=(cl-c[0]*100-c[1]*10);
    for (i=0; i<3; i++)
    {
        chiffre = s[i] - 126 +32;
        //sommer les chiffres pour avoir le prochain caractère de la clé avec quoi on va décoder
        *som = *som + chiffre;
        //soustraire chiffre par chiffre
        chiffre = chiffre - c[i];
        //construire le nombre chiffre par chiffre en concaténant
        nb = nb * 10 + chiffre;
    }
    //diviser le nombre obtenue par le chiffre des unités de la clé
    if (c[2] != 0)
    {
        *caract = nb / c[2];
    }
    else
    {
        *caract = nb;
    }
}
//*************************************************************
void decrypt (unsigned char *cle)
{
    char s[3],c; int indice = 0, i;  unsigned char ch;

    FILE *f1=fopen("crypter.txt","r");
    FILE *f2= fopen("decrypter.txt", "w");
    if(f1==NULL || f2==NULL){printf("Une erreu s'est produite lors l'ouvertue du fichier.\n");}

    c = fgetc(f1);
    while (c != EOF)
    {
        //récupérer les 3 caractères qui codent dans une chaine s
        i = 0;
        while (i<3 && c!=EOF)
        {
            s[i] = c;
            c = fgetc(f1);
            i++;
        }
        //décoder les trois caractères pour n'avoir qu'un seul
        decrypt_char(s, cle[indice % strlen(cle)], &ch, &indice);
        //ecrire le caractère décrypté
        fputc(ch, f2);
    }
    fclose(f2);
    fclose(f1);
}

//********************************************
void comparer(FILE *f1,FILE *f2)
{
    //comparer le fichier crypte et celui decrypter
    int c1,c2;
    int continu;
    c1=fgetc(f1);
    c2=fgetc(f2);
    continu=0;
   while((!feof(f1))&& (!feof(f2)&&continu==0))
   {
      if(c1!=c2)
      {continu=1;}
      c1=fgetc(f1);
      c2=fgetc(f2);
    }
    if((c1==EOF&&c2!=EOF)||(c1!=EOF&&c2==EOF))
    {
        continu=1;
    }


    if(continu==0){printf("les deux fichiers sont compatibles\n");}
    else{printf("les deux fichiers ne sont pas compatibles \n");}

}
//*************************************************************
void decorer()
{   int choix=0;
    FILE *f1=fopen("acrypter.txt","r");
    FILE *f2=fopen("crypter.txt","r");
    FILE *f3=fopen("decrypter.txt", "r");
    if(f1==NULL || f2==NULL || f3==NULL){printf("Une erreu s'est produite lors l'ouvertue du fichier.\n");}
    printf("**********************************************************************************************************************\n");
    printf("                                              *Mini TP SFSD1*                                                            \n");
   while(choix!=5)
   {
    printf("\n                  Choisissez une option:\n");
    printf("                                       1*Afficher le fichier a crypter.\n");
    printf("                                       2*Afficher le fichier apres cryptage.\n");
    printf("                                       3*Afficher le fichier decrypté.\n");
    printf("                                       4*Comparer entre le fichier a crypter et celui decrypté.\n");
    printf("                                       5*Quitter.\n");
    scanf("%d",&choix);
    if((int)choix==1)
    {
        Afficher(f1);
    }
    else if (choix==2)
    {
        Afficher(f2);
    }
    else if (choix==3)
    {
        Afficher(f3);
    }
    else if (choix==4)
    {
        comparer(f1,f3);
    }
    else if (choix!=5)
    {
        printf("\nLe choix que vous avez entre n'est pas valide, veuillez entrez un de ces choix :");
    }
    }

   printf("Bonne journee..:)");
   fclose(f1);
   fclose(f2);
   fclose(f3);

}
//*******************************************************
void Afficher(FILE *f1)
{
  char texte[255];
  if(f1==NULL){printf("le fichier est vide\n");}
  rewind(f1);
    printf("___________________________________________________________________________________________________________________________________________\n");
   while(!feof(f1))
   {
      fgets(texte,255,f1);
      printf("%s",texte);
   }

   printf("\n\n\n");
   printf("____________________________________________________________________________________________________________________________________________\n");


}



