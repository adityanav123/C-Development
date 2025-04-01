#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char byte_;
typedef unsigned char *pbyte_;

static inline void *safe_alloc(size_t size, byte_ default_value,
                               bool zero_init) {
  void *ptr = malloc(size);
  if (ptr == NULL) {
    fprintf(stderr, "Memory Allocation failed for %zu bytes", size);
    return NULL;
  }

  if (zero_init) {
    memset(ptr, 0, size);
  } else {
    memset(ptr, default_value, size);
  }
  return ptr;
}

#define SAFE_ALLOC(size, default_value) safe_alloc(size, default_value, false)
#define SAFE_CALLOC(size) safe_alloc(size, 0, true)
#define DEL_PTR(ptr)                                                           \
  do {                                                                         \
    if ((ptr) != NULL) {                                                       \
      free(ptr);                                                               \
      (ptr) = NULL;                                                            \
    }                                                                          \
  } while (0)

int main() {
  pbyte_ buffer = NULL;
  if ((buffer = SAFE_ALLOC(300, 0xFF)) == NULL) {
    printf("[err] invalid allocation!\n");
    return 0;
  }
  DEL_PTR(buffer);

  pbyte_ buffer2 = NULL;
  if ((buffer2 = SAFE_CALLOC(200)) == NULL) {
    printf("[err] invalid calloc allocation!\n");
    return 0;
  }
  DEL_PTR(buffer2);

  pbyte_ buffer3 = NULL;
  if ((buffer3 = safe_alloc(300, 0xAA, false)) == NULL) {
    printf("[err] invalid allocation!\n");
    return 0;
  }
  DEL_PTR(buffer3);

  return 1;
}