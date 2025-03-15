#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// POINTER DELETE
#define _del_ptr(ptr)                                                          \
  do {                                                                         \
    if (ptr) {                                                                 \
      free(ptr);                                                               \
      (ptr) = NULL;                                                            \
    }                                                                          \
  } while (0)

void *copy_realloc(int *__src, int *__size, int __new_size) {
  if (__src == NULL || *__size == 0) {
    __src = (int *)malloc(sizeof(int) * __new_size);
    *__size = __new_size;
    return __src;
  }

  if (__new_size >= *__size) {
    int new_size = *__size * 2;
    int *newarr = (int *)malloc(sizeof(int) * new_size);
    memcpy(newarr, __src, sizeof(int) * (*__size));
    _del_ptr(__src);
    *__size = new_size;
    return newarr;
  }

  return __src;
}

int *parse_cli(char **argv, int argc, int *count) {
  if (argc < 2) {
    printf("No arguments.\n");
    return NULL;
  }
  char *input = strdup(argv[1]); // Duplicate/deep copy

  const char comma_del[] = {","};

  int *array = (int *)malloc(sizeof(int) * 10);
  int size = 10;
  *count = 0;

  char *token;
  token = strtok(input, comma_del);
  while (token != NULL) {
    // printf("TOKEN : %s\n", token);
    // ignore whitespace
    while (isspace(*token))
      ++token;

    // check digit
    if (isdigit(*token)) {
      // update array
      if (*count >= size) {
        array = copy_realloc(array, &size, *count);
      }

      // check hiphen
      char *dash_ptr = strchr(token, '-');
      if (dash_ptr != NULL) {
        char *dash = strchr(token, '-');
        if (dash) {
          int start = atoi(token);
          int end = atoi(dash + 1);

          for (int i = start; i <= end; i++) {
            if (*count >= size) {
              array = copy_realloc(array, &size, *count + 1);
            }
            array[(*count)++] = i;
          }
        }
      } else {
        array[(*count)++] = atoi(token);
      }
    }
    token = strtok(NULL, comma_del);
  }
  return array;
}

int main(int argc, char **argv) {
  int count = 0;
  int *array = parse_cli(argv, argc, &count);
  if (count > 0 && array != NULL) {
    printf("Processed Values : ");
    for (size_t i = 0; i < count; ++i) {
      printf("%d ", array[i]);
    }
    printf("\n");
  }
  return 0;
}

// 1,2
// 2-1