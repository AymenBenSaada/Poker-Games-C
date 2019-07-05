#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
typedef struct card
{
	char val[2];
	int score;
	int type;
	int status;
	struct card *suiv;
}card;
//init deck cards
card *init_deck()
{
	char cards[13][2]={"2","3","4","5","6","7","8","9","10","J","Q","K","A"};
	card *deck=NULL,*cur1=NULL,*cur2=NULL; 
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<13;j++)
		{
			if(deck==NULL)
			{
				deck=(card*)malloc(sizeof(card));
				cur1=deck;
				strcpy(cur1->val,"2");
				cur1->score=2;
				cur1->type=0;
				cur1->status=1;
				cur1->suiv=NULL;
			}
			else
			{
				cur2=(card*)malloc(sizeof(card));
				strcpy(cur2->val,cards[j]);
				if(j==8)
				strcpy(cur2->val,"10");
				cur2->status=1;
				cur2->type=i;
				cur2->score=j+2;
				cur2->suiv=NULL;
				cur1->suiv=cur2;
				cur1=cur2;
				cur2=cur2->suiv;
			}
		}
	}
return deck;
}
int *bet(int cash[])
{
	int *betTab;
	betTab=(int*)malloc(sizeof(int));
	do
	{
		printf("bet is fixed at 100, type 0 to fold , 100 to call/allmoney or more to raise\n---------------------------\n");
		scanf("%d",betTab);
	}while (((*betTab>cash[0]) && (*betTab!=100)) || ((*betTab<100) && (*betTab>0))); //bet > money
	if(*betTab>100)
	cash[0]-=*betTab;
	else
	{
		if (*betTab==100)
			{
				if (cash[0]<100)
					{*betTab=cash[0];
					cash[0]=0;}
				else
				{
					*betTab=100;
					cash[0]-=100;
				}
			}
	}
	if(*betTab>cash[1])
	{
		printf("can't call,i'm all in then.\n");
		*(betTab+1)=cash[1];
		cash[1]=0;
	}
	else
	{
		printf("call\n");
		*(betTab+1)=*betTab;
		cash[1]-=*(betTab+1);
	}
	return betTab;
}

card *draw_card(card *deck,int pos)
{
	int i=1;
	card *c=deck;
	while(i<pos)
	{
		c=c->suiv;
		i++;
	}
	return c;
}
card *draw_hand(card *deck)
{
	int pos;
	card *c,*hand,*c2;
	do
	{
		srand(time(NULL));
		pos=rand()%(52);
		c=draw_card(deck,pos);
	}while(!(c->status));
	hand=(card*)malloc(sizeof(card));
	strcpy(hand->val,c->val);
	hand->score=c->score;
	hand->type=c->type;
	c->status=0;
	do
        {
                srand(time(NULL));
                pos=rand()%(52);
                c=draw_card(deck,pos);
        }while(!(c->status));
        c2=(card*)malloc(sizeof(card));
        strcpy(c2->val,c->val);
        c2->score=c->score;
        c2->type=c->type;
        c->status=0;
	hand->suiv=c2;
	c2->suiv=NULL;
	return hand;

}
void main()
{
int i,cash[2]={1000,1000},*betTab;
card *deck,*player_hand,*pc_hand;
deck=init_deck();
printf("-----------------initial bet: fixed at 100\n");
betTab=bet(cash);
printf("Your bet: %d\nPc's bet: %d\n",betTab[0],betTab[1]);
player_hand=draw_hand(deck);
pc_hand=draw_hand(deck);
printf("your hand:\n");
while(player_hand!=NULL)
{
	printf("%s | %d \n",player_hand->val,player_hand->type);
	player_hand=player_hand->suiv;
}
printf("second bet:\n");
}
