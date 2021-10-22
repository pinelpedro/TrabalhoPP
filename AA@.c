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

int MD = 1; // Selecionador de modo PLAY(0) / CORR(1)

// -Protótipos-
int argsOk(int argc, char *argv[]);
void errorMsg(int x);
void initOcean(char ocean[6][6]);
void showOcean(char ocean[6][6]);
void mantemOcean(char ocean[6][6]);
void showInventory(int d, int s, int t);
void submarinesIntoOcean(char ocean[6][6]);

int
main(int argc, char *argv[])
{
    char ocean[6][6]; // Oceano
    int d = 0;        // Quantidade destroyers
    int s = 3;        // Quantidade submarinos
    int t = 0;        // Quantidades torpedos

    int i = 0;
    int j = 0;
    char tentativa[2];  // Posição escolhida pelo jogador
    int ativo = 1;      // Condição para manter o jogo
    int coluna = 0;
    int fileira = 0;
    int r = 0;          // Valor do erro (argsOK)

	
    if( (r = argsOk(argc, argv)) != 0)
    {
        errorMsg(r);
        return r;
    }

    if(strcmp(argv[1], "-t") == 0)
    {
        t = atoi(argv[2]);
	MD = atoi(argv[4]);   
    }
    else
    {
        MD = atoi(argv[2]);
	t = atoi(argv[4]);   
    }

    initOcean(ocean);

    for(i=1;i<=s;i++)
    {
        submarinesIntoOcean (ocean);
    }

    while(ativo!=0)
    {
        mantemOcean(ocean);
        showOcean(ocean);
        showInventory (d,s,t);

        printf("onde deseja soltar o torpedo?  ");
        scanf("%s",&tentativa);

        coluna = tentativa[1] - '0';

        if(tentativa[0]=='A')
        {
            fileira = 1;
        }
        if(tentativa[0]=='B')
        {
            fileira = 2;
        }
        if(tentativa[0]=='C')
        {
            fileira = 3;
        }
        if(tentativa[0]=='D')
        {
            fileira = 4;
        }
        if(tentativa[0] == 'E')
        {
            fileira = 5;
        }

        for(i = 1; i <= 5; i++)
        {
            for(j = 1; j <= 5; j++)
            {
                if(ocean[i][j] == 'S')
                {
                    if (i == fileira && j == coluna)
                    {
                        ocean[i][j] = '*';
                        s--;
                        t--;
                        printf("\nO torpedo acertou um submarino!\n");
                    }
                }

                if (ocean[i][j] == ' ')
                {
                    if(i== fileira && j == coluna)
                    {
                        t--;
                        ocean[i][j] = 'W';
                        printf("\nO torpedo afundou na agua \n");
                    }
                }

                if (s <=0)
                {
                    ativo = 0;
                    printf("\nParabens, voce destruiu toda a frota!  \n");
                    return 0;
                }

                if (t <= 0)
                {
                    ativo = 0;
                    printf("\nVoce ficou sem torpedos  \n");
                    return 0;
                }
            }
        }
    }

    return 0;
}



void
submarinesIntoOcean (char ocean[6][6])
{
    int X = rand() %5;
    int Y = rand() %5;
    while(X == 0 || Y == 0)
    {
        X = rand() %5;
        Y = rand() %5;
    }

    if(ocean[X+1][Y]=='S'&& X-1 != 0)
    {
        X--;
    }
    if(ocean[X-1][Y]=='S'&& X+1 < 6)
    {
        X++;
    }
    if(ocean[X][Y+1]=='S'&& Y-1 != 0)
    {
        Y--;
    }
    if(ocean[X][Y-1]=='S'&& Y+1 < 6)
    {
        Y++;
    }

    ocean[X][Y] = 'S';
}


void
showInventory (int d, int s, int t)
{
    printf("\n\n Destruidores: %d\n Submarinos--: %d\n Torepedos---: %d\n",d,s,t);
}


void
showOcean(char ocean[6][6])
{
    int i = 0;
    int j = 0;
    for (i = 0; i < 6; i++)
    {
        printf("\n");

        for(j = 0; j < 6; j++)
        {
            if (i == 0)
            {
                printf(" %c  ", ocean[i][j]);
            }
            else
            {
                if(MD == 0)
                {
                    if(ocean[i][j]=='S')
                    {
                        printf("   |");
                    }
                    else
                    {
                        printf(" %c |", ocean[i][j]);
                    }
                }
                if(MD == 1)
                {
                    printf(" %c |", ocean[i][j]);
                }
            }
        }

        printf("\n   +---+---+---+---+---+");
    }
}

void
initOcean(char ocean[6][6])
{
    int i = 0;
    int j = 0;


    for(i=1;i<=5;i++)
    {
        for(j=1;j<=5;j++)
        {
            ocean[i][j] = ' ';
        }
    }

    ocean[0][0] = ' ';

    ocean[1][0] = 'A';
    ocean[2][0] = 'B';
    ocean[3][0] = 'C';
    ocean[4][0] = 'D';
    ocean[5][0] = 'E';

    ocean[0][1] = '1';
    ocean[0][2] = '2';
    ocean[0][3] = '3';
    ocean[0][4] = '4';
    ocean[0][5] = '5';
}

int
argsOk (int argc, char *argv[])
{
    if(argc < 5)
    {
        return 1;
    }
    if(	(((strcmp(argv[1], "-m") == 0) && (strcmp(argv[1], "-t") == 0)) 
	|| (((strcmp(argv[1], "-t") == 0) && (strcmp(argv[1], "-m") == 0)))
    {
        continue;
    }
    else if( (strcmp(argv[1], "-m") == 0) && strcmp(argv[3], "-t") != 0)
    {
        return 2;
    }
    else if( (strcmp(argv[1], "-t") == 0) && strcmp(argv[3], "-m") != 0)
    {
        return 2;
    }
    if( isdigit(*argv[2]) == 0)
    {
        return 3;
    }
    if( isdigit(*argv[4]) == 0)
    {
        return 3;
    }
    return 0;
}

void
errorMsg(int x)
{
    if(x == 1)
    {
	fprintf(stderr, "Faltam argumentos\n");   
    }
    else if(x == 2)
    {
	fprintf(stderr, "Valores invalidos\n");   
    }
    else if(x == 3)
    {
	fprintf(stderr, "O valor passado nao e um digito inteiro\n");   
    }
    else
    {
	fprintf(stderr, "Aconteceu algum erro\n");
    }
}

void
mantemOcean(char ocean[6][6])
{
    ocean[0][0] = ' ';

    ocean[1][0] = 'A';
    ocean[2][0] = 'B';
    ocean[3][0] = 'C';
    ocean[4][0] = 'D';
    ocean[5][0] = 'E';

    ocean[0][1] = '1';
    ocean[0][2] = '2';
    ocean[0][3] = '3';
    ocean[0][4] = '4';
    ocean[0][5] = '5';

}
