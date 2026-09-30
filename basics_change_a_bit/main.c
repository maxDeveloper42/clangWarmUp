#include "stdio.h"

// mask is 0xF0
#define BIT_MASK (0xF0)


void printVar(int turn, unsigned int var){
	printf("the %d turn, var in deci: %u, \n hex: %X \n\n", turn, var, var);
}

int main(){

	printf("hello wrold\n");

	int a, b;
	 
	a = 0;
	b = 0;
	unsigned int c = 0;

	// printf("a before is %b \n", a);
	printf("size of the a: %zu Byte\n", sizeof(a));

	a = 1<<8;

	printf("a after is %i\n", a);


	b |= 1<<(8*4-1);
	b += 1<<8;

	printf("b after is %b\n", b);

	printf("b after is %x\n", b);


	// c = (1 << (8*sizeof(c))) - 1;
	
	// c = (1U << (sizeof(c) * 8  )) - 1;

	printf("size of the c is %zu bits\n", sizeof(c)*8);

	// normal 1 can not be shifted by 32 bits
	// If you shift an integer by >= its bit width → undefined behavior (UB)
	c = (1U << 31) - 1;
	
	c = ~0U;
	
	//printf("initial c is hex:%X, udecimal: %u\n\n", c, c);
	
	printVar(1, c);

	/*
	//printf("c is %d\n", c);
	// u for unsigned int
	printf("c is %u\n", c);
	*/
	
	// i want to turn c to xxxFFAF
	// bit mask 0xF0
	
	// ???
	c = ~0U;
	c = c & (~BIT_MASK) | (0xA0 & BIT_MASK) ;
	printVar(2, c);

	// you shall mind the operator sequence
	c = ~0U;
	c = c & ~BIT_MASK | 0xA0 & BIT_MASK ;
	printVar(3, c);

	c = ~0U;
	c = (c & ~BIT_MASK) | 0xA0; 
	printVar(4, c);


	c = c & 0xA<<4;

	// c = b1111 ^ b0111;
	// note, 0xFF is one Byte
	//note, 0xF is 4 bits
	c =  0b1111;

	// 0xAA
	c = 0b10101010;

	// mask is 0xF0
	c = (~0xF0);

	c = 1<<1;
	
	c = 0xF<<4;

	printf("c is %X\n", c);
	printf("c is %d\n", c);
	return 0;
}


