#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct CALLBACK_METHODS_ {
    void (*callback)(); // function pointer
    struct CALLBACK_METHODS_ *next;
}callback, *pCallback;

// init
pCallback init() {
    return NULL;
}

// insert callback
pCallback insert(pCallback chain, void (*callback)()) {
    pCallback node = (pCallback)malloc(sizeof(callback));
    node->callback = callback;
    node->next = chain; // to front
    return node;
}

void exec(pCallback chain) {
    pCallback temp = chain;
    while (temp != NULL) {
        temp->callback();
        temp = temp->next;
    }
}

void free_chain(pCallback chain) {
    while (chain!=NULL) {
        pCallback temp = chain;
        chain = chain->next;
        free(temp);
    }
}


// example use
void exec_if_fails(bool (*conditional_method)(), pCallback callbacks, const char *err_msg) {
    if (conditional_method() == false) {
        exec(callbacks);
        printf("[error] : %s\n", err_msg);
    }
}

bool always_false() {
    return false;
}

bool always_true() {
    return true;
}

void method1() {
    printf("method1() called\n");
}

void method2() {
    printf("method2() called\n");
}

void method3() {
    printf("method3() called\n");
}

int main() {
    pCallback callbacks = init();
    callbacks = insert(callbacks, method3);
    callbacks = insert(callbacks, method2);
    callbacks = insert(callbacks, method1);

    exec_if_fails(always_false, callbacks, "This is an error message");

    free_chain(callbacks);

    return 0;
}


