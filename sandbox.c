/*
 *  * sandbox module
 *   */

#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <ucontext.h>

struct sigaction sandboxAction;

extern void readString(char *s, int r);
extern int main(int argc, char *argv[]);

void * returnAddr;

static void sandbox_handler(int sig,siginfo_t *siginfo, void *ucp) {

	int i;
#ifdef DEBUG
	printf("In handler: Segfault at %p \n",siginfo->si_addr);
#endif

	void *tmp;
	if (siginfo->si_addr == readString ) {
		 mprotect((void*)((unsigned int)readString & 0xfffffffffffff000), 1,
		    PROT_READ | PROT_WRITE  | PROT_EXEC );
		 mprotect((void*)((unsigned int)main & 0xfffffffffffff000), 1,
		    PROT_READ | PROT_WRITE   );

		tmp = (*(ucontext_t *)ucp).uc_mcontext.gregs[ 15 ];
		returnAddr = *(int *)tmp;

#ifdef DEBUG
		printf("Stored address is %p\n",returnAddr); 
#endif

	} else if ( siginfo->si_addr  == returnAddr ) {
                 mprotect((void*)((unsigned int)main & 0xfffffffffffff000), 1,
                    PROT_READ | PROT_WRITE  | PROT_EXEC );
                 mprotect((void*)((unsigned int)readString & 0xfffffffffffff000), 1,
                    PROT_READ | PROT_WRITE   );
	} else {
                 mprotect((void*)((unsigned int)main & 0xfffffffffffff000), 1,
                    PROT_READ | PROT_WRITE  | PROT_EXEC );

		printf("malicious buffer overflow detected, will exit!\n");
		exit(0);
	}
}

void init_sandbox(void) {

	 mprotect((void*)((unsigned int)readString & 0xfffffffffffff000), 1,
            PROT_READ | PROT_WRITE /* | PROT_EXEC */);

	memset(&sandboxAction,0,sizeof(struct sigaction));

	sigemptyset(&sandboxAction.sa_mask);
	sigaddset(&sandboxAction.sa_mask,SIGSEGV);

	sandboxAction.sa_flags = SA_RESTART|SA_SIGINFO ;
	sandboxAction.sa_handler = sandbox_handler;
	

	sigaction(SIGSEGV,&sandboxAction,NULL);

	sigprocmask(SIG_UNBLOCK,&sandboxAction.sa_mask,NULL);
}
