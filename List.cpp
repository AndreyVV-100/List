#include "List.h"

int main()
{
    List lst = {};
    ListConstructor (&lst, 10);

    InsertTail (&lst, 1);
    size_t el2 = InsertTail (&lst, 2);
    size_t el1 = InsertTail (&lst, 3);
    InsertBefore (&lst, el1, 2.5);
    Delete (&lst, el2);

    CreateDump (&lst);

    ListDestructor (&lst);

    return 0;
}

void ListConstructor (List* lst, const size_t size)
{
    assert (lst);
    assert (size);

    lst->sorted = 1;
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

size_t InsertEmpty (List* lst, double num)
{
    ass (lst);

    if (lst->head != NOT_EXISTING_VERTEX)
    {
        printf ("Call function InsertEmpty isn't justified");
        CreateDump (lst);
        ListDestructor (lst);
        exit (INSERT_EMPTY);
    }

    no_empty_elems;

    lst->head = lst->empty_1;
    lst->tail = lst->empty_1;
    empty_next;

    lst->elems[lst->head].num    = num;
    lst->elems[lst->head].status = TAIL_N_EMPTY;
    lst->elems[lst->head].next   = NOT_EXISTING_VERTEX;

    return lst->head;
}

size_t InsertHead (List* lst, double num)
{
    ass (lst);

    if (lst->head == NOT_EXISTING_VERTEX)
        return InsertEmpty (lst, num);

    no_empty_elems;

    size_t old_head = lst->head;
    lst->head = lst->empty_1;
    empty_next;

    lst->elems[lst->head].num = num;
    lst->elems[lst->head].status = HEAD_N_EMPTY;
    lst->elems[lst->head].next = old_head;

    lst->elems[old_head].prev = lst->head;
    if (old_head != lst->tail)
        lst->elems[old_head].status = N_EMPTY;

    lst->sorted = 0;
    return lst->head;
}

size_t InsertTail (List* lst, double num)
{
    ass (lst);

    if (lst->tail == NOT_EXISTING_VERTEX)
        return InsertEmpty (lst, num);

    no_empty_elems;

    size_t old_tail = lst->tail;
    lst->tail = lst->empty_1;
    empty_next;

    lst->elems[lst->tail].num    = num;
    lst->elems[lst->tail].status = TAIL_N_EMPTY;
    lst->elems[lst->tail].prev   = old_tail;
    lst->elems[lst->tail].next   = NOT_EXISTING_VERTEX;

    lst->elems[old_tail].next = lst->tail;
    if (old_tail == lst->head)
        lst->elems[old_tail].status = HEAD_N_EMPTY;
    else
        lst->elems[old_tail].status = N_EMPTY;

    return lst->tail;
}

size_t InsertBefore (List* lst, size_t el, double num)
{
    ass (lst);
    no_empty_elems;

    if (el == lst->head)
        return InsertHead (lst, num);

    return InsertAfter (lst, lst->elems[el].prev, num);
}

size_t InsertAfter (List* lst, size_t el, double num)
{
    ass (lst);
    no_empty_elems;

    if (el == lst->tail)
        return InsertTail (lst, num);

    size_t el_ins = lst->empty_1;
    empty_next;

    lst->elems[el_ins].next = lst->elems[el].next;
    lst->elems[el_ins].prev = el;

    lst->elems[el].next                      = el_ins;
    lst->elems[lst->elems[el_ins].next].prev = el_ins;

    lst->elems[el_ins].num    = num;
    lst->elems[el_ins].status = N_EMPTY;
    
    lst->sorted = 0;
    return el_ins;
}

void DeleteEmpty (List* lst)
{
    ass (lst);

    if (lst->head == NOT_EXISTING_VERTEX ||
        lst->head != NOT_EXISTING_VERTEX &&
        lst->head != lst->tail)
    {
        printf ("Call function DeleteEmpty isn't justified");
        CreateDump (lst);
        ListDestructor (lst);
        exit (DELETE_EMPTY);
    }

    do_empty (lst->head);

    lst->empty_1 = lst->head;
    lst->head    = NOT_EXISTING_VERTEX;
    lst->tail    = NOT_EXISTING_VERTEX;

    Sort (lst);
    return;
}

void DeleteHead (List* lst)
{
    ass (lst);

    if (lst->head == NOT_EXISTING_VERTEX)
        return;

    if (lst->head == lst->tail)
        DeleteEmpty (lst);

    size_t new_head = lst->elems[lst->head].next;

    do_empty (lst->head);

    lst->head = new_head;
    lst->elems[lst->head].prev = NOT_EXISTING_VERTEX;

    if (lst->elems[lst->head].status != TAIL_N_EMPTY)
        lst->elems[lst->head].status = HEAD_N_EMPTY;

    lst->sorted = 0;
    return;
}

void DeleteTail (List* lst)
{
    ass (lst);

    if (lst->tail == NOT_EXISTING_VERTEX)
        return;

    if (lst->head == lst->tail)
        return DeleteEmpty (lst);

    size_t new_tail = lst->elems[lst->tail].prev;

    do_empty (lst->tail);
    lst->elems[lst->tail].prev = NOT_EXISTING_VERTEX;

    lst->tail = new_tail;
    lst->elems[lst->tail].next = NOT_EXISTING_VERTEX;
    lst->elems[lst->tail].status = TAIL_N_EMPTY;

    return;
}

void Delete (List* lst, size_t el)
{
    ass (lst);

    if (el == lst->head)
        return DeleteHead (lst);

    if (el == lst->tail)
        return DeleteTail (lst);

    lst->elems[lst->elems[el].next].prev = lst->elems[el].prev;
    lst->elems[lst->elems[el].prev].next = lst->elems[el].next;
    
    do_empty (el);
    lst->elems[el].prev = NOT_EXISTING_VERTEX;
    lst->sorted = 0;
    return;
}

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
                                 label = \"             \
                                    <prev> Prev:   %u | \
                                           Element %u | \
                                           Value: %lf | \
                                    <next> Next:   %u\"];\n",
                i_list, 
                lst->elems[i_list].status,
                lst->elems[i_list].prev,
                i_list, 
                lst->elems[i_list].num,
                lst->elems[i_list].next);
    }
    
    for (size_t i_list = 0; i_list < lst->size - 1; i_list++)
        fprintf (graph, "unit%u -> unit%u [color = \"white\" truecolor = true];\n", 
                 i_list, i_list + 1);

    for (size_t i_list = 0; i_list < lst->size; i_list++)
    {
        if (lst->elems[i_list].prev < NOT_EXISTING_VERTEX)
            fprintf (graph, "unit%u:<prev> -> unit%u [color = \"darkgray\" constraint = false];\n", 
                    i_list, lst->elems[i_list].prev);
        if (lst->elems[i_list].next < NOT_EXISTING_VERTEX)
            fprintf (graph, "unit%u:<next> -> unit%u [color = \"blue\" constraint = false];\n", 
                    i_list, lst->elems[i_list].next);
    }

    fprintf (graph, "}");
    fclose (graph);
    
    system ("dot -Tpng Graph\\out.dot -o Graph\\gr.png");
    system ("start Graph\\gr.png");

    return;
}

void Sort (List* lst)
{
    ass (lst);

    Element* new_elems = (Element*) calloc (lst->size, sizeof (*new_elems));

    size_t i_elem = 0;
    size_t elem_old = lst->head;
    for (i_elem = 0; i_elem < lst->size && elem_old != NOT_EXISTING_VERTEX; i_elem++)
    {
        new_elems[i_elem] = lst->elems[elem_old];
        new_elems[i_elem].prev = i_elem - 1;
        new_elems[i_elem].next = i_elem + 1;
        elem_old = lst->elems[elem_old].next;
    }

    new_elems[0].prev          = NOT_EXISTING_VERTEX;
    new_elems[i_elem - 1].next = NOT_EXISTING_VERTEX;

    size_t start_empty = i_elem;

    for (i_elem; i_elem < lst->size; i_elem++)
        new_elems[i_elem] = { NAN, NOT_EXISTING_VERTEX, i_elem + 1, EMPTY };

    new_elems[start_empty].status = HEAD_EMPTY;
    new_elems[i_elem - 1].status  = TAIL_EMPTY;

    free (lst->elems);
    lst->elems = new_elems;
    lst->sorted = 1;
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
