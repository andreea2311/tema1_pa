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
    int points;
    struct Game *next;
};

typedef struct Game Game;

struct Meciuri
{
    Game *team1;
    Game *team2;
    
}


void addAtBeggining(Game **head,Game *team);
void create_list(Game **head,FILE *date_in);
void crPlayerArray(Game **team,FILE* date_in);
void afisare(Game *head,FILE *date_out);
void create_count(int num_teams, Game **head);
int powerOf2(int num_teams);
int minim_points(Game *head, int num_teams);
void delete_from_beggining(Game **head, int *num_teams);
void delete_from_list(Game *head, Game deleted, int *num_teams);
void delete_list(Game **head);
void add_points(Game **head);