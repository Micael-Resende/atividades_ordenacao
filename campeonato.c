#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Partida {
    char time_casa[4];
    int gols_casa;
    char time_fora[4];
    int gols_fora;
};

struct Time {
    char nome[4];
    int pontos;
    int vitorias;
    int empates;
    int derrotas;
    int saldo_gols;
    int gols_pro;
    int gols_contra;
};

void trocaTime(struct Time *a, struct Time *b) {
    struct Time temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void imprimirTimes(struct Time times[], int num_times) {
    printf("+----------------------+--------+----------+---------+-----------+---------+---------+\n");
    printf("| Nome do Time         | Pontos | Vitorias | Empates | Derrotas  | Saldo   | Gols    |\n");
    printf("+----------------------+--------+----------+---------+-----------+---------+---------+\n");

    for (int i = num_times - 1; i >= 0; i--) {
        printf("| %-20s | %-6d | %-8d | %-7d | %-9d | %-7d | %-7d |\n", times[i].nome, times[i].pontos, times[i].vitorias,
               times[i].empates, times[i].derrotas, times[i].saldo_gols, times[i].gols_pro);
    }

    printf("+----------------------+--------+----------+--------+------------+---------+---------+\n");
}


void bubbleSort(struct Time arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].pontos < arr[j + 1].pontos ||
                (arr[j].pontos == arr[j + 1].pontos && arr[j].vitorias < arr[j + 1].vitorias) ||
                (arr[j].pontos == arr[j + 1].pontos && arr[j].vitorias == arr[j + 1].vitorias && arr[j].saldo_gols < arr[j + 1].saldo_gols) ||
                (arr[j].pontos == arr[j + 1].pontos && arr[j].vitorias == arr[j + 1].vitorias && arr[j].saldo_gols == arr[j + 1].saldo_gols && arr[j].gols_pro < arr[j + 1].gols_pro)) {
                trocaTime(&arr[j], &arr[j + 1]);
            }
        }
    }
}


void selectionSort(struct Time arr[], int n) {
    int minIndex;
    for (int i = 0; i < n - 1; i++) {
        minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].pontos < arr[minIndex].pontos ||
                (arr[j].pontos == arr[minIndex].pontos && arr[j].vitorias < arr[minIndex].vitorias) ||
                (arr[j].pontos == arr[minIndex].pontos && arr[j].vitorias == arr[minIndex].vitorias && arr[j].saldo_gols < arr[minIndex].saldo_gols) ||
                (arr[j].pontos == arr[minIndex].pontos && arr[j].vitorias == arr[minIndex].vitorias && arr[j].saldo_gols == arr[minIndex].saldo_gols && arr[j].gols_pro < arr[minIndex].gols_pro)) {
                minIndex = j;
            }
        }
        trocaTime(&arr[i], &arr[minIndex]);
    }
}


void insertionSort(struct Time arr[], int n) {
    for (int i = 1; i < n; i++) {
        struct Time key;
        key = arr[i];
        int j = i - 1;
        while (j >= 0 && (key.pontos > arr[j].pontos ||
               (key.pontos == arr[j].pontos && key.vitorias > arr[j].vitorias) ||
               (key.pontos == arr[j].pontos && key.vitorias == arr[j].vitorias && key.saldo_gols > arr[j].saldo_gols) ||
               (key.pontos == arr[j].pontos && key.vitorias == arr[j].vitorias && key.saldo_gols == arr[j].saldo_gols && key.gols_pro > arr[j].gols_pro))) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}


void merge(struct Time arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    struct Time L[n1], R[n2];

    for (i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i].pontos > R[j].pontos || (L[i].pontos == R[j].pontos && L[i].vitorias > R[j].vitorias) ||
            (L[i].pontos == R[j].pontos && L[i].vitorias == R[j].vitorias && L[i].saldo_gols > R[j].saldo_gols) ||
            (L[i].pontos == R[j].pontos && L[i].vitorias == R[j].vitorias && L[i].saldo_gols == R[j].saldo_gols &&
             L[i].gols_pro > R[j].gols_pro)) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(struct Time arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() {
    FILE *arquivo;
    arquivo = fopen("../dados.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    struct Partida partidas[100];
    int num_partidas = 0;
    char linha[100];

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Processar a linha lida e preencher a struct Partida
        sscanf(linha, "%s %dX%d %s", partidas[num_partidas].time_casa,
               &partidas[num_partidas].gols_casa, &partidas[num_partidas].gols_fora,
               partidas[num_partidas].time_fora);

        num_partidas++;
    }

    fclose(arquivo);

    // Inicialize os times e calcule a tabela do campeonato
    struct Time times[20];
    int num_times = 0;

    for (int i = 0; i < num_partidas; i++) {
        // Verifique se os times j� est�o na lista de times
        int time_casa_existente = 0;
        int time_fora_existente = 0;

        for (int j = 0; j < num_times; j++) {
            if (strcmp(times[j].nome, partidas[i].time_casa) == 0) {
                time_casa_existente = 1;
            }
            if (strcmp(times[j].nome, partidas[i].time_fora) == 0) {
                time_fora_existente = 1;
            }
        }

        // Se o time da casa n�o existe, adicione-o � lista de times
        if (!time_casa_existente) {
            strcpy(times[num_times].nome, partidas[i].time_casa);
            times[num_times].pontos = 0;
            times[num_times].vitorias = 0;
            times[num_times].empates = 0;
            times[num_times].derrotas = 0;
            times[num_times].saldo_gols = 0;
            times[num_times].gols_pro = 0;
            times[num_times].gols_contra = 0;
            num_times++;
        }

        // Se o time visitante n�o existe, adicione-o � lista de times
        if (!time_fora_existente) {
            strcpy(times[num_times].nome, partidas[i].time_fora);
            times[num_times].pontos = 0;
            times[num_times].vitorias = 0;
            times[num_times].empates = 0;
            times[num_times].derrotas = 0;
            times[num_times].saldo_gols = 0;
            times[num_times].gols_pro = 0;
            times[num_times].gols_contra = 0;
            num_times++;
        }

        // Calcule o resultado da partida e atualize as estat�sticas dos times
        for (int j = 0; j < num_times; j++) {
            if (strcmp(times[j].nome, partidas[i].time_casa) == 0) {
                times[j].gols_pro += partidas[i].gols_casa;
                times[j].gols_contra += partidas[i].gols_fora;
                times[j].saldo_gols = times[j].gols_pro - times[j].gols_contra;
                if (partidas[i].gols_casa > partidas[i].gols_fora) {
                    times[j].pontos += 3;
                    times[j].vitorias++;
                } else if (partidas[i].gols_casa == partidas[i].gols_fora) {
                    times[j].pontos += 1;
                    times[j].empates++;
                } else {
                    times[j].derrotas++;
                }
            }
            if (strcmp(times[j].nome, partidas[i].time_fora) == 0) {
                times[j].gols_pro += partidas[i].gols_fora;
                times[j].gols_contra += partidas[i].gols_casa;
                times[j].saldo_gols = times[j].gols_pro - times[j].gols_contra;
                if (partidas[i].gols_fora > partidas[i].gols_casa) {
                    times[j].pontos += 3;
                    times[j].vitorias++;
                } else if (partidas[i].gols_fora == partidas[i].gols_casa) {
                    times[j].pontos += 1;
                    times[j].empates++;
                } else {
                    times[j].derrotas++;
                }
            }
        }
    }


    int opcao;
    do {
        printf("Escolha o tipo de ordenacao:\n");
        printf("1. Bubble Sort\n");
        printf("2. Selection Sort\n");
        printf("3. Insertion Sort\n");
        printf("4. Merge Sort\n");
        printf("5. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                bubbleSort(times, num_times);
                // Inverte a ordem dos times ap�s a ordena��o crescente
                for (int i = 0; i < num_times / 2; i++) {
                    trocaTime(&times[i], &times[num_times - i - 1]);
                }
                imprimirTimes(times, num_times);
            break;
            case 2:
                selectionSort(times, num_times);
                imprimirTimes(times, num_times);
                break;
            case 3:
                insertionSort(times, num_times);
                for (int i = 0; i < num_times / 2; i++) {
                    trocaTime(&times[i], &times[num_times - i - 1]);
                }
                imprimirTimes(times, num_times);
                break;
            case 4:
                mergeSort(times, 0, num_times - 1);
                 for (int i = 0; i < num_times / 2; i++) {
                    trocaTime(&times[i], &times[num_times - i - 1]);
                }
                imprimirTimes(times, num_times);
                break;
            case 5:
                printf("Saindo...");
                break;
            default:
                printf("Opcao invalida.\n");
                return 1;
        }
    } while (opcao != 5);


    return 0;
}

