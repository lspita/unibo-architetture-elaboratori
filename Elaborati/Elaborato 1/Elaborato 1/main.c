/********************************************************************************
 *                                                                              *
 *                   Architetture dei sistemi di Elaborazione                   *
 *                                                                              *
 ********************************************************************************

 Elaborato 1
 Descrizione: Dato un array di puntatori a stringa (ogni cella del vettore contiene
				l'indirizzo a 32 bit del primo carattere della stringa), ordinarlo
				secondo il codice ASCII. Ogni stringa termina con il carattere nullo
				(codice ASCII 0).

 ********************************************************************************/

#include <stdio.h>

void main() {
	// Le stringhe da ordinare (array di puntatori)
	char* strings[] = { "prova","1","adfadfas","bsfufdasi","ciao" };
	// Il numero di stringhe nell'array
	int num = sizeof(strings) / sizeof(strings[0]);

	__asm
	{
		JMP _Main;					//	jump to Main()

	_Swap:							//	Swap():

	_Confronto:						//	Confronto():
		XOR ECX, ECX;				//		ECX = 0
	
	_CicloStringa:					//		do:
		MOV DL, [ESI][ECX];			//			DL = word1[ECX]
		CMP DL, 0;					//			if DL == '\0':
		JZ _CicloStringaEnd;		//				jump to CicloStringaEnd

		MOV DH, [EDI][ECX];			//			DH = word2[ECX]

	_CicloStringaEnd:				//	CicloStringaEnd:
		CMP DL, DH;					//		do DL-DH, update flags
		RET;

	_Main:							//	Main():
		XOR EAX, EAX;				//		EAX = 0
		XOR EBX, EBX;				//		EBX = 0
		XOR EDX, EDX;				//		EDX = 0

		MOV EAX, num;				//		EAX = num (iterazioni)
	_Ciclo_Iterazioni:				//		do:
		MOV EBX, num;				//			EBX = num (confronti)
		DEC EBX;					//			EBX-- (per andare da n-1 a 1)
	
	_Ciclo_Confronti:				//			do:
		MOV ESI, strings[EBX*4];	//				ESI = (int)strings[EBX]	  (word1: strings[n-1..1])
		MOV EDI, strings[EBX*4-4];	//				ESI = (int)strings[EBX-1] (word2: strings[n-2..0])
		CALL _Confronto;			//				Confronto()
		
		DEC EBX;					//				EBX--
		JNZ _Ciclo_Confronti;		//			while EBX > 0
		
		DEC EAX;					//			EAX--
		JNZ _Ciclo_Iterazioni;		//		while EAX > 0
	}

	// Stampa su video
	{
		int i;
		for (i = 0; i < num; i++)
			printf("%s\n", strings[i]);
	}
}
