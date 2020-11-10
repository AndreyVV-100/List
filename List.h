#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

#pragma warning (disable : 4996)

#define ass(lst)    {DUMP check = ListVerificate (lst);     \
                    if (check != OK)                        \
                    {                                       \
                        printf ("Something went wrong... "  \
                                "Error number = %d", check);\
                        CreateDump (lst);                   \
                        ListDestructor (lst);               \
                        exit (check);                       \
                    }}

#define no_empty_elems  if (lst->empty_1 == NOT_EXISTING_VERTEX)            \
                        {                                                   \
                            printf ("Can`t insert the number: no place.");  \
                            CreateDump (lst);                               \
                            ListDestructor (lst);                           \
                            exit (INSERT_FULL);                             \
                        }

#define empty_next  lst->empty_1 = lst->elems[lst->empty_1].next;                       \
                    if (lst->empty_1 != NOT_EXISTING_VERTEX)                            \
                    {                                                                   \
                        lst->elems[lst->empty_1].status =                               \
                            (lst->elems[lst->empty_1].next == NOT_EXISTING_VERTEX) ?    \
                            TAIL_EMPTY : HEAD_EMPTY;                                    \
                    }

#define ins_del_check

const size_t NOT_EXISTING_VERTEX = -1;

enum STATUSES
{
    EMPTY           = 0xCCFFCC,
    HEAD_EMPTY      = 0x66FF66,
    TAIL_EMPTY      = 0xB2FF66,
    N_EMPTY         = 0xCCE5FF,
    HEAD_N_EMPTY    = 0xB266FF,
    TAIL_N_EMPTY    = 0x66B2FF,
    ERROR           = 0xFF9494
};

enum DUMP
{
    // List
    OK              = 0,
    LST_NULL        = 1,
    ELEMS_NULL      = 2,

    // Elements
    BAD_HEAD        = 3,
    BAD_TAIL        = 4,
    BAD_EMPTY_1     = 5,
    BAD_SIZE        = 6,
    BAD_ELEMS       = 7,
    PASS_FAILED     = 8,

    //Functions
    INSERT_EMPTY    = 9,
    INSERT_FULL     = 10
};

struct Element
{
    double num = NAN;
    size_t prev = 0;
    size_t next = 0;
    STATUSES status = EMPTY;
};

struct List
{
    Element* elems = nullptr;
    size_t head    = 0;
    size_t tail    = 0;
    size_t size    = 0;
    size_t empty_1 = 0;
};

void ListConstructor (List* lst, size_t size);

DUMP ListVerificate (List* lst);

DUMP ElementsVerificate (List* lst);

void ListDestructor (List* lst);

void InsertAllEmpty (List* lst, double num);

void InsertHead (List* lst, double num);

void InsertTail (List* lst, double num);

void InsertHead (List lst, double num);

void InsertTail (List lst, double num);

void InsertBefore (List* lst, size_t el, double num);

void InsertAfter (List* lst, size_t el, double num);

void Delete (List* lst, size_t el);

void CreateDump (List* lst);

void TestColors();
