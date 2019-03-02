#include <stdio.h>
#include <stdlib.h>
#include "aStart.h"

/*
TO DO:
lecture de la map a partir d'un fichier
ou faire comme une seule fonction ou on envoie juste une map
*/



Noeud openList[MAX];
Noeud closeList[MAX];
int front, rear;
int frontClose, rearClose;

void main(){
   
    Noeud map[NB_BLOC_LARGEUR][NB_BLOC_HAUTEUR];
    Noeud noeudStart, noeudFinal, noeudActuel;
    Noeud successeur[8];
    noeudStart.wall = 1; 
    noeudActuel.wall = 0;
    noeudFinal.wall = 3; 

    rearClose = 0;
    system("clear");
    front = rear = -1; // init the queue
    int x,y;
    int i=0;
    
    int continuer = 1;
    initArray(map); 
    
    /* on trouve les blocs de depart et d'arriver*/
    for( x = 0; x <= NB_BLOC_LARGEUR; x++)
    {
        for( y = 0; y <= NB_BLOC_HAUTEUR; y++)
        {
            if (map[x][y].wall == 1){
                noeudStart.x = x;
                noeudStart.y = y;
                noeudStart.g = 0;
                noeudStart.h = calculH(map, x, y);
                noeudStart.f = noeudStart.h +noeudStart.g;
                //noeudStart.wall = 1;
                map[x][y] = noeudStart;
                //map[x][y].wall = 1;
            }
            if (map[x][y].wall == 3){ 
                noeudFinal.x = x;
                noeudFinal.y = y;
                //noeudFinal.g = 0;
                noeudFinal.h = calculH(map, x, y);
                noeudFinal.f = noeudFinal.h +noeudFinal.g;
                noeudFinal.wall = 3;
                map[x][y] = noeudFinal;
                
                
            }
        }
    }

    // start with the noeud start
    noeudActuel = noeudStart; 
    
    while(continuer){ 

        for(i = 0; i < 9; i++){/// for all the successeur we assigne all the value
            if(i != 4){
                successeur[i].x = calculX(i, noeudActuel.x); 
                successeur[i].y = calculY(i, noeudActuel.y);
                successeur[i].g = noeudActuel.g + 1;// ca il faut voir avec les diagonals !!!!!
                successeur[i].h = calculH(map, successeur[i].x, successeur[i].y);
                successeur[i].f = successeur[i].h +successeur[i].g;
                //printf("successor %d   x: %d  y:%d  h:%d  g:%d  f:%d \n", i, successeur[i].x, successeur[i].y, successeur[i].h, successeur[i].g, successeur[i].f);
                if ((check_already(successeur[i]) == 1) && (map[successeur[i].x][successeur[i].y].wall != 2) && (successeur[i].y)>=0) /// si il y a pas deja le successeur et que c'est pas un mur
                {
                    if((successeur[i].x)>=0 && (successeur[i].y)>=0 && (successeur[i].x)<=NB_BLOC_LARGEUR && (successeur[i].y)<=NB_BLOC_HAUTEUR)
                        addInQu(successeur[i]); // we put the node in the queu
                }
                
            }
            
        } 
        //printf(" NOEUD ACTUEL : x:%d  y:%d  g:%d \n", noeudActuel.x, noeudActuel.y, noeudActuel.g);
        
        closeList[rearClose] = noeudActuel;
        rearClose ++;
            
        do// change the Actu node
        {
            if (front != -1){
                noeudActuel = openList[front];
                delInQu(noeudActuel);
            }
        } while (checkClose(noeudActuel) == -1);
      
        printf("\n\n");
        //display(map);
        if((noeudActuel.x == noeudFinal.x) && (noeudActuel.y == noeudFinal.y)){ // if the node Actu is the final node the processe stop
            noeudFinal = noeudActuel;
            printf("trouver en %d ", rearClose);
            retracage_chemin(&noeudFinal, &noeudStart, map);
            display(map);
            break;
        }
        
    }

}

void retracage_chemin(Noeud *pNoeudFinal, Noeud *pNoeudStart, Noeud map[NB_BLOC_LARGEUR][NB_BLOC_HAUTEUR]){
    Noeud test;
    test = *pNoeudFinal;
    int cont;
    
    int i;
    do
    {
        for(i = 0; i < rearClose; i++)
        {
        
        
            if ((test.x + 1 >= closeList[i].x  && closeList[i].x >= test.x -1) && (test.y + 1 >= closeList[i].y  && closeList[i].y >= test.y -1) && test.g == closeList[i].g + 1){
                test = closeList[i];
                map[test.x][test.y].wall = 4;
                break;
            }
        }
        if(test.x == pNoeudStart->x && test.x == pNoeudStart->x){
            cont = 0;
            map[test.x][test.y].wall = 1;
        }
    } while (cont);
    
}



int initArray(Noeud pointeurMap[NB_BLOC_LARGEUR][NB_BLOC_HAUTEUR]){
    int x,y;
    Noeud noeuBase;

    noeuBase.f = 0;
    noeuBase.g = 0;
    noeuBase.h = 0;
    noeuBase.x = 0;
    noeuBase.y = 0;
    noeuBase.wall = 0;

    for( x = 0; x <= NB_BLOC_LARGEUR; x++)
    {
        for( y = 0; y <= NB_BLOC_HAUTEUR; y++)
        {   
            pointeurMap[x][y] = noeuBase;
            pointeurMap[x][y].wall = 0;
            
            if(x >= 4 && y == 2){
                pointeurMap[x][y].wall = 2;
            }
            if(x == 4 && y == 1){
                pointeurMap[x][y].wall = 2;
            }
            
        }

    }
    pointeurMap[4][0].wall = 2;
    pointeurMap[8][2].wall = 0;
    pointeurMap[1][2].wall = 1; //block depart 
    pointeurMap[7][1].wall = 3; //block arriver 
}


int calculH(Noeud map[NB_BLOC_LARGEUR][NB_BLOC_HAUTEUR], int x, int y){
    int h;
    int xf = 0;
    int yf = 0;
    int i, j;
    int trouver = 0;

    /// pour x
        for (i = x; i <= NB_BLOC_LARGEUR; i++){
            for (j = 0; j <= NB_BLOC_HAUTEUR; j++){
                if(map[i][j].wall == 3){
                    trouver = 1;
                    break;
                }
            }
            if (trouver == 1){
                break;
            }
            xf++;
        }
    if (trouver == 0){
        xf = 0;
        for (i = x; i >= 0; i--){
            for (j = 0; j <= NB_BLOC_HAUTEUR; j++){
                if(map[i][j].wall == 3){
                    trouver = 1;
                    break;
                }
            }
            if (trouver == 1)
                break;
            xf++;

        }
    }
    //printf("xf: %d \n", xf);
    trouver = 0;

    for (j = y; j >= 0; j--){
        for (i = 0; i <= NB_BLOC_LARGEUR; i++){
            if(map[i][j].wall == 3){
                trouver = 1;
                break;
            }
        }
        if (trouver == 1){
            break;
        }
        yf++;
    }

    if (trouver == 0){
        yf = 0;
        for (j = y; j >= 0; j--){
            for (i = 0; i <= NB_BLOC_HAUTEUR; i++){
                if(map[i][j].wall == 3){
                    trouver = 1;
                    break;
                }
            }
            if (trouver == 1)
                break;
            yf++;
        }
    }

    h = xf + yf;
    return h;
}

int calculY(int i, int y){
    if(i < 3){
        return y-1;
    }
    else if (i < 6){
        return y;
    }
    else if (i<=8)
        return y+1;
}

int calculX(int i, int x){
    if((i == 0) || (i == 3) || (i == 6)){
        return x-1;
    }
    else if((i == 1) || (i == 4) || (i == 7)){
        return x;
    }
    else if((i == 2) || (i == 5) || (i == 8)){
        return x+1;
    }
}

int addInQu(Noeud data){ // just add 1 one the rear and send the node to trie the queu
    if ((front ==-1) && (rear == -1)){
        rear ++;
        front ++;
        openList[rear] = data;
    }
    else{    
        check(data);
        rear ++;       
    }
}

int delInQu(Noeud data){ // just delete the first node of the openList
    int i;

    if ((front ==-1) && (rear == -1)){
        printf("pas de truc a virer");
    }
    else{
        for(i = 0; i < rear; i++){
            openList[i] = openList[i + 1];
        }
        openList[rear].f = 0;
        openList[rear].g = 0;
        openList[rear].h = 0;
        openList[rear].x = 0;
        openList[rear].y = 0;
        openList[rear].wall = 0;
        rear --;
    }
}

int check_already(Noeud data){ // check if the node is already in the OpenListe
    int i;
    for(i = 0; i <= rear; i++){
        if((data.x == openList[i].x) && (data.y == openList[i].y)){
            if ( data.f >= openList[i].f)
                return -1;
        }       
    }
    return 1;
}

int checkClose(Noeud data){ // check if the node is already in the CloseListe
    int i;
    for(i = 0; i <= rearClose; i++){
        if((data.x == closeList[i].x) && (data.y == closeList[i].y)){
            if ( data.f >= closeList[i].f)
                return -1;
        }       
    }
    return 1;
}

void display(Noeud map[NB_BLOC_LARGEUR][NB_BLOC_HAUTEUR]){ // display the map 

    char c;
    int i, j;
    for (j = 0; j < NB_BLOC_HAUTEUR; j++){
        for (i = 0; i <= NB_BLOC_LARGEUR; i++){
            if(map[i][j].wall == 3) // if it's a block stop
            {
                my_putchar('F');
            }
            else if(map[i][j].wall == 1) // if it's a block start
            {
                my_putchar('S');
                //printf("%d %d \n", map[i][j].noeud.y, map[i][j].noeud.x);
            }
            else if(map[i][j].wall == 2) // if it's a block wall
            {
                my_putchar('#');
                //printf("#");
            }
            else if (map[i][j].wall == 0){
                my_putchar(' ');
            }
            else if (map[i][j].wall == 4){ //  si il a ete parcourue par la close liste
                my_putchar('.');
            }
        }
        my_putchar('\n');
    }
    
}

void my_putchar(char c)
{
    write(1, &c, 1);
}

void check(Noeud data) // add and tri the node and the openListe
{
    int i,j;
    
    for (i = 0; i <= rear; i++)
    {
        if (data.f <= openList[i].f)
        {
            for (j = rear + 1; j > i; j--)
            {
                openList[j] = openList[j - 1];
            }
            openList[i] = data;
            return;
        }
    }
    openList[i] = data;
}