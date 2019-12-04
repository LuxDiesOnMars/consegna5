#include <stdio.h>
#include <stdlib.h>


#define MAXSTR 20
#define NINSEGN 2
#define NSTUDENTI 10
#define NESAMI 2

   struct pianostudi
   {
       int codins;
       int voto;
   };
   struct studente
    {
        int numeromatricola;
        char nomeCognome[MAXSTR];
        int annoImm;
        char corstostudi[MAXSTR];
        struct insegnamento *assegnato;
        struct pianostudi ps[NINSEGN];
    };

    struct insegnamento
    {
        int codice;
        char descrizione[MAXSTR];
        int annoSomministrazione;
        int crediti;

    };


    struct studente studenti[NSTUDENTI];
    struct insegnamento insegnamenti[NINSEGN]={{1,"analisi",1,12},{2,"programmazione",1,12}};

    void nuovoPianoStudi(int );
    void modificaVotoPianoStudi(int);
    void addStudente();
    void stampaStudente(int);
    void mediaPesata();
    void menu();




int main(void)
{

    for(int j=0;j<NSTUDENTI;j++)
    {
        studenti[j].numeromatricola=0;
    }

    int risp;
    do{
        risp=0;
        menu();
        do{
            printf("eseguire alta operazione?[0/No-1/Sì]\n");
            scanf("%d",&risp);
            fflush(stdin);
        }while(risp!=0&&risp!=1);
        system("cls");
    }while(risp==1);


}




void addStudente()
{   int k=0;
    for(;k<NSTUDENTI;k++)
    {
        if(studenti[k].numeromatricola==0)break;
        if(k==NSTUDENTI-1 && studenti[k].numeromatricola!=0)
        {
            printf("ERRORE:vettore pieno.");
            return ;
        }
    }

    printf("inserire numero matricola:");
    scanf("%d",&studenti[k].numeromatricola);
    fflush(stdin);
    for(int h=0;h<NSTUDENTI;h++)
    {
        if(h==k)continue;
        else if(studenti[k].numeromatricola==studenti[h].numeromatricola)
        {
            printf("studente già presente in archivio\n");
            return;
        }
    }

    printf("\ninserire nome e cognome:");
    scanf("%[^\n]",studenti[k].nomeCognome);
    fflush(stdin);
    printf("\ninserire anno immatricolazione:");
    scanf("%d",&studenti[k].annoImm);
    fflush(stdin);
    printf("inserire corsto di studi:");
    scanf("%[^\n]",studenti[k].corstostudi);
    fflush(stdin);
    // modifica piano studi
    nuovoPianoStudi(studenti[k].numeromatricola);

}

void stampaStudente(int mat)
{
    int i=0;
    for(;i<NSTUDENTI;i++)
    {
        if(mat==studenti[i].numeromatricola)break;
        else if(i==NSTUDENTI-1){printf("STUDENTE NON TROVATO\n");return;}
    }
    printf("\n\nnome e cognome: %s, annoImm: %d, corso studi: %s \n",
           studenti[i].nomeCognome,studenti[i].annoImm,studenti[i].corstostudi);
    puts("piano di studi:\n");
    for(int m=0;m<NESAMI;m++)
    {
        if(studenti[i].ps[m].codins==0)break;

        printf("codice insegnamento:%d\nvoto:%d\n\n",studenti[i].ps[m].codins,studenti[i].ps[m].voto);
    }

}

void nuovoPianoStudi(int nMat)
{

    int i=0;
    for(;i<NSTUDENTI;i++)
    {
       if(studenti[i].numeromatricola==nMat)break;
       else if(i==NSTUDENTI-1)
       {
           printf("\nnumero di matricola non esiste in db\n");
           return;
       }
    }
    printf("inserire voto materie:\n");
    for(int j=0;j<NINSEGN;j++)
    {
       do{
            printf("%s:\n",insegnamenti[j].descrizione);
            int vo;
            studenti[i].ps[j].codins=insegnamenti[j].codice;
            scanf("%d",&studenti[i].ps[j].voto);
            fflush(stdin);
       }while(studenti[i].ps[j].voto<0||studenti[i].ps[j].voto>30);

    }
}


void modificaVotoPianoStudi(int nMat)
{
    int i=0;
    for(;i<NSTUDENTI;i++)
    {
       if(studenti[i].numeromatricola==nMat)break;
       else if(i==NSTUDENTI-1)
       {
           printf("\nnumero di matricola non esiste in db\n");
           return;
       }
    }
    int risp;
    do{
        int u;
        do{
            printf("di quale materia si vuole aggiungere/modificare il voto?:");
            for(int j=0;j<NINSEGN;j++)
            {
                printf("(%d)-%s \t",j,insegnamenti[j].descrizione);

                if(j==NINSEGN-1)printf("(%d)-annulla\n",NINSEGN);
            }
            scanf("%d",&u);
            fflush(stdin);
        }while(u<0||u>NINSEGN);
        if(u==NINSEGN)return;
        do{
            printf("voto:");
            scanf("%d",&studenti[i].ps[u].voto);
            fflush(stdin);
        }while(studenti[i].ps[u].voto<0||studenti[i].ps[u].voto>30);
        do{
            puts("aggiungere/modificare altro voto?[0/No-1/Sì]\n");
            scanf("%d",&risp);
            fflush(stdin);
        }while(risp!=0&&risp!=1);
    }while(risp==1);

}

void mediaPesata()
{
    float pesi=0;
    for(int j=0;j<NINSEGN;j++)
    {
        pesi+=insegnamenti[j].crediti;

    }
    //printf("pes%f",pesi);
    for(int i=0;i<NSTUDENTI;i++)
    {
        float mP=0;
        float num=0;
        if(studenti[i].numeromatricola==0)continue;
        int controllo=0;
        for(int l=0;l<NINSEGN;l++)
        {
            if(studenti[i].ps[l].voto==0)controllo=1;
        }
        if(controllo==1)continue;
        for(int j=0;j<NINSEGN;j++)
        {
            num+=(insegnamenti[j].crediti)*(studenti[i].ps[j].voto);
        }
        mP=num/pesi;
        printf("media pesata di studente %s è: %.2f\n",studenti[i].nomeCognome,mP);
    }

}


void menu()
{
    int risp;
    do{
        puts("quale opzione si desidera compiere:");
        puts("1-aggiungi studente");
        puts("2-modifica voto");
        puts("3-stampa studente");
        puts("4-media pesata di tutti gli studenti con piano di studi completo");
        scanf("%d",&risp);
        fflush(stdin);
        system("cls");
    }while(risp<1||risp>4);
    switch(risp)
    {
        case 1:
            addStudente();
            break;
        case 2:
            puts("inserisci numero di matricola di studente di cui si vuole aggiungere/modificare voto");
            int n;
            scanf("%d",&n);
            fflush(stdin);
            modificaVotoPianoStudi(n);
            break;
        case 3:
            puts("inserisci numero di matricola di studente di cui si vuole visualizzare i dettagli");
            int q;
            scanf("%d",&q);
            fflush(stdin);
            stampaStudente(q);
            break;
        case 4:
            mediaPesata();
            break;

    }




}

