#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

// Creation d'une structure memoire
typedef struct SaveNumber {
    int Value;
} SaveNumber;

int AskInt(const char* text, int Value, int Bmin, int Bmax) {
    int iError = 0;
    //Tant que la valeur rentre n'est pas un entier ou qu'il n'est pas compris dans les borns
    while (iError == 0) {
        printf("%s", text);

        // Verifier que l'entre est un int
        iError = scanf_s("%d", &Value);
        if (iError == 1) {
            //Si il est dans les bornes
            if (Value <= Bmax && Value >= Bmin) {
                printf("\n");
                return Value;
            }
            //Si il n'est pas dans les bornes
            else {
                printf("ERREUR Hors bornes \nEntrer entre %d et %d : \n", Bmin, Bmax);
                iError = 0;
            }
        }
        // reset buffer du scanf_s
        char c = 'a';
        while (c != '\n') {
            c = getchar();
        }
    }
}
// demande une chaine de caractere appartenant a une liste
int AskChar(const char* message, char* tableau) {
    int iError = 0;
    char replay = 'n';
    while (iError == 0) {
        // reset buffer du scanf_s
        char c = 'a';
        while (c != '\n') {
            c = getchar();
        }
        c = getchar();
        printf("%s", message);
        // Verifier que l'entre est un char
        iError = scanf_s("%c", &replay, 1);
        replay = toupper(replay);
        for (int i = 0; i < 2; i++) {
            if (replay == tableau[0]) {
                printf("Partie relance !\n");
                return 1;
            }
            else if (replay == tableau[1]) {
                printf("Jeu Arrete !\n");
                return 0;
            }
        }
        printf("ERREUR Entrer invalide, Appuyer sur Entrer pour continuer\n");
        iError = 0;
    }
}
// Fonction principale
int main()
{
    int play = 1;
    int partieGagne = 0;
    SaveNumber sn[100];
    char list[2] = { 'Y','N' };
    while (play == 1) {
        int AskNb = 0;
        int Try = 5;
        int Tryuse = 0;
        int Bmin = 0;
        int Bmax = 1000000;
        Bmin = AskInt("Choisi la borne min : \n", Bmin, Bmin, Bmax);
        Bmax = AskInt("Choisi la borne max : \n", Bmax, Bmin, Bmax);
        srand(time(NULL));
        int Nb = rand() % (Bmax - Bmin + 1) + Bmin;
        printf("Le nombre random %d\n", Nb);
        while (AskNb != Nb && Tryuse < Try)
        {
            AskNb = AskInt("Choisi un nombre : ", AskNb, Bmin, Bmax);
            if (Nb < AskNb) {
                printf("Moins\n");
            }
            else if (Nb > AskNb) {
                printf("Plus\n");
            }
            else if (Nb == AskNb) {
                printf("Vous Avez GAGNE\n");
                partieGagne++;
                sn[partieGagne].Value = Nb;
                break;
            }
            Tryuse++;
            printf("Il vous reste %d \n", Try - Tryuse);
        }
        if (Try == Tryuse) {
            printf("Vous Avez PERDU\n");
        }
        printf("Appuyez sur entrer pour continuer\n");
        play = AskChar("Voulez-vous rejouer ? (y,n)\n", list);
    }
    printf("Voici les anciens resultat trouve :\n");
    for (int i = 1; i <= partieGagne; i++) {
        printf("- %d\n", sn[i].Value);
    }

}