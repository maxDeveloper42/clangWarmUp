#include "stdio.h"

#define BIT_MASK (0xFF)

int main(){

	printf("hello wrold\n");

	int a, b;
	 
	a = 0;
	b = 0;

	// printf("a before is %b \n", a);
	printf("size of the a: %zu Byte\n", sizeof(a));

	a = 1<<8;

	printf("a after is %b \n", a);


	b |= 1<<(8*4-1);
	b += 1<<8;

	printf("b after is %b \n", b);

	printf("b after is %h \n", b);






	return 0;
}
















