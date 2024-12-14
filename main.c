#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
  // Load config files, if any
  // Si no, pasando

  // Loop para ejecutar el comando
  lsh_loop();

  //realiza el apagado cuando sale del loop
  return EXIT_SUCCESS;
}

void lsh_loop(void)
{
  char *line;
  char **args; //Recogemos los datos que se ejecutaran en la shell
  int status;

  do {
    printf("> ");
    line = lsh_read_line();
    args = lsh_split_line(line);
    status = lsh_execute(args);

    free(line);
    free(args);
  } while (status);
}

#define LSH_RL_BUFSIDE 1024
char *lsh_read_line(void)
{
  int bufsize = LSH_RL_BUFSIDE;
  int position = 0;
  chat *buffer = malloc(sizwof(char) * bufside);
  int c;

  if (!buffer) {
    fprintf(stder, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    //Leemos el caracter
    c = getchar();

    if (c == EOF || c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    if (position >= bufside) {
      bufside += LSH_RL_BUFSIDE;
      buffer = realloc(buffer, bufside);
      if (!buffer) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}
