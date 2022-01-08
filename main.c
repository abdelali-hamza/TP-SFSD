#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "bib.c"

int main()
{
    LOF fic11,fic12,fic21,fic22;
    int nb_acc_l_S11 = 0 , nb_acc_e_S11 = 0 ,
        nb_acc_l_S12 = 0 , nb_acc_e_S12 = 0 ,
        nb_acc_l_S21 = 0 , nb_acc_e_S21 = 0 ,
        nb_acc_l_S22 = 0 , nb_acc_e_S22 = 0  ;
    
    int nb_acc_l_I11 = 0 , nb_acc_e_I11 = 0 ,
        nb_acc_l_I12 = 0 , nb_acc_e_I12 = 0 ,
        nb_acc_l_I21 = 0 , nb_acc_e_I21 = 0 ,
        nb_acc_l_I22 = 0 , nb_acc_e_I22 = 0  ;
        
    int cle=0,op=0, cond =0,choix;
    int nb_de_insertion = 0, nb_de_suppression = 0 ;
    int trouv , size_text= 10000 ;
    Tenreg hamza;
    FILE *f;
     
     
    srand(time(NULL));
    createRandomTextFile(size_text,"Hamza.txt");
    
    ouvrir_LOF(&fic11,"LOF1",'N');
    ouvrir_LOF(&fic12,"LOF2",'N');
    ouvrir_LOF(&fic21,"LOF3",'N');
    ouvrir_LOF(&fic22,"LOF4",'N');
    
    chargement_initial_LOF(&fic11,0.2,"Hamza.txt");
    chargement_initial_LOF(&fic12,0.2,"Hamza.txt");
    chargement_initial_LOF(&fic21,0.2,"Hamza.txt");
    chargement_initial_LOF(&fic22,0.2,"Hamza.txt");
    
    
    f = fopen("Hamza.txt","r+");
    int i=0,j=0;
    int acc_ins11_lect[10000],acc_ins11_ecr[10000],
        acc_sup11_lect[10000],acc_sup11_ecr[10000],
        acc_ins12_lect[10000],acc_ins12_ecr[10000],
        acc_sup12_lect[10000],acc_sup12_ecr[10000],
        acc_ins21_lect[10000],acc_ins21_ecr[10000],
        acc_sup21_lect[10000],acc_sup21_ecr[10000],
        acc_ins22_lect[10000],acc_ins22_ecr[10000],
        acc_sup22_lect[10000],acc_sup22_ecr[10000];
    while (!feof(f))
    {
        fscanf(f,"%d %d",&cle,&op);
        if (op == 0) {
            suppression1(&fic11,cle,&nb_acc_l_S11,&nb_acc_e_S11);
                acc_sup11_lect[i] =  nb_acc_l_S11 ; 
                acc_sup11_ecr[i] =   nb_acc_e_S11;
            suppression1(&fic21,cle,&nb_acc_l_S21,&nb_acc_e_S21);
                acc_sup21_lect[i] =  nb_acc_l_S21 ; 
                acc_sup21_ecr[i] =   nb_acc_e_S21;
            suppression2(&fic12,cle,&nb_acc_l_S12,&nb_acc_e_S12);
                acc_sup12_lect[i] =  nb_acc_l_S12 ; 
                acc_sup12_ecr[i] =   nb_acc_e_S12;
            suppression2(&fic22,cle,&nb_acc_l_S22,&nb_acc_e_S22);
                acc_sup22_lect[i] =  nb_acc_l_S22 ; 
                acc_sup22_ecr[i] =   nb_acc_e_S22;
            i++;
            nb_de_suppression++;
        }
        if ( op == 1)
        {

            hamza.cle=cle;
            insertion1(&fic11,hamza,&nb_acc_l_I11,&nb_acc_e_I11);
                acc_ins11_lect[j] =  nb_acc_l_I11 ; 
                acc_ins11_ecr[j] =   nb_acc_e_I11;
            insertion2(&fic21,hamza,&nb_acc_l_I21,&nb_acc_e_I21);
                acc_ins21_lect[j] =  nb_acc_l_I21 ; 
                acc_ins21_ecr[j] =   nb_acc_e_I21;
            insertion1(&fic12,hamza,&nb_acc_l_I12,&nb_acc_e_I12);
                acc_ins12_lect[j] =  nb_acc_l_I12 ; 
                acc_ins12_ecr[j] =   nb_acc_e_I12;
            insertion2(&fic22,hamza,&nb_acc_l_I22,&nb_acc_e_I22);
                acc_ins22_lect[j] =  nb_acc_l_I22 ; 
                acc_ins22_ecr[j] =   nb_acc_e_I22;
            
            j++;
            nb_de_insertion ++;
        }
        //printf("%d %d %d %d %d ",nb_acc_e_I11,nb_acc_e_I12,nb_acc_e_I21,nb_acc_e_I22);
        //printf("\t%d %d %d %d %d \n",nb_acc_l_I11,nb_acc_l_I12,nb_acc_l_I21,nb_acc_l_I22);
    }
   
    printf(" Nombre d'elements qui contient 0 = [%d]  |||  Nombre d'elements qui contient 1 = [%d] \n", nb_de_suppression, nb_de_insertion);
    //printf(" nb_acc_lect = [%d]  |||  nb_acc_ecrt = [%d] \n",nb_acc_l,nb_acc_e);
    fclose(f);
    fermer_LOF(&fic11);
    fermer_LOF(&fic12);
    fermer_LOF(&fic21);
    fermer_LOF(&fic22);

    FILE *g = fopen("./test2/general.csv","w+");
    int MAX = 5000;
    fprintf(g,"ins11_lect_LOF;");
    for (int i = 0; i < MAX; i++){if (acc_ins11_lect[i] != 0){fprintf(g,"%d;",acc_ins11_lect[i]);}}
    fprintf(g,"\nins11_ecr_LOF;");
    for (int i = 0; i < MAX; i++){if (acc_ins11_ecr[i] != 0){fprintf(g,"%d;",acc_ins11_ecr[i]);}}
    fprintf(g,"\nsup11_lect_LOF;");
    for (int i = 0; i < MAX; i++){if (acc_sup11_lect[i] != 0){fprintf(g,"%d;",acc_sup11_lect[i]);}}
    fprintf(g,"\nsup11_ecr_LOF;");
    for (int i = 0; i < MAX; i++){if (acc_sup11_ecr[i] != 0){fprintf(g,"%d;",acc_sup11_ecr[i]);}}
    
    fprintf(g,"\nins21_lect_LOF;");
    for (int i = 0; i < MAX; i++){if (acc_ins21_lect[i] != 0){fprintf(g,"%d;",acc_ins21_lect[i]);}}
    fprintf(g,"\nins21_ecr_LOF;");
    for (int i = 0; i < MAX; i++){if (acc_ins21_ecr[i] != 0){fprintf(g,"%d;",acc_ins21_ecr[i]);}}
    fprintf(g,"\nsup21_lect_LOF;");
    for (int i = 0; i < MAX; i++){if (acc_sup21_lect[i] != 0){fprintf(g,"%d;",acc_sup21_lect[i]);}}
    fprintf(g,"\nsup21_ecr_LOF;");
    for (int i = 0; i < MAX; i++){if (acc_sup21_ecr[i] != 0){fprintf(g,"%d;",acc_sup21_ecr[i]);}}

    fprintf(g,"\nins12_lect_LOF;");
    for (int i = 0; i < MAX; i++){if (acc_ins12_lect[i] != 0){fprintf(g,"%d;",acc_ins12_lect[i]);}}
    fprintf(g,"\nins12_ecr_LOF;");
    for (int i = 0; i < MAX; i++){if (acc_ins12_ecr[i] != 0){fprintf(g,"%d;",acc_ins12_ecr[i]);}}
    fprintf(g,"\nsup12_lect_LOF;");
    for (int i = 0; i < MAX; i++){if (acc_sup12_lect[i] != 0){fprintf(g,"%d;",acc_sup12_lect[i]);}}
    fprintf(g,"\nsup12_ecr_LOF;");
    for (int i = 0; i < MAX; i++){if (acc_sup12_ecr[i] != 0){fprintf(g,"%d;",acc_sup12_ecr[i]);}}

    fprintf(g,"\nins22_lect_LOF;");
    for (int i = 0; i < MAX; i++){if (acc_ins22_lect[i] != 0){fprintf(g,"%d;",acc_ins22_lect[i]);}}
    fprintf(g,"\nins22_ecr_LOF;");
    for (int i = 0; i < MAX; i++){if (acc_ins22_ecr[i] != 0){fprintf(g,"%d;",acc_ins22_ecr[i]);}}
    fprintf(g,"\nsup22_lect_LOF;");
    for (int i = 0; i < MAX; i++){if (acc_sup22_lect[i] != 0){fprintf(g,"%d;",acc_sup22_lect[i]);}}
    fprintf(g,"\nsup22_ecr_LOF;");
    for (int i = 0; i < MAX; i++){if (acc_sup22_ecr[i] != 0){fprintf(g,"%d;",acc_sup22_ecr[i]);}}


    fclose(g);

    system("start ./test2/general.csv");
    sleep(2);
    system("start ./test2/general_grapheXX.xlsx");
    printf("Hello world");


    return 0;

}


/*FILE *g = fopen("./test/insr1_sup1_test.csv","w+");
    fprintf(g,"insr1_LOF;sup1_LOF\n");
    for (int i = 0; i < 100; i++)
    {
        fprintf(g,"%d;%d\n",acc_ins1[i],acc_sup1[i]);
    }
    fclose(g);
    system("start ./test/insr1_sup1_test.csv");
    sleep(0.5);
    system("start ./test/insr1_sup1_test_graph.xlsx");
    printf("Hello world");


fprintf(g,"insr1_LOF;");
    for (int i = 0; i < 100; i++)
    {
        //fprintf(g,"%d;%d\n",acc_sup[i],acc_ins[i]);
        fprintf(g,"%d;",acc_ins1[i]);
    }
    fprintf(g,"\n");
    fprintf(g,"sup1_LOF;");
    for (int i = 0; i < 100; i++)
    {
        //fprintf(g,"%d;%d\n",acc_sup[i],acc_ins[i]);
        fprintf(g,"%d;",acc_sup1[i]);
    }
    fclose(g);*/

