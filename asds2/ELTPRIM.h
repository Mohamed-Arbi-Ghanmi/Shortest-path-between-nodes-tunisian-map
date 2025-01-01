#ifndef ELTPRIM_H_INCLUDED
#define ELTPRIM_H_INCLUDED
#include "ELTSDD.h"
void elementLire(ELEMENT *);
void elementAfficher(ELEMENT);
void elementAffecter(ELEMENT*, ELEMENT);

void elementCopier(ELEMENT *, ELEMENT) ;

int elementComparer(ELEMENT, ELEMENT);
ELEMENT elementCreer(void) ;
void elementDetruire (ELEMENT);

#endif
