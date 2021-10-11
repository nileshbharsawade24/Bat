#include <stdio.h>
#include <unistd.h>
#include<sys/wait.h>
#include "handle_request.h"
#include "threads.h"
// #include "mysqlconnect.h"

int main(int argc, char const *argv[]) {
  printf("\n  ------------------------------------------------------------\n");
  printf("  |                                                          |\n");
  printf("  |                  WELCOME IN BAT ESB  /\\                  |\n");
  printf("  |                                                          |\n");
  printf("  ------------------------------------------------------------\n\n");
  //creating child process
  pid_t pid = fork();
  //fork will negative value if it failed
  if (pid < 0){
    fprintf(stderr,"ERROR: failed to fork\n");
    return 1;
  }
  //fork will zero to child process
  else if (pid == 0){
    // while(1){sleep(100);};
    request_handler();//child will handle incomming request
    exit(0);
  }
  //fork will positive pid to parent process
  else{
    // while(1){sleep(100);};
    start_esb_request_poller_thread();//parent will do polling and assigning task to threads
    wait(NULL);
  }
  return 0;
}
