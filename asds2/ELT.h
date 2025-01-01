#ifndef ELT_H_INCLUDED
#define ELT_H_INCLUDED
typedef struct{
int jour;
int mois;
int annee;}date;

typedef struct{
char nom[20];
long population;
long superficie;
int municip;
date naiss;
char n;

}gouvernorat,*ELEMENT;


#endif // ELT_H_INCLUDED
