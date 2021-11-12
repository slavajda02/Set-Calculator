/**
 * @file setcal.c
 * @author Miloslav Kužela (xkuzel09), "přidejte jména"
 * @brief Program implementuje základní matematické operace nad množinami a binárními relacemi.
 *        Pracuje s textovými daty reprezentující množiny a relace a zadání operací. 
 * @version 0.1
 * @date 2021-11-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

enum returnvalue {true, false};

#include <stdio.h>

int main(int argc, char** argv)
{
    int pocetsouboru = 0;
    if(argc > 1)
    {
        pocetsouboru = argc-1;
    }
    else
    {
        fprintf(stderr,"Zadejte název aspoň jednoho souboru\n");
        return false;
    }
    return true;
}