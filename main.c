#include <stdio.h>
#include "progetto.h"

int main() {
    t_brano brano;
    int scelta, error_code, pos, progressivo;
    ptr_list start, playlist;
    char tipo[50];
    char artist[50];
    FILE *file_brani;
    FILE *file_contatore;
    int contatore_brani = 0;

    start = create();

    playlist = create();
    //file contatore
    file_contatore = fopen("contatore.txt", "r");
    fscanf(file_contatore, "%d\n", &contatore_brani);
    file_contatore = fopen("contatore.txt", "w");
    //file brani
    file_brani = fopen("playlist.txt", "r");
    for (int i = 0; i < contatore_brani; ++i) {
        fscanf(file_brani, "Titolo:%s\n Genere:%s\n Artista:%s\n Durata:%f\n\n", brano.titolo, brano.genere,
               brano.artista, &brano.durata);
        inserimento_brano(&start, brano);
    }
    fclose(file_brani);
    file_brani = fopen("playlist.txt", "w");

    do {
        printf("============== PLAYLIST UNIMOL =========\n");
        printf("1. Inserisci un brano                   \n");
        printf("2. ricerca un brano                     \n");
        printf("3. elimina un brano                     \n");
        printf("4. mostra tutti i brani                 \n");
        printf("0. Chiudi il Programma                  \n");
        scanf("%d", &scelta);

        switch (scelta) {

            case INSERIMENTO_BRANO:
                if (is_full(start) == TRUE) {
                    printf("hai superato il numero massimo di brani nella playlist!!\n\n");
                    printf("vuoi eliminare qualche brano per fare spazio? \n 1-si 2-no");
                    scanf("%d", &scelta);

                    if (scelta == 1) {
                        printf("dammi il numero da eliminare\n");
                        scanf("%d", &progressivo);

                        error_code = elimina_brano(&start, progressivo);
                        if (error_code != 1) {
                            printf("brano eliminato con successo\n");
                        } else {
                            printf("brano non presente\n");
                        }
                    } else {
                        show(start);
                    }
                } else {
                    brano = leggi_brano();
                    error_code = inserimento_brano(&start, brano);
                    if (error_code == 0) {
                        printf("Brano inserito!\n");
                        contatore_brani++;

                    } else {
                        printf("Errore nell' inserimento del brano\n");
                    }
                }
                break;
            case RICERCA_BRANO:

                printf("inserisci il tipo da cercare ");
                scanf("%s", tipo);

                playlist = cerca_brano(start, tipo);
                if(playlist->head == NULL){
                    printf("playlist vuota!\n");
                }else{
                    show(playlist);
                    error_code = svuota_lista(&playlist);

                    if (error_code != FALSISSIMO) {
                        printf("Nessun brano trovato\n");
                    }
                }

                break;
            case ELIMINA_BRANO:
                printf("dammi il numero da eliminare\n");
                scanf("%d", &progressivo);

                error_code = elimina_brano(&start, progressivo);
                if (error_code != 1) {
                    printf("brano eliminato con successo\n");
                } else {
                    printf("brano non presente\n");
                }
                break;
            case MOSTRA_TUTTI:
                show(start);
                break;
            case USCITA:
                printf("arrivederci e buon ascolto");
                break;
            default:
                printf("Comando non valido\n");
                break;
        }
    } while (scelta != USCITA);

    show_file(start, file_brani);
    fprintf(file_contatore, "%d\n", contatore_brani);
    fclose(file_contatore);
    fclose(file_brani);
}

