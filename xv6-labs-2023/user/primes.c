#include "kernel/types.h"
#include "user/user.h"

int helper(int r)
{
  int num;
  if (read(r, &num, sizeof(int)) == 0)
  {
    exit(0);
  }

  int pid;
  int fds[2];

  if (pipe(fds) == -1)
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

  if (pid > 0)
  {
    close(fds[0]);
    fprintf(1, "prime %d\n", num);
    int p = num;
    while (read(r, &num, sizeof(int)) != 0)
    {
      if (num % p != 0)
      {
        write(fds[1], &num, sizeof(int));
      }
    }
    close(fds[1]);
  }
  else
  {
    close(fds[1]);
    helper(fds[0]);
    close(fds[0]);
  }
  exit(0);
}

int main()
{
  int pid;
  int fds[2];

  if (pipe(fds) == -1)
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

  if (pid > 0)
  {
    close(fds[0]);
    for (int i = 2; i <= 35; ++i)
    {
      write(fds[1], &i, sizeof(int));
    }
    close(fds[1]);
  }
  else
  {
    close(fds[1]);
    helper(fds[0]);
    close(fds[0]);
  }
  exit(0);
}