#include <stdio.h>

int main(){
	printf("this is the very baisc\n");

	int arr[4] = {1, 2, 3, 4};

	printf("the arr[3] is %d\n", arr[3]);	

	int arrSize = sizeof(arr)/sizeof(arr[0]);

	printf("the sieze of the array is %i\n", arrSize);

	printf("the size of byte of array is %i\n", (int)sizeof(arr));


		
	printf("wrong example=============start print each\n");	
	for(int i = 0; i < sizeof(arr); i++){

		
							
		printf("the arr[%i] is %i\n", i, arr[i]);	


	}
	printf("wrong example=============end print each\n");	






	printf("=============start print each\n");	
	for(int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++){
		printf("the arr[%i] is %i\n", i, arr[i]);	
	}
	printf("=============end print each\n");	


	int arr2[8];

	int* p = &arr[0];
	int* p2 = arr2;  // temp pointer points to arr2[0]
		
	for(int i = 0; i < sizeof(arr); i++){
		*p2++ = *p++;
	}

	

	printf("=============start print arr2 start\n");	
	for(int i = 0; i < sizeof(arr2)/sizeof(arr2[0]); i++){
		printf("the arr2[%i] is %i\n", i, arr2[i]);	
	}
	printf("=============end print arr2 end\n");	





	return 0;
}
