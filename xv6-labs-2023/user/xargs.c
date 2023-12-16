#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    fprintf(2, "xargs [options] [command]\n");
    exit(1);
  }
  char *arg[MAXARG];
  int j = 0;
  for (int i = 1; i < argc; ++i)
  {
    arg[j++] = argv[i];
  }

  for (int i = argc - 1; i < MAXARG; ++i)
  {
    arg[i] = (char *)malloc(sizeof(128));
  }

  char buf;
  int readSize;
  while (1)
  {
    int m = 0;
    while ((readSize = read(0, &buf, 1)) != 0)
    {
      if (buf == ' ')
      {
        arg[j][m] = 0;
        m = 0;
        j++;
      }
      else if (buf == '\n')
      {
        arg[j][m] = 0;
        m = 0;
        j++;
        break;
      }
      else
      {
        arg[j][m] = buf;
        m++;
      }
    }
    arg[j] = 0;
    j = argc - 1;

    if (readSize <= 0)
    {
      break;
    }

    int pid = fork();
    if (pid == 0)
    {
      exec(arg[0], arg);
    }
    else
    {
      wait(0);
    }
  }

  exit(0);
}