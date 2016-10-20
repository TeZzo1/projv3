#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define VELIKOST_RADKU 16

int delka(char *slovo);
int strcmp(char *co, char *cim);
int my_atoi(char *slovo);
void hexa_vypis();
void normalni_vypis(int start);
void hex2text_vypis();

int main(int argc, char *argv[])
{
    int start = 0; // pocet = -1;
    if(argc == 5)
        printf("Not supported yet");

    if(argc == 3){
        if(strcmp(argv[1], "-s")){
            start = my_atoi(argv[2]);
            if(start >= 0)
                normalni_vypis(start);
            else
                printf("Parametr nebyl zadan spravne.\nProgram bude ukoncen.\n");
            //printf("Not supported yet");
        }
         else if(strcmp(argv[1], "-n")){
            //pocet = my_atoi(argv[i+1]);
            printf("Not supported yet");
        }
        else if (strcmp(argv[1], "-S"))
                printf("Not supported yet");
            else
                printf("Parametr nebyl zadan spravne.\nProgram bude ukoncen.\n");

    }

    if(argc == 2){
        if(strcmp(argv[1], "-x"))
            hexa_vypis();
        if(strcmp(argv[1], "-r"))
            hex2text_vypis();
        else
            printf("Parametr nebyl zadan spravne.\nProgram bude ukoncen.\n");
    }

    if(argc == 1)
        normalni_vypis(start);

    if(argc == 0 || argc == 4)
        printf("Parametry nebyly zadany spravne.\nProgram bude ukoncen.\n");

    return 0;
}


int delka(char *slovo){
    int i = 0;
    while(slovo[i] != '\0'){
        i++;
    }
    return i;
}

int strcmp(char *co, char *cim){
    if(delka(co) != delka(cim))
        return 0;
    for(int i = 0; i < delka(co); i++)
        if(co[i] != cim[i])
            return 0;
    return 1;
}

int my_atoi(char *slovo){
    int vysledek = 0;
    for(int i = 0; i < delka(slovo); i++){
        if(slovo[i] <= '9' || slovo[i] >= '0'){
            vysledek *= 10;
            vysledek += slovo[i] - '0';
        }
        else
            return -1;
    }
    return vysledek;
}

void hexa_vypis(){
    char pom;
    while((pom = getchar()) != EOF)
        printf("%.2x", pom);
    printf("\n");
    return;
}

/*
void normalni_vypis(){
    char vstup[VELIKOST_RADKU + 1];
    while(1){
        for(int i = 0; i < VELIKOST_RADKU; i++){
            if((vstup[i] = getchar()) != EOF){
                printf("%c", vstup[i]);

            }
        }
        printf("\n");


        printf("%d\n", delka(vstup));
        if(delka(vstup) < 16)
            break;
        continue;
    }
}
*/

void normalni_vypis(int start){
    char vstup[VELIKOST_RADKU + 1] = "";
    int i = 0;
    if(start > 0) {
        while ((vstup[0] = getchar()) != EOF && i < start)
            i++;
        if (vstup[0] == EOF)
            return;
    }
    /*if(start > 0)
        for(int i = 0; i < start; i++)
            if((vstup[0] = getchar()) == EOF)
                return;*/
    int pocet_nacteni = 0, soupatko = 1, adress_counter = 0x0, pom;
    if(start > 0)
        adress_counter = i;
    pom = i;
    while(soupatko == 1){
        for(i = 0; i < VELIKOST_RADKU; i++) {
            if ((vstup[i] = getchar()) != EOF) {
                pocet_nacteni++;
            }
        }

        printf("%.8x  ", adress_counter);
        if(pocet_nacteni % 16 == 0)
            adress_counter = pocet_nacteni + pom;
        //vypsání prvních 8 bajtů
        //pom zjišťuje konec textu
        //int pom = 0;
        for(i = 0; i < 8; i++){
            if(pocet_nacteni % 16 == 0){
                printf("%.2x ", vstup[i]);
            }
            else
            if(i < pocet_nacteni % 16)
                printf("%.2x ", vstup[i]);
            else
                printf("   ");
            /*if(vstup[i] == '\0'){
                printf("%.2x ", vstup[i]);
                pom = 1;
                i++;
            }
            if(pom == 1)
                printf("   ");
            else
                printf("%.2x ", vstup[i]);
            */

        }

        printf(" ");

        //vypsání druhých 8 bajtů
        for(i = 8; i < 16; i++){
            if(pocet_nacteni % 16 == 0){
                printf("%.2x ", vstup[i]);
            }
            else
            if(i < pocet_nacteni % 16)
                printf("%.2x ", vstup[i]);
            else
                printf("   ");

            /*if(pom == 1){
                printf("   ");
            }
            else {
                if(vstup[i] == '\0'){
                    printf("%.2x ", vstup[i]);
                    pom = 1;
                }
                else
                    printf("%.2x ", vstup[i]);
            }*/
        }

        printf(" ");

        // výpis textu po 16 bajtech

        if(pocet_nacteni % 16 == 0){
            printf("|");
            for(int i = 0; i < VELIKOST_RADKU; i++)
                printf("%c", isprint(vstup[i]) ? vstup[i] : '.');
            printf("|");
        }
        else{
            printf("|");
            for(i = 0; i < VELIKOST_RADKU; i++){
                if(i < (pocet_nacteni % 16))
                    printf("%c", isprint(vstup[i]) ? vstup[i] : '.');
                else
                    printf(" ");
            }
            printf("|");
        }
        if(pocet_nacteni % 16 != 0)
            soupatko = 0;
        printf("\n");
    }
    //vypsání posledního řádku adres jako u programu hexdump
    /*adress_counter += pocet_nacteni % 16;
    printf("%.8x  \n", adress_counter);*/
}

void hex2text_vypis(){
    char znak[2];
    znak[1] = '\0';
    int soupatko = 1;
    while(soupatko == 1) {
        for (int i = 0; i < 2; i++) {
            znak[i] = getchar();
            if(znak[i] == ' ')
                znak[i] = getchar();
            if (znak[i] == EOF)
                soupatko = 0;
        }

        int numeric_char = (int) strtol(znak, NULL, 16);
        if(isblank(numeric_char) && soupatko == 1)
            continue;
/*
        if((numeric_char < '\x20' && soupatko == 1))
            continue;
*/
        printf("%c", numeric_char);
    }
    printf("\n");
}


