#include <stdio.h>
#include <stdlib.h>
#include "aStart.h"



int loadMap(Noeud pointeurMap[NB_BLOC_LARGEUR][NB_BLOC_HAUTEUR])
{
    int x,y;
    Noeud noeuBase;
    FILE* file;
    int actualChar;

    file = fopen("test.map", "r");
    if(!file)
        printf("il y a un problème");
    noeuBase.f = 0;
    noeuBase.g = 0;
    noeuBase.h = 0;
    noeuBase.x = 0;
    noeuBase.y = 0;
    noeuBase.wall = 0;
    
   

     
    do
    {
        actualChar = fgetc(file);
        pointeurMap[x][y] = noeuBase;
        switch (actualChar)
        {
            case 49:
                pointeurMap[x][y].wall = 2; 
                break;
            case 32:
                pointeurMap[x][y].wall = 0;
            break;
            case 10:
                x = -1;
                y++;
            break;
            case 115:
                pointeurMap[x][y].wall = 1;
            break;
            case 102:
                pointeurMap[x][y].wall = 3;
            break;
            default:
                pointeurMap[x][y] = noeuBase;
                break;
        }
        x++;
        if(x > NB_BLOC_LARGEUR || y > NB_BLOC_HAUTEUR)
            break;
        
            printf("%d \n", actualChar);            
    }while(actualChar != EOF);
    
    /*pointeurMap[4][0].wall = 2;
    pointeurMap[8][2].wall = 0;
    pointeurMap[1][2].wall = 1; //block depart 
    pointeurMap[7][1].wall = 3; //block arriver*/
    fclose(file);
}



