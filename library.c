
#include "library.h"

void addAtBeggining(Game **head,Game *team) //adauga pe prima poz elem team primit parametru
{
    Game *aux;

    aux=*head;
    *head=team;
    team->next=aux;

}

void create_list(Game **head,FILE *date_in)
{
    Game *team; //declarare de element nou si alocare
    team=(Game*)malloc(sizeof(Game));
    team->next=NULL;

    char aux;

    //citirea datelor despre echipa
    fscanf(date_in,"%d",&(team->num_particip));
    fscanf(date_in,"%c", &aux);
    team->name_team=(char*)malloc(sizeof(char)*40);
    fgets(team->name_team,40,date_in);

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
        (*team)->play[i].nume=(char*)malloc(sizeof(char)*(strlen(nume)));//declarare nume
        strcpy((*team)->play[i].nume,nume);

        fgets(aux,1,date_in);//read pause

        fscanf(date_in,"%s",nume);
        (*team)->play[i].prenume=(char*)malloc(sizeof(char)*(strlen(nume)));//declarare prenume
        strcpy((*team)->play[i].prenume,nume);

        fgets(aux,1,date_in);//read pause

        fscanf(date_in,"%f",&((*team)->play[i].num_points));//citeste punctaj

        fgets(aux,1,date_in);//read end of line char
    }

}

void afisare(Game *head,FILE *date_out)//afisare in fisier pt checker
{
    Game *aux;
    aux=head;
    
    while(aux!=NULL)
    {
        fprintf(date_out,"%s",aux->name_team);
        aux=aux->next;
    }
}

void create_count(int num_teams, Game **head)
{
    int count;
    Game *aux;
    aux=*head;

    for(int j=0;j<num_teams && aux!=NULL;j++)
    {
        count=0;
        for(int i=0;i<aux->num_particip;i++)
            count+=aux->play[i].num_points;
        aux->points=count;
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

int minim_points(Game *head,int num_teams)
{
    int mini=head->points;
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
        *head=(*head)->next;
        free(aux);
        aux=*head;
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

Queue* create_queue()
{
    Queue *meci;
    meci=(Queue*)malloc(sizeof(Queue));

    if(meci==NULL)
    {
        printf("Nu s a putut aloca - create_queue");
        exit(1);
    }

    meci->front=meci->rear=NULL;

    return meci;
}

void enqueue(Game *head, Queue *meci)
{
    Game *aux;
    aux=head;

    while(aux!=NULL)
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
            meci->front=newnode;
        else 
            {
                (meci->rear)->next=newnode;
                meci->rear=newnode;
            }
        
        if(meci->front==NULL) meci->front=meci->rear;
    }
}

void dequeue(Queue *meci)
{
    Meci *aux;

    if(isEmptyQueue(meci)==1) return;

    aux=meci->front;
    meci->front=(meci->front)->next;

    if(meci->front==NULL)
        meci->rear=meci->front;
    
    free(aux);
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


    Game *newnode;
    newnode=(Game*)malloc(sizeof(Game));
    if(newnode==NULL)
    {
        printf("Nu s a alocat - push");
    }



    strcpy(newnode->name_team,node->name_team);
    newnode->num_particip=node->num_particip;
    newnode->points=node->points;
    newnode->play=node->play;
    newnode->next=*stack;
    *stack=newnode;
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
}

void afisare_runde(Queue *meci,int round, FILE *date_out)
{

    fprintf(date_out,"--- ROUND NO:%d\n",round);
    int len;

    Meci *aux;
    aux=meci->front;

    while(aux!=NULL)
    {
        len=strlen(aux->team1->name_team);
        fprintf(date_out,"%s",aux->team1->name_team);
        for(int i=0;i<33-len+1;i++)
            fprintf(date_out," ");

        fprintf(date_out,"-");
        
        len=strlen(aux->team2->name_team);
        for(int i=0;i<33-len+1;i++)
            fprintf(date_out," ");
        fprintf(date_out,"%s\n",aux->team2->name_team);

        aux=aux->next;
    }
}

void afisare_winners(Game *castigatori,int round,FILE *date_out)
{
    int len;

    fprintf(date_out,"WINNERS OF ROUND NO:%d\n",round);

    while(castigatori!=NULL)
    {
        len=strlen(castigatori->name_team);
        fprintf(date_out,"%s",castigatori->name_team);
        for(int i=0;i<34-len+1;i++)
            fprintf(date_out," ");
        
        fprintf(date_out,"-  %0.2f\n",castigatori->points);

        castigatori=castigatori->next;
    }
}

Game* play_round(int *num_teams,int *round,Queue *meci, Game **pierzatori)
{
    Game *castigatori;
    castigatori=(Game*)malloc(sizeof(Game));
    if(castigatori==NULL)
    {
        printf("Eroare la alocare - play round");
        exit(1);
    }

    for(int i=(*num_teams);i>1;i=i/2)
    {
        if(meci->front->team1->points>meci->front->team2->points)
        {
            push(meci->front->team1,&castigatori);
            push(meci->front->team2,pierzatori);            
        }
        else 
            {
                push(meci->front->team1,pierzatori);
                push(meci->front->team2,&castigatori);
            } 
        
        dequeue(meci);

    }

    round++;

    return castigatori;
}