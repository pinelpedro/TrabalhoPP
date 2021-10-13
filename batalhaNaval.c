/*
    Cria um jogo similar ao Batalha Naval. Nesse jogo, uma frota está escondida no oceano,
    portanto, você não consegue perceber onde estão as naves que compõem a frota. O objetivo
    do jogo é você destruir a frota, isto é, afundar todas as naves com a quantidade de torpedos
    disponível.

    por Jhully Vitoria, 2021
    por Pedro Pinel, 2021
    por Luis Arthur, 2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const int MD = 1; // Selecionador de modo PLAY(0) / CORR(1)


void
aleatorio(int A, int B,int naves[6][6])
{

        A = rand() % 5;
        B = rand() % 5;

        if(naves[A + 1][B] == 'S')
        {
            A++;
        }
        if( naves[A - 1][B] == 'S')
        {
            A--;
        }
        if(naves[A][B + 1] == 'S')
        {
            B++;
        }
        if(naves[A][B - 1] == 'S')
        {
            B--;
        }
        if(A == 0)
        {
            A++;
        }
         if(B == 0)
        {
            B++;
        }

        printf(" Valor de A:%d\n Valor de B:%d \n",A,B);

            naves[A][B] = 'S';
}



int main()
{
    // --DECLARANDO AS VARIAVEIS--

    int i = 0; // fileira da matriz(oceano)
    int j = 0; // coluna da matriz(oceano)

    char matriz[6][6]; // matriz do oceno
    int act = 0; // quantas chances faltam
    int torpedos = 6; // quantidade máximas de torpedos

    char torpedo[4]; // valor digitado pelo usuário
    int fileira; // fileira que o usuário digitou
    int coluna; // coluna que o usuário digitou

    int naves[6][6]; // matriz das posições das naves
    int submarinos = 3; // quantidade de submarinos
    int A = 0; // número pseudo-aleatório
    int B = 0; // número pseudo-aleatório
    int count = 0; // contador

    // --CRIANDO O OCEANO--

    matriz[1][0] = 'A';
    matriz[2][0] = 'B';
    matriz[3][0] = 'C';
    matriz[4][0] = 'D';
    matriz[5][0] = 'E';

    matriz[0][0] = ' ';
    matriz[0][1] = '1';
    matriz[0][2] = '2';
    matriz[0][3] = '3';
    matriz[0][4] = '4';
    matriz[0][5] = '5';

    for(i = 1; i < 6; i++)
    {
        for(j = 1; j < 6; j++)
        {
            matriz[i][j] = ' ';
        }
    }

    // --MONTANDO A POSIÇÃO DOS NAVIOS--

    naves[1][0] = 'A';
    naves[2][0] = 'B';
    naves[3][0] = 'C';
    naves[4][0] = 'D';
    naves[5][0] = 'E';

    naves[0][0] = ' ';
    naves[0][1] = '1';
    naves[0][2] = '2';
    naves[0][3] = '3';
    naves[0][4] = '4';
    naves[0][5] = '5';

    for(i = 1; i < 6; i++)
    {
        for(j = 1; j < 6; j++)
        {
            naves[i][j] = ' ';
        }
    }

    // --COLOCANDO OS SUBMARINOS NO OCEANO--


    for(i = 1; i <= 3; i++)
    {
    aleatorio(A,B,naves);

    }

    // --MODO DE JOGO PLAY--

    if(MD == 0)
    {
        while(act <= torpedos)
        {
            // --MONSTRANDO O OCEANO NA TELA--

            for (i = 0; i < 6; i++)
            {
                printf("\n");

                for(j = 0; j < 6; j++)
                {
                    if (i == 0)
                    {
                        printf(" %c  ", matriz[i][j]);
                    }
                    else
                    {
                        printf(" %c |", matriz[i][j]);
                    }
                }

            printf("\n   +---+---+---+---+---+");
            }

            printf("\n");
            printf("\n Destroyers:  0\n");
            printf(" Submarines:  %d\n", submarinos);
            printf(" Torpedos:    %d\n", torpedos - act);


            // --VERIFICA VITORIA--

            if(count == 3)
            {
                printf("\n Voce destruiu toda frota, parabens!!\n");
                return 0;
            }
            if(act == torpedos)
            {
                return 0;
            }
            // --LANÇANDO O TORPEDO--

            printf("\n Onde deseja soltar o torpedo: ");
            scanf ("%s", torpedo);
            printf("\n ====================================\n");

            coluna = torpedo[1]-'0';

            switch (torpedo[0])
            {
                case 'A':
                    fileira = 1;
                    break;

                case 'B':
                    fileira = 2;
                    break;

                case 'C':
                    fileira = 3;
                    break;

                case 'D':
                    fileira = 4;
                    break;

                case 'E':
                    fileira = 5;
                    break;

                default:
                    printf(" invalid");
                    break;
            }

            // --CONFIRMANDO O RESULTADO DO TORPEDO--

            if(naves[fileira][coluna] == 'S')
            {
                matriz[fileira][coluna] = '*';
                printf("\n Voce afundou um submarino!\n");
                submarinos--;
                count++;
            }
            else
            {
                matriz[fileira][coluna] = 'W';
                printf("\n O torpedo se perdeu na agua!\n");
            }

            act++;
        }
    }

    // --MODO DE JOGO CORR--

    else if(MD == 1)
    {
        for (i = 0; i < 6; i++)
        {
            printf("\n");

            for(j = 0; j < 6; j++)
            {
                if (i == 0)
                {
                    printf(" %c  ", naves[i][j]);
                }
                else
                {
                    printf(" %c |", naves[i][j]);
                }
            }

            printf("\n   +---+---+---+---+---+ ");
        }

        printf("\n");
        printf("\n Destroyers:  0\n");
        printf(" Submarines:  3\n");
        printf(" Torpedos:    6\n");
    }
return 0;
}
