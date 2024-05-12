
/********************************************************************************
 *                                                                              *
 *                   Architetture dei sistemi di Elaborazione                   *
 *                                                                              *
 ********************************************************************************

 Elaborato 2
 Descrizione: Calcolare la matrice di DWORD prodotto di due matrici di WORD.
              Le matrici sono memorizzate per righe all’interno di array
              monodimensionali. Gli elementi delle matrici sono da considerarsi
              con segno (in complemento a due).
 ********************************************************************************/

#include <stdio.h>


void main()
{
    unsigned int m = 3; // numero di righe della prima matrice
    unsigned int n = 2; // numero di colonne della prima matrice
    unsigned int k = 4; // numero di colonne della seconda matrice
    short int mat1[] = { -1,-2, 4,5, 4,-2 }; // prima matrice
    short int mat2[] = { 2,0,0,0, 0,2,0,0 }; // seconda matrice
    int mat3[1024]; // matrice risultato

    __asm
    {
                                    //  Reset registers
        XOR EAX, EAX;               //  EAX = 0
        XOR EBX, EBX;               //  EBX = 0
        XOR ECX, ECX;               //  ECX = 0
        XOR EDX, EDX;               //  EDX = 0

                                    //  Calculate matrix total size
        MOV EAX, m;                 //  EAX = m
        MOV EBX, k;                 //  EBX = k
        MUL EBX;                    //  EDX:EAX = m*k

                                    //  Set result matrix to 0
        MOV ECX, EAX;               //  ECX = EAX (EDX ignored because adresses indexes are 32bit max)
    _ResetLoop:                     //  do:
        MOV mat3[ECX*4-4], 0;       //      (int)mat3[ECX-1] = 0 (no xor because of memory access)
        LOOP _ResetLoop;            //  ECX--; while ECX > 0
        


    }

    // Stampa su video
    {
        unsigned int i, j, h;
        printf("Matrice prodotto:\n");
        for (i = h = 0; i < m; i++)
        {
            for (j = 0; j < k; j++, h++)
                printf("%6d ", mat3[h]);
            printf("\n");
        }
    }
}


