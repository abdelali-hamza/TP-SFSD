#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "bib.c"

int main()
{
    LOF fic ;
    int nb_acc_l = 0 , nb_acc_e = 0  ;
    int cle=0,op=0, cond =0,choix;
    int nb_de_insertion = 0, nb_de_suppression = 0 ;
    int trouv , size_text= 200 ;
    Tenreg hamza;
    FILE *f;
    //Menu();
    printf(" nb_acc_lect = [%d]  |||  nb_acc_ecrt = [%d] \n",nb_acc_l,nb_acc_e);
    srand(time(NULL));
    ouvrir_LOF(&fic,"LOF",'N');
    createRandomTextFile(size_text,"Hamza.txt");
    chargement_initial_LOF(&fic,1,"Hamza.txt");
    f = fopen("Hamza.txt","r+");
    int i=0,j=0;
    int acc_ins1[10000],acc_sup1[10000];
    while (!feof(f))
    {
        fscanf(f,"%d %d",&cle,&op);
        if (op == 0) {
            suppression1(&fic,cle,&nb_acc_l,&nb_acc_e);
            acc_sup1[i] =  nb_acc_l + nb_acc_e ;
            i++;
            //printf("acc = %d\n",nb_acc_l + nb_acc_e);
            nb_de_suppression++;
        }
        if ( op == 1)
        {

            hamza.cle=cle;
            insertion1(&fic,hamza,&nb_acc_l,&nb_acc_e);
            acc_ins1[j] =  nb_acc_l + nb_acc_e ;
            j++;
            //printf("\tacc = %d\n",nb_acc_l + nb_acc_e);
            nb_de_insertion ++;
        }
    }
    //printf(" Nombre d'elements supr = [%d]  |||  Nombre d'elements insr = [%d] \n",cpt_sup,cpt_inser);
    printf(" Nombre d'elements qui contient 0 = [%d]  |||  Nombre d'elements qui contient 1 = [%d] \n", nb_de_suppression, nb_de_insertion);
    printf(" nb_acc_lect = [%d]  |||  nb_acc_ecrt = [%d] \n",nb_acc_l,nb_acc_e);
    fclose(f);
    fermer_LOF(&fic);

FILE *g = fopen("./test2/insr1_sup1_test.csv","w+");
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
    fclose(g);
    system("start ./test2/insr1_sup1_test.csv");
    sleep(0.5);
    system("start ./test2/insr1_sup1_test_graph.xlsx");
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
    printf("Hello world");*/

    