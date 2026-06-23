#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

void merge(int arr[], int left, int mid, int right) {
int n1 = mid - left + 1;
int n2 = right - mid;

int* L = (int*)malloc(n1 * sizeof(int));
int* R = (int*)malloc(n2 * sizeof(int));

for (int i = 0; i < n1; i++) L[i] = arr[left + i];
for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

int i = 0, j = 0, k = left;

while (i < n1 && j < n2) {
if (L[i] <= R[j]) {
arr[k] = L[i];
i++;
}
else {
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

free(L);
free(R);
}

void mergeSort(int arr[], int left, int right) {
if (left >= right) {
return;
}

int mid = left + (right - left) / 2;
mergeSort(arr, left, mid);
mergeSort(arr, mid + 1, right);
merge(arr, left, mid, right);
}

void printArray(int arr[], int size) {
for (int i = 0; i < size; i++) {
printf("%d ", arr[i]);
}
printf("\n");
}

int main() {
setlocale(LC_ALL, "Russian");
srand(time(NULL));

int arr[100];
int n = 0;
int choice;

printf("Сортировка слиянием:\n");
printf("1. Ввести данные вручную\n");
printf("2. Считать данные из файла (input.txt)\n");
printf("3. Сгенерировать массив случайно\n");

if (scanf("%d", &choice) != 1) {
printf("Ошибка: нужно ввести число от 1 до 3!\n");
return 1;
}

if (choice == 1) {
printf("Введите количество элементов (от 1 до 100): ");
if (scanf("%d", &n) != 1 || n <= 0 || n > 100) {
printf("Ошибка: неверное количество элементов!\n");
return 1;
}

printf("Введите %d элементов через пробел: ", n);
for (int i = 0; i < n; i++) {
if (scanf("%d", &arr[i]) != 1) {
printf("Ошибка: ожидалось число!\n");
return 1;
}
}
}
else if (choice == 2) {
FILE* fileIn = fopen("input.txt", "r");
if (fileIn == NULL) {
printf("Ошибка: файл input.txt не найден!\n");
return 1;
}

while (fscanf(fileIn, "%d", &arr[n]) == 1) {
n++;
if (n >= 100) break;
}
fclose(fileIn);

if (n == 0) {
printf("Ошибка: файл пуст или в нем нет чисел!\n");
return 1;
}
printf("Успешно считано %d элементов из файла.\n", n);
}
else if (choice == 3) {
printf("Введите желаемый размер массива (от 1 до 100): ");
if (scanf("%d", &n) != 1 || n <= 0 || n > 100) {
printf("Ошибка: неверное количество элементов!\n");
return 1;
}

for (int i = 0; i < n; i++) {
arr[i] = rand() % 100;
}
printf("Массив успешно сгенерирован.\n");
}
else {
printf("Ошибка: такого варианта нет в меню.\n");
return 1;
}

printf("\nИсходный массив: ");
printArray(arr, n);

mergeSort(arr, 0, n - 1);

printf("Отсортированный массив: ");
printArray(arr, n);

FILE* fileOut = fopen("output.txt", "w");
if (fileOut != NULL) {
for (int i = 0; i < n; i++) {
fprintf(fileOut, "%d ", arr[i]);
}
fclose(fileOut);
printf("\nРезультат сохранен в output.txt\n");
}
else {
printf("\nОшибка записи в файл.\n");
}

return 0;
}

