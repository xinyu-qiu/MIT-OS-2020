#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void print(const char *s)
{
  write(1, s, strlen(s));
}

int main(void)
{
  int pid = fork();

  if (pid == 0)
  {
    print("child: exiting\n");
    exit(0);
  }
  else if (pid > 0)
  {
    pid = wait((int *)0);
    print("child is done\n");
  }
  else
  {
    print("fork error\n");
  }

  exit(0);
}