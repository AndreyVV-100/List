#include "List.h"

int main()
{
    List lst = {};
    ListConstructor (&lst, 10);
    lst.elems[1].status = ERROR;
    CreateDump (&lst);
    ListDestructor (&lst);

    return 0;
}

void ListConstructor (List* lst, const size_t size)
{
    assert (lst);
    assert (size);

    lst->size = size;
    lst->elems = (Element*) calloc (size, sizeof (Element));
    assert (lst->elems);

    lst->first      = 0;
    lst->first_null = 1;
    lst->last       = 0;
    
    lst->elems[0].next   = 0;
    lst->elems[0].prev   = 0;
    lst->elems[0].num    = NAN;
    lst->elems[0].status = ZERO;

    for (size_t i_elem = 1; i_elem < size; i_elem++)
    {
        lst->elems[i_elem].next   = i_elem + 1;
        lst->elems[i_elem].prev   = NOT_EXISTING_VERTEX;
        lst->elems[i_elem].num    = NAN;
        lst->elems[i_elem].status = EMPTY;
    }
    lst->elems[size - 1].next = NOT_EXISTING_VERTEX;

    return;
}

void ListVerificate (List* lst)
{
    assert (lst);

    return;
}

void ListDestructor (List* lst)
{
    assert (lst);
    
    free (lst->elems);
    lst->elems = nullptr;
    
    lst->first      = 0;
    lst->first_null = 0;
    lst->last       = 0;
    lst->size       = 0;

    return;
}

void InsertBefore (List* lst, size_t el, double num, size_t )
{
    
}

void InsertAfter (List* lst, size_t el, double num);

void Delete (List* lst, size_t el);

void CreateDump (List* lst)
{
    //ToDo: sprintf
    FILE* graph = fopen ("Graph/out.dot", "w");
    
    fprintf (graph, "digraph G{\n" "rankdir = LR;\n");

    for (size_t i_list = 0; i_list < lst->size; i_list++)
    {
        fprintf (graph, "unit%u [style=\"filled\",      \
                                 fillcolor = \"#%X\"    \
                                 shape = record,        \
                                 label = \"number: %u | \
                                           value: %lf | \
                                    <prev> prev:   %u | \
                                    <next> next:   %u\"];\n",
                i_list, 
                lst->elems[i_list].status, 
                i_list, 
                lst->elems[i_list].num,
                lst->elems[i_list].prev,
                lst->elems[i_list].next);
    }

    for (size_t i_list = 0; i_list < lst->size; i_list++)
    {
        if (lst->elems[i_list].prev < NOT_EXISTING_VERTEX)
            fprintf (graph, "unit%u:<prev> -> unit%u;\n", i_list, lst->elems[i_list].prev);
        if (lst->elems[i_list].next < NOT_EXISTING_VERTEX)
            fprintf (graph, "unit%u:<next> -> unit%u;\n", i_list, lst->elems[i_list].next);
    }

    fprintf (graph, "}");
    fclose (graph);
    
    system ("dot -Tpng Graph\\out.dot -o Graph\\gr.png");
    system ("start Graph\\gr.png");

    return;
}
