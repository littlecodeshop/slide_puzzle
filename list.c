//compile with gcc main.c
//run with ./a.out

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    struct _node  *n = (struct _node*)(&(l->head));
    struct _node * new_node = (struct _node*)malloc(sizeof(struct _node));
    new_node->data = element;
    new_node->next = NULL;


    while(n->next!=NULL){
        n=n->next;
    }

    n->next = new_node;
}

/**
 * 
 *  Remove the last element from a list
 * 
 */

struct _node * list_remove_last(list * l)
{

    struct _node ** address_ptr = &(l->head);
    struct _node ** address_previous = NULL;

    struct _node * ret= NULL;

    while((*address_ptr)!=NULL){
        address_previous = address_ptr;
        address_ptr = &((*address_ptr)->next);
    }

    if(address_previous!=NULL){

        //free(*address_previous);
        ret = *address_previous;
        *address_previous = NULL;
    }

    return ret;
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

/**
 * Generates a list containing the list of successors
 * from the passed position
 */

list * slide_successors(char * position)
{

    list * l = (list*)malloc(sizeof(list));
    list_init(l);

    //find the position of 0 
    int i,index = 0;
    while(position[index]!='0'){
        index++;
    }

    //index a la position 
    int cnt = possible_moves[index][0];
    printf("CNT : %d\n",cnt);
    for(i = 1;i<=cnt;i++){
        printf("MOVE %d\n",possible_moves[index][i]);
        int spot = possible_moves[index][i];
        char * new_position = strdup(position);
        //je swappe la position vide avec le spot
        new_position[index] = new_position[spot];
        new_position[spot] = '0'; 
        list_add_element(l,new_position);
        slide_dump(new_position);
    }

    return l;
}

int list_contains(list * l, char * elem){

    int ret = 0; 
    struct _node * n = l->head;

    while(n!=NULL){
        if(strcmp(elem,n->data)==0)
            return 1;
        n=n->next;
    }
    return ret;
}

void slide_search(list * openset, list *closedset, char * goal){

   //Generic search :
   //pop last element and add the successors
   struct _node * candidate = list_remove_last(openset);
   if(0==strcmp(goal,candidate->data)){
       //We found a goal !
       //return the complete path to get there !
       printf("REACHED GOAL\n");
       return;
   }

   
   list_add_element(closedset,candidate->data);

   list * l = slide_successors(candidate->data);



}

int main ()
{

  list *openset=(list*)malloc(sizeof(list));
  list *closedset=(list*)malloc(sizeof(list));
  
  
  list_init(openset);
  list_init(closedset);

  list_add_element(openset,"hello");
  list_add_element(openset,"world");
  list_add_element(openset,"again");

  printf("contains hello : %d\n",list_contains(openset,"hello"));
  printf("contains again : %d\n",list_contains(openset,"again"));
  printf("contains GOGO : %d\n",list_contains(openset,"GOGO"));




  list_add_element(openset,"102345678");

  //launch a search 
  slide_search(openset,closedset,"012345678");
  
  return 0;
}
 
