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
    int sz;                 //size of an element in bytes
} list;

list * list_init(int sz)
{
    list * l = (list *)malloc(sizeof(list));
    l->head = NULL;
    l->sz = sz;
    return l;
}

/**
 * 
 * Add an element at the end of the list (list must NOT be null)
 * 
 */

void list_add_element(list * l,unsigned char * element)
{
    struct _node  *n = (struct _node*)(&(l->head));
    struct _node * new_node = (struct _node*)malloc(sizeof(struct _node));
    
    
    new_node->data = malloc(l->sz); //on doit copier la memoire 
    //copy the memory from element into data
    memcpy(new_node->data,element,l->sz);

    
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

char * charstar_format(struct _node * n)
{
    //si c'est une liste de char* on a rien a faire
    return n->data;
}

void list_dump(list * l,char * (*format)(struct _node *))
{
    printf("***** DUMPING GENERIC ******\n"); 
    struct _node * n = l->head;
    while(n!=NULL){
        printf("==> %s\n",format(n));
        n=n->next;
    }
}

void list_dump_int(list * l)
{
    printf("***** DUMPING INTS ******\n"); 
    struct _node * n = l->head;
    while(n!=NULL){
        int dt = 
        printf("==> %d\n",*((int*)(n->data)));
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

void slide_search(char * start, char * goal, list *(*successors)(char *)){
}

int main ()
{

    int a = 1975;
    int b = 15;
    int c = 2;
    //make a list of ints
    list *list_int = list_init(sizeof(int));
    list_add_element(list_int,&a);
    list_add_element(list_int,&b);
    list_add_element(list_int,&c);

    //list of chars
    list *path1 = list_init(sizeof(char*));
    list *path2 = list_init(sizeof(char*));


    //list of lists
    list * paths = list_init(sizeof(list*));

    list_add_element(path1,"012345678");
    list_add_element(path1,"102345678");
    list_add_element(path1,"120345678");

    list_add_element(path2,"ABCDEFGHI");
    list_add_element(path2,"BACDEFGHI");
    list_add_element(path2,"CABDEFGHI");
    
    list_add_element(paths,path1);
    list_add_element(paths,path2);


    list_dump(path1,charstar_format);
    list_dump(path2,charstar_format);

    list_dump_int(list_int);



    return 0;
}

