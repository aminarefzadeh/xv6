#include "types.h"
#include "user.h"

#define NCHILD 10

int main(int argc,char *argv[]) //  1:for Ticket  2:for FCFS  3:for priority
{
  if(argc!=3 && argc!=4){
    printf(2,"valid format 1 : changeproc pid queue (priiority or ticketNum)\n");
    exit();
  }
  if(atoi(argv[2])!=2 && argc!=4){
    printf(2,"valid format 2 : changeproc pid queue (priiority or ticketNum)\n");
    exit();
  }
  if(atoi(argv[2])==1){
    addToTicket(atoi(argv[1]), atoi(argv[3]));
    exit();
  }
  else if(atoi(argv[2])==2){
    addToFCFS(atoi(argv[1]));
    exit();
  }
  else if(atoi(argv[2])==3){
    addToPriority(atoi(argv[1]), atoi(argv[3]));
    exit();
  }
  else{
    exit();
  }
}
