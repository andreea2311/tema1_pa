
#include "library.h"
#pragma pack(8)
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
    char nume[40];
    

    //citirea datelor despre echipa
    fscanf(date_in,"%d",&(team->num_particip));
    fscanf(date_in,"%c", &aux);
    fgets(nume,40,date_in);
    nume[strlen(nume)-1] = '\0';

    if(nume[strlen(nume)-2] == ' ')
    {
        nume[strlen(nume)-1] = '\0';
    }

    team->name_team=(char*)malloc(sizeof(char)*strlen(nume)+2);    
    if(team->name_team==NULL)
    {
        printf("Eroare la afisare - create list");
        exit(1);
    }
    strcpy(team->name_team,nume);

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
        int len=strlen(aux->name_team);
        if(aux->name_team[len]-2==' ')
            len--;
        for(int i=0;i<len-1;i++)
            fprintf(date_out,"%c",aux->name_team[i]);
        fprintf(date_out,"\n");
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

    for(int i=1;i<num_teams;i++)
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
    
}

Meci* deQueue(Queue* q){
    Meci* aux;
    if(isEmptyQueue(q)){
        aux = (Meci*)malloc(sizeof(Meci));
        if(aux == NULL){
            printf("Memory allocation failed.\n");
            exit(1);
        }

        aux->team1 = (Game*)malloc(sizeof(Game));
        if(aux->team1 == NULL){
            printf("Memory allocation failed.\n");
            exit(1);
        }
        aux->team2 = (Game*)malloc(sizeof(Game));
        if(aux->team2 == NULL){
            printf("Memory allocation failed.\n");
            exit(1);
        }
        strcpy(aux->team1->name_team, "Queue is empty.");
        strcpy(aux->team2->name_team, "Queue is empty.");
        printf("Queue is empty.\n");
        return aux;
    }

    aux = q->front;
    q->front = (q->front)->next;
    aux->next = NULL;
    if(q->front == NULL)
        q->rear = NULL;
    return aux;
}

int isEmptyQueue(Queue *meci)
{
    return (meci->front==NULL);
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
    node->next = *stack;
    *stack = node;
}

int stackIsEmpty(Game* top){
    return (top == NULL);
}

void clear_stack(Game** top,int num_teams){
    //Game* temp;
    for(int i=0;i<num_teams;i++)
    {
       // temp = *top;
        *top = (*top)->next;
    }
}

void afisare_runde(Queue *meci,int rund, FILE * date_out)
{
    fprintf(date_out,"\n--- ROUND NO:%d\n",rund);
    
    int len;

    Meci *aux;
    aux=meci->front;

    while(aux!=NULL)
    {
        len=strlen(aux->team1->name_team);
        for(int i=0;i<len-1;i++)
            fprintf(date_out,"%c",aux->team1->name_team[i]);
        
        for(int i=0;i<34-len;i++)
            fprintf(date_out," ");
    
        fprintf(date_out,"-");
        
        len=strlen(aux->team2->name_team);
        for(int i=0;i<33-len+1;i++)
            fprintf(date_out," ");

        for(int i=0;i<len-1;i++)
            fprintf(date_out,"%c",aux->team2->name_team[i]);
        fprintf(date_out,"\n");
            
        aux=aux->next;
    }

    fprintf(date_out,"\n");
}

void runda(Meci *node, Game **pierzatori, Game **castigatori)
{
    if(node->team1->points>node->team2->points)
    {
        push(node->team1,castigatori);
        push(node->team2,pierzatori);
    }
    else if(node->team1->points<node->team2->points)
        {
            push(node->team2,castigatori);
            push(node->team1,pierzatori);
        }
        else if(node->team1->points==node->team2->points)
            {
                push(node->team2,castigatori);
                push(node->team1,pierzatori);
            }
}

void create_winners(Game *castigatori,Game **top8)
{
    Game *aux;
    aux=castigatori;

    
}