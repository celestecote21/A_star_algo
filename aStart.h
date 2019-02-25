#define NB_BLOC_LARGEUR 8
#define NB_BLOC_HAUTEUR 4
#define MAX NB_BLOC_LARGEUR*NB_BLOC_HAUTEUR



typedef struct Noeud Noeud;
typedef struct STACK STACK;

struct Noeud
{
    int wall;
    int x;
    int y;
    int g;
    int h;
    int f;
    

};

struct STACK
{
    Noeud stk[MAX];
    int top;
};



int initArray(Noeud pointeurMap[NB_BLOC_LARGEUR][NB_BLOC_HAUTEUR]);
int calculH(Noeud map[NB_BLOC_LARGEUR][NB_BLOC_HAUTEUR], int x, int y);
int calculX(int i, int x);
int calculY(int i, int y);
int addInQu(Noeud data);
int delInQu(Noeud data);
void creat_Qu();
void check_Qu(Noeud data);
int check_already(Noeud data);
void display(Noeud map[NB_BLOC_LARGEUR][NB_BLOC_HAUTEUR]);
void my_putchar(char c);
void display_pqueue();
void check(Noeud data);
int checkClose(Noeud data);