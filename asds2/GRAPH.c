#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"GHRAPHPRIM.h"
#include <limits.h>


Node createNode(ELEMENT value, int weight) {
    Node n = (Node) malloc(sizeof(structNode));
    if(!n)
        printf("pas d'espace memoire\n");
    else{
        n->info = value;
        n->weight = weight;
        n->next = NULL;
        }

    return n;
}

Graph creategraph(int V){
Graph g = (Graph) malloc(sizeof(strucGraph));
if(!g)
    printf("pas d'espace memoire");
else{
    g->V=V;
    for (int i = 0; i < V; i++) {
        g->adjList[i] = NULL;
        }
    return g;
    }

}

void addEdge(Graph g, ELEMENT src, ELEMENT dest, int weight) {
    Node nd = createNode(dest, weight);
    nd->next = g->adjList[(src->n)-65];
    g->adjList[(src->n)-65] = nd;

    nd = createNode(src, weight);
    nd->next = g->adjList[(dest->n)-65];
    g->adjList[(dest->n)-65] = nd;
}
int estvidegraph(Graph g){
int vrai=1,i=0;
while(i<26 && vrai){
    if(g->adjList[i]!=NULL)
        vrai=0;
    else
        i++;
    }
return vrai;
}

void noeudsdetruire(Node nd){
Node n;
while(nd!=NULL){

    n=nd;
    nd=nd->next;
    //elementDetruire(n->info);
    free (n);
    }
free (nd);
}

void graphdetruire(Graph g){
int i;
for(i=0;i<26;i++){
    if(g->adjList[i]!=NULL)
        noeudsdetruire(g->adjList[i]);
    }
free (g);
}
// Fonction pour trouver le nœud avec la distance minimale dans le tableau de distance
int minDistance(int dist[], int visited[], int V) {

    int min = INT_MAX, min_index,i;
    for (i=0;i<V;i++) {
        if (visited[i] == 0 && dist[i] <= min) {
            min = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

// Fonction pour afficher le chemin le plus court entre la source et la destination
void printPath(int parent[], int dest) {


      if (parent[dest] == -1) {

        matricegouv(dest);
        return;
    }
    printPath(parent, parent[dest]);
    printf("-->");
    matricegouv(dest);
}




void printPath2(int parent[], int dest) {
    if (parent[dest] == -1) {
        printf("%c",dest+65);
        return;
    }
    printPath2(parent, parent[dest]);
    printf("-->");
    printf("%c",dest+65);
}

// Fonction pour afficher la distance minimale de la source à tous les nœuds du graphe
void printallShpaths(int dist[], int parent[], int src, int V) {
int i,l;
    printf("\033[39mDeparture from: ");printf("\033[30m\033[107m");matricegouv(src);printf("\033[39m\033[49m\n");sleep(1);
    printf("\033[93mdestination\t Distance\t Path\n\033[39m");sleep(1);
    for (i = 0; i < V; i++) {
        if (i != src) {
            printf("\033[39m------------------------------------------------------------------------------------------------\033[39m\n");sleep(1);
            l=longueurmot(i);
            if(l>=8){
            printf("\033[35m");
            matricegouv(i);printf("\033[39m");
            printf("\t \033[33m%d km\t\t\033[39m ", dist[i]);
            printf("\033[36m");printPath(parent, i);printf("\033[39m");
            printf("\n");
            }
            else{
            printf("\033[35m");
            matricegouv(i);printf("\033[39m");
            printf("\t\t \033[33m%d km\t\t\033[39m ", dist[i]);
            printf("\033[36m");printPath(parent, i);printf("\033[39m");
            printf("\n");}
            }
        }
    printf("\033[39m------------------------------------------------------------------------------------------------\033[39m\n");


}

void printallShpaths12(int dist[], int parent[], int src,ELEMENT elem[], int V) {
int i;
    printf("\033[39mDeparture from: ");printf("\033[30m\033[107m%c",src+65);printf("\033[39m\033[49m\n");sleep(1);
    printf("\033[93mdestination\t Distance\t Path\n\033[39m");sleep(1);
    for (i = 0; i < V; i++) {
        if (i != src && elem[i]!=NULL) {
            printf("\033[39m------------------------------------------------------------------------------------------------\033[39m\n");sleep(1);


            printf("\033[35m");
            printf("%c",elem[i]->n);printf("\033[39m");
            if(dist[i]==INT_MAX)
                    printf("\t\t \033[33mthere is no edge between %c et %c\033[39m\n",src+65,elem[i]->n);
            else{
            printf("\t\t \033[33m%d \t\t\033[39m ", dist[i]);
            printf("\033[36m");printPath2(parent, i);printf("\033[39m");
            printf("\n");}}
            }

    printf("\033[39m------------------------------------------------------------------------------------------------\033[39m\n");


}

void shortestpath(Graph g, char src, char dest) {
    int count,u,v,weight,i;
    Node temp;
    int V = g->V;
    int dist[V];
    int visited[V];
    int parent[V];

    for ( i=0;i<V;i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
        parent[i] = -1;
    }


dist[src] = 0;
for (count=0;count<V - 1;count++) {
    u = minDistance(dist, visited, V);
    visited[u] = 1;

    // Mettre à jour la distance minimale de tous les nœuds adjacents non visités
     temp = g->adjList[u];
    while (temp != NULL) {
         v = (temp->info->n)-65;
         weight = temp->weight;
        if (!visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            dist[v] = dist[u] + weight;
            parent[v] = u;
        }
        temp = temp->next;
    }
}

// Afficher la solution
printf("\n\033[39mShortest path from ");printf ("\033[97m\033[46m");matricegouv(src);printf(" \033[39m\033[49mto ");printf ("\033[97m\033[46m");matricegouv(dest);printf ("\033[39m\033[49m");
printf("\nShortest distance: \033[36m%d km\033[39m\n", dist[dest]);

printf("Shortest path: ");printf("\033[36m");
printPath(parent, dest);printf("\033[39m");
printf("\n");

}

void shortestpath1(Graph g, char src, char dest) {

    int count,u,v,weight,i;
    Node temp;
    int V = 26;//on a initialisé le V à 26 et non à g->V  pour donner la possibilité à l'utilisateur de choisir des lettres distincts
    int dist[V];
    int visited[V];
    int parent[V];
    for ( i=0;i<V;i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
        parent[i] = -1;
    }


dist[src] = 0;
for (count=0;count<V - 1;count++) {
     u = minDistance(dist, visited, V);
    visited[u] = 1; // Marquer le nœud comme visité

    // Mettre à jour la distance minimale de tous les nœuds adjacents non visités
     temp = g->adjList[u];
    while (temp != NULL) {
         v = (temp->info->n)-65;
         weight = temp->weight;
        if (!visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            dist[v] = dist[u] + weight;
            parent[v] = u;
        }
        temp = temp->next;
    }
}

// Afficher la solution
printf("\n\033[39mShortest path from ");printf ("\033[97m\033[46m%c",src+65);printf(" \033[39m\033[49mto ");printf ("\033[97m\033[46m%c",dest+65);printf ("\033[39m\033[49m");
printf("\nShortest distance: \033[36m%d \033[39m\n", dist[dest]);

printf("Shortest path: ");printf("\033[36m");
printPath2(parent, dest);printf("\033[39m");
printf("\n");

}




void printgraph(Graph g){
int i;
Node nd=createNode(g->adjList[0]->info,g->adjList[0]->weight);
printf("here's the graph :\n\n");
for(i=0;i<(g->V);i++){sleep(1);
    nd=g->adjList[i];
    printf("\033[92m");
    matricegouv(i);
    printf(": \033[37m");
    while(nd!=NULL){

    printf("%s(%ikm) ",nd->info->nom,nd->weight);
    if(nd->next!=NULL)
        printf(",");
    nd=nd->next;

    }
    printf("\n");

    }

}

void printgraph2(Graph g){
int i;
ELEMENT e=elementCreer();
Node nd=createNode(e,2);
printf("here's the graph :\n");
for(i=0;i<26;i++){
    nd=g->adjList[i];
    printf("\033[92m");
    if(nd!=NULL){
        printf("%c",i+65);
        printf(": \033[37m");}
    while(nd!=NULL){

    printf("%c(%i) ",nd->info->n,nd->weight);
    if(nd->next!=NULL)
        printf(",");
    else
            printf("\n");

    nd=nd->next;

    }

    }
elementDetruire(e);

}




void shortestpath2(Graph g, char src) {
    int count,u,v,weight,i;
    Node temp;
    int V = g->V;
    int dist[V];
    int visited[V];
int parent[V];

    for ( i=0;i<V;i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
        parent[i] = -1;
    }


dist[src] = 0;
for (count=0;count<V - 1;count++) {
    u = minDistance(dist, visited, V);
    visited[u] = 1; // Marquer le nœud comme visité

    // Mettre à jour la distance minimale de tous les nœuds adjacents non visités
     temp = g->adjList[u];
    while (temp != NULL) {
         v = (temp->info->n)-65;
         weight = temp->weight;
        if (!visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            dist[v] = dist[u] + weight;
            parent[v] = u;
        }
        temp = temp->next;
    }
}
printallShpaths(dist, parent, src, V);// Afficher la distance minimale de la source à tous les nœuds du graphe
}


void shortestpath12(Graph g, char src,ELEMENT elem[]) {
    int count,u,v,weight,i;
    Node temp;
    int V = 26;//g->V;
    int dist[V]; // Tableau pour stocker les distances minimales de la source à chaque nœud du graphe
    int visited[V]; // Tableau pour marquer les nœuds visités
    int parent[V]; // Tableau pour stocker les nœuds parents du chemin le plus court

    // Initialisation des tableaux
    for ( i=0;i<V;i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
        parent[i] = -1;
    }


dist[src] = 0; // La distance de la source à elle-même est de 0
// Trouver le chemin le plus court pour tous les nœuds du graphe
for (count=0;count<V - 1;count++) {
    u = minDistance(dist, visited, V);
    visited[u] = 1; // Marquer le nœud comme visité

    // Mettre à jour la distance minimale de tous les nœuds adjacents non visités
     temp = g->adjList[u];
    while (temp != NULL) {
         v = (temp->info->n)-65;
         weight = temp->weight;
        if (!visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            dist[v] = dist[u] + weight;
            parent[v] = u;
        }
        temp = temp->next;
    }
}
printallShpaths12(dist, parent, src,elem, V);// Afficher la distance minimale de la source à tous les nœuds du graphe
}







//procédure qui fait la lecture des points avec un controle de saisie
void checkpoints(char* x,char* y){
char alphabets[24];
int test=0,j,i,count=0;


for(i=0;i<24;i++){
    alphabets[i]=i+65;}

while(!test){
  if(!count){
    printf("\033[34mchoose the starting point :\033[39m\n");getchar();
    scanf("%c",&*x);}
  else{
    printf(" \033[31minvalid choice, would you choose again\033[39m\n");
    scanf("%c",&*x);
    }
    j=0;
    while(j<24 && !test){
        if(alphabets[j]==*x)
            test=1;
        else
        j++;}
        getchar();
        if(!test)
            count++;
    }

test=0;
count=0;
while(!test){
  if(!count){
    printf("\033[34mchoose your destination :\033[39m\n");
    scanf("%c",&*y);}
  else{
    printf("\033[31minvalid choice, would you choose again\033[91m\n");
    scanf("%c",&*y);
    }
    j=0;
    while(j<24 && !test){
        if(alphabets[j]==*y)
            test=1;
        else
        j++;}
        getchar();
        if(!test)
            count ++;

    }

}

void checkpoint(char* x){
char alphabets[24];
int test=0,j,i,count=0;


for(i=0;i<24;i++){
    alphabets[i]=i+65;}

while(!test){
  if(!count){
    printf("\033[34mchoose a governorate :\033[39m\n");getchar();
    scanf("%c",&*x);}
  else{
    printf(" \033[31minvalid choice, would you choose again\033[39m\n");
    scanf("%c",&*x);
    }
    j=0;
    while(j<24 && !test){
        if(alphabets[j]==*x)
            test=1;
        else
        j++;}
        getchar();
        if(!test)
            count++;
    }}

void matricegouv(int x){
char M[24][20]={"BIZERTE","BEJA","JENDOUBA","ARIANA","MANOUBA","TUNIS","BEN AROUS","NABEUL","ZAGHOUAN","SILIANA","KEF","KASSERINE","KAIROUAN","SOUSSE","MONASTIR","MAHDIA","SFAX","GAFSA","SIDI BOUZID","TOZEUR","KEBILI","GABES","MEDENINE","TATAOUINE"};
printf("%s",M[x]);
}

int longueurmot(int x){
int l;
char M[24][20]={"BIZERTE","BEJA","JENDOUBA","ARIANA","MANOUBA","TUNIS","BEN AROUS","NABEUL","ZAGHOUAN","SILIANA","KEF","KASSERINE","KAIROUAN","SOUSSE","MONASTIR","MAHDIA","SFAX","GAFSA","SIDI BOUZID","TOZEUR","KEBILI","GABES","MEDENINE","TATAOUINE"};
l=strlen(M[x]);
return l;
}

void symbole(){
int i;
printf("\033[32maccording to what mentioned here :\n");
for(i=0;i<24;i++){
    printf("%c :",i+65);
    matricegouv(i);
    printf(" / ");
    }
    printf("\n\n\033[39m");

}
void welcome(){
printf("\n\n\n\n\n\n\n\n\t\t\t");
printf("\t\t\t\t \033[35m|\t\t\t|\n");
printf("\t\t\t\t\t\t\t |\t\033[36m\033[49mwelcome\033[39m\033[49m\t\t\033[35m|\n");
printf("\t\t\t\t\t\t\t |\t\t\t|\n");
printf("\n\n\t\t\t\t\t\033[39mpress Enter");




}
void menu1(){
int c;
printf("\n\n\n\n\n");printf("\033[95m\t\t\t\t ____________________________________________________________\n");
printf("\t\t\t\t|\033[34mwould you :\t\t\t\t\t\t     \033[95m|\n\t\t\t\t|\033[34m1: create your own graph\t\t\t\t     \033[95m|\n\t\t\t\t|\033[34m2: explore the graph of tunisia\t\t\t     \033[95m|\n\t\t\t\t|\033[34m3: exit\t\t\t\t\t\t     \033[95m|\n");
printf("\033[95m\t\t\t\t|____________________________________________________________|\033[39m\n");
printf("\n\t\t\t\t");
scanf("%d",&c);
while(c!=1 && c!=2 && c!=3){
    printf("\033[31minvalid choice! choose again\033[39m\n");
    scanf("%d",&c);getchar();}
if(c==3)
    return;
else if(c==2)
    menu2();
else
    entre();
return;
}
void menu21(int *k){
printf("\n\n\n\n\n");printf("\t\t\033[34m __________________________________________________________________________________________\n");
printf("\t\t|\033[95m\twould you :\t\t\t\t\t\t\t\t\t   \033[34m|\n\t\t|\t\033[95m1: explore the graph of Tunisia\t\t\t\t\t\t\t   \033[34m|\n\t\t|\t\033[95m2: discover the shortest path between two governorates\t\t\t\t   \033[34m|\n\t\t|\t\033[95m3: discover the shortest path between to all governorates\t\t\t   \033[34m|\n\t\t|\033[95m\t4: check some information about the governorates\t\t\t\t   \033[34m|\n\t\t|\033[95m\t5: previous\t\t\t\t\t\t\t\t\t   \033[34m|\033[39m\n");
printf("\t\t\033[34m|__________________________________________________________________________________________|\033[39m\n\n\t\t");

scanf("%d",k);
while(*k!=1 && *k!=2 && *k!=3 && *k!=4 && *k!=5){
    printf("\033[31minvalid choice! choose again\033[39m\n");getchar();
    scanf("%d",k);
    }

}


int menu2(){
int k,V=24;
char depart,src,dest;
Graph g=creategraph(V);
system("clear");
mapTun2(g);
menu21(&k);
while(k==1 || k==2 ||  k==3){
if(k==1){
    system("clear");
    printgraph(g);
    printf("press enter\n");
    getchar();
    getchar();system("clear");
    menu21(&k);

}
else if(k==2){
    system("clear");
    symbole();
    checkpoints(&src,&dest);
    shortestpath(g, src-65, dest-65);
    printf("\npress enter\n");
    getchar();system("clear");
    menu21(&k);

}
else {
    system("clear");
    symbole();
    checkpoint(&depart);
    shortestpath2(g,depart-65);
    printf("\npress enter\n");
    getchar();system("clear");
    menu21(&k);

    }}
if(k==5){
    //graphdetruire(g);
    system("clear");
    menu1();}

else
 {
    system("clear");
    menu3(g);}
}

void coordonnees(int k,Graph g){
char h,alphabets[25];
int test=0,i,j,s,r,s1;


Node nd=createNode(g->adjList[0]->info,g->adjList[0]->weight);
if(k==1){
    symbole();
    checkpoint(&h);}
printf("\n\033[93mname\t\tpopulation\tacreage(km²)\tmunicipality\tcreation date\033[37m  ");

if(k==1){
    printf("\n");
    i=0;
    while(i<(g->V) && !test){
    nd=g->adjList[i];
    while(nd!=NULL && !test){
        if(nd->info->n==h){
            if(strlen(nd->info->nom)<6)
                elementAfficher1(nd->info);
            else
                elementAfficher(nd->info);
            test++;}
        else
            nd=nd->next;
        }
        i++;

    }

    printf("\n");

    }
else{getchar();
    printf("\033[96m    |\033[39m");
    i=0;
    while(i<(g->V) && strlen(alphabets)<24){
    nd=g->adjList[i];
    while(nd!=NULL && strlen(alphabets)<24){
        j=0;
        test=0;
        while(j<strlen(alphabets) && !test){
            if(alphabets[j]==nd->info->n)
                test++;
            else
                j++;
            }
        if(!test){
            printf("\n\033[96m-----------------------------------------------------------------------------------|\033[39m\n");sleep(1);
            s=strlen(alphabets)+1;
            if(nd->info->n=='I')
                printf(" %s \t %ld \t\t %ld \t\t    %i \t\t %i/%i/%i",nd->info->nom,nd->info->population,nd->info->superficie,nd->info->municip,nd->info->naiss.jour,nd->info->naiss.mois,nd->info->naiss.annee);
            else if(strlen(nd->info->nom)<6)
                elementAfficher1(nd->info);
            else
                elementAfficher(nd->info);printf("\t   \033[96m|");
            alphabets[strlen(alphabets)]=nd->info->n;
            s1=strlen(alphabets);
            while(s!=strlen(alphabets)){                /*j'ai ajouté cette boucle de suppression (+ les variables s,s1,r) a cause d'un probleme que j'ai rencontré */
                for(r=s;r<s1;r++)
                    alphabets[r]=alphabets[r+1];
                s1--;
                }
            }
        nd=nd->next;

        }
    i++;
    }


}
if(k!=1)
    printf("\n\033[96m-----------------------------------------------------------------------------------|\n");

printf("\n\033[39mpress enter :\n");
getchar();
system("clear");
menu3(g);
}

void menu3(Graph g){
int f;
printf("\n\n\n\n\n\n\t\t\t\t\t\033[33m _____________________________________\n");
printf("\t\t\t\t\t|1: one governorate\t\t      |\n\t\t\t\t\t|2: all governorates\t\t      |\n\t\t\t\t\t|3: previous\t\t\t      |\n\t\t\t\t\t|4: exit\t\t\t      |\n");printf("\t\t\t\t\t|_____________________________________|\n\n\t\t\t\t\t\033[39m");

scanf("%d",&f);
while(f!=1 && f!=2 && f!=3 && f!=4){
    printf("\033[31minvalid choice! choose again\033[39m\n");getchar();
    scanf("%d",&f);
    }
if(f==1 || f==2 ){
    system("clear");
    coordonnees(f,g);}
else if(f==3){
    graphdetruire(g);
    system("clear");
    menu2();}
return;

}
void menu4(int * x){


printf("\n\n\n\n\n");printf("\t\t\033[92m __________________________________________________________________________________________\n");
printf("\t\t|\033[33m\t1: add edge\t\t\t\t\t\t\t\t\t   \033[92m|\n\t\t|\t\033[33m2: print graph\t\t\t\t\t\t\t\t\t   \033[92m|\n\t\t|\t\033[33m3: shortest path between two vertices\t\t\t\t\t\t   \033[92m|\n\t\t|\t\033[33m4: shortest path to all other vertices\t\t\t\t\t\t   \033[92m|\n\t\t|\t\033[33m5: change weight\t\t\t\t\t\t\t\t   \033[92m|\n\t\t|\t\033[33m6: previous\t\t\t\t\t\t\t\t\t   \033[92m|\n");
printf("\t\t\033[92m|__________________________________________________________________________________________|\033[39m\n\n\t\t");
scanf("%d",x);
while(*x!=1 && *x!=2 && *x!=3 && *x!=4 && *x!=5 && *x!=6){

        printf("\033[31minvalid choice! choose again\033[39m\n");getchar();
        scanf("%d",x);}

}


void checkcharacter(ELEMENT elem[],char *c){
int trouve=0,i,j;
    while(!trouve){
    j=0;
    while(j<26 && !trouve){
      if(elem[j]!=NULL){
        if(elem[j]->n==*c)
            trouve++;
            }
        j++;}
    if(!trouve){
            printf("\033[31mcharacter does not exist! would you verify \033[39m\n");getchar();
            scanf("%c",c);}}

}



void entre(){
int i,V,weight,choix,test,j,trouve;
char car1,car2;
ELEMENT elt,elt1,elt2;
Graph g;
Node n;
ELEMENT elem[100];
system("clear");
printf("how many vertices in your graph: \n");
scanf("%d",&V);
while(V>26 || V<2)
    {printf("\033[31mnumber of vertices must be between 1 and 26\033[39m\n");getchar();
    scanf("%d",&V);}
g=creategraph(V);
for(i=0;i<26;i++){
    elem[i]=NULL;
    }

for(i=0;i<(g->V);i++){
    elt=elementCreer();getchar();
    element1lire(&elt);
    while(elt->n<'A' || elt->n>'Z'){
        printf("\033[31minvalid choice! the character must be an uppercase letter\033[39m\n");getchar();
        scanf("%c",&elt->n);}
    trouve=0;
    j=0;
    while(j<26 && !trouve){
      if(elem[j]!=NULL){
        if(elem[j]->n==elt->n){
            trouve++;
            printf("\033[31mcharactar exists already,choose another one\033[39m\n");
            i--;}}
         j++;}
    if(!trouve)
        elem[(elt->n)-65]=elt;



    }
system("clear");
menu4(&choix);

while(choix==1 || choix==2 || choix==3 || choix==4 || choix==5 ){
if(choix==1){
    system("clear");
    printf("\033[36mHere are the elements you created :\n");
    for(i=0;i<26;i++)
        if(elem[i]!=NULL)
            printf("%c\t",elem[i]->n);printf("\033[39m\n");
    elt1=elementCreer();getchar();
    element1lire(&elt1);
    checkcharacter(elem,&elt1->n);

    elt2=elementCreer();getchar();
    element1lire(&elt2);
    checkcharacter(elem,&elt2->n);
    while(elt2->n==elt1->n){getchar();
        printf("\033[31minvalid choice! the edge must be between two different characters\033[39m\n");
        element1lire(&elt2);
        checkcharacter(elem,&elt2->n);}
    do{
    printf("weight?: \n");getchar();
    scanf("%d",&weight);printf("\033[31m");}
    while(weight>1000 || weight<1 );
    printf("\033[39m");
    n=createNode(elt1,weight);
    n=g->adjList[(elt1->n)-65];
    test=0;
    while(n!=NULL && !test){
        if(n->info->n==elt2->n){
            test++;
            getchar();
            printf("\033[31mthere is already an edge between %c et %c\033[39m\n",elt1->n,elt2->n);}
        else n=n->next;
            }
    if(!test)
        addEdge(g,elt1,elt2,weight);

    getchar();system("clear");
    menu4(&choix);


    }

if(choix==2){
    getchar();system("clear");
    if(estvidegraph(g))
        printf("\033[31mthe graph is empty,maybe you should add edges between vertices\033[39m\n");
    else
        printgraph2(g);
    getchar();system("clear");
    menu4(&choix);

}
if(choix==3){
    system("clear");
    printf("\033[36mHere are the elements you created :\n");
    for(i=0;i<26;i++)
        if(elem[i]!=NULL)
            printf("%c\t",elem[i]->n);printf("\033[39m\n");
    elt1=elementCreer();getchar();
    element1lire(&elt1);
    checkcharacter(elem,&elt1->n);
    car1=elt1->n;
    elt2=elementCreer();getchar();
    element1lire(&elt2);
    checkcharacter(elem,&elt2->n);
    car2=elt2->n;
     n=createNode(elt1,weight);
    n=g->adjList[(elt1->n)-65];
    test=0;
    while(n!=NULL && !test){
        if(n->info->n==elt2->n)
            test++;
        else n=n->next;
            }
        getchar();
    if(!test)
            printf("\033[31mthere is no edge between %c et %c\033[39m\n",elt1->n,elt2->n);
    else
           shortestpath1(g,car1-65,car2-65);
    getchar();system("clear");
    menu4(&choix);


}
if(choix==4){
    system("clear");
    elt=elementCreer();getchar();
    element1lire(&elt);
    checkcharacter(elem,&elt->n);
    car1=elt->n;
    getchar();
    shortestpath12(g,car1-65,elem);
    getchar();system("clear");
    menu4(&choix);

}
if(choix==5){
    system("clear");
    printf("\033[36mHere are the elements you created :\n");
    for(i=0;i<26;i++)
        if(elem[i]!=NULL)
            printf("%c\t",elem[i]->n);printf("\033[39m\n");
    elt1=elementCreer();getchar();
    element1lire(&elt1);
    checkcharacter(elem,&elt1->n);
    car1=elt1->n;
    elt2=elementCreer();getchar();
    element1lire(&elt2);
    checkcharacter(elem,&elt2->n);
    car2=elt2->n;
     n=createNode(elt1,weight);
    n=g->adjList[(elt1->n)-65];
    test=0;
    while(n!=NULL && !test){
        if(n->info->n==elt2->n){
            do{
                printf("weight?: \n");getchar();
                scanf("%d",&weight);}
            while(weight>1000 || weight<1);
            n->weight=weight;
            test++;}
        else n=n->next;
            }
    if(test){
    n=createNode(elt2,weight);
    n=g->adjList[(elt2->n)-65];
    test=0;
    while(n!=NULL && !test){
        if(n->info->n==elt1->n){
            n->weight=weight;
            test++;}
        else n=n->next;
            }
    getchar();
      printf("\033[32mweight changed successfully\033[39m\n");
      }
    if(!test){
            getchar();
            printf("\033[31mthere is no edge between %c et %c\033[39m\n",elt1->n,elt2->n);}

    getchar();system("clear");
    menu4(&choix);


}
}

   //graphdetruire(g);
   /*elementDetruire(elt);
    elementDetruire(elt1);
   elementDetruire(elt2);*/

    system("clear");
    menu1();


}

void mapTun2(Graph g){
ELEMENT elem[24];
 char line[300];
    char *bloc;
    char ch[30][30],ch1[5],ch2[2];
    int i,k=0;
 FILE *fp = fopen("Document", "r");
    if (fp == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return;
    }

     while (fgets(line, 300, fp)) {
        ELEMENT elt=elementCreer();
        i=0;
        bloc = strtok(line, "#");
        while (bloc != NULL) {
           strcpy(ch[i],bloc);
            bloc = strtok(NULL, "#");
            i++;
        }
        elt->n=ch[0][0];
        strcpy(elt->nom,ch[1]);
        elt->population=atoi(ch[2]);
        elt->superficie=atoi(ch[3]);
        elt->municip=atoi(ch[4]);
        elt->naiss.annee=atoi(strncpy(ch1,ch[5]+6,4));strcpy(ch1,"");
        elt->naiss.jour=atoi(strncpy(ch2,ch[5],2));
        elt->naiss.mois=atoi(strncpy(ch2,ch[5]+3,2));
        elem[k]=elt;
        k++;
    }

    fclose(fp);

addEdge(g, elem[0],  elem[1], 105);
addEdge(g, elem[0],  elem[4], 63);
addEdge(g, elem[0],  elem[3], 63);
addEdge(g, elem[1],  elem[4], 115);
addEdge(g, elem[1],  elem[8], 131);
addEdge(g, elem[1],  elem[9], 101);
addEdge(g, elem[1],  elem[2], 49);
addEdge(g, elem[2],  elem[9], 98);
addEdge(g, elem[2],  elem[10], 50);
addEdge(g, elem[3],  elem[4], 1);
addEdge(g, elem[3],  elem[5], 1);
addEdge(g, elem[4],  elem[8], 60);
addEdge(g, elem[4],  elem[6], 14);
addEdge(g, elem[4],  elem[5], 10);
addEdge(g, elem[5],  elem[6], 14);
addEdge(g, elem[6],  elem[8], 49);
addEdge(g, elem[6],  elem[7], 60);
addEdge(g, elem[7],  elem[8], 61);
addEdge(g, elem[7],  elem[13], 102);
addEdge(g, elem[8],  elem[13], 92);
addEdge(g, elem[8],  elem[12], 103);
addEdge(g, elem[8],  elem[9], 93);
addEdge(g, elem[9],  elem[10], 73);
addEdge(g, elem[9],  elem[11], 144);
addEdge(g, elem[9],  elem[18], 147);
addEdge(g, elem[9],  elem[12], 99);
addEdge(g, elem[10], elem[11], 130);
addEdge(g, elem[11], elem[18], 73);
addEdge(g, elem[11], elem[17], 111);
addEdge(g, elem[12], elem[15], 102);
addEdge(g, elem[12], elem[13], 56);
addEdge(g, elem[12], elem[18],111);
addEdge(g, elem[12], elem[16], 138);
addEdge(g, elem[13], elem[15], 59);
addEdge(g, elem[13], elem[14], 24);
addEdge(g, elem[14], elem[15], 43);
addEdge(g, elem[15], elem[16], 117);
addEdge(g, elem[16], elem[18], 136);
addEdge(g, elem[16], elem[17], 200);
addEdge(g, elem[16], elem[21], 137);
addEdge(g, elem[17], elem[18], 115);
addEdge(g, elem[17], elem[21], 156);
addEdge(g, elem[17], elem[20], 111);
addEdge(g, elem[17], elem[19], 93);
addEdge(g, elem[19], elem[20], 96);
addEdge(g, elem[20], elem[21], 118);
addEdge(g, elem[20], elem[22], 194);
addEdge(g, elem[20], elem[23], 233);
addEdge(g, elem[21], elem[22], 76);
addEdge(g, elem[22], elem[23], 52);



}







/*void mapTun(Graph g){

ELEMENT e0=elementCreer();
e0->n='A';
strcpy(e0->nom,"BIZERTE");

e0->population=568219;
e0->superficie=3750;
e0->municip=17;
e0->naiss.jour=21;
e0->naiss.mois=06;
e0->naiss.annee=1956;



ELEMENT e1=elementCreer();
e1->n='B';
strcpy(e1->nom,"BEJA");
e1->population=303032;
e1->superficie=3740;
e1->municip=12;
e1->naiss.jour=21;
e1->naiss.mois=06;
e1->naiss.annee=1956;


ELEMENT e2=elementCreer();
e2->n='C';
strcpy(e2->nom,"JENDOUBA");
e2->population=401477;
e2->superficie=	3100;
e2->municip=14;
e2->naiss.jour=21;
e2->naiss.mois=06;
e2->naiss.annee=1956;


ELEMENT e3=elementCreer();
e3->n='D';
strcpy(e3->nom,"ARIANA");
e3->population=576088;
e3->superficie=482;
e3->municip=6;
e3->naiss.jour=3;
e3->naiss.mois=12;
e3->naiss.annee=1983;


ELEMENT e4=elementCreer();
e4->n='E';
strcpy(e4->nom,"MANOUBA");
e4->population=379518;
e4->superficie=1137;
e4->municip=10;
e4->naiss.jour=31;
e4->naiss.mois=07;
e4->naiss.annee=2000;


ELEMENT e5=elementCreer();
e5->n='F';
strcpy(e5->nom,"TUNIS");
e5->population=1056247;
e5->superficie=288;
e5->municip=8;
e5->naiss.jour=21;
e5->naiss.mois=06;
e5->naiss.annee=1956;


ELEMENT e6=elementCreer();
e6->n='G';
strcpy(e6->nom,"BEN AROUS");
e6->population=631842;
e6->superficie=761;
e6->municip=13;
e6->naiss.jour=3;
e6->naiss.mois=12;
e6->naiss.annee=1983;



ELEMENT e7=elementCreer();
e7->n='H';
strcpy(e7->nom,"NABEUL");
e7->population=787920;
e7->superficie=2840;
e7->municip=27;
e7->naiss.jour=21;
e7->naiss.mois=06;
e7->naiss.annee=1956;



ELEMENT e8=elementCreer();
e8->n='I';
strcpy(e8->nom,"ZAGHOUAN");
e8->population=787920;
e8->superficie=2820;
e8->municip=8;
e8->naiss.jour=01;
e8->naiss.mois=01;
e8->naiss.annee=1976;



ELEMENT e9=elementCreer();
e9->n='J';
strcpy(e9->nom,"SILIANA");
e9->population=223087;
e9->superficie=4642;
e9->municip=12;
e9->naiss.jour=05;
e9->naiss.mois=06;
e9->naiss.annee=1974;



ELEMENT e10=elementCreer();
e10->n='K';
strcpy(e10->nom,"KEF");
e10->population=243156;
e10->superficie=5081;
e10->municip=15;
e10->naiss.jour=21;
e10->naiss.mois=06;
e10->naiss.annee=1956;





ELEMENT e11=elementCreer();
e11->n='L';
strcpy(e11->nom,"KASSERINE");
e11->population=439243;
e11->superficie=8260;
e11->municip=19;
e11->naiss.jour=21;
e11->naiss.mois=06;
e11->naiss.annee=1956;



ELEMENT e12=elementCreer();
e12->n='M';
strcpy(e12->nom,"KAIROUAN");
e12->population=570559;
e12->superficie=6712;
e12->municip=19;
e12->naiss.jour=21;
e12->naiss.mois=06;
e12->naiss.annee=1956;



ELEMENT e13=elementCreer();
e13->n='N';
strcpy(e13->nom,"SOUSSE");
e13->population=674971;
e13->superficie=2669;
e13->municip=18;
e13->naiss.jour=21;
e13->naiss.mois=06;
e13->naiss.annee=1956;



ELEMENT e14=elementCreer();
e14->n='O';
strcpy(e14->nom,"MONASTIR");
e14->population=548828;
e14->superficie=1024;
e14->municip=31;
e14->naiss.jour=05;
e14->naiss.mois=06;
e14->naiss.annee=1974;



ELEMENT e15=elementCreer();
e15->n='P';
strcpy(e15->nom,"MAHDIA");
e15->population=410812;
e15->superficie=2878;
e15->municip=18;
e15->naiss.jour=05;
e15->naiss.mois=06;
e15->naiss.annee=1974;



ELEMENT e16=elementCreer();
e16->n='Q';
strcpy(e16->nom,"SFAX");
e16->population=955421;
e16->superficie=7545;
e16->municip=23;
e16->naiss.jour=21;
e16->naiss.mois=06;
e16->naiss.annee=1974;



ELEMENT e17=elementCreer();
e17->n='R';
strcpy(e17->nom,"GAFSA");
e17->population=337331;
e17->superficie=7807;
e17->municip=13;
e17->naiss.jour=21;
e17->naiss.mois=06;
e17->naiss.annee=1974;



ELEMENT e18=elementCreer();
e18->n='S';
strcpy(e18->nom,"SIDI BOUZID");
e18->population=429912;
e18->superficie=7400;
e18->municip=17;
e18->naiss.jour=01;
e18->naiss.mois=01;
e18->naiss.annee=1973;



ELEMENT e19=elementCreer();
e19->n='T';
strcpy(e19->nom,"TOZEUR");
e19->population=107912;
e19->superficie=5593;
e19->municip=6;
e19->naiss.jour=21;
e19->naiss.mois=06;
e19->naiss.annee=1956;



ELEMENT e20=elementCreer();
e20->n='U';
strcpy(e20->nom,"KEBILI");
e20->population=156961;
e20->superficie=22454;
e20->municip=8;
e20->naiss.jour=01;
e20->naiss.mois=01;
e20->naiss.annee=1981;


ELEMENT e21=elementCreer();
e21->n='V';
strcpy(e21->nom,"GABES");
e21->population=374300;
e21->superficie=7166;
e21->municip=16;
e21->naiss.jour=21;
e21->naiss.mois=06;
e21->naiss.annee=1956;



ELEMENT e22=elementCreer();
e22->n='W';
strcpy(e22->nom,"MEDENINE");
e22->population=479520;
e22->superficie=9167;
e22->municip=10;
e22->naiss.jour=21;
e22->naiss.mois=06;
e22->naiss.annee=1956;


ELEMENT e23=elementCreer();
e23->n='X';
strcpy(e23->nom,"TATAOUINE");
e23->population=149453;
e23->superficie=38889;
e23->municip=7;
e23->naiss.jour=02;
e23->naiss.mois=03;
e23->naiss.annee=1981;





addEdge(g, e0, e1, 105);
addEdge(g, e0, e4, 63);
addEdge(g, e0, e3, 63);
addEdge(g, e1, e4, 115);
addEdge(g, e1, e8, 131);
addEdge(g, e1, e9, 101);
addEdge(g, e1, e2, 49);
addEdge(g, e2, e9, 98);
addEdge(g, e2, e10, 50);
addEdge(g, e3, e4, 1);
addEdge(g, e3, e5, 1);
addEdge(g, e4, e8, 60);
addEdge(g, e4, e6, 14);
addEdge(g, e4, e5, 10);
addEdge(g, e5, e6, 14);
addEdge(g, e6, e8, 49);
addEdge(g, e6, e7, 60);
addEdge(g, e7, e8, 61);
addEdge(g, e7, e13, 102);
addEdge(g, e8, e13, 92);
addEdge(g, e8, e12, 103);
addEdge(g, e8, e9, 93);
addEdge(g, e9, e10, 73);
addEdge(g, e9, e11, 144);
addEdge(g, e9, e18, 147);
addEdge(g, e9, e12, 99);
addEdge(g, e10, e11, 130);
addEdge(g, e11, e18, 73);
addEdge(g, e11, e17, 111);
addEdge(g, e12, e15, 102);
addEdge(g, e12, e13, 56);
addEdge(g, e12, e18,111);
addEdge(g, e12, e16, 138);
addEdge(g, e13, e15, 59);
addEdge(g, e13, e14, 24);
addEdge(g, e14, e15, 43);
addEdge(g, e15, e16, 117);
addEdge(g, e16, e18, 136);
addEdge(g, e16, e17, 200);
addEdge(g, e16, e21, 137);
addEdge(g, e17, e18, 115);
addEdge(g, e17, e21, 156);
addEdge(g, e17, e20, 111);
addEdge(g, e17, e19, 93);
addEdge(g, e19, e20, 96);
addEdge(g, e20, e21, 118);
addEdge(g, e20, e22, 194);
addEdge(g, e20, e23, 233);
addEdge(g, e21, e22, 76);
addEdge(g, e22, e23, 52);

}
*/
