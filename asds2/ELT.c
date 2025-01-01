#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ELTPRIM.h"


ELEMENT elementCreer (void) {
    ELEMENT L;

    L = (ELEMENT) malloc(sizeof(gouvernorat));

    return L;

}

void elementDetruire (ELEMENT elt) {
    free (elt);
}

void elementLire(ELEMENT* elt) {

    printf(" Donnez un nom svp :\n") ;getchar();
    fgets((*elt)->nom, 20, stdin);

//    printf("donner sa population\n");
//    scanf("%ld",&((*elt)->population)) ;
//    printf("donner sa superficie\n");
//    scanf("%ld",&((*elt)->superficie));
//    printf("donner le nombre de ses municipalites\n");
//    scanf("%i",&((*elt)->municip));
//    printf("donner sa date de naissance\n");
//    scanf("%i ",&((*elt)->naiss.jour)); scanf("%i ",&((*elt)->naiss.mois));scanf("%i  ",&((*elt)->naiss.annee));
//
//




}

void elementAfficher(ELEMENT elt) {
    printf(" %s \t %ld \t %ld \t\t    %i \t\t %i/%i/%i",elt->nom,elt->population,elt->superficie,elt->municip,elt->naiss.jour,elt->naiss.mois,elt->naiss.annee);

}
void elementAfficher1(ELEMENT elt) {
    printf(" %s \t\t %ld \t %ld \t\t    %i \t\t %i/%i/%i",elt->nom,elt->population,elt->superficie,elt->municip,elt->naiss.jour,elt->naiss.mois,elt->naiss.annee);

}


void elementAffecter(ELEMENT* e1, ELEMENT e2) {
*e1 = e2 ;
}

void elementCopier(ELEMENT *e1, ELEMENT e2) {
*(*e1)=*e2;


}
int elementComparer(ELEMENT e1, ELEMENT e2) {
return (strcmp((e1->nom),(e2->nom))==0) ;
}


void element1lire(ELEMENT* elt){
printf("choose a character\n");
scanf("%c",&(*elt)->n);
}

