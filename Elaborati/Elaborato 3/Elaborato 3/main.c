/********************************************************************************
 *                                                                              *
 *                   Architetture dei sistemi di Elaborazione                   *
 *                                                                              *
 ********************************************************************************

 Elaborato 3
 Descrizione:	Data una sequenza di bit, sapendo che ogni n bit (di dati) vi �
                un bit di parit� (1 se il numero di bit a 1 fra i precedenti n �
                dispari), verificare se vi sono errori.

 ********************************************************************************/

#include <stdio.h>

void main()
{
    // Input
    unsigned char vet[] = { 0xE3,0xA5,0x0E,0x92,0x2F,0xB2,0x00 };
    unsigned int len = 50;	// lunghezza (numero di bit)
    unsigned char n = 4;	// numero di bit dati

    // Ouput
    unsigned char errori = 0;	// 1 = errori; 0 = no errori

    __asm
    {
                                //  # reset registers
        XOR EAX, EAX;           //  EAX = 0;
        XOR EBX, EBX;           //  EBX = 0;
        XOR ECX, ECX;           //  ECX = 0;
        XOR EDX, EDX;           //  EDX = 0;
        XOR ESI, ESI;           //  ESI = 0;
        XOR EDI, EDI;           //  EDI = 0;

        LEA ESI, vet;           //  ESI = vet # pointer to vet[0]
        MOV BL, [ESI];          //  BL = *ESI
        MOV EDI, 8;             //  EDI = 8 # size of byte

        MOV DL, n;              //  DL = n;
        INC EDX;                //  EDX = n+1;
        MOV ECX, len;           //  ECX = len
    _MainLoop:                  //  do:
        TEST BL, 1;             //      check first bit of BL
        JZ _SkipIncrement;      //      if == 0: jump to SkipIncrement
        INC EAX;                //      EAX++;
    
    _SkipIncrement:             //      SkipIncrement:
        SHR BL, 1;              //      BL >> # point next bit
        DEC EDX;                //      EDX--;
        JNZ _SetPointer;        //      if EDX > 0: jump to SetPointer # skip CheckParity
    
    _CheckParity:
        TEST EAX, 1;            //      check first bit of EAX
        JNZ _SetError;          //      if != 0: ERROR # even number of 1 = parity
        XOR EAX, EAX;           //      EAX = 0;
        MOV DL, n;              //      DL = n;
        INC EDX;                //      EDX = n+1;

    _SetPointer:                //      SetPointer:
        DEC EDI;                //      EDI--
        JNZ _MainLoopEND;       //      if EDI != 0: jump to MainLoopEND
        INC ESI;                //      ESI++ # point next value of vector
        MOV BL, [ESI];          //      BL = *ESI
        MOV EDI, 8;             //      EDI = 8 # size of byte

    _MainLoopEND:               //      MainLoopEND:
        LOOP _MainLoop;         //  ECX--; while ECX > 0
        JMP _End;               //  END

    _SetError:
        MOV errori, 1;          //  errori = 1
    _End:
    }

    // Stampa su video
    printf("La sequenza di bit %scontiene errori\n", (errori ? "" : "non "));
}

