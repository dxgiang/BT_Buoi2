//Code cứng
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Ham khoi tao decimal convert sang binary
int decimalToBinary(int decimal) {
	static int counter = 0;
	counter++;
	if (decimal==0){
		return 0;
	}
	if (decimal==1) {
		return pow(10,counter-1);
	}
	int r = (decimal % 2) * (pow(10,counter-1));
	return decimalToBinary(decimal/2) + r;
}

// Ham khoi tao decimal convert sang hexadecimal
int decimalToHexadecimal(int decimal){
	static int counter = 0;
	counter++;
	if (decimal==0){
		return 0;
	}
	if (decimal==1) {
		return pow(10,counter-1);
	}
	int r = (decimal % 16) * (pow(10,counter-1));
	return decimalToHexadecimal(decimal/16) + r;
}

int main(void){
	int selected_value, option;
	
	printf("Nhap so thap phan: ");
	scanf("%d",&selected_value); // Doc gia tri se duoc convert
	printf("Chon kieu convert: \n[1] - Binary\n[2] - Hexadecimal\n");
	
	 // Option [1] hoac [2].
	scanf("%i", &option);
	system("cls");
	switch(option){
		// Convert decimal sang binary
		case 1:
			option = decimalToBinary(selected_value);
			break;
		case 2:
			// Convert decimal sang hexadecimal
			option = decimalToHexadecimal(selected_value);
			break;
	}
	// In ket qua
	printf("Ket qua: %d", option);
	return (0);
}
