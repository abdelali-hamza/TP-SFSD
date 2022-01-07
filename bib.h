#ifndef BIB_H_INCLUDED
#define BIB_H_INCLUDED


#define b 10



int cpt_inser=0 , cpt_sup = 0;


/*-----------------------------------------------   Structures TOF --------------------------------------*/
typedef struct Tenreg{
    int cle;
}Tenreg;

typedef struct LOF_bloc{
    Tenreg tab[b];
    int nb;
    int suivant;
}LOF_bloc;

typedef struct LOF_entete{
    int nb_PrBloc;
    int nb_bloc ;
    int nb_enreg ;
} LOF_entete ;

typedef struct LOF {
    FILE *fichier;
    LOF_entete entete ;
}LOF ;
typedef struct LOF_bloc LBuffer;

/*----------------------------------------Machine Abstraite LOF ------------------------------------------*/

void ouvrir_LOF(LOF *fic ,char NomFichier[],char mode);
void fermer_LOF( LOF *fic);
void lireDir_LOF(LOF *fic , int num_bloc , LBuffer *buf);
void EcrireDir_LOF( LOF *fic , int num_bloc , LBuffer *buf);
void alloc_bloc_LOF ( LOF*fic) ;
int entete_LOF( LOF *fic , int i);
void Aff_entete_LOF(LOF *fic,int i , int info );

/*---------------------------------------- Les Modules qui traitent un fichier de type  LOF ------------------------------------------*/

void afficher_LOF ( LOF *fichier);
void chargement_initial_LOF( LOF *fic ,float u, char NomFichier[]);
void Rech_LOF(LOF *fic, int cle, int *Trouv,int *prec, int *num_bloc_cle, int *depl,int *acc_disc_lec);
void suppression1(LOF *fic , int cle ,int *acc_disc_lec , int *acc_disc_ecr);
void suppression2(LOF *fic , int cle,int *acc_disc_lec , int *acc_disc_ecr);
int max ( LOF *fic);
void insertion1 ( LOF *fic,Tenreg e ,int *acc_disc_lec , int *acc_disc_ecr);
void insertion2 ( LOF *fic,Tenreg e ,int *acc_disc_lec , int *acc_disc_ecr );

/*---------------------------------------- Autres Modules ------------------------------------------*/
void createRandomTextFile ( int num_enreg , char FileName []  );
void Menu ();


#endif // BIB_H_INCLUDED
