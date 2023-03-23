#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "progetto.h"

ptr_list create() {
    ptr_list new_list = (ptr_list) malloc(sizeof(struct t_lista_brani));

    new_list->num_elementi = 0;
    new_list->head = NULL;
    new_list->coda = NULL;

    return new_list;
}

int inserimento_brano(ptr_list *lista_brani, t_brano nuovo_brano) {

    ptr_brani new_element;

    if ((*lista_brani)->num_elementi == LIST_SIZE) {
        return FULL;
    }
    new_element = malloc(sizeof(struct t_brani));
    new_element->brano = nuovo_brano;
    new_element->next = NULL;
    new_element->progressivo = genera_progrrssivo(*lista_brani);

    if ((*lista_brani)->num_elementi == 0) {
        (*lista_brani)->head = new_element;
        (*lista_brani)->coda = new_element;
        (*lista_brani)->num_elementi++;
        return OK;
    }
    (*lista_brani)->coda->next = new_element;
    (*lista_brani)->coda = new_element;
    (*lista_brani)->num_elementi++;

    return OK;
}

int genera_progrrssivo(ptr_list _lista_brani) {
    if (_lista_brani->head == NULL) {
        return 1;
    } else {
        return _lista_brani->coda->progressivo + 1;
    }
}

t_brano leggi_brano() {
    t_brano nuovo_brano;

    printf("Inserisci il titolo del brano: ");
    scanf("%s", nuovo_brano.titolo);
    printf("Inserisci l'artista: ");
    scanf("%s", nuovo_brano.artista);
    printf("Inserisci la durata del brano: ");
    scanf("%f", &nuovo_brano.durata);
    printf("Inserisci il genere del brano: ");
    scanf("%s", nuovo_brano.genere);


    return nuovo_brano;
}

int is_empty(ptr_list new_list) {
    if (new_list->head == NULL) {
        return TRUE;
    }
    return FALSE;
}

int is_full(ptr_list new_list) {
    if (new_list->num_elementi == MAX_LIST) {
        return TRUE;
    }
    return FALSE;
}

void show_file(ptr_list new_list, FILE *file_brani) {
    ptr_brani ptr;

    if (is_empty(new_list)) {
        printf("Playlist vuota!\n");
    } else {
        ptr = new_list->head;
        while (ptr != NULL) {

            printf("Titolo : %s\n", ptr->brano.titolo);
            printf("Genere : %s\n", ptr->brano.genere);
            printf("Artista: %s\n", ptr->brano.artista);
            printf("Durata : %0.2f minuti\n\n", ptr->brano.durata);
            //stampa su file
            fprintf(file_brani, "Titolo:%s\n Genere:%s\n Artista:%s\n Durata:%f\n\n", ptr->brano.titolo,
                    ptr->brano.genere, ptr->brano.artista, ptr->brano.durata);
            ptr = ptr->next;
        }
    }
}

ptr_list cerca_brano(ptr_list _list, char *_tipo) {
    ptr_list _new_list;
    ptr_brani ptr;

    _new_list = create();

    ptr = _list->head;

    while (ptr != NULL) {
        if ((strcmp(ptr->brano.genere, _tipo) == 0)) {
            inserimento_brano(&_new_list, ptr->brano);
            ptr = ptr->next;
        } else {
            ptr = ptr->next;
        }
    }

    return _new_list;
}

int elimina_brano(ptr_list *new_list, int _progressivo) {
    ptr_brani to_delete, s;

    to_delete = (*new_list)->head;
    if (_progressivo == 1) {
        to_delete = (*new_list)->head;
        (*new_list)->head = (*new_list)->head->next;
        (*new_list)->num_elementi--;

        free(to_delete);
        return OK;
    } else {
        while (to_delete != NULL) {
            if (to_delete->next->progressivo == _progressivo) {
                s = to_delete->next;
                to_delete->next = to_delete->next->next;
                (*new_list)->num_elementi--;
                free(s);
                return OK;
            } else {
                to_delete = to_delete->next;
            }

        }

    }
    return FALSE;
}

int svuota_lista(ptr_list *_lista) {
    ptr_brani to_delete, s;
    int i;
    i = 0;
    to_delete = (*_lista)->head;

    while (to_delete == NULL) {
        s = to_delete->next;
        free(to_delete);
        to_delete = s;
        i++;
    }
    if (i == (*_lista)->num_elementi) {
        return TRUE;
    }else{
        return FALSISSIMO;
    }
}

void show(ptr_list new_list) {
    ptr_brani ptr;
    ptr = new_list->head;
    if (is_empty(new_list)) {
        printf("Playlist vuota!\n");
    } else {

        while (ptr != NULL) {
            printf("Titolo : %s\n", ptr->brano.titolo);
            printf("Genere : %s\n", ptr->brano.genere);
            printf("Artista: %s\n", ptr->brano.artista);
            printf("Durata : %0.2f minuti\n\n", ptr->brano.durata);
            ptr = ptr->next;
        }
    }
}



