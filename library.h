#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct player
{
    char* nume;
    char* prenume;
    int num_points;
};

typedef struct player player;

struct Game
{
    int num_particip;
    char* name_team;
    player *play;
    struct Game *next;
};

typedef struct Game Game;


void addAtBeggining(Game **head,Game *team);
void create_list(Game **head,FILE *date_in);
void crPlayerArray(Game **team,FILE* date_in);
void afisare(Game *head,FILE *date_out);
