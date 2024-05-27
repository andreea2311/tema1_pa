#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

struct player
{
    char* nume;
    char* prenume;
    float num_points;
};

typedef struct player player;

struct Game
{
    int num_particip;
    char* name_team;
    player *play;
    float points;
    struct Game *next;
};

typedef struct Game Game;

struct Meci
{
    Game *team1;
    Game *team2;
    struct Meci *next;
};

typedef struct Meci Meci;

struct Queue
{
    Meci *front;
    Meci *rear;
};

typedef struct Queue Queue;

void addAtBeggining(Game **head,Game *team);
void create_list(Game **head,FILE *date_in);
void crPlayerArray(Game **team,FILE* date_in);
void afisare(Game *head, FILE* date_out);
void create_count(int num_teams, Game **head);
int powerOf2(int num_teams);
float minim_points(Game *head, int num_teams);
void make_media(Game **head,int num_teams);
void delete_from_beggining(Game **head, int *num_teams);
void print_list(Game *head,int num_teams);
void delete_from_list(Game *head, Game deleted, int *num_teams);
void delete_list(Game **head);
void delete_element(Game **head, Game*delete, int *num_teams);
void add_points(Game **head);
void enqueue(Game *node1,Game *node2, Queue *meci);
Meci* deQueue(Queue* q);
int isEmptyQueue(Queue *meci);
int lenght(Game *castigatori);
void pop(Game **stack);
void push(Game *node,Game **stack);
int stackIsEmpty(Game* top);
void clear_stack(Game **top,int num_teams);
void afisare_runde(Queue *meci,int rund, FILE *date_out);
void runda(Meci *node, Game **pierzatori, Game **castigatori);
void create_winners(Game *castigatori,Game **top8);