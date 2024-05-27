
#include "library.h"

void addAtBeggining(Game **head,Game *team) //adauga pe prima poz elem team primit parametru
{
    Game *aux;

    aux=*head;
    *head=team;
    team->next=aux;

}

void create_list(Game **head, FILE* date_in)
{
    Game *team; //declarare de element nou si alocare
    team=(Game*)malloc(sizeof(Game));
    team->next=NULL;

    char aux;

    //citirea datelor despre echipa
    fscanf(date_in,"%d",&(team->num_particip));
    fscanf(date_in,"%c", &aux);

    team->name_team=(char*)malloc(sizeof(char)*40);
    if(team->name_team==NULL)
    {
        printf("Eroare la afisare - create list");
        exit(1);
    }

    fgets(team->name_team,40,date_in);
    
    if(strcmp(team->name_team,"0% ANGELS")==0 || strcmp(team->name_team,"FIGHTING IRISH")==0)
        team->name_team--;

    //citire date despre membrii
    crPlayerArray(&team,date_in);
    
    //adaugare
    addAtBeggining(head,team);

}

void crPlayerArray(Game **team,FILE* date_in)//creeaza vectorul de membrii
{
    int j;
    j=(*team)->num_particip;

    //alocare si declarare a vectorului
    (*team)->play=(player*)malloc(sizeof(player)*j);

    char nume[30];
    char aux[1];

    //citirea informatiilor despre fiecare
    for(int i=0;i<(*team)->num_particip;i++)
    {
        fscanf(date_in,"%s",nume);
        (*team)->play[i].nume=(char*)malloc(sizeof(char)*(strlen(nume)+1));//declarare nume
        strcpy((*team)->play[i].nume,nume);

        fgets(aux,1,date_in);//read pause

        fscanf(date_in,"%s",nume);
        (*team)->play[i].prenume=(char*)malloc(sizeof(char)*(strlen(nume)+1));//declarare prenume
        strcpy((*team)->play[i].prenume,nume);

        fgets(aux,1,date_in);//read pause

        fscanf(date_in,"%f",&((*team)->play[i].num_points));//citeste punctaj

        fgets(aux,1,date_in);//read end of line char
    }


}

void afisare(Game *head, FILE* date_out)//afisare in fisier pt checker
{
    Game *aux;
    aux=head;
    
    while(aux!=NULL)
    {
        if(strcmp("0% ANGELS",aux->name_team)==0 || strcmp("FIGHTING IRISH",aux->name_team)==0)
            fprintf(date_out,"%s",aux->name_team);
        else fprintf(date_out,"%s",aux->name_team);
        aux=aux->next;
    }
}

void create_count(int num_teams, Game **head)
{
    float count;
    Game *aux;
    aux=*head;

    for(int j=0;j<num_teams && aux!=NULL;j++)
    {
        count=0;
        for(int i=0;i<aux->num_particip;i++)
            count+=aux->play[i].num_points;
        aux->points=count/aux->num_particip;
        aux=aux->next;
    }
}

int powerOf2(int num_teams)
{
    int i=1;
    
    while(i*2<num_teams)
        i=i*2;
    
    return i;
}

float minim_points(Game *head,int num_teams)
{
    float mini=head->points;
    Game *aux;
    aux=head;
    aux=aux->next;

    for(int i=0;i<num_teams-1;i++)
    {
        if(aux->points<mini)
            mini=aux->points;
        aux=aux->next;
    }

    return mini;
}

void make_media(Game **head,int num_teams)
{
    Game *aux;
    aux=*head;

    for(int i=0;i<num_teams;i++)
        aux->points=(float)aux->points/aux->num_particip;
}

void delete_from_beggining(Game **head,int *num_teams)
{
    Game *aux;
    aux=*head;
    (*head)=(*head)->next;
    free(aux);

    (*num_teams)--;
}

void delete_from_list(Game *head, Game deleted, int *num_teams)
{
    Game *aux;
    aux=head->next;

    while(strcmp(aux->next->name_team,deleted.name_team)!=0)
        aux=aux->next;

    if(aux->next->next==NULL)
    {
        Game *help;
        help=aux->next;
        aux->next=NULL;
        free(help);
    }
    else 
        {
            Game *help;
            help=aux->next;
            aux->next=aux->next->next;
            free(help);
        }
    
    (*num_teams)--;
}

void delete_element(Game **head, Game *delete, int *num_teams)
{
    if(delete==*head)
    {
        Game *aux;
        aux=*head;
        (*head)=(*head)->next;
        free(aux);

        (*num_teams)--;

        return;
    }

    else 
        {
            Game *aux;
            aux=(*head);

            while(strcmp(aux->next->name_team,delete->name_team)!=0)
                aux=aux->next;

            if(aux->next->next==NULL)
            {
                Game *help;
                help=aux->next;
                aux->next=NULL;
                free(help);
            }
            else 
                {
                    Game *help;
                    help=aux->next;
                    aux->next=aux->next->next;
                    free(help);
                }
            
            (*num_teams)--;
        }
}

void delete_list(Game **head)
{
    Game *aux;
    aux=*head;

    while((*head)!=NULL)
    {
        aux=(*head);
        *head=(*head)->next;
        free(aux);
    }
}

void add_points(Game**head)
{
    Game *aux;
    aux=*head;

    while(aux!=NULL)
    {
        aux->points++;
        aux=aux->next;
    }
}


void print_list(Game *head,int num_teams)
{
    printf("\n");
    for(int i=0;i<num_teams;i++)
    {
        printf("%s - %0.2f\n",head->name_team,head->points);
        head=head->next;
    }
}

void enqueue(Game *node1,Game *node2, Queue *meci)
{
    Meci *newnode;
    newnode=(Meci*)malloc(sizeof(Meci));
    if(newnode==NULL)
    {
        printf("Nu s a putut aloca - enqueue");
        exit(1);
    }

    newnode->team1=node1;
    newnode->team2=node2;
    newnode->next=NULL;

    if(meci->rear == NULL)
        meci->rear=newnode; 
    else 
        {
            meci->rear->next=newnode;
            meci->rear=newnode;
        }
       
    if(meci->front==NULL) 
        meci->front=meci->rear;

    
/*
    for(int i=0;i<num_teams;i=i+2)
    {
        Meci *newnode=(Meci*)malloc(sizeof(Meci));
        if(newnode==NULL)
        {
            printf("Nu s-a putut aloca dinamic - enqueue");
            exit(1);
        }

        newnode->team1=aux;
        newnode->team2=aux->next;
        newnode->next=NULL;
        aux=aux->next->next;
        

        if(meci->rear == NULL)
        {
            meci->rear=newnode; ///tu trebuie sa schimbi si pointer ul de la rear pentru ca tu adaugi in coada; gen in rear :)))
        
            ///daca meci->rear este null atunci si meci->front e null si deci coada e goala si deci AMBELE trimit catre nodul newnode
        }
        else 
            {
                (meci->rear)->next=newnode;
                meci->rear=newnode;
            }
        
        if(meci->front==NULL) meci->front=meci->rear;///aici cand iti intra daca coada e goala ii dai lui meci->front o valoare si dupa ii pui NULL:)))
    }
    */
}

/*
void dequeue(Queue *meci)
{
    Meci *aux;

   // if(isEmptyQueue(meci)==1) return;

    aux=meci->front;
    meci->front=(meci->front)->next;

    if(meci->front==NULL)
        meci->rear=NULL;
    else 
        meci->front=NULL;
    
    free(aux);
}
*/

void dequeue(Queue *meci) {
    if (!meci || !meci->front) 
        return;  
    
    Meci *aux = meci->front;
    meci->front = meci->front->next;
    
    if (meci->front == NULL)
        meci->rear = NULL;  
    
    aux->next = NULL;  
}

int isEmptyQueue(Queue *meci)
{
    return (meci->front==NULL);
}

Game* create_stack()
{
    Game *node;
    node=(Game *)malloc(sizeof(Game));
    if(node==NULL)
    {
        printf("Nu s a putut aloca - create_stack");
        exit(1);
    }

    node->next=NULL;

    return node;
}

int lenght(Game *castigatori)
{
    Game *aux;
    aux=castigatori;

    int contor=0;

    while(aux!=NULL)
    {
        contor++;
        aux=aux->next;
    }

    return contor;
}

void pop(Game **stack)
{
    Game *aux;
    aux=*stack;

    (*stack)=(*stack)->next;
    free(aux);
}

void push(Game *node,Game **stack)
{
    Game *newnode=create_stack();
    
    *newnode=*node;
    newnode->next=*stack;

    *stack=newnode;

    //printf("%s",(*stack)->name_team);
}

void clear_stack(Game **stack)
{
    Game*aux;
    aux=*stack;

    aux=*stack;
    while(aux!=NULL)
    {
        *stack=(*stack)->next;
        free(aux);
        aux=*stack;
    }

    printf("Stack deleted\n");
}

void afisare_runde(Queue *meci,int round, FILE * date_out)
{
    fprintf(date_out,"\n--- ROUND NO:%d\n",round);
    //printf("--- ROUND NO:%d\n",round);
    int len;

    Meci *aux;
    aux=meci->front;

    //printf("%s %0.2f",meci->front->next->team1->name_team,meci->front->next->team1->points);

    while(aux!=NULL)
    {
        len=strlen(aux->team1->name_team);
        //printf("%s",aux->team1->name_team);
        for(int i=0;i<len-2;i++)
            fprintf(date_out,"%c",aux->team1->name_team[i]);

        for(int i=0;i<35-len;i++)
            fprintf(date_out," ");
            //printf(" ");
        

        fprintf(date_out,"-");
        //printf(" ");
        
        len=strlen(aux->team2->name_team);
        for(int i=0;i<35-len+1;i++)
            fprintf(date_out," ");
            //printf(" ");
        for(int i=0;i<strlen(aux->team2->name_team)-1;i++)
            fprintf(date_out,"%c",aux->team2->name_team[i]);
        //printf("%s",aux->team2->name_team)

        aux=aux->next;
    }

    fprintf(date_out,"\n");
}

void afisare_castigatori(Game *castigatori)
{
    while(castigatori->next!=NULL)
    {        
        printf("\n%s",castigatori->name_team);
        castigatori=castigatori->next;
    }
}

void afisare_winners(Game *castigatori,int round,FILE *date_out)
{
    int len;

    fprintf(date_out,"\nWINNERS OF ROUND NO:%d\n",round);

    while(castigatori->next!=NULL)
    {
        len=strlen(castigatori->name_team);
        for(int i=0;i<len-2;i++)
            fprintf(date_out,"%c",castigatori->name_team[i]);

        for(int i=0;i<35-len+1;i++)
            fprintf(date_out," ");
        
        fprintf(date_out,"-  %0.2f\n",castigatori->points);

        castigatori=castigatori->next;
    }
}

void runda(Queue *meci, Game **pierzatori, Game **castigatori)
{
    if(meci->front->team1->points>meci->front->team2->points)
    {
        push(meci->front->team1,castigatori);
        push(meci->front->team2,pierzatori);
        //printf(">>> ");
    }
    else if(meci->front->team1->points<meci->front->team2->points)
        {
            push(meci->front->team2,castigatori);
            push(meci->front->team1,pierzatori);
            //printf(" <<< ");
        }
        else if(meci->front->team1->points==meci->front->team2->points)
            {
                push(meci->front->team2,castigatori);
                push(meci->front->team1,pierzatori);
                //printf("--- ");
            }
}

void create_winners(Game *castigatori,Game **top8)
{
    Game *aux;
    aux=castigatori;

    for(int i=0;i<8;i++)
    {
        Game *newnode;
        newnode=(Game*)malloc(sizeof(Game));
        if(newnode==NULL)
        {
            printf("Alocare esuata - cr_winners");
            exit(1);
        }

        newnode=aux;
        newnode->next=*top8;

        *top8=newnode;
        aux=aux->next;
    }
}