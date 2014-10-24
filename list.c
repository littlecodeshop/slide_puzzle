//compile with gcc main.c
//run with ./a.out

#include <stdio.h>
#include <stdlib.h>

//012
//345
//678
int possible_moves[][9] = {
  {2,1,3},      //0
  {3,0,2,4},    //1
  {2,1,5},      //2
  {3,0,4,6},    //3
  {4,1,3,5,7},  //4
  {3,2,4,8},    //5
  {2,3,7},      //6
  {3,6,4,8},    //7
  {2,5,7}       //8
  }; 


struct _node
{
  struct _node * next;
  char * data; 
};

typedef struct _list
{
struct _node * head;
} list;

void list_init(list * l)
{
  l->head = NULL;
}

/**
 * 
 * Add an element at the end of the list (list must NOT be null)
 * 
 */
 
void list_add_element(list * l,char * element)
{
  struct _node  *n = l->head;
  struct _node * new_node = (struct _node*)malloc(sizeof(struct _node));
  new_node->data = element;
  new_node->next = NULL;

  //TODO : avoid this test ??
  if(l->head == NULL){
      l->head = new_node;
      return;
  }

  while(n->next!=NULL){
    printf("skipping ... %s\n",n->data);
    n=n->next;
  }
 
  n->next = new_node;
}

/**
 * 
 *  Remove the last element from a list
 * 
 */

void list_remove_last(list * l)
{

    struct _node ** address_ptr = &(l->head);
    struct _node ** address_previous = NULL;

    while((*address_ptr)!=NULL){
        printf("SKIPPING %s\n",(*address_ptr)->data);
        address_previous = address_ptr;
        address_ptr = &((*address_ptr)->next);
        printf("ADDRESS : %ld\n",address_ptr);
    }

    if(address_previous!=NULL){
        free(*address_previous);
        *address_previous = NULL;
    }
}


/**
 * 
 *  Remove the first element from a list
 * 
 */

void list_remove_first(list * l)
{
    struct _node * ptr_node = l->head;
    if(l->head !=NULL){
        l->head = l->head->next; 
        free(ptr_node);
    }
}

/**
 * 
 * print the list to help debug
 * 
 */
 
void list_dump(list * l)
{
    printf("***** DUMPING ******\n"); 
  struct _node * n = l->head;
  while(n!=NULL){
    printf("==> %s\n",n->data);
    n=n->next;
  }
}


void slide_dump(char * position)
{
    int i,j;
    for(j=0;j<3;j++){
        printf("|");
        for(i=0;i<3;i++){
            printf("%c|",position[i+(j*3)]);
        }
        printf("\n");
    }

}

int main ()
{
  list *l=(list*)malloc(sizeof(list));
  
  
  list_init(l);
  list_add_element(l,"Hello");
  list_add_element(l,"wold");
  list_add_element(l,"!");
  list_dump(l);
  list_remove_last(l);
  list_dump(l);
  list_remove_last(l);
  list_dump(l);
  list_remove_last(l);
  list_dump(l);
  list_remove_last(l);
  list_dump(l);
  list_add_element(l,"ALL");
  list_add_element(l,"YOUR");
  list_add_element(l,"BASES!");
  list_dump(l);
  list_remove_first(l);
  list_dump(l);
  list_remove_first(l);
  list_dump(l);
  list_remove_first(l);
  list_dump(l);
  list_remove_first(l);
  list_dump(l);
  
  slide_dump("012345678");
  return 0;
}
 
