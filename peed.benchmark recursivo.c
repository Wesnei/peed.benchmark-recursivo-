
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gerarArquivo(int quantidade) {
    FILE *arquivo = fopen("numeros.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        exit(1);
    }

    srand(time(NULL));

    for (int i = 0; i < quantidade; i++) {
        int numero = rand() % 1000;
        fprintf(arquivo, "%d ", numero);
    }

    fclose(arquivo);
}

int buscaLinear(int numero) {
    FILE *arquivo = fopen("numeros.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        exit(1);
    }

    int elemento;
    clock_t inicio = clock();

    while (fscanf(arquivo, "%d", &elemento) != EOF) {
        if (elemento == numero) {
            fclose(arquivo);
            clock_t fim = clock();
            return (int)(fim - inicio);
        }
    }

    fclose(arquivo);
    return -1;
}

int buscaSentinela(int numero) {
    FILE *arquivo = fopen("numeros.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        exit(1);
    }

    int elemento;
    int ultimoElemento;
    clock_t inicio = clock();

    while (fscanf(arquivo, "%d", &elemento) != EOF) {
        if (elemento == numero) {
            fclose(arquivo);
            clock_t fim = clock();
            return (int)(fim - inicio);
        }
        ultimoElemento = elemento;
    }

    if (ultimoElemento == numero) {
        fclose(arquivo);
        clock_t fim = clock();
        return (int)(fim - inicio);
    }

    fclose(arquivo);
    return -1;
}

int particionar(int *numeros, int esquerda, int direita) {
    int pivo = numeros[direita];
    int i = esquerda - 1;

    for (int j = esquerda; j <= direita - 1; j++) {
        if (numeros[j] < pivo) {
            i++;
            int temp = numeros[i];
            numeros[i] = numeros[j];
            numeros[j] = temp;
        }
    }

    int temp = numeros[i + 1];
    numeros[i + 1] = numeros[direita];
    numeros[direita] = temp;

    return i + 1;
}

void quickSort(int *numeros, int esquerda, int direita) {
    if (esquerda < direita) {
        int pivo = particionar(numeros, esquerda, direita);
        quickSort(numeros, esquerda, pivo - 1);
        quickSort(numeros, pivo + 1, direita);
    }
}

int buscaBinaria(int numero, int quantidade) {
    FILE *arquivo = fopen("numeros.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        exit(1);
    }

    int *numeros = (int *)malloc(quantidade * sizeof(int));
    if (numeros == NULL) {
        printf("Erro de alocação de memória.\n");
        exit(1);
    }

    for (int i = 0; i < quantidade; i++) {
        fscanf(arquivo, "%d", &numeros[i]);
    }

    fclose(arquivo);

    quickSort(numeros, 0, quantidade - 1);

    clock_t inicio = clock();
    int esquerda = 0;
    int direita = quantidade - 1;

    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;

        if (numeros[meio] == numero) {
            free(numeros);
            clock_t fim = clock();
            return (int)(fim - inicio);
        }

        if (numeros[meio] < numero) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }

    free(numeros);
    return -1;
}

void bubbleSort(int *numeros, int quantidade) {
    clock_t inicio = clock();

    for (int i = 0; i < quantidade - 1; i++) {
        for (int j = 0; j < quantidade - i - 1; j++) {
            if (numeros[j] > numeros[j + 1]) {
                int temp = numeros[j];
                numeros[j] = numeros[j + 1];
                numeros[j + 1] = temp;
            }
        }
    }

    clock_t fim = clock();
    printf("Tempo gasto no Bubble Sort: %d ms\n", (int)(fim - inicio));
}

void insertionSort(int *numeros, int quantidade) {
    clock_t inicio = clock();

    for (int i = 1; i < quantidade; i++) {
        int chave = numeros[i];
        int j = i - 1;

        while (j >= 0 && numeros[j] > chave) {
            numeros[j + 1] = numeros[j];
            j--;
        }

        numeros[j + 1] = chave;
    }

    clock_t fim = clock();
    printf("Tempo gasto no Insertion Sort: %d ms\n", (int)(fim - inicio));
}

int fatorialRecursivo(int n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * fatorialRecursivo(n - 1);
    }
}

int fibonacciRecursivo(int n) {
    if (n <= 1) {
        return n;
    } else {
        return fibonacciRecursivo(n - 1) + fibonacciRecursivo(n - 2);
    }
}

int somatorioRecursivo(int n) {
    if (n == 0) {
        return 0;
    } else {
        return n + somatorioRecursivo(n - 1);
    }
}

int main() {
    int quantidade;
    int escolha;

    printf("Quantos números inteiros aleatórios você deseja gerar e salvar no arquivo? ");
    scanf("%d", &quantidade);

    gerarArquivo(quantidade);

    do {
        printf("\nEscolha uma operação:\n");
        printf("1. Busca de elemento (Linear, Sentinela, Binária)\n");
        printf("2. Classificação de elementos (Bubble Sort, Insertion Sort, Quick Sort)\n");
        printf("3. Comparação entre algoritmos iterativos e recursivos\n");
        printf("0. Sair\n");
        printf("Es

colha: ");
        scanf("%d", &escolha);

        if (escolha == 1) {
            int numero;
            printf("Digite o número que deseja buscar: ");
            scanf("%d", &numero);

            int tempoLinear = buscaLinear(numero);
            int tempoSentinela = buscaSentinela(numero);
            int tempoBinaria = buscaBinaria(numero, quantidade);

            if (tempoLinear != -1) {
                printf("Número encontrado com busca Linear em %d ms.\n", tempoLinear);
            } else {
                printf("Número não encontrado com busca Linear.\n");
            }

            if (tempoSentinela != -1) {
                printf("Número encontrado com busca Sentinela em %d ms.\n", tempoSentinela);
            } else {
                printf("Número não encontrado com busca Sentinela.\n");
            }

            if (tempoBinaria != -1) {
                printf("Número encontrado com busca Binária em %d ms.\n", tempoBinaria);
            } else {
                printf("Número não encontrado com busca Binária.\n");
            }
        } else if (escolha == 2) {
            FILE *arquivo = fopen("numeros.txt", "r");
            if (arquivo == NULL) {
                printf("Erro ao abrir o arquivo para leitura.\n");
                exit(1);
            }

            int *numeros = (int *)malloc(quantidade * sizeof(int));
            if (numeros == NULL) {
                printf("Erro de alocação de memória.\n");
                exit(1);
            }

            for (int i = 0; i < quantidade; i++) {
                fscanf(arquivo, "%d", &numeros[i]);
            }

            fclose(arquivo);

            int *copia = (int *)malloc(quantidade * sizeof(int));
            if (copia == NULL) {
                printf("Erro de alocação de memória.\n");
                exit(1);
            }

            for (int i = 0; i < quantidade; i++) {
                copia[i] = numeros[i];
            }

            clock_t inicioQuickSort = clock();
            quickSort(numeros, 0, quantidade - 1);
            clock_t fimQuickSort = clock();

            bubbleSort(copia, quantidade);
            insertionSort(numeros, quantidade);

            free(numeros);
            free(copia);

            printf("Tempo gasto no Quick Sort: %d ms\n", (int)(fimQuickSort - inicioQuickSort));
        } else if (escolha == 3) {
            int n;
            printf("Digite um número para operações recursivas: ");
            scanf("%d", &n);

            clock_t inicioFatorialRecursivo = clock();
            int resultadoFatorialRecursivo = fatorialRecursivo(n);
            clock_t fimFatorialRecursivo = clock();
            printf("Fatorial Recursivo de %d: %d em %d ms\n", n, resultadoFatorialRecursivo, (int)(fimFatorialRecursivo - inicioFatorialRecursivo));

            clock_t inicioFatorialIterativo = clock();
            int resultadoFatorialIterativo = 1;
            for (int i = 1; i <= n; i++) {
                resultadoFatorialIterativo *= i;
            }
            clock_t fimFatorialIterativo = clock();
            printf("Fatorial Iterativo de %d: %d em %d ms\n", n, resultadoFatorialIterativo, (int)(fimFatorialIterativo - inicioFatorialIterativo));

            clock_t inicioSomatorioRecursivo = clock();
            int resultadoSomatorioRecursivo = somatorioRecursivo(n);
            clock_t fimSomatorioRecursivo = clock();
            printf("Somatório Recursivo de 1 até %d: %d em %d ms\n", n, resultadoSomatorioRecursivo, (int)(fimSomatorioRecursivo - inicioSomatorioRecursivo));

            clock_t inicioSomatorioIterativo = clock();
            int resultadoSomatorioIterativo = 0;
            for (int i = 1; i <= n; i++) {
                resultadoSomatorioIterativo += i;
            }
            clock_t fimSomatorioIterativo = clock();
            printf("Somatório Iterativo de 1 até %d: %d em %d ms\n", n, resultadoSomatorioIterativo, (int)(fimSomatorioIterativo - inicioSomatorioIterativo));

            clock_t inicioFibonacciRecursivo = clock();
            int resultadoFibonacciRecursivo = fibonacciRecursivo(n);
            clock_t fimFibonacciRecursivo = clock();
            printf("Fibonacci Recursivo de %d: %d em %d ms\n", n, resultadoFibonacciRecursivo, (int)(fimFibonacciRecursivo - inicioFibonacciRecursivo));

            int a = 0, b = 1;
            clock_t inicioFibonacciIterativo = clock();
            for (int i = 2; i <= n; i++) {
                int temp = a + b;
                a = b;
                b = temp;
            }
            clock_t fimFibonacciIterativo = clock();
            printf("Fibonacci Iterativo de %d: %d em %d ms\n", n, b, (int)(fimFibonacciIterativo - inicioFibonacciIterativo));
        }
    } while (escolha != 0);

    return 0;
}
