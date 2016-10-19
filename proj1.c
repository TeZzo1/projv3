#include <stdio.h>
#include <ctype.h>

#define VELIKOST_RADKU 16

int delka(char *slovo);
int strcmp(char *co, char *cim);
int atoi(char *slovo);
void hexa_vypis();
void normalni_vypis();
void hex2text_vypis();

int main(int argc, char *argv[])
{
    //int start = 0, pocet = -1;
    if(argc == 3)
        for(int i = 0; i < argc; i++){
            if(strcmp(argv[i], "-s")){
                //start = atoi(argv[i+1]);
                printf("Not supported yet");
            }
            if(strcmp(argv[i], "-n")){
                //pocet = atoi(argv[i+1]);
                printf("Not supported yet");
            }
            if(strcmp(argv[i], "-S")){
                printf("Not supported yet");
            }
        }
    if(argc == 2)
        for(int i = 1; i < argc; i++){
            if(strcmp(argv[i], "-x")){
                hexa_vypis();
            }
            if(strcmp(argv[i], "-r")){
                printf("XXX");
                hex2text_vypis();
                //printf("Not supported yet");
                //dec();
            }
        }
    if(argc == 1)
        normalni_vypis();
    if(argc == 0 || argc == 4)
        printf("Spatne zadane argumenty!\nProgram bude ukoncen.\n");

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

int atoi(char *slovo){
    int vysledek = 0;
    for(int i = 0; i < delka(slovo); i++){
        vysledek *= 10;
        vysledek += slovo[i] - '0';
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
void dec(){
    char pom[3];
    for(int i = 0; i < 2; i++)

    return;
}
*/
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

void normalni_vypis(){
    char vstup[VELIKOST_RADKU + 1] = "";
    int pocet_nacteni = 0, soupatko = 1, adress_counter = 0x0;
    while(soupatko == 1){
        for(int i = 0; i < VELIKOST_RADKU; i++) {
            if ((vstup[i] = getchar()) != EOF) {
                pocet_nacteni++;
            }
        }

        printf("%.8x  ", adress_counter);
        if(pocet_nacteni % 16 == 0)
            adress_counter = pocet_nacteni;
        //vypsání prvních 8 bajtů
        //pom zjišťuje konec textu
        //int pom = 0;
        for(int i = 0; i < 8; i++){
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
        for(int i = 8; i < 16; i++){
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
            for(int i = 0; i < VELIKOST_RADKU; i++){
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
    adress_counter += pocet_nacteni % 16;
    printf("%.8x  \n", adress_counter);
}

void hex2text_vypis(){
    char znak[3];
    for(int i = 0; i < 2; i++)
        znak[i] = getchar();
    printf("%s", znak);
}