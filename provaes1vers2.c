#include <stdio.h>
#include <stdlib.h>


#define MAXSTR 20
#define NINSEGN 2
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


    //struct studente * studenti=(struct studente *)malloc(sizeof(struct studente)*10);
    struct insegnamento insegnamenti[NINSEGN]={{1,"analisi",1,12},{2,"programmazione",1,12}};

    void nuovoPianoStudi(struct studente *,int );
    void modificaVotoPianoStudi(struct studente *,int);
    void addStudente(struct studente *);
    void stampaStudente(struct studente *,int);
    void mediaPesata(struct studente *);
    void menu(struct studente *);

    int NSTUDENTI=10;
    struct studente * studenti;


int main(void)
{
    if((studenti=(struct studente *)malloc(sizeof(struct studente)*NSTUDENTI))==NULL)
    {
        printf("MEMORIA PIENA\n");
        exit(1);
    };

    for(int j=0;j<NSTUDENTI;j++)
    {
        studenti[j].numeromatricola=0;
    }

    int risp;
    do{
        risp=0;
        menu(studenti);
        do{
            printf("eseguire alta operazione?[0/No-1/Sì]\n");
            scanf("%d",&risp);
            fflush(stdin);
        }while(risp!=0&&risp!=1);
        system("cls");
    }while(risp==1);
    free(studenti);

}




void addStudente(struct studente *a)
{   int k=0;
    int controllo=0;
    for(;k<NSTUDENTI;k++)
    {
        if(a[k].numeromatricola==0)break;
        else if(k==NSTUDENTI-1 && a[k].numeromatricola!=0)
        {
           controllo=1;
           break;
        }
    }
    if(controllo==1)
    {
        NSTUDENTI*=2;
        if((a=studenti=(struct studente *)realloc(a,sizeof(struct studente)*NSTUDENTI))==NULL)
        {
            printf("memoria piena");
            exit(1);
        }

        for(int j=k+1;j<NSTUDENTI;j++)
        {
            a[j].numeromatricola=0;
        }
        k++;

    }

    printf("inserire numero matricola:");
    int r;
    scanf("%d",&r);
    fflush(stdin);
    for(int h=0;h<NSTUDENTI;h++)
    {
        if(h==k)continue;
        else if(r==a[h].numeromatricola)
        {
            printf("studente già presente in archivio\n");
            return;
        }
    }
    a[k].numeromatricola=r;


    printf("\ninserire nome e cognome:");
    scanf("%[^\n]",a[k].nomeCognome);
    fflush(stdin);
    printf("\ninserire anno immatricolazione:");
    scanf("%d",&a[k].annoImm);
    fflush(stdin);
    printf("inserire corsto di studi:");
    scanf("%[^\n]",a[k].corstostudi);
    fflush(stdin);
    // modifica piano studi
    printf("(%d)",a[k].numeromatricola);
    nuovoPianoStudi(a,a[k].numeromatricola);

}

void stampaStudente(struct studente *a,int mat)
{
    int i=0;
    for(;i<NSTUDENTI;i++)
    {
        if(mat==a[i].numeromatricola)break;
        else if(i==NSTUDENTI-1){printf("STUDENTE NON TROVATO\n");return;}
    }
    printf("\n\nnome e cognome: %s, annoImm: %d, corso studi: %s \n",
           a[i].nomeCognome,a[i].annoImm,a[i].corstostudi);
    puts("piano di studi:\n");
    for(int m=0;m<NESAMI;m++)
    {
        if(a[i].ps[m].codins==0)break;

        printf("codice insegnamento:%d\nvoto:%d\n\n",a[i].ps[m].codins,a[i].ps[m].voto);
    }

}

void nuovoPianoStudi(struct studente *a,int nMat)
{

    int i=0;
    for(;i<NSTUDENTI;i++)
    {
       if(a[i].numeromatricola==nMat)break;
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
            a[i].ps[j].codins=insegnamenti[j].codice;
            scanf("%d",&a[i].ps[j].voto);
            fflush(stdin);
       }while(a[i].ps[j].voto<0||a[i].ps[j].voto>30);

    }
}


void modificaVotoPianoStudi(struct studente *a,int nMat)
{
    int i=0;
    for(;i<NSTUDENTI;i++)
    {
       if(a[i].numeromatricola==nMat)break;
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
            scanf("%d",&a[i].ps[u].voto);
            fflush(stdin);
        }while(a[i].ps[u].voto<0||a[i].ps[u].voto>30);
        do{
            puts("aggiungere/modificare altro voto?[0/No-1/Sì]\n");
            scanf("%d",&risp);
            fflush(stdin);
        }while(risp!=0&&risp!=1);
    }while(risp==1);

}

void mediaPesata(struct studente *a)
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
        if(a[i].numeromatricola==0)continue;
        int controllo=0;
        for(int l=0;l<NINSEGN;l++)
        {
            if(a[i].ps[l].voto==0)controllo=1;
        }
        if(controllo==1)continue;
        for(int j=0;j<NINSEGN;j++)
        {
            num+=(insegnamenti[j].crediti)*(a[i].ps[j].voto);
        }
        mP=num/pesi;
        printf("media pesata di studente %s è: %.2f\n",a[i].nomeCognome,mP);
    }

}


void menu(struct studente *a)
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
            addStudente(a);
            break;
        case 2:
            puts("inserisci numero di matricola di studente di cui si vuole aggiungere/modificare voto");
            int n;
            scanf("%d",&n);
            fflush(stdin);
            modificaVotoPianoStudi(a,n);
            break;
        case 3:
            puts("inserisci numero di matricola di studente di cui si vuole visualizzare i dettagli");
            int q;
            scanf("%d",&q);
            fflush(stdin);
            stampaStudente(a,q);
            break;
        case 4:
            mediaPesata(a);
            break;

    }




}

