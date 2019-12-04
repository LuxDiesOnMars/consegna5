#include <stdio.h>

int fattoriale(int );

int main(void)
{
    int num;

    do{
        printf("inserisci numero intero di cui fare il fattoriale:\n");
        scanf("%d",&num);
        fflush(stdin);
    }while(num<0);
    int a=fattoriale(num);
    printf("%\nil fattoriale di %d è %d",num,a);
    return 0;
}




int fattoriale(int n)
{
    static int cont=0;
    int fatt;

    for(int i=0;i<cont;i++)printf("\t");
    printf("chiamata a fattoriale con n=%d\n",n);
    if(n<=0)
    {
        return 1;
    }
    else
    {
        cont++;
        fatt=n*fattoriale(n-1);
        cont--;
        for(int i=0;i<cont;i++)printf("\t");
        printf("chiusura  fattoriale con n=%d\n",n);

    }
    return fatt;
}
