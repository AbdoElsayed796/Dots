#include<stdio.h>
#include "PrintGrid.h"
#include "Initialization.h"
#include "Modification.h"
int main ()
{
GameGridExpert S;
PrintGridExpert(&S);
ModificationExpert(&S,'n');
return 0;
}