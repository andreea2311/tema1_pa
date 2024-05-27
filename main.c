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

    FILE* date_out;
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
        fgets(nume,40,date_in);
        head->name_team=(char*)malloc(sizeof(char)*(strlen(nume)+1));
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
        //creez campul cu media punctajelor
        create_count(num_teams,&head);

        int power_two=powerOf2(num_teams);
        float mini; 
        int ok;


        //stergerea elementelor
        while(num_teams>power_two)
        {
            //calculez valoarea minima
            mini=minim_points(head,num_teams);
            
            Game *aux;
            aux=head;

            ok=0;
            
            //parcurg pana o gasesc si scot acel nod
            while(ok==0)
            {
                if(aux->points==mini && ok==0)
                {
                    delete_element(&head,aux,&num_teams);
                    ok=1;
                }

                if(aux!=NULL)
                    aux=aux->next;
            }
        }

        //se afiseaza in fisier la sfarsit
        afisare(head,date_out);
    }


    if(cerinte[2]==1)
    { 
        make_media(&head,num_teams);
        add_points(&head);

        //creez coada de meciuri
        Queue *meci;
        meci=(Queue*)malloc(sizeof(Queue));
        if(meci==NULL)
        {
            printf("Nu s a putut aloca - create_queue");
            exit(1);
        }

        meci->front=meci->rear=NULL;

        //introducerea tuturor elementelor in coada
        int round=1;
        Game *aux;
        aux=head;
        for(int i=0;i<num_teams;i=i+2)
        {
            enqueue(aux,aux->next,meci);
            aux=aux->next->next;            
        }

        Game *top8=create_stack();
        top8->next=NULL;
       
        //simulare meciuri si afisarea in fisier
        while(num_teams*2!=1)
        {   
            //se initializeaza stivele de castigatori/pierzatori
            Game *castigatori=create_stack();
            castigatori->next=NULL;
            Game *pierzatori=create_stack();
            pierzatori->next=NULL;

            num_teams=num_teams/2;
            afisare_runde(meci,round,date_out);

            
            int contor=0;

            printf("\n\n");

            while(contor<num_teams)
            {
                runda(meci,&pierzatori,&castigatori);

                if(round==2)
                   printf("%s",castigatori->name_team);

                dequeue(meci);
                contor++;
            }

            if(round==2)
               afisare_castigatori(castigatori);
            afisare_winners(castigatori,round,date_out);

            add_points(&castigatori);

            //se memoreaza ultimii 8 ramasi
            if(num_teams==8)
                create_winners(castigatori,&top8);


            round++;

            clear_stack(&pierzatori);
            meci->front=NULL;
            meci->rear=NULL;

            aux=castigatori;
            for(int i=0;i<num_teams;i=i+2)
            {
                enqueue(aux,aux->next,meci);
                aux=aux->next->next;
            }

            clear_stack(&castigatori);
        }
        
    }

    if(cerinte[3]==1)
    {

    }

    if(cerinte[4]==1)
    {

    }

    delete_list(&head);

    //inchiderea tuturor fisierelor
    fclose(date_in);
    fclose(date_out);
    fclose(cerinte_in);

    return 0;
}