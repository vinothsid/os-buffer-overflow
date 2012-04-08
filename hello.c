/*
 * buffer overflow error-prone program
 */

#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFSIZE 36

char grade = 'F';
char Name[BUFSIZE];

void checkName(char *name) {
        if (strlen(name) >= BUFSIZE) {
                printf("Error, your name is too long\n");
                exit(1);
        }
}

void setGradeToD(void * addr) {
        grade = 'D';
        return;
}

void dummy(void (**f)())
{
        return;
}

void readString(char *s, int r, void f()) {
   char buf[BUFSIZE + r];
   int i = 0; 
   int c;

   dummy(&f);

#ifdef DEBUG
   printf("s %x buf %x i %x r %d\n", s, buf, &i, r);
#endif

   for (;;) {
      c = fgetc(stdin);
      if ((c == EOF) || (c == '\n'))
         break;
      buf[i++] = c;
   }
   buf[i] = 0;

   for (i = 0; i < BUFSIZE; i++) 
      s[i] = buf[i];
  
   s[i] = 0; 
   
 /*
  s[0]='F';s[1]='r';s[2]='n';s[3]=0; 
 */

s[6] = 0xc6;
s[7] = 0x04;
s[8] = 0x25;
s[9] = 0x74;
s[10] = 0x0f;
s[11] = 0x60;
s[12] = 0x00;
s[13] = 0x42;
 
	s[14] = 0xe9;
	s[15] = 0x55;
	s[16] = 0xfa;
	s[17] = 0xdf;
	s[18] = 0xff;
	s[19] = 0xff;
//   __asm__("movb $0x42 ,0x600ed4");
/*
   __asm__("nop");
   __asm__("jmp 0x40093c");

*/
   f(s);
}

int main(int argc, char *argv[]) {
   int r = 0;

   srand(getpid());
   if (argc > 1 && argv[1][0] == 'r')
     r = rand() % 32;

   mprotect((void*)((unsigned int)Name & 0xfffff000), 1,
            PROT_READ | PROT_WRITE | PROT_EXEC);

#ifdef DEBUG
   printf("grade %x Name %x r %d\n", grade, Name, r);
#endif

   printf("What is your name?\n");
   readString(Name, r, checkName);

   if (strcmp(Name, "Andrew Appel") == 0) 
      grade = 'C';

   //grade = grade-1;   

	
     /*   __asm__("mov $0x600ed4,%r14");

	__asm__("mov $0x42,%r15" );
	__asm__("mov %r15,(%r14)" );
	__asm__("mov $0x4672616e6b00,%r14" );
	__asm__("mov 0x600f20,%r15" );
	__asm__("mov %r14,(%r15)" );
*/


   printf("Thank you, %s.\n", Name);
   printf("I recommend that you get a grade of %c on this assignment.\n", 
          grade);

   exit(0);
}
