#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define FINVALID -1

int createBinaryFile(const char *filename, mode_t mode) {
  int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode);

  if (fd == -1) {
    fprintf(stderr, "Error creating file [%s] : %s\n", filename,
            strerror(errno));
    close(fd);
    return FINVALID;
  }
  return fd;
}

FILE *createFileStream(const char *filename, mode_t mode) {
  int fd = createBinaryFile(filename, mode);
  if (fd == FINVALID) {
    return NULL;
  }

  FILE *file = fdopen(fd, "wb");
  if (file == NULL) {
    fprintf(stderr, "Error converting file descriptor to stream: %s",
            strerror(errno));
    close(fd);
    return NULL;
  }
  return file;
}

int main(int argc, char **argv) {
  const char *filename = "test.txt";
  int fd = createBinaryFile(filename, 0644);
  if (fd != -1) {
    printf("File created successfully with file descriptor: %d\n", fd);
    const char data[] = "This is binary data\n";
    write(fd, data, sizeof(data));

    close(fd);
  }

  FILE *file = createFileStream("test_Stream.txt", 0644);
  if (file != NULL) {
    printf("File Created sucessfully with FILE\n");
    const char data[] = "This is a binary data written using FILE Stream";
    fwrite(data, 1, sizeof(data), file);

    fclose(file);
  }

  return 0;
}
