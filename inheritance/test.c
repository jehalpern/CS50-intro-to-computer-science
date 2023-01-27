#include <stdio.h>
#include <stdlib.h>



typedef struct person
{
    int number;
    struct person *parents[2];
}
person;

int main(void)
{

//created new list called new
person *new = NULL;

//in a buffer, allocate memory and assign pointer to that memory
person *n = malloc(sizeof(person));

//assign values to the fist node of the list including a value, creating two pointers to null nodes
//lastly, assigning all the data of node from buffer to original pointer
n->number = 4;
n->parents[0] = NULL;
n->parents[1] = NULL;
new = n;

//allocate more memory to create next node
n = malloc(sizeof(person));

//add values to new node
//lastly assign the new node to the parent[0] pointer belonging to the previous node (node value 4)
n->number = 3;
n->parents[0] = new;
n->parents[1] = NULL;
new = n;


printf("%i\n", new->number);
printf("%i\n", new->parents[0]->number);

free(n);

}


