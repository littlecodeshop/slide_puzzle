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


/**
 *
 * List generique en C
 *
 */

struct _node
{
    struct _node * next;    //pointeur sur le prochain element
    void * data;            //pointeur sur l'element 
};

typedef struct _list
{
    struct _node * head;    //pointer to first element
} list;

list * list_init()
{
    list * l = (list *)malloc(sizeof(list));
    l->head = NULL;
    return l;
}

int list_is_empty(list *l)
{
    return ((l->head) == NULL);
}

/**
 * 
 * Add an element at the end of the list (list must NOT be null)
 * 
 */

void list_add_element(list * l,void * element)
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


struct _node * list_last_node(list * l)
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

void * list_pop_last_element(list * l){
    struct _node * node = list_last_node(l);
    return node->data;
}

void * list_last_element(list *l){
    struct _node ** address_ptr = &(l->head);
    struct _node ** address_previous = NULL;

    struct _node * ret= NULL;

    while((*address_ptr)!=NULL){
        address_previous = address_ptr;
        address_ptr = &((*address_ptr)->next);
    }

    if(address_previous!=NULL){

        ret = *address_previous;
    }



    return ((struct _node*)ret)->data;

}
/**
 * 
 *  Remove the first element from a list
 * 
 */

struct _node * list_remove_first(list * l)
{
    struct _node * ptr_node = l->head;
    if(l->head !=NULL){
        l->head = l->head->next; 
        free(ptr_node);
    }
    return ptr_node;
}

/**
 * 
 * print the list to help debug
 * 
 */

char * charstar_format(struct _node * n)
{
    //si c'est une liste de char* on a rien a faire
    return n->data;
}

void list_dump(list * l,char * (*format)(struct _node *))
{
    struct _node * n = l->head;
    while(n!=NULL){
        printf("==> %s\n",format(n));
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

void list_dump_slide(list * l)
{
    struct _node * n = l->head;
    while(n!=NULL){
        slide_dump(n->data);
        printf("\n");
        n=n->next;
    }
}
void list_dump_int(list * l)
{
    printf("***** DUMPING INTS ******\n"); 
    struct _node * n = l->head;
    while(n!=NULL){
        printf("==> %d\n",*((int*)(n->data)));
        n=n->next;
    }
}


/**
 * Generates a list containing the list of successors
 * from the passed position
 */

list * slide_successors(char * position)
{

    list * l = list_init();

    //find the position of 0 
    int i,index = 0;
    while(position[index]!='0'){
        index++;
    }

    //index a la position 
    int cnt = possible_moves[index][0];
    for(i = 1;i<=cnt;i++){
        int spot = possible_moves[index][i];
        char * new_position = strdup(position);
        //je swappe la position vide avec le spot
        new_position[index] = new_position[spot];
        new_position[spot] = '0'; 
        list_add_element(l,new_position);
    }

    return l;
}

int list_contains(list * l, void * elem){

    int ret = 0; 
    struct _node * n = l->head;

    while(n!=NULL){
        
        if(strcmp(elem,n->data)==0){
            return 1;
        }
        n=n->next;
    }
    return ret;
}

list* list_copy(list *l){
    list *tmp = list_init();
    struct _node * n = l->head;

    while(n!=NULL){
        list_add_element(tmp,n->data);
        n=n->next;
    }

    return tmp;

}

void slide_search(char * start, char * goal, list *(*successors)(char *)){

    char c;
    list * closed_set = list_init();
    list * open_set = list_init();
    list * path = list_init();


    list_add_element(path,start);
    list_add_element(open_set,path);

    while(1){ //do until the end ?? what is the end ??


        //list * candidate_path  = (list*)(list_last_node(open_set)->data);
        list * candidate_path  = (list*)(list_remove_first(open_set)->data);
        char * last_state = (char*)list_last_element(candidate_path);
        list_add_element(closed_set,last_state);
        list_dump(closed_set,charstar_format);

        if(strcmp(last_state,goal)==0)
        {
            printf("FOUND :) !!!\n");
            list_dump_slide(candidate_path);
            return;
        }

        list * game_successors = slide_successors(last_state);

        //create the new candidate paths
        while(!list_is_empty(game_successors)){
            //create a new list

            list * new_path = list_copy(candidate_path);
            char * next_one = list_pop_last_element(game_successors);
            if(!list_contains(closed_set,next_one)){
                if(strcmp(next_one,"012345678")==0)
                    printf("ADDING A SOLUTION");
                list_add_element(new_path,next_one);
                list_add_element(open_set,new_path);
                //list_dump_slide(new_path);
            }

        }

    }
}

int main ()
{


    slide_search("740132685","012345678",slide_successors);

    return 0;
}

