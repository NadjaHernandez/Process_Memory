// memory_segments.cpp

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

/***********************Homework Answers****************************
 5. As variables get added to the stack, the addresses get larger. 
 6. Yes there are variables that are stored on the stack that share
 the same address. Two variables that have the same are lc4 & lc6.
 7. I expect variables in recursive functions to be stored in the
 heap. 
 */

/*
       +------------------+
       |  TEXT            |
       |                  |
       |  instructions in | x40135d  = proc1
       |  machine code    | x401443  = proc2
       |                  |
       +------------------+ x4015e5  = etext
       |  DATA            | x404034  = g1   global initialized
       |  - initialized   | x404038  = g3
       |    variables     | x40403c  = ls1  static initialized
       |                  |          = ls3
       |                  |
       | ---------------  | x404044  = edata
       |                  | x404080  = g0   global uninitialized
       |                  | x4040a0  = g2   big array
       |                  | x405810  = g4
       |  - uninitialized | x405814  = ls0  static uninitialized
       |    variables     |          = ls2
       |                  |
       |                  | 
       | ---------------  | x405820  = end
       |  - heap for      | x225de70  pointed to by heap1
       |  dynamic         | x225dea0  pointed to by heap2
       |  allocation      |
       |                  |
       |                  |
       +------------------+ 
                |
                |
                V
              ......
                ^
                |
                |
       +------------------+
       |  STACK           | x7fffalb096e8  = lc4, lc6   | Activation record for
       |  - function      | x7fffalb096ec  = lc3, lc5   | proc1 or proc2
       |    activation    |
       |    records       |
       |  - local         | x7fffalb09704  = lc2       | Activation record for
       |    automatic     | x7fffalb09708  = lc1       | main
       |    variables     | x7fffalb0970c  = lc0       |
       +------------------+
*/

int g0;       /* global variable, uninitialized */
int g1 = 14;  /* global variable, initialized */
int g2[1500]; /* global variable, uninitialized */
int g3 = 16;  /* global variable, initialized */
int g4;       /* global variable, uninitialized */

void proc1();
void proc2();
//new function
int fac(int);

int main()
{
	int n;
	cout << "Enter a number: ";
	cin >> n;
	cout << fac(n);
 extern int etext[], edata[], end[];

 int lc0;      /* local variable, stored on stack */
 int lc1 = 27; /* local variable, stored on stack; mix init and uninit */
 int lc2;      /* local variable, stored on stack */
 static int ls0; /* local static variable, uninitialized data */
 static int ls1 = 19;      /* local static variable, initialized data */       
 int *pheap1;       
 int *pheap2;
        
 pheap1 = new int[10];       
 pheap2 = new int[100];
       
 printf("\n\n---------- main -------------------\n\n");       
 printf("%14p (%15lu): Last address\n", 
  0xffffffffffff, 999999999999999);
 
 printf("%14p (%15lu): Address etext\n",   etext, etext);       
 printf("%14p (%15lu): Address edata\n",   edata, edata);       
 printf("%14p (%15lu): Address end\n", end, end);
        
 printf("%14p (%15lu): Address of code for proc1\n",   &proc1, &proc1);       
 printf("%14p (%15lu): Address of code for proc2\n",   &proc2, &proc2);
       
 printf("%14p (%15lu): Address of uninitialized global variable g0\n",   &g0, &g0);
 printf("%14p (%15lu): Address of initialized   global variable g1\n", 
  &g1, &g1);       
 printf("%14p (%15lu): Address of uninitialized global array    g2\n",   &g2[0], &g2[0]);
 printf("%14p (%15lu): Address of initialized   global variable g3\n",   &g3, &g3);       
 printf("%14p (%15lu): Address of uninitialized global variable g4\n", 
  &g4, &g4);

 printf("%14p (%15lu): Address heap1 in heap space\n",   pheap1, (unsigned long) pheap1);      
 printf("%14p (%15lu): Address heap2 in heap space\n", 
  pheap2, (unsigned long) pheap2);
 
 printf("%14p (%15lu): Address of local variable lc0\n",   &lc0, &lc0);
 printf("%14p (%15lu): Address of local variable lc1\n",   &lc1, &lc1);
 printf("%14p (%15lu): Address of local variable lc2\n",   &lc2, &lc2);

 printf("%14p (%15lu): Address of local uninitialized static var ls0\n",   &ls0, &ls0);
 printf("%14p (%15lu): Address of local initialized   static var ls1\n",   &ls1, &ls1);

 proc1();
 proc2();
 
 return 0;
}

void proc1() {
 int lc3;
 int lc4 = 37;

 printf("\n\n----------- proc1 ------------------\n\n");
 printf("%14p (%15lu): Address of code for proc1\n",   &proc1, &proc1);
 printf("%14p (%15lu): Address of global variable g0\n",   &g0, &g0);
 printf("%14p (%15lu): Address of global variable g1\n",   &g1, &g1);
 printf("%14p (%15lu): Address of global variable g2\n",   &g2[0], &g2[0]);
 printf("%14p (%15lu): Address of global variable g3\n",   &g3, &g3);
 printf("%14p (%15lu): Address of global variable g4\n",   &g4, &g4);
 printf("%14p (%15lu): Address of local variable lc3\n",   &lc3, &lc3);
 printf("%14p (%15lu): Address of local variable lc4\n",   &lc4, &lc4);
}

void proc2() {
 int lc5;
 int lc6 = 51;
 static int ls2;
 static int ls3 = 47;

 printf("\n\n------------ proc2 -----------------\n\n");
 printf("%14p (%15lu): Address of code for proc2\n",   &proc2, &proc2);
 printf("%14p (%15lu): Address of global variable g0\n",   &g0, &g0);
 printf("%14p (%15lu): Address of global variable g1\n",   &g1, &g1);
 printf("%14p (%15lu): Address of global variable g2\n",   &g2[0], &g2[0]);
 printf("%14p (%15lu): Address of global variable g3\n",   &g3, &g3);
 printf("%14p (%15lu): Address of global variable g4\n",   &g4, &g4);
 printf("%14p (%15lu): Address of local variable lc5\n",   &lc5, &lc5);
 printf("%14p (%15lu): Address of local variable lc6\n",   &lc6, &lc6);
 printf("%14p (%15lu): Address of local uninitialized static var ls2\n",   &ls2, &ls2);
 printf("%14p (%15lu): Address of local initialized   static var ls3\n",   &ls3, &ls3);
}

//New factorial function
int fac(int n)
{
	printf("%14p (%15lu) : Address of function fac\n", &fac, &fac);
	//cout << &fac(n) << endl;

	cout << "n is " << n << endl;
	printf("%14p (%15lu) : Address of n\n", &n, &n);


	if( n == 0)
	{
		return 1;
	}else
	{
		return (n * fac(n-1));
	}

}
