
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