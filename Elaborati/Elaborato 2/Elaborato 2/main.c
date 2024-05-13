
/********************************************************************************
 *                                                                              *
 *                   Architetture dei sistemi di Elaborazione                   *
 *                                                                              *
 ********************************************************************************

 Elaborato 2
 Descrizione: Calcolare la matrice di DWORD prodotto di due matrici di WORD.
              Le matrici sono memorizzate per righe all�interno di array
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
                                    //  # reset registers
        XOR EAX, EAX;               //  EAX = 0
        XOR EBX, EBX;               //  EBX = 0
        XOR ECX, ECX;               //  ECX = 0
        XOR EDX, EDX;               //  EDX = 0
                                    //  # calculate matrix total size
        MOV EAX, m;                 //  EAX = m
        MOV EBX, k;                 //  EBX = k
        MUL EBX;                    //  EDX:EAX = m*k

                                    //  # set result matrix to 0
        MOV ECX, EAX;               //  ECX = EAX # EDX discarded beacuse addresses are 32b
    _ResetLoop:                     //  do:
        MOV mat3[ECX*4-4], 0;       //      (int)mat3[ECX-1] = 0 # no xor because of memory access
        LOOP _ResetLoop;            //  ECX--; while ECX > 0

        MOV EAX, m;                 //  EAX = m
    _Loop1:                         //  do: # i1
        MOV EBX, EAX;               //      PushEAX() # save original value

        MOV ESI, k;                 //      ESI = k # columns of (m,k)
        LEA ESI, [ESI*2];           //      ESI = k * 2 # total i1 row size
        MUL ESI;                    //      EDX:EAX = EAX * ESI # i1 row index offset
        MOV ESI, EAX;               //      ESI = EAX # EDX discarded beacuse addresses are 32b

        MOV EAX, EBX;               //      PopEAX() # retrieve original value
        MOV EBX, k;                 //      EBX = k
    _Loop2:                         //      do: # i2
        MOV ECX, n;                 //          ECX = n
    _Loop3:                         //          do: # i3
        MOV EBX, EAX;               //              PushEAX() # save original

        MOV EDI, k;                 //              EDI = k # columns of (m,k)
        LEA EDI, [EDI*2];           //              EDI = k * 2 # total i3 row size
        
        MOV EAX, ECX;               //              EAX = ECX
        MUL EDI;                    //              EDX:EAX = EAX * EDI # i3 row index offset
        MOV EDI, EAX;               //              EDI = EAX # EDX discarded beacuse of max 32 bit addresses

        XOR EAX, EAX;               //              EAX = 0
                                    //              
                                    //              # Direct matrix indexing with registers gives C2404
                                    //              # MOV EAX, mat3[EBX][ECX*4]; # COMPILE ERROR
        
        LEA EDX, mat1[EDI];         //              EDX = &mat1[i3]
        MOV AX, [EDX][EBX*2-2];     //              AX = EDX[i2]

        LEA EDX, mat2[ESI];         //              EDX = &mat2[i1]
        IMUL AX, [EDX][ECX*2-2];    //              EAX = AX * EDX[i3]
        
        LEA EDX, mat3[ESI];         //              EDX = &mat3[i1]
        ADD [EDX][EBX*2-2], EAX;    //              EDX[i2] += EAX


        MOV EAX, EBX;               //              PopEAX() # retrieve original
        DEC ECX;                    //              ECX--
        JNZ _Loop3;                 //          while ECX > 0
        DEC EBX;                    //          EBX--
        JNZ _Loop3;                 //      while EBX > 0
        DEC EAX;                    //      EAX--
        JNZ _Loop3;                 //  while EAX > 0
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


