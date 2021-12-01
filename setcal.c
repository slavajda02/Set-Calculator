#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int count;
    char** value;
}UNIVERSE;

typedef struct{
    int count;
    char** value;
}SETS;

typedef struct{
    int count;
    char** value;
}RELATIONS;

typedef struct{
    int count;
    char** value;
}COMMANDS;

typedef struct
{
    UNIVERSE universe;
    int sets_count;
    SETS sets;
    RELATIONS relations;
    COMMANDS commands;
}STRUKTURA;

typedef struct {
    int rowArr_size;
    char** rowArr;
}PARSE_LINE_RESULT;


PARSE_LINE_RESULT parseLine(char* row) //rozdeleni radku na jednotlive prvky
{
    PARSE_LINE_RESULT x;
    int element_size = 0;
    char* element = (char*)malloc(0);
    x.rowArr_size = 0;                  //pocitadlo elementu (stringu) v radku
    x.rowArr = (char**)malloc(0);
    for(int i = 2; row[i] != '\0';i++){
        if(row[i] != ' '){
            element = (char*)realloc(element,sizeof(char)*element_size+1);
            element[element_size] = row[i];
        }else{
            x.rowArr = (char**)realloc(x.rowArr,sizeof(char*)*x.rowArr_size+1);
            x.rowArr[x.rowArr_size] = (char*)realloc(x.rowArr[x.rowArr_size],sizeof(char)*element_size);
            strcpy(x.rowArr[x.rowArr_size],element);
            element_size = 0;
            x.rowArr_size++;
        }
    }

    return x;
}

STRUKTURA processFile(char* fileName){ //precteni radku, rozdeleni podle typu radku 
    FILE *fr = fopen(fileName, "r");

    STRUKTURA s;

    s.universe.value = (char**)malloc(0);
    s.universe.count = 0;
    s.sets.value = (char**)malloc(0);
    s.sets.count = 0;
    s.relations.value = (char**)malloc(0);
    s.relations.count = 0;
    s.commands.value = (char**)malloc(0);
    s.commands.count = 0;

    do{
        char* row;
        int row_size = 0;
        char znak;
        row = (char*)malloc(row_size);
            do{
                znak = getc(fr);
                row_size++;
                row = (char*)realloc(row,sizeof(char)*row_size);
                row[row_size-1] = znak;
            }while(znak != '\n' && znak != EOF);
            row = (char*)realloc(row,sizeof(char)*row_size+1);
            row[row_size] = '\0';

        switch(row[0]){
            case 'U':{
                s.universe.value = (char**)realloc(s.universe.value,sizeof(char*)*s.universe.count+1);
                s.universe.value[s.universe.count] = (char*)malloc(sizeof(char)*strlen(row));
                strcpy(s.universe.value[s.universe.count],row);
                s.universe.count++;
                break;
            }
             case 'S':{ //rozdeleni prvku mnoziny na jednotlive retezce
                /*s.sets = (SETS*)realloc(s.sets,sizeof(SETS)*s.sets_count+1);              
                s.sets[s.sets_count].count = 0;
                s.sets[s.sets_count].value = (char**)malloc(0);
                PARSE_LINE_RESULT x = parseLine(row);
                for(int i = 0; i < x.rowArr_size; i++){
                    printf("\n %d,%s",x.rowArr_size,x.rowArr[i]);
                }
                s.sets[s.sets_count].count = x.rowArr_size;
                for(int i = 0; i < x.rowArr_size; i++){
                    s.sets[s.sets_count].value = (char**)realloc(s.sets[s.sets_count].value,sizeof(char*)*s.sets[s.sets_count].count+1);
                    s.sets[s.sets_count].value[s.sets[s.sets_count].count] = (char*)realloc(s.sets[s.sets_count].value[s.sets[s.sets_count].count],strlen(x.rowArr[i]));
                    strcpy(s.sets[s.sets_count].value[s.sets[s.sets_count].count],x.rowArr[i]);         t
                }
                s.sets_count++;                         (toto je nefunkcni prototyp, kdybyste vedeli jak to opravit,smele do toho ale  je v tom bordel :D)
                break;*/
                 s.sets.value = (char**)realloc(s.sets.value,sizeof(char*)*s.sets.count+1);
                s.sets.value[s.sets.count] = (char*)malloc(sizeof(char)*strlen(row));
                strcpy(s.sets.value[s.sets.count],row);
                s.sets.count++;
                break;
            }
             case 'R':{
                s.relations.value = (char**)realloc(s.relations.value,sizeof(char*)*s.relations.count+1);
                s.relations.value[s.relations.count] = (char*)malloc(sizeof(char)*strlen(row));
                strcpy(s.relations.value[s.relations.count],row);
                s.relations.count++;
                break;
            }
             case 'C':{
                s.commands.value = (char**)realloc(s.commands.value,sizeof(char*)*s.commands.count+1);
                s.commands.value[s.commands.count] = (char*)malloc(sizeof(char)*strlen(row));
                strcpy(s.commands.value[s.commands.count],row);
                s.commands.count++;
                break;
            }
        }
    }while(!feof(fr));

    return s;

}



int main(int argc, char** argv)
{
    
    if(argc != 2)
    {
    fprintf(stderr,"Zadali jste spatny pocet argumentu.\n");
    return 1;    
    }
    STRUKTURA s = processFile(argv[1]);

    for(int i = 0; i < s.sets.count; i++){
        printf("\n %s",s.sets.value[i]);
    }
    printf("\n");
    printf("%s\n", *s.universe.value);                        //test
    /*for(int i = 0; i < s2.sets[0].count; i++){
        printf("\n %s",s2.sets[0].value[i]);
    }*/

return EXIT_SUCCESS;
}