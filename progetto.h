#define MAX_CHAR_ARTIST 25
#define MAX_CHAR_TITLE 25
#define MAX_CHAR_GEN 20
#define MAX_LIST 50

#define FULL -1

#define LIST_SIZE 10

#define TRUE 1
#define FALSE 0
#define FALSISSIMO -1

#define OK 0

#define INSERIMENTO_BRANO 1
#define RICERCA_BRANO 2
#define ELIMINA_BRANO 3
#define MOSTRA_TUTTI 4
#define USCITA 0

typedef struct {
    char titolo[MAX_CHAR_TITLE];
    float durata;
    char artista[MAX_CHAR_ARTIST];
    char genere[MAX_CHAR_GEN];
} t_brano;

typedef struct t_brani {
    t_brano brano;
    struct t_brani *next;
    int progressivo;
} t_brani;

typedef struct t_lista_brani {
    t_brani *head;
    t_brani *coda;
    int num_elementi;
} t_lista_brani;

typedef struct t_brani *ptr_brani;

typedef struct t_lista_brani *ptr_list;

ptr_list create();

t_brano leggi_brano();

int genera_progrrssivo(ptr_list);

int inserimento_brano(ptr_list *, t_brano);

ptr_list cerca_brano(ptr_list, char *);

int elimina_brano(ptr_list *, int);

void show(ptr_list);

void show_file(ptr_list, FILE *);

int svuota_lista(ptr_list *);

int is_empty(ptr_list);

int is_full(ptr_list);
