#include <stdio.h>
#include <string.h>

void troca(char a[], char b[]) {
    char temp[100];
    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);
}

void imprimirNomes(char nomes[][100], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s\n", nomes[i]);
    }
}

void bubbleSort(char nomes[][100], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(nomes[j], nomes[j + 1]) > 0) {
                troca(nomes[j], nomes[j + 1]);
            }
        }
    }
}

void selectionSort(char nomes[][100], int n) {
    int minIndex;
    for (int i = 0; i < n - 1; i++) {
        minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (strcmp(nomes[j], nomes[minIndex]) < 0) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            troca(nomes[i], nomes[minIndex]);
        }
    }
}

void insertionSort(char nomes[][100], int n) {
    for (int i = 1; i < n; i++) {
        char key[100];
        strcpy(key, nomes[i]);
        int j = i - 1;
        while (j >= 0 && strcmp(nomes[j], key) > 0) {
            strcpy(nomes[j + 1], nomes[j]);
            j = j - 1;
        }
        strcpy(nomes[j + 1], key);
    }
}



void merge(char nomes[][100], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    char L[n1][100], R[n2][100];

    for (i = 0; i < n1; i++) {
        strcpy(L[i], nomes[left + i]);
    }
    for (j = 0; j < n2; j++) {
        strcpy(R[j], nomes[mid + 1 + j]);
    }

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (strcmp(L[i], R[j]) <= 0) {
            strcpy(nomes[k], L[i]);
            i++;
        } else {
            strcpy(nomes[k], R[j]);
            j++;
        }
        k++;
    }

    while (i < n1) {
        strcpy(nomes[k], L[i]);
        i++;
        k++;
    }

    while (j < n2) {
        strcpy(nomes[k], R[j]);
        j++;
        k++;
    }
}

void mergeSort(char nomes[][100], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(nomes, left, mid);
        mergeSort(nomes, mid + 1, right);
        merge(nomes, left, mid, right);
    }
}

int main() {
    FILE *arquivo;
    arquivo = fopen("nomes2.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    char nomes[1000][100];
    int n = 0;

    while (fgets(nomes[n], sizeof(nomes[0]), arquivo) != NULL) {
        // Remova a quebra de linha se necessário
        int len = strlen(nomes[n]);
        if (len > 0 && nomes[n][len - 1] == '\n') {
            nomes[n][len - 1] = '\0';
        }
        n++;
    }

    fclose(arquivo);

    int op;
    do {
        printf("+------ Menu de Ordenacao ------+\n");
        printf("[1] - Bubble Sort\n");
        printf("[2] - Selection Sort\n");
        printf("[3] - Insertion Sort\n");
        printf("[4] - Merge Sort\n");
        printf("[5] - Sair\n");
        printf("+-------------------------------+\n");
        scanf("%d", &op);

        switch (op) {
            case 1:
                bubbleSort(nomes, n);
                printf("Nomes ordenados pelo Bubble Sort:\n");
                imprimirNomes(nomes, n);
                break;
            case 2:
                selectionSort(nomes, n);
                printf("Nomes ordenados pelo Selection Sort:\n");
                imprimirNomes(nomes, n);
                break;
            case 3:
                insertionSort(nomes, n);
                printf("Nomes ordenados pelo Insertion Sort:\n");
                imprimirNomes(nomes, n);
                break;
            case 4:
                mergeSort(nomes, 0, n - 1);
                printf("Nomes ordenados pelo Merge Sort:\n");
                imprimirNomes(nomes, n);
                break;
            case 5:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (op != 5);

    return 0;
}

