#ifndef _DYN_ARRAY_
#define _DYN_ARRAY_

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
typedef void* Val_t;
typedef size_t Index_t;

typedef struct{
    Val_t _data;
    Index_t size;
    Index_t cap;
    Index_t elem_size;
} Dyn_array;

Dyn_array dyn_array_create(Index_t element_size);
void dyn_array_destroy(Dyn_array* da);
void dyn_array_push_back(Dyn_array* da, Val_t elem);
Val_t dyn_array_get(Dyn_array* const da, Index_t index);
void dyn_array_set(Dyn_array* da, Index_t index, Val_t elem);

#endif


#ifdef DYN_ARRAY_IMPL
#define INITIAL_CAP 5
#define GROWTH_FACTOR 2
 Dyn_array dyn_array_create(Index_t element_size){
    Dyn_array d =  {  ._data = (Val_t)malloc(element_size*INITIAL_CAP),
                        .size = 0,
                        .cap = INITIAL_CAP,
                        .elem_size = element_size};
    return d;
}
void dyn_array_destroy(Dyn_array* da){
    free(da->_data);
    da->size = 0;
    da->cap  = 0;
}
void dyn_array_push_back(Dyn_array* da, Val_t elem){
    if(!da->_data || da->cap==0 || da->cap<=da->size) {
        int newCap = da->cap==0?INITIAL_CAP:da->cap*GROWTH_FACTOR;
        Val_t newData = (Val_t)malloc(newCap*da->elem_size);
        memcpy(newData, da->_data, da->elem_size*da->size);
        free(da->_data);
        da->_data = newData;
        da->cap = newCap;
    }
    memcpy(((da->_data) + (da->size*da->elem_size)), elem, da->elem_size);
    da->size++;
    return;
}
Val_t dyn_array_get(Dyn_array* const da, Index_t index){
    if(!da->_data || index >= da->size) return NULL;
    
    return da->_data+index*da->elem_size;
    
}
void dyn_array_set(Dyn_array* da, Index_t index, Val_t elem){
    if(!da->_data || index >= da->size) return;
    memcpy(da->_data + index*da->elem_size, elem, da->elem_size); 
}


#endif
