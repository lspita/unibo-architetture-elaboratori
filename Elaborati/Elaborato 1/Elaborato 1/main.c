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
									//	Reset registers
		XOR EAX, EAX;				//	EAX = 0
		XOR EBX, EBX;				//	EBX = 0
		XOR EDX, EDX;				//	ECX = 0
		XOR EDX, EDX;				//	EDX = 0

		MOV EAX, num;				//	EAX = num
		CMP EAX, 1;					//	compare EAX, 1
		JA _Sort;					//	if EAX > 1: Sort()
		JMP _End;					//	else: END
	
									//	Confronto: Finchè non finisce la prima stringa, cicla carattere per carattere
									//		- Se sono uguali, continua a ciclare
									//		- Se sono diversi, fai la differenza (aggiornando i flag) e ritorna
									// 
	_Confronto:						//	Confronto(ESI=word1, EDI=word2):
		XOR ECX, ECX;				//		ECX = 0
									
	_CicloStringa:					//		do:
		MOV DL, [ESI][ECX];			//			DL = word1[ECX]
		MOV DH, [EDI][ECX];			//			DH = word2[ECX]
		INC ECX;					//			ECX++ (updated here to not interfere with flags after compares)

		CMP DL, DH;					//			compare DL DH
		JNE _ConfrontoRet;			//			if DL != DH: return
		CMP DL, 0;					//			compare DL, 0
		JE _ConfrontoRet;			//			if DL (== DH) == 0: return
		
		JMP _CicloStringa;			//		while (true)

	_ConfrontoRet:
		RET;						// 

	_Sort:							//	Sort(EAX=num):
	_Ciclo_Iterazioni:				//		do:
		MOV EBX, num;				//			EBX = num
		DEC EBX;					//			EBX-- (num-1..1)
	
	_Ciclo_Confronti:				//			do:
		MOV ESI, strings[EBX*4-4];	//				ESI = (int)strings[EBX-1] (word1: strings[num-2..0])
		MOV EDI, strings[EBX*4];	//				EDI = (int)strings[EBX]	  (word2: strings[num-1..1])
		
		CALL _Confronto;			//				Confronto()
		JBE _NoSwap;				//				if word1 <= word2: skip swap
									//				Swap:
		MOV strings[EBX*4-4], EDI;	//				strings[num-2..0] = word2
		MOV strings[EBX*4], ESI;	//				strings[num-1..1] = word1

	_NoSwap:					
		DEC EBX;					//				EBX--
		JNZ _Ciclo_Confronti;		//			while EBX > 0
		
		DEC EAX;					//			EAX--
		JNZ _Ciclo_Iterazioni;		//		while EAX > 0

	_End:
	}

	// Stampa su video
	{
		int i;
		for (i = 0; i < num; i++)
			printf("%s\n", strings[i]);
	}
}
