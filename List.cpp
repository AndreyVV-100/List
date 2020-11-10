#include "List.h"

int main()
{
    List lst = {};
    ListConstructor (&lst, 10);
    printf ("%d", ListVerificate (&lst));
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

    lst->head    = NOT_EXISTING_VERTEX;
    lst->empty_1 = 0;
    lst->tail    = NOT_EXISTING_VERTEX;

    for (size_t i_elem = 1; i_elem < size - 1; i_elem++)
        lst->elems[i_elem] = { NAN, NOT_EXISTING_VERTEX, i_elem + 1, EMPTY };

    lst->elems[0]      = { NAN, NOT_EXISTING_VERTEX,                   1, HEAD_EMPTY };
    lst->elems[size-1] = { NAN, NOT_EXISTING_VERTEX, NOT_EXISTING_VERTEX, TAIL_EMPTY };

    return;
}

DUMP ListVerificate (List* lst)
{
    if (lst == nullptr)
        return LST_NULL;
    if (lst->elems == nullptr)
        return ELEMS_NULL;
    
    return ElementsVerificate (lst);
}

DUMP ElementsVerificate (List* lst)
{
    assert (lst);
    assert (lst->elems);

    if (lst->size == NOT_EXISTING_VERTEX)
        return BAD_SIZE;
    
    // if (lst->head >= lst->size && lst->head != NOT_EXISTING_VERTEX || ect.)

    if (lst->head + 1 > lst->size                     ||
        lst->head < lst->size                         &&
       (lst->elems[lst->head].status != HEAD_N_EMPTY  &&
        lst->elems[lst->head].status != TAIL_N_EMPTY  ||
        lst->tail == NOT_EXISTING_VERTEX))
            return BAD_HEAD;

    if (lst->tail + 1 > lst->size                       ||
        lst->tail < lst->size                           && 
       (lst->elems[lst->tail].status != TAIL_N_EMPTY    ||
        lst->head == NOT_EXISTING_VERTEX))
            return BAD_TAIL;

    if (lst->empty_1 + 1 > lst->size                    ||
        lst->empty_1 < lst->size                        &&
        lst->elems[lst->empty_1].status != HEAD_EMPTY   &&
        lst->elems[lst->empty_1].status != TAIL_EMPTY)
            return BAD_EMPTY_1;

    DUMP err = OK;

    for (size_t i_elem = 0; i_elem < lst->size; i_elem++)
    {
        switch (lst->elems[i_elem].status)
        {
            case EMPTY:
            case HEAD_EMPTY:
            case TAIL_EMPTY:
                if (lst->elems[i_elem].prev != NOT_EXISTING_VERTEX ||
                    lst->elems[i_elem].next + 1 > lst->size)
                    {
                        err = BAD_ELEMS;
                        lst->elems[i_elem].status = ERROR;
                    }
                break;

            case N_EMPTY:
                if (lst->elems[i_elem].prev >= lst->size ||
                    lst->elems[i_elem].next >= lst->size ||
                    isnan (lst->elems[i_elem].num))
                    {
                        err = BAD_ELEMS;
                        lst->elems[i_elem].status = ERROR;
                    }
                break;

            case HEAD_N_EMPTY:
                if (lst->head != i_elem                            ||
                    lst->elems[i_elem].prev != NOT_EXISTING_VERTEX ||
                    lst->elems[i_elem].next + 1> lst->size         ||
                    isnan (lst->elems[i_elem].num))
                    {
                        err = BAD_ELEMS;
                        lst->elems[i_elem].status = ERROR;
                    }
                break;

            case TAIL_N_EMPTY:
                if (lst->tail != i_elem ||
                    lst->elems[i_elem].next != NOT_EXISTING_VERTEX ||
                    lst->elems[i_elem].prev + 1 > lst->size        ||
                    isnan (lst->elems[i_elem].num))
                    {
                        err = BAD_ELEMS;
                        lst->elems[i_elem].status = ERROR;
                    }
                break;
        }
    }

    // Passing

    if (err != OK)
        return err;

    size_t passed_elems = 0;
    
    if (lst->head != NOT_EXISTING_VERTEX)
    {
        size_t next = lst->elems[lst->head].next;
        passed_elems++;

        while (passed_elems < lst->size && next != NOT_EXISTING_VERTEX)
        {
            if (lst->elems[lst->elems[next].prev].next != next)
                err = PASS_FAILED;
            next = lst->elems[next].next;
            passed_elems++;
        }
    }

    if (lst->empty_1 != NOT_EXISTING_VERTEX)
    {
        if (lst->elems[lst->empty_1].prev != NOT_EXISTING_VERTEX)
        {
            err = PASS_FAILED;
            lst->elems[lst->empty_1].status = ERROR;
        }

        size_t next = lst->elems[lst->empty_1].next;
        passed_elems++;

        while (passed_elems < lst->size && next != NOT_EXISTING_VERTEX)
        {
            if (lst->elems[next].prev != NOT_EXISTING_VERTEX)
            {
                err = PASS_FAILED;
                lst->elems[next].status = ERROR;
            }
            next = lst->elems[next].next;
            passed_elems++;
        }
    }

    if (passed_elems != lst->size)
        err = PASS_FAILED;

    return err;
}

void ListDestructor (List* lst)
{
    assert (lst);
    
    free (lst->elems);
    lst->elems = nullptr;
    
    lst->head       = 0;
    lst->empty_1    = 0;
    lst->tail       = 0;
    lst->size       = 0;

    return;
}

void InsertAllEmpty (List* lst, double num)
{
    ass (lst);

    if (lst->head != NOT_EXISTING_VERTEX)
    {
        printf ("Call function InsertAllEmpty isn't justified");
        exit (INSERT_EMPTY);
    }

    no_empty_elems;

    lst->head = lst->empty_1;
    lst->tail = lst->empty_1;
    lst->empty_1 = lst->elems[lst->empty_1].next;

    lst->elems[lst->head].num = num;
    lst->elems[lst->head].status = TAIL_N_EMPTY;

    ass (lst);
    return;
}

void InsertHead (List* lst, double num)
{
    ass (lst);

    if (lst->head == NOT_EXISTING_VERTEX)
    {
        InsertAllEmpty (lst, num);
        return;
    }
}

void InsertTail (List* lst, double num);

void InsertBefore (List* lst, size_t el, double num);

void InsertAfter (List* lst, size_t el, double num);

void DeleteHead (List* lst);

void DeleteTail (List* lst);

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

void TestColors()
{
    const size_t COLORS = 6;
    List lst = {};

    ListConstructor (&lst, COLORS);

    lst.elems[0].status = EMPTY;
    lst.elems[1].status = HEAD_EMPTY;
    lst.elems[2].status = N_EMPTY;
    lst.elems[3].status = HEAD_N_EMPTY;
    lst.elems[4].status = TAIL_N_EMPTY;
    lst.elems[5].status = ERROR;

    CreateDump (&lst);
    ListDestructor (&lst);
    return;
}
