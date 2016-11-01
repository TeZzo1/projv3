/****************************************************/
/* * *        Projekt 1 - Práce s textem        * * */
/* * *                                          * * */
/* * *             Tomáš Willaschek             * * */
/* * *                 xwilla00                 * * */
/* * *             1BIB - 2016/2017             * * */
/****************************************************/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define VELIKOST_RADKU 16

/* POMOCNÉ FUNKCE */
int delka(char *s);
int strcmp(char *co, char *cim);
int my_atoi(char *s);

/* FUNKCE PARAMETRŮ */
void hexa_vypis();
void normalni_vypis(int start, int pocet);
void hex2text_vypis();
void napoveda();
void delka_retezce(int delka);
void chybna_hodnota();

int main(int argc, char **argv) {
    int start = 0, pocet = 0, delka = 0;

    if (argc > 5 || argc == 4)
        napoveda();

    else if (argc == 5) {
        if (strcmp(argv[1], "-s") || strcmp(argv[3], "-n")) {
            pocet = my_atoi(argv[4]);
            start = my_atoi(argv[2]);
            if (pocet && start >= 0)
                normalni_vypis(start, pocet);
            else
                napoveda();
        } else if (strcmp(argv[1], "-n") || strcmp(argv[3], "-s")) {
            pocet = my_atoi(argv[2]);
            start = my_atoi(argv[4]);
            if (pocet > 0 && start >= 0)
                normalni_vypis(start, pocet);
            else
                chybna_hodnota();
        } else
            napoveda();
    }

    else if (argc == 3) {
        if (strcmp(argv[1], "-s")) {
            start = my_atoi(argv[2]);
            if (start >= 0)
                normalni_vypis(start, pocet);
            else
                chybna_hodnota();
        } else if (strcmp(argv[1], "-n")) {
            pocet = my_atoi(argv[2]);
            if (pocet > 0)
                normalni_vypis(start, pocet);
            else
                chybna_hodnota();
        } else if (strcmp(argv[1], "-S")) {
            delka = my_atoi(argv[2]);
            if (delka > 0 && delka < 200)
                delka_retezce(delka);
            else
                chybna_hodnota();   /********************************************nebo nápověda???*******************/
        } else
            napoveda();
    }

    else if (argc == 2) {
        if (strcmp(argv[1], "-x"))
            hexa_vypis();
        else if (strcmp(argv[1], "-r"))
            hex2text_vypis();
        else
            napoveda();
    }

    else if (argc == 1)
        normalni_vypis(start, pocet);

    return 0;
}


/* POMOCNÉ FUNKCE */

/**
 * Zjistí délku řetězce
 * @param s - vstupní řetězec
 * @return - číselná délka řetězce
 */
int delka(char *s) {
    int i;
    for (i = 0; s[i] != '\0'; i++)
        {}
    return i;
}

/**
 * Porovná dané řetězce
 * @param s1 - 1. řetězec pro porovnání
 * @param s2 - 2. řetězec pro porovnání
 * @return - návratová hodnota true/false
 */
int strcmp(char *s1, char *s2) {
    if (delka(s1) != delka(s2))
        return 0;
    for (int i = 0; i < delka(s1); i++)
        if (s1[i] != s2[i])
            return 0;
    return 1;
}

/**
 * Pokud je vstup v rozsahu 0-9, převede char na int
 * @param s
 * @return - převedená hodnota nebo chyba
 */
int my_atoi(char *s) {
    int vysledek = 0;
    for (int i = 0; i < delka(s); i++) {
        if (s[i] <= '9' && s[i] >= '0') {
            vysledek *= 10;
            vysledek += s[i] - '0';
        } else
            return -1;
    }
    return vysledek;
}



/* FUNKCE PAEAMETRŮ */

/* proměnná "soupatko" slouží jako booleanovská proměnná stavů 'true' a 'falce' */
/**
 * Načte znak na vstupu a vypíše ho hexadecimálně
 */
void hexa_vypis() {
    int pom;
    while ((pom = getchar()) != EOF)
        printf("%02x", pom);
    printf("\n");
}

/**
 * funkce pro program spuštěný bez parametru, s parametrem "-s", "-n", nebo oběma
 * @param start - je nenulový, pokud je zadaný parametr -s při spuštění
 * @param pocet - je nenulový, pokud je zadaný parametr -n při spuštění
 */
void normalni_vypis(int start, int pocet) {
    int vstup[VELIKOST_RADKU] = {'\0'};
    int pocet_nacteni = 0, soupatko = 1, adress_counter = 0x0, i = 0;

    //při zadání parametru -s se vyprázdní getchar M-krát
    if (start != 0) {
        while ((vstup[0] = getchar()) != EOF && i < start - 1)
            i++;
        if (vstup[0] == EOF)
            return;

        //zaznamenání adresy - kolik znaků bylo smazáno
        adress_counter = i + 1;
    }

    /* cyklus while se opakuje tolikrát, dokud nenastane EOF nebo se nenačte právě N znaků ("-n") */
    while (soupatko) {
        /* program byl spuštěn bez parametru "-n" */
        if (!pocet)
            for (i = 0; i < VELIKOST_RADKU && soupatko; i++) {
                vstup[i] = getchar();
                /* bez téhle podmínky se vypisuje při zadání 15 znaků + binární nuly řánek navíc */
                if (vstup[0] == EOF)
                    return;
                else if (vstup[i] == EOF)
                    soupatko = 0;
                else
                    pocet_nacteni++;
            }
        /* program byl spuštěń právě s parametrem "-n" */
        else
            for (i = 0; i < VELIKOST_RADKU && soupatko; i++) {
                if (pocet_nacteni < pocet) {
                    vstup[i] = getchar();
                    if (vstup[0] == EOF)
                        return;
                    else if (vstup[i] == EOF)
                        soupatko = 0;
                    else
                        pocet_nacteni++;
                } else
                    break;
            }

        /* vypsání adresy */
        printf("%08x  ", adress_counter);
        adress_counter += i;

        //vypsání prvních 8 bajtů v hexa
        for (i = 0; i < 8; i++) {
            /* pokud došly znaky na vstupu, doplní se mezery */
            if (pocet_nacteni % VELIKOST_RADKU == 0 || i < pocet_nacteni % VELIKOST_RADKU)
                printf("%02x ", vstup[i]);
            else {
                printf("   ");
                soupatko = 0;
            }
        }
        printf(" ");

        //vypsání druhých 8 bajtů
        for (i = 8; i < VELIKOST_RADKU; i++) {
            if (pocet_nacteni % VELIKOST_RADKU == 0 || i < pocet_nacteni % VELIKOST_RADKU)
                printf("%02x ", vstup[i]);
            else {
                printf("   ");
                soupatko = 0;
            }
        }

        printf(" |");
        // výpis textu po 16 bajtech
        if (pocet_nacteni % VELIKOST_RADKU == 0)
            for (i = 0; i < VELIKOST_RADKU; i++)
                /* pokud je znak tisknutelný, tak se vypíše, jinak se vypíše tečka */
                printf("%c", isprint(vstup[i]) ? vstup[i] : '.');
        else
            for (i = 0; i < VELIKOST_RADKU; i++) {
                if (i < pocet_nacteni % VELIKOST_RADKU)
                    printf("%c", isprint(vstup[i]) ? vstup[i] : '.');
                else
                    printf(" ");
            }
        printf("|");
        /* pokud bylo načteno méně než 16 znaků ze vstupu, znamená to, že nastal EOF */
        if (pocet_nacteni % VELIKOST_RADKU != 0)
            soupatko = 0;
        printf("\n");
        /* kontrola parametru "-n" */
        if (pocet_nacteni == pocet)
            return;
    }
}

/**
 * Funkce reverse
 * Převádí hexadecimální vstup na text
 */
void hex2text_vypis(){
    int vstup[2], soupatko = 1, i;
    char znak[3] = {'\0'};

    while(soupatko) {
        for (i = 0; i < 2 && soupatko; i++) {
            if ((vstup[i] = getchar()) != EOF) {
                /* pokud je na vstupu mezera (tabulátor a jiné bílé znaky), načte se místo ní další znak */
                while (isblank(vstup[i]))
                    if((vstup[i] = getchar()) == EOF)
                        soupatko = 0;
                znak[i] = vstup[i];
            } else
                soupatko = 0;
        }

        /* kontrola hexadecimálních znaků */
        for (i = 0; i < 2 && soupatko; i++)
            /* pokud zde není isprint() tak to vyhodnotí EOF jako chybu */
            if (!isxdigit(znak[i]) && isprint(znak[i])) {
                printf("\nZnak \"%c\" neni v rozsahu 0-9a-fA-F!\n", znak[i]);
                soupatko = 0;
            }

        if (soupatko) {
            /* převedení znaku na číselnou hodnotu a vypsání */
            int pom = (int) strtol(znak, NULL, 16);
            printf("%c", pom);

        }
    }
}

/**
 * Parametr -S
 * Do proměnné o velikosti N (zadaná hodnota) se načítá ze vstupu a hledají se oddělovače, pokud jsou nalezeny, funkce
 * se opakuje
 * @param delka - minimální délka řetězce, aby byl vypsán
 */
void delka_retezce(int delka) {
    int text[delka], soupatko = 1, i = 0;

    while (soupatko) {
        /* hledání oddělovače nebo EOF */
        while (i < delka && soupatko) {
            text[i] = getchar();
            if (text[i] == EOF) {
                //return;
                soupatko = 0;
            }
            if (!isprint(text[i]) && soupatko) {
                i = 0;
                continue;
            }
            i++;
        }

        /* vypsání proměnné */
        for (i = 0; i < delka && soupatko; i++) {
            printf("%c", text[i]);
            text[i] = '\0';
        }

        /* vypisování dalších znaků dokud není nalezen oddělovač nebo EOF */
        while ((text[0] = getchar()) != EOF && soupatko) {
            if (!isprint(text[0]))
                break;
            else
                printf("%c", text[0]);
        }

        /* byl nalezen řetězec o velikosti >= N, tak se zalomí řádek */
        if (soupatko) {
            printf("\n");
            if (text[delka] == EOF || text[0] == EOF)
                soupatko = 0;
            i = 0;
        }
    }
}

/* CHYBOVÉ VÝPISY */
/**
 * Vypíše nápovědu
 */
void napoveda() {
    printf("\nPROJ1 \t ©xwilla00 2016\n\n");
    printf("Proj1 je nastroj pro praci s textem, ktery formatuje binarni data do textove podoby\n"
                   "nebo text do binarny podoby.\n");
    printf("Spusteni bez parametru:\n");
    printf("\tProgram prevede vstupni retezec na hexadecimalni.\n");
    printf("Spusteni s parametry:\n");
    printf("\t-s M\t(skip) definuje, na ktere adrese ma vstup zacinat\n");
    printf("\t-n N\t(number-of-chars) definuje maximalni delku vstupnih bajtu ke zpracovani\n");
    printf("\t-x\tvstupni data budou prevedena do hexadedimalni podoby\n");
    printf("\t-S N\tN = (0 - 200) program vypise pouze retezce delsi nez zadana velikost parametru\n");
    printf("\t-r\t(reverse) prevede hexadecimalni vstup na text\n");
}

void chybna_hodnota() {
    printf("Hodnota parametru nebyla zadana spravne.\n");
}