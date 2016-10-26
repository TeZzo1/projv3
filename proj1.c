#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define VELIKOST_RADKU 16


// načíst do intu, zjistit eof a pak uložit do charu
//-s -n 03






int delka(char *slovo);
int strcmp(char *co, char *cim);
int my_atoi(char *slovo);
void hexa_vypis();
void normalni_vypis(int start, int pocet);
void hex2text_vypis();
void napoveda();
void delka_retezce(int delka);
void chybna_hodnota();

int main(int argc, char **argv) {
    int start = 0, pocet = 0, delka = 0;

    if (argc > 5 || argc == 4) {
        napoveda();
        return 0;
    }

    if(argc == 5){
        if(strcmp(argv[1], "-s") || strcmp(argv[3], "-n")){
            pocet = my_atoi(argv[4]);
            start = my_atoi(argv[2]);
            if(pocet > 0 && start >= 0)
                normalni_vypis(start, pocet);
            else {
                napoveda();
                return 0;
            }
        }
        else if(strcmp(argv[1], "-n") || strcmp(argv[3], "-s")){
            pocet = my_atoi(argv[2]);
            start = my_atoi(argv[4]);
            if(pocet > 0 && start >= 0)
                normalni_vypis(start, pocet);
            else
                chybna_hodnota();
        }
        else {
            napoveda();
            return 0;
        }
    }

    if(argc == 3){
        if(strcmp(argv[1], "-s")){
            start = my_atoi(argv[2]);
            if(start >= 0)
                normalni_vypis(start, pocet);
            else
                chybna_hodnota();
        }
        else if(strcmp(argv[1], "-n")){
            pocet = my_atoi(argv[2]);
            if(pocet > 0)
                normalni_vypis(start, pocet);
            else
                chybna_hodnota();
        }
        else if (strcmp(argv[1], "-S")) {
            delka = my_atoi(argv[2]);
            //if(delka < 200 && delka > 0)
                delka_retezce(delka);
            //else
            //   chybna_hodnota();
        }
        else {
            napoveda();
            return 0;
        }
    }

    if(argc == 2){
        if(strcmp(argv[1], "-x"))
            hexa_vypis();
        else if(strcmp(argv[1], "-r"))
            hex2text_vypis();
        else {
            napoveda();
            return 0;
        }
    }

    if(argc == 1)
        normalni_vypis(start, pocet);

    return 0;
}

/* MOJE FUNKCE */

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
    /*int j;
    while(slovo[0] != '0') {
        for (j = 0; j < delka(slovo); j++) {
            slovo[j] = slovo[j + 1];
            slovo[j+1] = '\0';
        }

    }*/
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


/* FUNKCE PAEAMETRŮ */

void hexa_vypis(){
    int pom;
    while((pom = getchar()) != EOF)
        printf("%02x", pom);
    printf("\n");
}


void normalni_vypis(int start, int pocet){
    int vstup[VELIKOST_RADKU + 1] = {'\0'};
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

        printf("%08x  ", adress_counter );
        if(pocet_nacteni % 16 == 0)
            adress_counter = pocet_nacteni + pom + 1;
        //vypsání prvních 8 bajtů
        //pom zjišťuje konec textu
        for(i = 0; i < 8; i++){
            if(pocet_nacteni % 16 == 0){
                printf("%02x ", vstup[i]);
            }
            else
            if(i < pocet_nacteni % 16)
                printf("%02x ", vstup[i]);
            else
                printf("   ");


        }

        printf(" ");
        //vypsání druhých 8 bajtů
        for(i = 8; i < 16; i++){
            if(pocet_nacteni % 16 == 0){
                printf("%02x ", vstup[i]);
            }
            else
            if(i < pocet_nacteni % 16)
                printf("%02x ", vstup[i]);
            else
                printf("   ");

        }

        // výpis textu po 16 bajtech
        if(pocet_nacteni % 16 == 0){
            printf(" |");
            for(int i = 0; i < VELIKOST_RADKU; i++)
                printf("%c", isprint(vstup[i]) ? vstup[i] : '.');
            printf("|");
        }
        else{
            printf(" |");
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
    char znak[2] = {'\0'};
    int soupatko = 1;
    while(soupatko == 1) {
        for (int i = 0; i < 2; i++) {
            znak[i] = (char)getchar();
            if(znak[i] == ' ')
                znak[i] = (char)getchar();
            if (znak[i] == EOF)
                return;
        }
        int numeric_char = (int) strtol(znak, NULL, 16);
        if((isblank(numeric_char) && numeric_char != ' ') && soupatko == 1)
            continue;
        if(!isxdigit(znak[0])){
            printf("Tenhle vstup se mi nelibi.\nRadeji se ukoncim.\n");
            return;
        }
        printf("%c", numeric_char);
    }
    //printf("\n");
}


void delka_retezce(int delka){
    char text[delka + 1];
    int i = 0, soupatko = 1;

    while(soupatko) {
        while (i < delka) {
            text[i] = (char)getchar();
            if (text[i] == EOF) {
                soupatko = 0;
                i = 0;
                break;
            }
            if (!isprint(text[i]) || text[i] == '\0' || text[i] == '\n') {
                i = 0;
                continue;
            }

            i++;
        }
        text[i] =  '\0';
        printf("%s", text);
        text[1] = '\0';

        while((text[0] = (char)getchar()) != EOF){
            if (!isprint(text[0]) || (text[0] == '\0') || text[0] == '\n')
                break;
            else
                printf("%c", text[0]);
        }
        if(soupatko)
            printf("\n");
        if(text[delka] == EOF || text[0] == EOF)
            soupatko = 0;
        i = 0;

    }
}

/* CHYBOVÉ VÝPISY */

void napoveda() {
    printf("proj1 \t ©xwilla00 2016\n");
    printf("Proj1 je nastroj pro praci s textem, ktery formatuje binarni data do textove podoby\n"
                   "nebo text do binarny podoby.\n");
    printf("Spusteni bez parametru:\n");
    printf("\tProgram prevede vstupni retezec na hexadecimalni.\n");
    printf("Spusteni s parametry:\n");
    printf("\t-s\t(skip) definuje, na ktere adrese ma vstup zacinat\n");
    printf("\t-n\t(number-of-chars) definuje maximalni delku vstupnih bajtu ke zpracovani\n");
    printf("\t-x\tvstupni data budou prevedena do hexadedimalni podoby\n");
    printf("\t-S\tprogram vypise pouze retezce delsi nez zadana velikost parametru\n");
    printf("\t-r\t(reverse) prevede hexadecimalni vstup na text\n");
}

void chybna_hodnota(){
    printf("Hodnota parametru nebyla zadana spravne.\n");
}