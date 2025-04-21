#include "main.h"

pHashMap init_hashmap(int sz) {
    pHashMap map = (pHashMap)malloc(sizeof(hashmap));
    if (map == NULL) {
        perror("hashmap.memalloc : failed\n");
        return NULL;
    }

    map->buckets_cnt = sz;
    map->count = 0;
    map->buckets = (ppHashNode)calloc(sz, sizeof(pHashNode));
    
    if (map->buckets == NULL)
    {
        perror("hashmap.buckets.memalloc : failed\n");
        free(map);
        return NULL;
    }

    return map;
}

// Hash Function
// Temporary
int hash(pHashMap map, int value) {
    const int _HIGH_PRIME = 131807699;
    return abs(value) % map->buckets_cnt;
}

bool map_insert(pHashMap map, int key, int value) {
    int hKey = hash(map, key);
    
    // check if already present
    pHashNode curr_node = map->buckets[hKey];
    while (curr_node != NULL) {
        if (curr_node->key == key) {
            curr_node->value = value; // update value
            return true;
        }
        curr_node = curr_node->next;
    }
    
    // if not present
    pHashNode newNode = (pHashNode)malloc(sizeof(hashnode));
    if (newNode == NULL) {
        perror("map.newnode.memalloc : failed\n");
        return false;
    }
    
    newNode->key = key;
    newNode->value = value;
    newNode->next = map->buckets[hKey]; // inserting at the end.
    map->buckets[hKey] = newNode;
    map->count++; // total_elments++;

    return true;
}


// Get Value
bool map_get(pHashMap map, int key, int *value) {
    int hKey = hash(map, key);
    
    pHashNode currNode = map->buckets[hKey];
    while (currNode != NULL) {
        if (currNode->key == key) {
            if (value != NULL) {
                *value = currNode->value;
            }
            return true;
        }
        currNode = currNode->next;
    }
    return false;
}

bool map_remove(pHashMap map, int key) {
    int hKey = hash(map, key);
    pHashNode currNode = map->buckets[hKey];
    pHashNode prev = NULL;
    
    while (currNode != NULL) {
        if (currNode->key == key) {
            if (prev != NULL) {
                prev->next = currNode->next;
            } else {
                // starting node
                map->buckets[hKey] = currNode->next;
            }
            free(currNode);
            map->count--;
            return true;
        }
        currNode = currNode->next;
    }
    // element not present
    return false;
}


void map_free(pHashMap map) {
    if (map == NULL) return;
    
    // empty each bucket
    for (size_t i = 0; i < map->buckets_cnt; ++i) {
        pHashNode currNode = map->buckets[i];
        while (currNode != NULL) {
            pHashNode toDelete = currNode;
            currNode = currNode->next;
            free(toDelete);
        }
    }
    free(map->buckets);
    free(map);
}


bool isArrayDistinct(int *arr, int arrSize) {
    pHashMap map = init_hashmap(1024); // no of buckets = 1024
    if (map == NULL) {
        return false;
    }
    
    bool distinct = true;
    for (size_t i = 0; i < arrSize; ++i) {
        if (map_get(map, arr[i], NULL)) {
            distinct = false;
            break;
        }
        map_insert(map, arr[i], 1);
    }
    return distinct;
}


int main(void) {
    int arr[] = {4, 1, 9, 6, 2, 2};
    int arrSize = arr_size(arr);
    
    bool isDistinct = isArrayDistinct(arr, arrSize);
    if (!isDistinct) {
        printf("Duplicates are present!\n");
    } else {
        printf("Duplicates are not present!\n");
    }
    return 0;
}
