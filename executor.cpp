#include "executor.hpp"
#include <cmath>
#include <string>
#include <iostream>

#define none 0			// none			| nop			| do nothing
#define jmp 1			// jmp p 		| goto p 		| p-pointer (jmp=jump)
#define mov 2 			// mov v0 v1 	| v0=v1 		| n0,n1-variables
#define def 3 			// def v n 		| v=n 			| v-variable n-number
#define add 4 			// add v0 v1 	| v0+=v1 		| v0,v1-variables
#define sub 5 			// sub v0 v1 	| v0-=v1 		| v0,v1-variables
#define mult 6 			// mult v0 v1 	| v0*=v1 		| v0,v1-variables
#define div 7			// div v0 v1 	| v0/=v1 		| v0,v1-variables
#define asm_min 8		// min v0 v1 	| v0=min(v0,v1)	| v0,v1-variables
#define asm_max 9		// max v0 v1 	| v0=max(v0,v1)	| v0,v1-variables
#define addn 10			// addn v n 	| v+=n 			| v-variable n-number
#define subn 11			// subn v n 	| v-=n 			| v-variable n-number
#define multn 12		// multn v n 	| v*=n 			| v-variable n-number
#define divn 13			// divn v n 	| v/=n 			| v-variable n-number
#define asm_sin 14 		// sin v0 v1 	| v0=sin(v1) 	| v0,v1-variables
#define asm_cos 15		// cos v0 v1 	| v0=cos(v1) 	| v0,v1-variables
#define asm_tg 16		// tg v0 v1 	| v0=tg(v1)		| v0,v1-variables
#define asm_ctg 17		// ctg v0 v1 	| v0=ctg(v1) 	| v0,v1-variables
#define asm_asin 18 	// asin v0 v1 	| v0=arcsin(v1) | v0,v1-variables
#define asm_acos 19		// acos v0 v1 	| v0=arccos(v1) | v0,v1-variables
#define asm_atg 20 		// atg v0 v1 	| v0=atan(v1) 	| v0,v1-variables
#define asm_actg 21		// actg v0 v1 	| v0=arcctg(v1) | v0,v1-variables
#define jgz 22			// jgz v p 		| if(v>0)goto p	| v-variable p-pointer
#define jez 23			// jez v p 		| if(v==0)goto p| v-variable p-pointer
#define jlz 24			// jlz v p 		| if(v<0)goto p | v-variable p-poiner
#define asm_break 25	// break		| break 		| stop program

bool canReadFrom(int i) { return (i>=0) && (i<=20); }

bool canWriteTo(int i) { return ((i>=12) && (i<=13)) || ((i>=16) && (i<=20)); }

float min(float a,float b) { return (a<b)?a:b; }
float max(float a,float b) { return (a>b)?a:b; }

void execute(float *program, int program_length)
{
	int pointer=21;
	int v0,v1;
	float p,n;

	while(pointer<program_length)
	{
		switch(int(program[pointer]))
		{
			case none: pointer++; break;

			case jmp: 
			if(pointer>=program_length-1) { pointer++; break; }
			p=int(program[pointer+1]);
			if(p>pointer) pointer=p;
			else pointer++;
			break;

			case mov:
			if(pointer>=program_length-2) { pointer++; break; }
			v0=int(program[pointer+1]);
			v1=int(program[pointer+2]);
			if(canWriteTo(v0) && canReadFrom(v1))
			{
				program[v0]=program[v1];
				pointer+=3;
			}
			else
			pointer++;
			break;

			case def:
			if(pointer>=program_length-2) { pointer++; break; }
			v0=int(program[pointer+1]);
			n=program[pointer+2];
			if(canWriteTo(v0))
			{
				program[v0]=n;
				pointer+=3;
			}
			else
			pointer++;
			break;

			case add:
			if(pointer>=program_length-2) { pointer++; break; }
			v0=int(program[pointer+1]);
			v1=int(program[pointer+2]);
			if(canWriteTo(v0) && canReadFrom(v1))
			{
				program[v0]=program[v0]+program[v1];
				pointer+=3;
			}
			else
			pointer++;
			break;

			case sub:
			if(pointer>=program_length-2) { pointer++; break; }
			v0=int(program[pointer+1]);
			v1=int(program[pointer+2]);
			if(canWriteTo(v0) && canReadFrom(v1))
			{
				program[v0]=program[v0]-program[v1];
				pointer+=3;
			}
			else
			pointer++;
			break;

			case mult:
			if(pointer>=program_length-2) { pointer++; break; }
			v0=int(program[pointer+1]);
			v1=int(program[pointer+2]);
			if(canWriteTo(v0) && canReadFrom(v1))
			{
				program[v0]=program[v0]*program[v1];
				pointer+=3;
			}
			else
			pointer++;
			break;

			case div:
			if(pointer>=program_length-2) { pointer++; break; }
			v0=int(program[pointer+1]);
			v1=int(program[pointer+2]);
			if(canWriteTo(v0) && canReadFrom(v1))
			{
				program[v0]=program[v0]/program[v1];
				pointer+=3;
			}
			else
			pointer++;
			break;

			case asm_min:
			if(pointer>=program_length-2) { pointer++; break; }
			v0=int(program[pointer+1]);
			v1=int(program[pointer+2]);
			if(canWriteTo(v0) && canReadFrom(v1))
			{
				program[v0]=min(program[v0],program[v1]);
				pointer+=3;
			}
			else
			pointer++;
			break;

			case asm_max:
			if(pointer>=program_length-2) { pointer++; break; }
			v0=int(program[pointer+1]);
			v1=int(program[pointer+2]);
			if(canWriteTo(v0) && canReadFrom(v1))
			{
				program[v0]=max(program[v0],program[v1]);
				pointer+=3;
			}
			else
			pointer++;
			break;

			case addn:
			if(pointer>=program_length-2) { pointer++; break; }
			v0=int(program[pointer+1]);
			n=program[pointer+2];
			if(canWriteTo(v0))
			{
				program[v0]=program[v0]+n;
				pointer+=3;
			}
			else
			pointer++;
			break;

			case subn:
			if(pointer>=program_length-2) { pointer++; break; }
			v0=int(program[pointer+1]);
			n=program[pointer+2];
			if(canWriteTo(v0))
			{
				program[v0]=program[v0]-n;
				pointer+=3;
			}
			else
			pointer++;
			break;

			case multn:
			if(pointer>=program_length-2) { pointer++; break; }
			v0=int(program[pointer+1]);
			n=program[pointer+2];
			if(canWriteTo(v0))
			{
				program[v0]=program[v0]*n;
				pointer+=3;
			}
			else
			pointer++;
			break;

			case divn:
			if(pointer>=program_length-2) { pointer++; break; }
			v0=int(program[pointer+1]);
			n=program[pointer+2];
			if(canWriteTo(v0))
			{
				program[v0]=program[v0]/n;
				pointer+=3;
			}
			else
			pointer++;
			break;

			case asm_sin:
			if(pointer>=program_length-2) { pointer++; break; }
			v0=int(program[pointer+1]);
			v1=int(program[pointer+2]);
			if(canWriteTo(v0) && canReadFrom(v1))
			{
				program[v0]=sin(program[v1]);
				pointer+=3;
			}
			else
			pointer++;
			break;

			case asm_cos:
			if(pointer>=program_length-2) { pointer++; break; }
			v0=int(program[pointer+1]);
			v1=int(program[pointer+2]);
			if(canWriteTo(v0) && canReadFrom(v1))
			{
				program[v0]=cos(program[v1]);
				pointer+=3;
			}
			else
			pointer++;
			break;

			case asm_tg:
			if(pointer>=program_length-2) { pointer++; break; }
			v0=int(program[pointer+1]);
			v1=int(program[pointer+2]);
			if(canWriteTo(v0) && canReadFrom(v1))
			{
				program[v0]=tan(program[v1]);
				pointer+=3;
			}
			else
			pointer++;
			break;

			case asm_ctg:
			if(pointer>=program_length-2) { pointer++; break; }
			v0=int(program[pointer+1]);
			v1=int(program[pointer+2]);
			if(canWriteTo(v0) && canReadFrom(v1))
			{
				program[v0]=1.0/tan(program[v1]);
				pointer+=3;
			}
			else
			pointer++;
			break;

			case asm_asin:
			if(pointer>=program_length-2) { pointer++; break; }
			v0=int(program[pointer+1]);
			v1=int(program[pointer+2]);
			if(canWriteTo(v0) && canReadFrom(v1))
			{
				program[v0]=asin(program[v1]);
				pointer+=3;
			}
			else
			pointer++;
			break;

			case asm_acos:
			if(pointer>=program_length-2) { pointer++; break; }
			v0=int(program[pointer+1]);
			v1=int(program[pointer+2]);
			if(canWriteTo(v0) && canReadFrom(v1))
			{
				program[v0]=acos(program[v1]);
				pointer+=3;
			}
			else
			pointer++;
			break;

			case asm_atg:
			if(pointer>=program_length-2) { pointer++; break; }
			v0=int(program[pointer+1]);
			v1=int(program[pointer+2]);
			if(canWriteTo(v0) && canReadFrom(v1))
			{
				program[v0]=atan(program[v1]);
				pointer+=3;
			}
			else
			pointer++;
			break;

			case asm_actg:
			if(pointer>=program_length-2) { pointer++; break; }
			v0=int(program[pointer+1]);
			v1=int(program[pointer+2]);
			if(canWriteTo(v0) && canReadFrom(v1))
			{
				program[v0]=M_PI_2-atan(program[v1]);
				pointer+=3;
			}
			else
			pointer++;
			break;

			case jgz:
			if(pointer>=program_length-2) { pointer++; break; }
			v0=int(program[pointer+1]);
			p=int(program[pointer+2]);
			if(canReadFrom(v0) && (p>pointer))
			{
				if(program[v0]>0) pointer=p;
				else pointer+=3;
			}
			else
			pointer++;
			break;

			case jez:
			if(pointer>=program_length-2) { pointer++; break; }
			v0=int(program[pointer+1]);
			p=int(program[pointer+2]);
			if(canReadFrom(v0) && (p>pointer))
			{
				if(program[v0]==0) pointer=p;
				else pointer+=3;
			}
			else
			pointer++;
			break;

			case jlz:
			if(pointer>=program_length-2) { pointer++; break; }
			v0=int(program[pointer+1]);
			p=int(program[pointer+2]);
			if(canReadFrom(v0) && (p>pointer))
			{
				if(program[v0]<0) pointer=p;
				else pointer+=3;
			}
			else
			pointer++;
			break;

			case asm_break:
				pointer=program_length;
			break;

			default: pointer++; break;
		}
	}
}