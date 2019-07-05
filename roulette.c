
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<math.h>

int main()
{
int cagnotte=1000,mise=0,numBille=0,numChoisie=0;
char rejouer=' ';
do
{

    srand(time(NULL));
    numBille = rand() % 50;

    do
    {
        printf("etablir votre mise   ");
        scanf("%d",&mise);

    }while(!(mise>0 && mise<=cagnotte));
    do
    {
        printf("choisie un numbre entre 0 et 49   ");
        scanf("%d",&numChoisie);

    }while(!(numChoisie>-1 && numChoisie<50));

     if (numBille == numChoisie)
        cagnotte=cagnotte+mise*2;
     else if ((numBille % 2) == (numChoisie % 2))
        cagnotte+= ceil(mise/2);
     else
        cagnotte-=mise;
        

    do
    {
        printf("si vouz voulez rejouez appuier sur o sinon appuier sur n    \n");
        getchar();
        scanf("%c",&rejouer);
    }while(rejouer!= 'o' && rejouer != 'n');

    printf("votre cagnotte =   %d \n",cagnotte);




}while(cagnotte!=0 && rejouer == 'o');
    return 0;
}
