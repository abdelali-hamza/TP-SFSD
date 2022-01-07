#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bib.h"


/*----------------------------------------Machine Abstraite LOF Et modules demandés ------------------------------------------*/


void ouvrir_LOF(LOF *fic ,char NomFichier[],char mode) {
    if (  ( mode =='A' ) || ( mode == 'a')) {
        fic->fichier=fopen(NomFichier,"rb+") ; //ouverture en mode binaire lecture ecriture
        fread(&(fic->entete),sizeof(LOF_entete) , 1 , fic->fichier);
        fseek(fic->fichier, + (fic->entete.nb_PrBloc -1 )* sizeof(LOF_bloc),SEEK_SET);
    }
    else {
        if ( ( mode == 'N' ) || ( mode == 'n')) {
            fic->fichier=fopen(NomFichier,"wb+");
            fic->entete.nb_PrBloc = 0 ;
            fic->entete.nb_bloc = 0 ;
            fic->entete.nb_enreg = 0 ;
            fwrite(&(fic->entete) , sizeof(LOF_entete),1 , fic->fichier);
        }
    }
}
/*--------------------------------------------------------------------------------------------*/
void fermer_LOF( LOF *fic){
    rewind(fic->fichier); //se ramener au Debut du fichier
    fwrite(&(fic->entete),sizeof(LOF_entete),1,fic->fichier ); //sauvegarder l'entete
    fclose(fic->fichier); // fermer le fichier
    free(fic); // libérer la structure allouée
}
/*--------------------------------------------------------------------------------------------*/
void lireDir_LOF(LOF *fic , int num_bloc , LBuffer *buf){
    int i =1;
        fseek(fic->fichier,sizeof(LOF_entete) + (num_bloc -1 )* sizeof(LOF_bloc),SEEK_SET);
        fread(buf, 1 , sizeof(LBuffer),fic->fichier);
}
/*-------------------------------------------------------------------------------------------*/
void EcrireDir_LOF( LOF *fic , int num_bloc , LBuffer *buf) {
    int i =1;
    LBuffer buff;
        fseek(fic->fichier,sizeof(LOF_entete) + (num_bloc -1 )* sizeof(LOF_bloc),SEEK_SET);
        fwrite(buf, 1 , sizeof(LBuffer),fic->fichier);
}
/*----------------------------------------------------------------------------------------------*/
void alloc_bloc_LOF ( LOF*fic) {
    fic->entete.nb_bloc ++ ;
}
/*--------------------------------------------------------------*/
int entete_LOF( LOF *fic , int i){
    switch (i)
    {
    case 1:
        return fic->entete.nb_PrBloc ;
        break;
    case 2 :
        return fic->entete.nb_bloc ;
        break ;
    case 3 :
        return fic->entete.nb_enreg  ;
    default:
        break;
    }
}
/*-----------------------------------------------------------------------------*/
void Aff_entete_LOF(LOF *fic,int i , int info ) {
        switch (i)
    {
    case 1:
        fic->entete.nb_PrBloc = info;
        break;
    case 2 :
        fic->entete.nb_bloc = info;
        break ;
    case 3 :
        fic->entete.nb_enreg = info ;
    default:
        break;
    }
}
/*----------------------------------------------------------------------------------------------*/
void createRandomTextFile ( int num_enreg , char FileName []  ) {
    int i , cle , op = 0 ;
    FILE *f ;
    f = fopen( "Hamza.txt", "w+" );
    if ( f == NULL) {
        printf(" An error occured while opening the file \n ");
        exit(1);
    }
    cle = 1 + rand()% 4;
    for ( i = 0; i < num_enreg; i++)
    {
      //if ( i != num_enreg -1 )
      fprintf(f,"%d %d%s",cle,op,"\n");
      cle += 1+rand()% 3 ;
      op = rand()%2;
    }
    rewind(f);
    fclose(f);
}
/*----------------------------------------------------------------------------------------------*/
void afficher_LOF ( LOF *fichier){
    LBuffer bloc;
    int i = entete_LOF(fichier,1),j;
    int nbBloc = entete_LOF(fichier,2);


    printf("\n========================================= FICHIER ================================\n");
    if (nbBloc == 0)printf(" LE FICHIER EST VIDE!!\n");
    else
    {
        printf(" Num du premier bloc dans le fichier   = %d \n",entete_LOF(fichier,1));
        printf(" Nombre de blocs dans ce fichier   = %d \n",entete_LOF(fichier,2));
        printf(" Nombre d'elements inseres  dans ce fichier   = %d \n",entete_LOF(fichier,3));
        //printf(" Nombre d'elements supprimes  dans ce fichier   = %d \n",entete_LOF(fichier,4));
        printf("\n==================================================================================\n");

    while( i != -1)
        {
          printf("\n-------------------------------BLOC %d ----------------------------------- \n",i);

          lireDir_LOF(fichier,i,&bloc);

          printf(" Nombre d'enregistrement dans ce bloc  = %d \n",bloc.nb);
          for( j=0 ; j< bloc.nb ; j++)
          {
              printf("la cle [%d] : %d \n",j,bloc.tab[j].cle);
          }
          i = bloc.suivant;
        }
    }
   }
/*-----------------------------------------------------------------------------*/
void chargement_initial_LOF( LOF *fic ,float u, char NomFichier[]){
    int i=1,j=0 ,  cle ,op;
    int nb_de_cle = 0;
    LBuffer buf ;

    FILE *g = fopen( NomFichier, "r+" );
    if ( g == NULL)  printf("ERROR while openning the file \n");
    while (! feof(g))
    {
        fscanf(g,"%d %d",&cle,&op);
        if ( op ==  0 )
        {
                nb_de_cle++;
                if (j < b*u )
                   {
                   buf.tab[j].cle= cle ;
                   j++;
                   }
                else
                    {
                    buf.nb = j  ;
                    alloc_bloc_LOF(fic);
                    if ( i == 1 ) Aff_entete_LOF(fic ,1 , 1) ;
                    buf.suivant = i +1 ;
                    EcrireDir_LOF(fic,i,&buf);
                    i ++ ;
                    buf.tab[0].cle = cle ;
                    j=1;
                    }
        }

    }
    buf.nb = j ;
    buf.suivant = -1 ;
    alloc_bloc_LOF(fic);
    EcrireDir_LOF(fic,i,&buf);

    Aff_entete_LOF(fic ,2 , i) ;
    Aff_entete_LOF(fic , 3 , nb_de_cle );
    fclose(g);
}
/*-----------------------------------------------------------------------------*/
void Rech_LOF(LOF *fic, int cle, int *Trouv,int *prec, int *num_bloc_cle, int *depl,int *acc_disc_lec){
    int inf,sup;
    int stop , BufnbPrec;
    //*acc_disc_lec = 10 ;

    LBuffer buf;
    *Trouv = 0 ;
    stop = 0; *depl = 1;
    *num_bloc_cle = entete_LOF(fic,1);
    while ( *num_bloc_cle != -1 && (*Trouv ==0) && (stop ==0) )
    {
        lireDir_LOF(fic,*num_bloc_cle,&buf);
        *acc_disc_lec = *acc_disc_lec + 1  ;
        if ( (cle >= buf.tab[0].cle) && (cle <= buf.tab[buf.nb-1].cle) )
        {
            inf = 0;
            sup = buf.nb-1;
            while ( (inf <= sup) && (*Trouv ==0) )
                {
                *depl = (inf + sup) / 2;
                if (cle == buf.tab[*depl].cle) *Trouv = 1;
                else
                    {
                    if (cle < buf.tab[*depl].cle) sup = *depl - 1 ;
                    else inf = *depl + 1 ;
                    }
               }
            if(inf > sup) *depl = inf ;
            stop = 1;
        }
        else{

            if (cle <buf.tab[0].cle)
            {
                stop = 1;
                if(  *num_bloc_cle == 1 || BufnbPrec ==b) *depl = 0 ;
                else {
                    *depl =BufnbPrec;
                    *num_bloc_cle = *prec;
                }
            }
            else{
                 if (buf.suivant != -1)
                 {
                    *prec= *num_bloc_cle ;
                     BufnbPrec = buf.nb ;
                    *num_bloc_cle = buf.suivant ;
                 }
                 else {
                     *prec= *num_bloc_cle ;
                     stop = 1;
                     if ( buf.nb == b) {
                         *num_bloc_cle = -1;
                         *depl = 0 ;
                     }
                     else *depl = buf.nb;

                 }


            }

        }
    }
    if ( *num_bloc_cle == 1) *prec=-1;

}
/*-----------------------------------------------------------------------------*/
void suppression1(LOF *fic , int cle ,int *acc_disc_lec , int *acc_disc_ecr){
    int trouv,suiv,num_bloc,depl,k ,prec ;
    LBuffer buf;

    Rech_LOF(fic,cle,&trouv,&prec,&num_bloc,&depl,acc_disc_lec);
    if (trouv)
    {
        cpt_sup++;
        lireDir_LOF(fic,num_bloc,&buf);
        *acc_disc_lec =  *acc_disc_lec + 1;
        for (k= depl; k < buf.nb;k++) buf.tab[k].cle = buf.tab[k+1].cle;
        buf.nb = buf.nb -1 ;
        if ( buf.nb != 0 )  {EcrireDir_LOF(fic,num_bloc,&buf); *acc_disc_ecr  = *acc_disc_ecr + 1 ;}
        else{
            suiv =buf.suivant;
            Aff_entete_LOF(fic,2,entete_LOF(fic,2) - 1 );
            if (num_bloc == 1) Aff_entete_LOF(fic,1,suiv);
            else{
                lireDir_LOF(fic,prec,&buf);
                *acc_disc_lec =  *acc_disc_lec + 1;
                buf.suivant = suiv ;
                EcrireDir_LOF(fic,prec,&buf);
                *acc_disc_ecr  = *acc_disc_ecr + 1 ;
            }
        }
        Aff_entete_LOF(fic,3,entete_LOF(fic,3)-1);
    }
}
/*-----------------------------------------------------------------------------*/
void suppression2(LOF *fic , int cle,int *acc_disc_lec , int *acc_disc_ecr){
    int trouv,suiv,num_bloc,x,y,depl,k ,i,n,prec ;
    LBuffer buf,buf2;
    Rech_LOF(fic,cle,&trouv,&prec,&num_bloc,&depl,acc_disc_lec);
    if (trouv)
    {
        cpt_sup++;
        lireDir_LOF(fic,num_bloc,&buf);
        *acc_disc_lec =  *acc_disc_lec + 1;
        for (k= depl; k < buf.nb;k++) buf.tab[k].cle = buf.tab[k+1].cle;
        buf.nb = buf.nb -1 ;
        suiv=buf.suivant;
        if ( buf.nb != 0 )  {EcrireDir_LOF(fic,num_bloc,&buf);*acc_disc_ecr  = *acc_disc_ecr + 1 ;}
        else
        {
            if (  prec == -1 )
            {
                lireDir_LOF(fic,suiv,&buf2);
                *acc_disc_lec =  *acc_disc_lec + 1;
                n = 0;
                y= (buf2.nb) / 2;
                for ( k =  0; k < y; k++)
                            {
                            buf.tab[n] = buf2.tab[k] ;
                            n ++ ;
                            buf.nb++;
                            }
                for ( k = y; k >buf2.nb; k++) buf2.tab[k-y] = buf2.tab[y];
                buf2.nb = buf2.nb - y;
                EcrireDir_LOF(fic,num_bloc,&buf);
                EcrireDir_LOF(fic,suiv,&buf2); *acc_disc_ecr  = *acc_disc_ecr + 2 ;

            }
            else if (suiv == -1 )
            {
                lireDir_LOF(fic,prec,&buf2);
                *acc_disc_lec =  *acc_disc_lec + 1;
                n = 0;
                y= (buf2.nb) / 2;
                for ( k =  buf2.nb -y; k < buf2.nb; k++)
                            {
                            buf.tab[n] = buf2.tab[k] ;
                            n ++ ;
                            buf.nb++;
                            }
                buf2.nb = buf2.nb - y;
                EcrireDir_LOF(fic,num_bloc,&buf);
                EcrireDir_LOF(fic,prec,&buf2);
                *acc_disc_ecr  = *acc_disc_ecr + 2 ;

            }
            else
            {
                lireDir_LOF(fic,prec,&buf2);
                *acc_disc_lec =  *acc_disc_lec + 1;
                n=0;
                y= (buf2.nb) / 3;
                for ( k =  0; k < y; k++)
                    {
                    buf.tab[n] = buf2.tab[buf2.nb-(y-k)] ;
                    n ++ ;
                    buf.nb++;
                    }
                buf2.nb = buf2.nb-y;
                EcrireDir_LOF(fic,prec,&buf2);
                *acc_disc_ecr  = *acc_disc_ecr + 1 ;
                lireDir_LOF(fic,suiv,&buf2);
                *acc_disc_lec =  *acc_disc_lec + 1;
                y= (buf2.nb) / 3;
                for ( k =  0; k < y; k++)
                {
                  buf.tab[n] = buf2.tab[k] ;
                  n ++ ;
                  buf.nb++;
                }
                for ( k = y; k <buf2.nb ; k ++) buf2.tab[k-y]=buf2.tab [k];
                buf2.nb = buf2.nb-y;
                EcrireDir_LOF(fic,suiv,&buf2);
                EcrireDir_LOF(fic,num_bloc,&buf);
                *acc_disc_ecr  = *acc_disc_ecr + 2 ;

        }
        Aff_entete_LOF(fic,3,entete_LOF(fic,3)-1);
    }
}
}
/*-----------------------------------------------------------------------------*/
int max ( LOF *fic){
    int i = entete_LOF(fic,1),max=0;
    LBuffer bloc;
     while( i != -1)
        {
          lireDir_LOF(fic,i,&bloc);
          if (i > max) max = i ;
          i = bloc.suivant;
        }
    return (max +1) ;

}
/*-----------------------------------------------------------------------------*/
void insertion1 ( LOF *fic,Tenreg e ,int *acc_disc_lec , int *acc_disc_ecr){
    int trouv,prec,i,j,suiv,w=max(fic);
    Tenreg x;
    LBuffer buf,buf2;
    Rech_LOF(fic,e.cle,&trouv,&prec,&i,&j,acc_disc_lec);
    if (!trouv) {
        cpt_inser ++;
        if (i != -1 ){
        lireDir_LOF(fic,i,&buf);
        *acc_disc_lec =  *acc_disc_lec + 1;
        if (buf.nb< b)
            {
            buf.nb ++ ;
            for (int k = buf.nb-1; k > j; k--) buf.tab[k] = buf.tab[k-1];
            buf.tab[j] = e ;
            EcrireDir_LOF(fic,i,&buf);
            *acc_disc_ecr  = *acc_disc_ecr + 1 ;
            }
        else {
            suiv=buf.suivant;
            x= buf.tab[buf.nb-1];
            for (int k = buf.nb-1; k > j; k--) buf.tab[k] = buf.tab[k-1];
            buf.tab[j] = e ;
            alloc_bloc_LOF(fic);
            buf.suivant = w;
            EcrireDir_LOF(fic,i,&buf);
            *acc_disc_ecr  = *acc_disc_ecr + 1 ;
            buf.nb=1;
            buf.tab[0]= x;
            buf.suivant=suiv;
            EcrireDir_LOF(fic,w,&buf);
            *acc_disc_ecr  = *acc_disc_ecr + 1 ;
           }
        }
        else {
            alloc_bloc_LOF(fic);
            lireDir_LOF(fic,prec,&buf);
            *acc_disc_lec =  *acc_disc_lec + 1;
            buf.suivant= w;
            EcrireDir_LOF(fic,prec,&buf);
            *acc_disc_ecr  = *acc_disc_ecr + 1 ;
            buf.tab[0]=e;
            buf.nb = 1 ;
            buf.suivant = -1 ;
            EcrireDir_LOF(fic,w,&buf);
            *acc_disc_ecr  = *acc_disc_ecr + 1 ;

        }

       Aff_entete_LOF(fic,3,entete_LOF(fic,3)+1);
    }
}
/*-----------------------------------------------------------------------------*/
void insertion2 ( LOF *fic,Tenreg e ,int *acc_disc_lec , int *acc_disc_ecr ) {
        int trouv,prec,i,j,k,y,n,suiv,w=max(fic);
        int NBdeEnreg ;

    Tenreg x;
    LBuffer buf,buf2;
    Rech_LOF(fic,e.cle,&trouv,&prec,&i,&j,acc_disc_lec);
    if (!trouv) {
        cpt_inser++;
        if (i != -1)
        {
            lireDir_LOF(fic,i,&buf);
            *acc_disc_lec =  *acc_disc_lec + 1;
            if (buf.nb< b)
            {
                buf.nb ++ ;
                for ( k = buf.nb -1; k >j; k--) buf.tab[k] = buf.tab[k-1];
                buf.tab[j] = e ;
                EcrireDir_LOF(fic,i,&buf);
                *acc_disc_ecr  = *acc_disc_ecr + 1 ;
            }
            else
            {
                 suiv=buf.suivant;
                x= buf.tab[buf.nb-1];
                for (int k = buf.nb-1; k > j; k--) buf.tab[k] = buf.tab[k-1];
                buf.tab[j] = e ;
                alloc_bloc_LOF(fic);
                buf.suivant = w;
                buf2.nb=1;
                buf2.suivant=suiv;
                if ( (suiv == -1) && (buf.nb>= 2))
                {
                    n = 0;
                    y=buf.nb - (buf.nb) / 2;
                    for ( k =  y; k < buf.nb; k++)
                    {
                        buf2.tab[n] = buf.tab[k] ;
                        n ++ ;
                        buf2.nb++;
                    }
                    buf.nb = y;
                    buf2.tab[n]= x;
                    EcrireDir_LOF(fic,i,&buf);
                    EcrireDir_LOF(fic,w,&buf2);
                    *acc_disc_ecr  = *acc_disc_ecr + 2 ;
                }
                if (suiv != -1 )
                {
                    n=0;
                    y= (buf.nb) / 3;
                    for ( k =  0; k < y; k++)
                    {
                        buf2.tab[n] = buf.tab[buf.nb-(y-k)] ;
                        n ++ ;
                        buf2.nb++;
                    }
                    buf.nb = buf.nb-y;
                    buf2.tab[n]= x;
                    n++;
                    EcrireDir_LOF(fic,i,&buf);
                    *acc_disc_ecr  = *acc_disc_ecr + 1 ;
                    lireDir_LOF(fic,suiv,&buf);
                    *acc_disc_lec =  *acc_disc_lec + 1;
                    y= (buf.nb) / 3;
                    for ( k =  0; k < y; k++)
                    {
                        buf2.tab[n] = buf.tab[k] ;
                        n ++ ;
                        buf2.nb++;
                    }
                    for ( k = y; k <buf.nb ; k ++) buf.tab[k-y]=buf.tab [k];
                    buf.nb = buf.nb-y;
                    EcrireDir_LOF(fic,suiv,&buf);
                    EcrireDir_LOF(fic,w,&buf2);
                   *acc_disc_ecr  = *acc_disc_ecr + 2 ;
                }
            }
        }
        else
        {
            alloc_bloc_LOF(fic);
            lireDir_LOF(fic,prec,&buf);
            *acc_disc_lec =  *acc_disc_lec + 1;
            buf.suivant= w;
            y= buf.nb /2;
            for (k = 0; k < y; k++) buf2.tab[k] = buf.tab[(buf.nb)-(y-k)];
            buf.nb = buf.nb - y ;
            EcrireDir_LOF(fic,prec,&buf);
            buf2.tab[y]=e;
            buf2.nb = y+1 ;
            buf2.suivant = -1 ;
            EcrireDir_LOF(fic,w,&buf2);
            *acc_disc_ecr  = *acc_disc_ecr + 2 ;

        }
        Aff_entete_LOF(fic,3,entete_LOF(fic,3)+1);
    }
}
/*-----------------------------------------------------------------------------*/


void Menu ()
{
    printf (" \n -----------------------------------------------------------------------------MENU---------------------------------------------------------------------------\n");
    printf ( "||  NOTE IMPORTANTE || : si vous ne creez pas un nouveau fichier texte toutes les operations vont se faire en utlisant le fichier qui existe dans le Folder  \n");
    printf ( " \n                    1. Afficher le fichier LOF\n");
    printf ( "                    2. Creer un nouveau fichier texte ( aléatoire) \n");
    printf ( "                    3. Faire supression 1 avec insertion 1 \n");
    printf ( "                    4. Faire supression 1 avec insertion 2 \n");
    printf ( "                    5. Faire supression 2 avec insertion 1 \n");
    printf ( "                    6. Faire supression 2 avec insertion 2 \n");
    printf ( "                    7. EXIT \n");
}
