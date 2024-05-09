#include <stdio.h>
#include <stdlib.h>

/// <summary>
/// Ricerca di un carattere in una stringa
/// </summary>
void ricerca()
{
    char Stringa[] = "Questa è una stringa";
    int Lunghezza = sizeof(Stringa) - 1;
    char Carattere = 'è';
    int Posizione;

    __asm
    {
        MOV ECX, Lunghezza
        CMP ECX, 0
        JE Fine // stringa vuota
        XOR EAX, EAX
        XOR EBX, EBX
        MOV BL, Carattere
    Ciclo:
        MOV AL, Stringa[ECX-1]
        CMP EAX, EBX
        JE Fine
        LOOP Ciclo
    Fine:
        DEC ECX
        MOV Posizione, ECX
    }

    printf("Posizione=%d\n", Posizione);
}

/// <summary>
/// Dato un numero, dire se è una potenza di due
/// </summary>
void potenza()
{
    unsigned int Num = 0b10001;
    unsigned int Ris;

    // Num potenza di 2 => solo un bit è a 1

    __asm
    {
        XOR EAX, EAX // Ris = 0
        MOV EBX, Num
        CMP EBX, 0
        JE Fine // jump if Num = 0
    TestFirst1: // check if first bit is 1
        TEST EBX, 1
        JNZ CheckRis // true
        SHR EBX, 1 // shift right
        JMP TestFirst1 // retry (x != 0 => there's at least a 1)
    CheckRis:
        CMP EBX, 1
        JNE Fine // more than 1 bit is at value 1
        INC EAX // Ris = 1
    Fine:
        MOV Ris, EAX
    }

    printf("Ris=%d\n", Ris);
}


int main()
{
    ricerca();
    potenza();
}