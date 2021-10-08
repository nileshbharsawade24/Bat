#include <stdio.h>
#include <unistd.h>
#include "handle_request.h"
#include "threads.h"
// #include "mysqlconnect.h"

int main(int argc, char const *argv[]) {
  //creating child process
  pid_t pid = fork();
  //fork will negative value if it failed
  if (pid < 0){
    fprintf(stderr,"ERROR: failed to fork\n");
    return 1;
  }
  //fork will zero to child process
  else if (pid == 0){
    request_handler();//child will handle incomming request
  }
  //fork will positive pid to parent process
  else{
    start_esb_request_poller_thread();//parent will do polling and assigning task to threads
  }
  return 0;
}
