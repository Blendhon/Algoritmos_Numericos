#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>

// Função para exibir a matriz lida do arquivo
void exibir_matriz(int dim, double** a, double b[]) {
    printf("\nMatriz A | Vetor B:\n");
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            printf("%.2f\t", a[i][j]);
        }
        printf("|\t%.2f\n", b[i]);
    }
}

void eliminacao_de_gauss(int n, double** a, double b[], double x[]) {
    int k, l, c;
    double m;

    // Realiza a Eliminação de Gauss
    for (k = 0; k < n - 1; k++) {
        for (l = k + 1; l < n; l++) {
            m = a[l][k] / a[k][k];
            for (c = k; c < n; c++) {
                a[l][c] -= m * a[k][c];
            }
            b[l] -= m * b[k];
        }
    }

    // Exibe a matriz após a Eliminação de Gauss
    printf("\nMatriz apos Eliminacao de Gauss:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.2f\t", a[i][j]);
        }
        printf("|\t%.2f\n", b[i]);
    }

    // Substituição reversa para encontrar as soluções
    for (l = n - 1; l >= 0; l--) {
        for (k = l + 1; k < n; k++) {
            b[l] -= a[l][k] * x[k];
        }
        x[l] = b[l] / a[l][l];
    }

    // Exibe as soluções
    printf("\nSolucoes:\n");
    for (int i = 0; i < n; i++) {
        printf("x[%d] = %.3f\n", i + 1, x[i]);
    }
}

void fatoracao_lu(int n, double** a, double b[], double x[]) {
    double L[n][n] = {0};
    double U[n][n] = {0};
    double y[n] = {0};

    // Fatoração LU
    for (int i = 0; i < n; i++) {
        for (int k = i; k < n; k++) {
            U[i][k] = a[i][k];
            for (int j = 0; j < i; j++) {
                U[i][k] -= L[i][j] * U[j][k];
            }
        }
        for (int k = i; k < n; k++) {
            if (i == k) {
                L[i][i] = 1;
            } else {
                L[k][i] = a[k][i];
                for (int j = 0; j < i; j++) {
                    L[k][i] -= L[k][j] * U[j][i];
                }
                L[k][i] /= U[i][i];
            }
        }
    }

    printf("\nTriangular inferior\t\t\tTriangular superior\n\n");
    for (int i = 0; i < n; i++) {
        // Triangular inferior
        for (int j = 0; j < n; j++)
            printf("%.2f\t", L[i][j]);
        printf("\t");

        // Triangular superior
        for (int j = 0; j < n; j++)
            printf("%.2f\t", U[i][j]);
        printf("\n");
    }

    // Resolução do sistema Ly = b
    for (int i = 0; i < n; i++) {
        y[i] = b[i];
        for (int j = 0; j < i; j++) {
            y[i] -= L[i][j] * y[j];
        }
    }

    // Resolução do sistema Ux = y
    for (int i = n - 1; i >= 0; i--) {
        x[i] = y[i];
        for (int j = i + 1; j < n; j++) {
            x[i] -= U[i][j] * x[j];
        }
        x[i] /= U[i][i];
    }

    // Exibe as soluções
    printf("\nSolucoes:\n");
    for (int i = 0; i < n; i++) {
        printf("x[%d] = %.3f\n", i + 1, x[i]);
    }
}

/* int diagonalmente_dominante(int n, double** a) {
    for (int i = 0; i < n; i++) {
        double soma = 0.0;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                	soma += fabs(a[i][j]);
            }
        }
        
        if (fabs(a[i][i]) <= soma) {
            return 0; // Não é diagonalmente dominante
        }
    }
    return 1; // É diagonalmente dominante
} */

void gauss_jacobi(int n, double** a, double b[], double x1[], double x2[], int max_iter, double tol) {

	double erro = 0.0;
    double erro_ant = 0.0;
        
    // Inicializa a solução com zero
    for (int i = 0; i < n; i++) {
        x1[i] = 0.0;
    }

    // Iterações
    for (int iter = 0; iter < max_iter; iter++) {
        // Copia o valor atual de x1 para x2
        for (int i = 0; i < n; i++) {
            x2[i] = x1[i];
        }

        // Atualiza os valores de x1 usando os valores anteriores de x2
        for (int i = 0; i < n; i++) {
            double soma = b[i];
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    soma -= a[i][j] * x2[j]; // Usa x2 ao invés de x1
                }
            }
            x1[i] = soma / a[i][i];
        }

        // Verifica a convergência
        erro_ant = erro;
        erro = 0.0;
        for (int i = 0; i < n; i++) {
            erro = fmax(erro, fabs(x1[i] - x2[i]));
        }
        
		// Atualiza x2
		for (int i = 0; i < n; i++) {
			x2[i] = x1[i];
		}
        
        // Exibe o erro atual
        printf("\nIteracao %d: erro = %.6f", iter + 1, erro);
        
        if (erro < tol) {
        	printf("\n\nPrecisao desejada: %.6f\n", tol);
            printf("\nConvergiu em %d iteracoes\n", iter + 1);
            printf("\nSolucoes:\n");
            for (int i = 0; i < n; i++) {
                printf("x[%d] = %.3f\n", i + 1, x2[i]);
            }
            return;
        } else if (erro >= 100 && erro > erro_ant && iter > 8) {
        	printf("\n\nO erro tende a infinito e a funcao nao converge\n");
        	return;
		}
    }

    printf("\n\nNao convergiu em %d iteracoes\n", max_iter);
}

void gauss_seidel(int n, double** a, double b[], double x1[], double x2[], int max_iter, double tol) {

	double erro = 0.0;
    double erro_ant = 0.0;
    
    // Inicializa a solução com zero
    for (int i = 0; i < n; i++) {
        x1[i] = 0.0;
    }

    // Iterações
    for (int iter = 0; iter < max_iter; iter++) {
        // Copia o valor atual de x1 para x2
        for (int i = 0; i < n; i++) {
            x2[i] = x1[i];
        }

        // Atualiza os valores de x1
        for (int i = 0; i < n; i++) {
            double soma = b[i];
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    soma -= a[i][j] * x1[j];
                }
            }
            x1[i] = soma / a[i][i];
        }

        // Verifica a convergência
        erro_ant = erro;
        erro = 0.0;
        for (int i = 0; i < n; i++) {
            erro = fmax(erro, fabs(x1[i] - x2[i]));
        }

        // Exibe o erro atual
        printf("\nIteracao %d: erro = %.6f", iter + 1, erro);

        if (erro < tol) {
        	printf("\n\nPrecisao desejada: %.6f\n", tol);
            printf("\nConvergiu em %d iteracoes\n", iter + 1);
            printf("\nSolucoes:\n");
            for (int i = 0; i < n; i++) {
                printf("x[%d] = %.3f\n", i + 1, x1[i]);
            }
            return;
        } else if (erro >= 100 && erro > erro_ant && iter > 8) {
        	printf("\n\nO erro tende a infinito e a funcao nao converge\n");
        	return;
		}
    }

    printf("\n\nNao convergiu em %d iteracoes\n", max_iter);
}

void ler_matriz(const char* nome_arquivo, int metodo) {
    int n_sis, dim;  // Número de sistemas / Dimensão
    double prec;     // Precisão

    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        perror("\n\n--------------------------------\n\nErro ao abrir o arquivo");
        exit(1);
    }

    fscanf(arquivo, "%d %d %lf\n", &n_sis, &dim, &prec);

    // Aloca dinamicamente a matriz A
    double** a = new double*[dim];
    for (int i = 0; i < dim; i++) {
        a[i] = new double[dim];
    }

    double b[dim], x1[dim], x2[dim];

    // Lê os coeficientes da matriz A
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            fscanf(arquivo, "%lf", &a[i][j]);
        }
    }

    clock_t start, end;
    start = clock();

    // Processa cada sistema
    for (int sistema = 0; sistema < n_sis; sistema++) {
        // Lê o vetor B para o sistema atual
        for (int k = 0; k < dim; k++) {
            fscanf(arquivo, "%lf", &b[k]);
        }

        printf("\n\n--------------------------------\n\n");
        printf("\nSistema %d:\n", sistema + 1);
        exibir_matriz(dim, a, b);  // Chama a função para exibir a matriz lida

        // Escolhe o método de solução
        if (metodo == 0) {
        	// Cria uma cópia da matriz a
	        double** a_copia = new double*[dim];
	        for (int i = 0; i < dim; i++) {
	            a_copia[i] = new double[dim];
	            for (int j = 0; j < dim; j++) {
	                a_copia[i][j] = a[i][j];
	            }
	        }
	        
            eliminacao_de_gauss(dim, a_copia, b, x1);
            
            // Libera a memória alocada para a_copia
	        for (int i = 0; i < dim; i++) {
				delete[] a_copia[i];
			}
			delete[] a_copia;
		} else if (metodo == 1) {
 			fatoracao_lu(dim, a, b, x1);
		} else if (metodo == 2) {
			gauss_jacobi(dim, a, b, x1, x2, 1000, prec);
		} else if (metodo == 3) {
			gauss_seidel(dim, a, b, x1, x2, 1000, prec);
        } else {
			printf("\n\nMetodo desconhecido\n");
		}
	}

    end = clock();

    printf("\n\n--------------------------------\n\n");
    printf("\nTempo gasto para calcular: %5.3f seg.\n", ((double)(end - start)) / CLOCKS_PER_SEC);

    // Libera a memória alocada para a matriz A
    for (int i = 0; i < dim; i++) {
        delete[] a[i];
    }
    delete[] a;

    fclose(arquivo);
}

