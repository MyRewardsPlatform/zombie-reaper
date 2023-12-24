***                               
                    ___.   .__        
____________   _____\_ |__ |__| ____  
\___   /  _ \ /     \| __ \|  |/ __ \ 
 /    (  <_> )  Y Y  \ \_\ \  \  ___/ 
/_____ \____/|__|_|  /___  /__|\___                                   
  _ __ ___  __ _ _ __   ___ _ __ 
 | '__/ _ \/ _` | '_ \ / _ \ '__|
 | | |  __/ (_| | |_) |  __/ |   
 |_|  \___|\__,_| .__/ \___|_|   
                | |              
                |_|        2.0      
***

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void reap_child(int signo) {
    (void) signo;
    pid_t pid;
    int status;

    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        printf("Child process %d terminated\n", pid);
    }
}

int main() {
    // Register the signal handler for SIGCHLD
    struct sigaction sa;
    sa.sa_handler = reap_child;
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    sigaction(SIGCHLD, &sa, NULL);

    // Fork a child process
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Child process
        printf("Child process is running\n");
        // Simulate some work
        sleep(2);
        printf("Child process is done\n");
        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        printf("Parent process is waiting for the child to finish\n");

        // Simulate some work in the parent
        sleep(5);

        // The parent process will automatically catch the termination of the child
        // due to the signal handler we registered for SIGCHLD
        printf("Parent process is done\n");
    }

    return 0;
}

***                               
                    ___.   .__        
____________   _____\_ |__ |__| ____  
\___   /  _ \ /     \| __ \|  |/ __ \ 
 /    (  <_> )  Y Y  \ \_\ \  \  ___/ 
/_____ \____/|__|_|  /___  /__|\___                                   
  _ __ ___  __ _ _ __   ___ _ __ 
 | '__/ _ \/ _` | '_ \ / _ \ '__|
 | | |  __/ (_| | |_) |  __/ |   
 |_|  \___|\__,_| .__/ \___|_|   
                | |              
                |_|        2.0      
***
