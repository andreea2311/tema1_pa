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
    Game *head = NULL; //declar capul listei si il initializez cu primul element din fisier
    head=(Game*)malloc(sizeof(Game)); 
    head->next=NULL;

    //verificare cerinta 1 si executarea ei
    if(cerinte[0]==1)
    {
         //numarul de elemenete(echipe din fisier)
        fscanf(date_in,"%d",&num_teams);

        char aux;//citeste pauza/end of life character
        fscanf(date_in,"%c",&aux);
        
        fscanf(date_in,"%d",&(*head).num_particip);//citesc numarul de persoane din echipa
        fscanf(date_in,"%c",&aux);

        //citire nume echipa folosind o variabila ajutatoare
        char nume[40];
        fgets(nume,40,date_in);

        nume[strlen(nume)-1]='\0';
        if(nume[strlen(nume)-2] == ' ')
        {
            nume[strlen(nume)-2] = '\0';
        }
      
        head->name_team=(char*)malloc(sizeof(char)*(strlen(nume)+1));
        strcpy(head->name_team,nume);
       
        //creare vector de playeri din echipa
        crPlayerArray(&head,date_in);

        //functie de creare a listei
        for(int i=0;i<num_teams-1;i++)
        create_list(&head,date_in);

        //delete_enter(&head);
        //delete_spaces(&head);

        //afisare in fisier
        if(cerinte[1]==0)
        {
            Game *aux;
            aux=head;
            while(aux!=NULL)
            {
                fprintf(date_out,"%s\n",aux->name_team);
                aux=aux->next;
            }
        }
    }

    
    if(cerinte[1]==1)
    {
        //creez campul cu media punctajelor
        create_count(num_teams,&head);

        int power_two=powerOf2(num_teams+1);
       // printf("%d %d",num_teams,power_two);
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

    Game *top8=NULL;

    if(cerinte[2]==1)
    { 
        float n=head->points;
        make_media(&head,num_teams);
        head->points=n;

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
        int rund=1;
        Game *aux;
        aux=head;
        for(int i=0;i<num_teams;i=i+2)
        {
            enqueue(aux,aux->next,meci);
            aux=aux->next->next;            
        }
        
        meci->front->team1->points=head->points;
        
        //simulare meciuri si afisarea in fisier
        while(num_teams!=1)
        {   
            //se initializeaza stivele de castigatori/pierzatori
            Game *castigatori=NULL;

            Game *pierzatori=NULL;

            num_teams=num_teams/2;
            afisare_runde(meci,rund,date_out);

            int contor=0;

            //se simuleaza fiecare meci din runda si se afla castigatorul/pierzatorul
            while(contor<num_teams)
            {
                Meci *help;
                help=deQueue(meci);

                runda(help,&pierzatori,&castigatori);

                contor++;
            }


            //se afiseaza castigatorii
            fprintf(date_out,"WINNERS OF ROUND NO:%d\n",rund);

            int len;
            Game *copy;
            copy=castigatori;

            while(copy!=NULL)
            {
                len=strlen(copy->name_team);
                for(int i=0;i<len-1;i++)
                    fprintf(date_out,"%c",copy->name_team[i]);

                for(int i=0;i<34-len+1;i++)
                    fprintf(date_out," ");
                
                fprintf(date_out,"-  %0.2f\n",copy->points);

                copy=copy->next;
            }

            //se adauga puncte 
            add_points(&castigatori);

            //se memoreaza ultimii 8 ramasi
            if(num_teams==8)
                copy_stack(castigatori,&top8);
            
            rund++;

            //se elibereaza spatiile de memorie ocupate
            if(num_teams>1)
                clear_stack(&pierzatori,num_teams);

            meci->front=NULL;
            meci->rear=NULL;

            aux=castigatori;

            //se reconstruieste urmatoarea coada de meciuri
            for(int i=0;i<num_teams && num_teams>1;i=i+2)
            {
                enqueue(aux,aux->next,meci);
                aux=aux->next->next;
            }
    
            if(num_teams>1)
                clear_stack(&castigatori,num_teams);

        }
    }

    if(cerinte[3]==1)
    {
        //se creeaza arborele
        Arbore *root;
        root=(Arbore*)malloc(sizeof(Arbore));
        if(root==NULL)
        {
            printf("Eroare la alocare - root");
            exit(1);
        }

        root->value=top8;
        root->left=NULL;
        root->right=NULL;
        
        Game *aux=top8->next;

        //se adauga nodurile din stiva
        while(aux)
        {
            root=inserare_bst(aux,root);
            aux=aux->next;
        }

        //se afiseaza in fisier
        fprintf(date_out,"\nTOP 8 TEAMS:\n");
        BST_print(root,date_out);

    }

    if(cerinte[4]==1)
    {
        //se creeaza arborele
        Arbore *root;
        root=(Arbore*)malloc(sizeof(Arbore));
        if(root==NULL)
        {
            printf("Eroare la alocare - root");
            exit(1);
        }

        root->value=top8;
        root->left=NULL;
        root->right=NULL;
        
        Game *aux=top8->next;

        //se adauga nodurile din stiva
        while(aux)
        {
            root=inserare_bst(aux,root);
            aux=aux->next;
        }

        //se afiseaza in fisier
        fprintf(date_out,"\nTOP 8 TEAMS:\n");
        BST_print(root,date_out);

        

        
    }

    delete_list(&head);

    //inchiderea tuturor fisierelor
    fclose(date_in);
    fclose(date_out);
    fclose(cerinte_in);

    return 0;
}