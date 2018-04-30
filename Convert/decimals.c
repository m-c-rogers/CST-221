//Created by Michael Rogers
//Takes a number input from user and displays it as binary, hexadecimal. Program then shifts the user number 16 bits to the left and displays new number as decimal, binary, hexadecimal

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


//Function to convert a number to binary
void toBinary(int num) {
	int i;
	int j;
	printf("Your number as binary is: ");
	for (i = 31; i >= 0; i--) {
		j = num >> i;
		if(j & 1)
			printf("1");
		else
			printf("0");
	}
}

//Function to convert a number to hexadecimal
void toHex(int num) {
	printf("Your number as hexadecimal is: %05x", num);
}

void transform(int num) {
	int shift;
	int fin;
	int hex_number = 0x07FF;
	printf("Transforming number....\n");
	//Shift number 16 bits to left using bitwise shift operator
	shift = num << 16;
	printf("Shifting number 16 bits to the left: %i\n", shift);
	//Mask out bottom 16 bits
	fin = shift & num;
	printf("Masking bottom 16 bits: %i\n", fin);
	//Add hex number
	printf("Adding hex number: %i\n", hex_number);
	fin = fin + hex_number;
	printf("Your new decimal number is: %i\n", fin);
	toBinary(fin);
	printf("\n");
	toHex(fin);
	printf("\n");
}

void* convert(int num) {
	printf("Your number is: %i\n", num);
	toBinary(num);
	printf("\n");
	toHex(num);
	printf("\n");
}

int main() {

	int num;
	printf("Please enter a number between 0 and 4095: ");
	scanf("%d", &num);
	convert(num);
	transform(num);

}
