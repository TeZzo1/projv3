#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define VELIKOST_RADKU 16

int delka(char *slovo);
int strcmp(char *co, char *cim);
int my_atoi(char *slovo);
void hexa_vypis();
void normalni_vypis(int start, int pocet);
void hex2text_vypis();
void chyba();
void delka_retezce(int delka);

int main(int argc, char *argv[])
{
    int start = 0, pocet = 0, delka = 0;

    if(argc > 5)
        chyba();

    if(argc == 5){
        if(strcmp(argv[1], "-s") || strcmp(argv[3], "-n")){
            pocet = my_atoi(argv[4]);
            start = my_atoi(argv[2]);
            if(pocet > 0 && start >= 0)
                normalni_vypis(start, pocet);
            else
                chyba();
        }
        else if(strcmp(argv[1], "-n") || strcmp(argv[3], "-s")){
            pocet = my_atoi(argv[2]);
            start = my_atoi(argv[4]);
            if(pocet > 0 && start >= 0)
                normalni_vypis(start, pocet);
            else
                chyba();
        }
        else
            chyba();
    }

    if(argc == 3){
        if(strcmp(argv[1], "-s")){
            start = my_atoi(argv[2]);
            if(start >= 0)
                normalni_vypis(start, pocet);
            else
                chyba();
        }
        else if(strcmp(argv[1], "-n")){
            pocet = my_atoi(argv[2]);
            if(pocet > 0)
                normalni_vypis(start, pocet);
            else
                chyba();
        }
        else if (strcmp(argv[1], "-S")) {
            delka = my_atoi(argv[2]);
            delka_retezce(delka);
        }
        else
            chyba();
    }

    if(argc == 2){
        if(strcmp(argv[1], "-x"))
            hexa_vypis();
        else if(strcmp(argv[1], "-r"))
            hex2text_vypis();
        else
            chyba();
    }

    if(argc == 1)
        normalni_vypis(start, pocet);

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


void normalni_vypis(int start, int pocet){
    char vstup[VELIKOST_RADKU + 1] = "";
    int pocet_nacteni = 0, soupatko = 1, adress_counter = 0x0, pom, i = 0;

    if(start > 0) {
        while ((vstup[0] = getchar()) != EOF && (i < start-1))
            i++;
        if (vstup[0] == EOF)
            return;
    }


    if(start > 0)
        adress_counter = i + 1;
    pom = i;

    while(soupatko == 1){
        for(i = 0; i < VELIKOST_RADKU; i++) {
            if ((vstup[i] = getchar()) != EOF && soupatko == 1) {
                if(pocet != 0 && (pocet_nacteni < pocet))
                    pocet_nacteni++;
                else if(pocet == 0)
                    pocet_nacteni++;
                else{
                    soupatko = 0;
                    break;
                }

            }
        }

        printf("%.8x  ", adress_counter);
        if(pocet_nacteni % 16 == 0)
            adress_counter = pocet_nacteni + pom;
        //vypsání prvních 8 bajtů
        //pom zjišťuje konec textu
        for(i = 0; i < 8; i++){
            if(pocet_nacteni % 16 == 0){
                printf("%.2x ", vstup[i]);
            }
            else
            if(i < pocet_nacteni % 16)
                printf("%.2x ", vstup[i]);
            else
                printf("   ");


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
        if(!isxdigit(numeric_char)){
            printf("Tenhle vstup se mi nelibi.\nRadeji se ukoncim.\n");
            return;
        }
        printf("%c", numeric_char);
    }
    printf("\n");
}


void chyba(){
    printf("Parametr nebyl zadan spravne.\nProgram bude ukoncen.\n");
}

void delka_retezce(int delka){
    char text[delka + 1];
    int i = 0, soupatko = 1;

    while(soupatko) {
        while (i < delka) {
            text[i] = getchar();
            if (text[i] == EOF) {
                soupatko = 0;
                i = 0;
                break;
            }
            if (!isprint(text[i])) {
                i = 0;
                continue;
            }

            i++;
        }
        text[i] =  '\0';
        printf("%s", text);
        text[1] = '\0';

        while((text[0] = getchar()) != EOF){
            if (!isprint(text[0]))
                break;
            else
                printf("%c", text[0]);
        }
        if(text[delka] == EOF || text[0] == EOF)
            soupatko = 0;
    }


    /*
    char text[delka+1];
    int i = 0, soupatko = 1;
    for(i = 0; i < delka; i++){
        text[i] = getchar();
        if(text[i] == EOF || !isprint(text[i])){
            printf(" nic ");
            continue;
        }
    }
    while(((text[i] = getchar()) != EOF) && (i < delka)){
        if(!isprint(text[i]) || text[i] == '\n'){
        //if(text[i] == '\n' || text[i] == '\0'){
            i = 0;
            continue;
        }
        i++;
    }

    text[i+1] = '\0';
    printf("%s", text);
    text[1] = '\0';
    while(soupatko){
        if((text[0] = getchar()) == EOF) {
            soupatko = 0;
            break;
        }
        printf("%c", text[0]);
    }
*/
}