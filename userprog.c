#include "types.h"
#include "user.h"

#define NCHILD 3

int main(int argc,char *argv[])
{
  int pid;
  pid = fork();
  for(int i=1;i<NCHILD;i++)
    if (pid>0)
      pid = fork();
  if (pid <  0)
  {
    printf(2,"fork error\n");
  }
  else if (pid == 0)
  {
    // child body
    double i = 0;
    printf(1,"child pid : %d\n",getpid());
    for (i=0;i<10000000;i+=0.01);
    printf(1,"child pid : %d done\n",getpid());
    exit();
  }
  else{
    //parent body
    //double i = 0;
    printf(1,"parent pid : %d\n",getpid());
    // for (i=0;i<1000000;i+=0.01);
    // printf(1,"parent pid : %d done\n",getpid());
    // for (int i=0; i<NCHILD ; i++)
    //   wait();
    exit();
  }
}
