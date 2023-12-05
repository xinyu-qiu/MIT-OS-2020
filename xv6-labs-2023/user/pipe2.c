#include "kernel/types.h"
#include "user/user.h"

int main()
{
  int n, pid;
  int fds[2];
  char buf[100];

  pipe(fds);

  pid = fork();
  if (pid == 0)
  {
    write(fds[1], "this is pipe2\n", 14);
  }
  else
  {
    n = read(fds[0], buf, sizeof(buf));
    write(1, buf, n);
  }
  exit(0);
}