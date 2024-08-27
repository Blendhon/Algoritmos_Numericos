#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void menu_ini();
void ler_matriz(const char* nome_arquivo, int metodo);

void reset() {
    int t;

    printf("\n\n--------------------------------\n\n"
        "Precione [ENTER] para voltar ou [ESC] para fechar o programa.");

    while (1) {
        if (kbhit()) {
            t = getch();
            if (t == 13) {
                menu_ini();
                return;
            }
            if (t == 27) {
                printf("\nEncerrando o programa...\n");
                exit(0);
            }
        }
    }
}

void titulo() {
    system("cls");
    printf("--------------------------------\n\n"
        "     ALGORITIMOS NUMERICOS!\n"
        "         SISTEMA LINEAR\n"
        "        ALUNOS: BLENDHON\n"
        "\n--------------------------------\n\n");
}

char* escolher_arquivo() {
    int numero;
    char* nome_arquivo = (char*)malloc(100 * sizeof(char)); // Aloca memória para o nome do arquivo

    if (nome_arquivo == NULL) {
        perror("\n--------------------------------\n\nErro ao alocar memoria");
        exit(1);
    }

    printf("\n Digite o numero do arquivo : ");
    scanf("%d", &numero);

    // Concatena a string para formar o nome do arquivo
    sprintf(nome_arquivo, "sistema%d.dat", numero);
    
    printf("\n Nome do Arquivo : %s\n", nome_arquivo);

    return nome_arquivo;
}

void menu_ini() {
    int opc = 0;
    int tecla;

    while (1) {
        titulo();

        printf("\n  %s Eliminacao de Gauss", opc == 0 ? "-> " : "  ");
        printf("\n  %s Fatoracao LU", opc == 1 ? "-> " : "  ");
        printf("\n  %s Gauss-Jacobi", opc == 2 ? "-> " : "  ");
        printf("\n  %s Gauss-Seidel", opc == 3 ? "-> " : "  ");
        printf("\n                                    ");
        printf("\n  %s Sair\n", opc == 4 ? "-> " : "  ");

        tecla = _getch();

        switch (tecla) {
            case 224:
                tecla = _getch();
                if (tecla == 72) {
                    opc = (opc - 1 + 5) % 5;  // Move para cima com volta
                } else if (tecla == 80) {
                    opc = (opc + 1) % 5;  // Move para baixo com volta
                } else if (tecla == 75) {
                    opc = (opc - 1 + 5) % 5; // Move para a esquerda com volta
                } else if (tecla == 77) {
                    opc = (opc + 1) % 5;  // Move para a direita com volta
                }
                break;

            case 13:
                switch (opc) {

                    case 0:
                        titulo();
                        printf("\n  ->  Eliminacao de Gauss  <-\n");
                        ler_matriz(escolher_arquivo(), opc);
                        reset();
                        return;

                    case 1:
                        titulo();
                        printf("\n      ->  Fatoracao LU  <-\n");
                        ler_matriz(escolher_arquivo(), opc);
                        reset();
                        return;

                    case 2:
                        titulo();
                        printf("\n      ->  Gauss-Jacobi  <-\n");
                        ler_matriz(escolher_arquivo(), opc);
                        reset();
                        return;

                    case 3:
                        titulo();
                        printf("\n      ->  Gauss-Seidel  <-\n");
                        ler_matriz(escolher_arquivo(), opc);
                        reset();
                        return;

                    case 4:
                        titulo();
                        printf("\n");
                        printf("\n\n--------------------------------\n\n"
                            "Precione qualquer tecla para fechar o programa.");

                        while (1) {
                            if (kbhit()) {
                                if (getch()) {
                                    printf("\nEncerrando o programa...\n");
                                    exit(0);
                                }
                            }
                        }
                        return;
                }
                break;
        }
    }
}

