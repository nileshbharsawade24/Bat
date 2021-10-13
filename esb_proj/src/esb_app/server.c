#include <stdio.h>
#include <unistd.h>
#include<sys/wait.h>
#include "handle_request.h"
#include "threads.h"

int main(int argc, char const *argv[]) {
  printf("\n  ------------------------------------------------------------\n");
  printf("  |                                                          |\n");
  printf("  |                  WELCOME IN BAT ESB  /\\                  |\n");
  printf("  |                                                          |\n");
  printf("  ------------------------------------------------------------\n\n");

  //creating child process
  pid_t pid = fork();

  //fork will return negative value if it fails
  if (pid < 0){
    fprintf(stderr,"ERROR: failed to fork\n");
    return 1;
  }

  //fork will return zero to child process
  else if (pid == 0){
    
    request_handler();//child will handle incomming request
    exit(0);
  }

  //fork will return positive pid to parent process
  else{
    //parent will do polling and assigning task to threads
    start_esb_request_poller_thread();
    wait(NULL);
  }
  return 0;
}
