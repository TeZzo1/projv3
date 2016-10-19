#include <stdio.h>
#include <ctype.h>

#define VELIKOST_RADKU 16


int delka(char *slovo);
int strcmp(char *co, char *cim);
int atoi(char *slovo);
void hexa_vypis();
void normalni_vypis();
char *dec2hex(int dec);
int pow(int cislo, int mocnina);

int main(int argc, char *argv[])
{
    //int start = 0, pocet = -1;

    printf("\n");

    if(argc > 1)
        for(int i = 0; i < argc; i++){
            if(strcmp(argv[i], "-s")){
                //start = atoi(argv[i+1]);
                printf("Not supported yet");
            }
            if(strcmp(argv[i], "-n")){
                //pocet = atoi(argv[i+1]);
                printf("Not supported yet");
            }
            if(strcmp(argv[i], "-x")){
                hexa_vypis();
            }
            if(strcmp(argv[i], "-S")){
                printf("Not supported yet");

            }
            if(strcmp(argv[i], "-r")){
                printf("Not supported yet");
                //dec();
            }
        }
    else if(argc == 1)
        normalni_vypis();
    else
        printf("Spatne zadane argumenty!\nProgram bude ukoncen.");





    return 0;
}


int delka(char *slovo){
    int i = 0;
    while(slovo[i] != '\0'){
        i++;
        printf("%c", slovo[i]);
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
    int pocet_nacteni = 0, soupatko = 1;;
    while(soupatko == 1){
        for(int i = 0; i < VELIKOST_RADKU; i++){
            if((vstup[i] = getchar()) != EOF){
                pocet_nacteni++;
            }
        }



        printf("00000000  ");

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
}

int pow(int cislo, int mocnina){
    int vysledek = 1;
    for(int i = 0; i < mocnina; i++)
        vysledek *= cislo;
    return vysledek;
}

char *dec2hex(int dec){
    int zbytek, i = 0;
    char *vysledek;
    while(dec / 16 == 0){
        zbytek = dec % 16;
        dec /= 16;
        vysledek += zbytek * pow(16, i);
    }

}