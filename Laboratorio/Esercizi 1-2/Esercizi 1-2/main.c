#include <stdio.h>
#include <stdlib.h>


void prodotto()
{
	unsigned short Num1 = 69;
	unsigned short Num2 = 69;
	unsigned int Prodotto;

	__asm
	{
		XOR EAX, EAX			// EAX = 0 (Prodotto)
		XOR EBX, EBX			// EBX = 0
		XOR ECX, ECX			// ECX = 0
		MOV BX, Num1			// EBX (basso) = Num1
		MOV CX, Num2			// ECX (basso) = Num2
		JECXZ Fine				// Salta il ciclo se Num2 = 0
		Ciclo :					// Ciclo: while Num2 != 0
		ADD EAX, EBX			//		Prodotto += Num1
			LOOP Ciclo			//		Num2--
			Fine :				// Fine:
		MOV Prodotto, EAX		//		Prodotto = EAX
	}

	printf("Prodotto=%u\n", Prodotto);
}

void radice()
{
	unsigned int Num = 10;
	unsigned int Radice;

	__asm
	{
		MOV EAX, Num			// EAX = Num
		XOR EBX, EBX			// EBX = 0 (Radice)
		MOV ECX, 1				// ECX = 1 (S)
		Ciclo:					// Ciclo:
		SUB EAX, ECX			//		Num = Num - S
			JB Fine				//		Se Num < 0 esci dal ciclo
			INC EBX				//		Radice += 1
			ADD ECX, 2			//		S += 2
			JMP Ciclo			//		Torna a Ciclo
			Fine :				// Fine:
		MOV Radice, EBX			//		Radice = EBX
	}

	printf("Radice=%d\n", Radice);
}

int main()
{
	prodotto();
	radice();
}