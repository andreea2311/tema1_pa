
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

        fscanf(date_in,"%d",&((*team)->play[i].num_points));//citeste punctaj

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

void create_queue(Game *head)
{
    
}