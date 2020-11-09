#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

#pragma warning (disable : 4996)

const size_t NOT_EXISTING_VERTEX = -1;

enum STATUSES
{
    ZERO      = 0xFFFF8A,
    EMPTY     = 0xB3FFE5,
    NOT_EMPTY = 0xB0C4D4,
    ERROR     = 0xFF9494
};

enum ERRORS
{

};

struct Element
{
    double num = NAN;
    size_t prev = 0;
    size_t next = 0;
    size_t status = EMPTY;
};

struct List
{
    Element* elems = nullptr;
    size_t first = 0;
    size_t last  = 0;
    size_t size  = 0;
    size_t first_null = 0;
};

void ListConstructor (List* lst, size_t size);

void ListVerificate (List* lst);

void ListDestructor (List* lst);

void InsertBefore (List* lst, size_t el, double num);

void InsertAfter (List* lst, size_t el, double num);

void Delete (List* lst, size_t el);

void CreateDump (List* lst);
