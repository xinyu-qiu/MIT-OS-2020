#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void)
{
  int pid;
  int fd1[2];
  int fd2[2];
  char buf[10];

  if (pipe(fd1) == -1)
  {
    fprintf(2, "Pipe failed");
    exit(1);
  }
  if (pipe(fd2) == -1)
  {
    fprintf(2, "Pipe failed");
    exit(1);
  }

  pid = fork();
  if (pid < 0)
  {
    fprintf(2, "Fork failed");
    exit(1);
  }

  if (pid > 0) // parent process
  {
    // close read end of pipe 1
    close(fd1[0]);

    // write input string and close write end of pipe 1
    write(fd1[1], "a", 1);
    close(fd1[1]);

    close(fd2[1]);
    if (read(fd2[0], buf, sizeof(buf)) > 0)
    {
      fprintf(1, "%d: received pong\n", pid);
    }
    close(fd2[0]);
  }
  else
  {
    close(fd1[1]);
    if (read(fd1[0], buf, sizeof(buf)) > 0)
    {
      fprintf(1, "%d: received ping\n", pid);
    }
    close(fd1[0]);

    close(fd2[0]);
    write(fd2[1], "a", 1);
    close(fd2[1]);
  }

  exit(0);
}