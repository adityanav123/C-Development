//
//  main.h
//  Hashmap
//
//  Created by Aditya Navphule on 20/04/25.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define arr_size(x) sizeof(x)/sizeof(x[0])

typedef struct HASHNODE {
    int key;
    int value;
    struct HASHNODE *next; // chaining.
}hashnode, *pHashNode, **ppHashNode;

typedef struct HASHMAP {
    int buckets_cnt; // bucket size
    int count; // no of elements stored
    ppHashNode buckets;
}hashmap, *pHashMap;

// Methods
pHashMap init_hashmap(int sz);
int hash(pHashMap map, int value);
bool map_insert(pHashMap map, int key, int value);
bool map_get(pHashMap map, int key, int *value);
void map_free(pHashMap map);
bool map_remove(pHashMap map, int key);


// Test Methods
bool isArrayDistinct(int *arr, int arrSize);
