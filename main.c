#include "library.h"

int main(int argc, char* argv[])
{
    // deschiderea si declararea fisierelor care vor fi folosite
    FILE* cerinte_in;
    if((cerinte_in=fopen(argv[1],"r"))==NULL)
    {
        printf("Fisierul nu s-a putut deschide. ");
        exit(1);
    }
  
    //citire numar cerinta
    int cerinte[5];
    for(int i=0;i<5;i++)
    {
        fscanf(cerinte_in,"%d",&cerinte[i]);
      //  printf("%d",cerinte[i]);
    }

    FILE* date_in;
    if((date_in=fopen(argv[2],"r"))==NULL)
    {
        printf("Fisierul nu s-a putut deschide. ");
        exit(1);
    }

    FILE *date_out;
    if((date_out=fopen(argv[3],"w"))==NULL)
    {
        printf("Fisierul nu s-a putut deschide. ");
        exit(1);
    }

    int num_teams;
    Game *head; //declar capul listei si il initializez cu primul element din fisier
    head=(Game*)malloc(sizeof(Game)); 
    head->next=NULL;

    //verificare cerinta 1 si executarea ei
    if(cerinte[0]==1)
    {
         //numarul de elemenete(echipe din fisier)
        fscanf(date_in,"%d",&num_teams);

        char aux;//citeste pauza/end of life character
        fscanf(date_in,"%c",&aux);
        
        fscanf(date_in,"%d",&(*head).num_particip);//citesc numele de persoane din echipa

        fscanf(date_in,"%c",&aux);

        //citire nume echipa folosind o variabila ajutatoare
        char nume[40];
        head->name_team=(char*)malloc(sizeof(char)*40);
        fgets(nume,40,date_in);
        strcpy(head->name_team,nume);
    
       // fscanf(date_in,"%d",&(head->num_particip));

        //creare vector de playeri din echipa
        crPlayerArray(&head,date_in);

        //functie de creare a listei
        for(int i=0;i<num_teams-1;i++)
        create_list(&head,date_in);

        //afisare in fisier
        if(cerinte[1]==0)
        {
            afisare(head,date_out);
        }
    }
    
    if(cerinte[1]==1)
    {
        create_count(num_teams,&head);
        int power_two=powerOf2(num_teams);
        int mini; 

        while(num_teams>power_two)
        {
            mini=minim_points(head,num_teams);
            
            Game *aux;
            aux=head;

            int ok=0;
            while(aux!=NULL && ok==0)
            {
                if(aux->points==mini && ok==0)
                {
                    if(aux==head)
                        delete_from_beggining(&head,&num_teams);
                    else delete_from_stack(head,*aux,&num_teams);
                    ok=1;
                }
                if(aux!=NULL)
                    aux=aux->next;
            }

        }
        

       

        afisare(head,date_out);

    }

    if(cerinte[2]==1)
    {

    }

    if(cerinte[3]==1)
    {

    }

    if(cerinte[4]==1)
    {

    }

    delete_stack(&head);

    //inchiderea tuturor fisierelor
    fclose(date_in);
    fclose(date_out);
    fclose(cerinte_in);

    return 0;
}