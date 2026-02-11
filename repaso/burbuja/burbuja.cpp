#include <iostream>
#include <chrono>
#include <cstdlib>
using namespace std;
using namespace chrono;

void burbuja(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n = 1000;
    const int LIMITE_TIEMPO = 60;

    while (true) {
        int* arr = new int[n];

        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 100000;
        }

        auto inicio = high_resolution_clock::now();
        burbuja(arr, n);
        auto fin = high_resolution_clock::now();

        duration<double> tiempo = fin - inicio;

        cout << "Elementos: " << n
             << " | Tiempo: " << tiempo.count() << " segundos" << endl;

        delete[] arr;

        if (tiempo.count() >= LIMITE_TIEMPO) {
            cout << "\nMaximo aproximado de elementos ordenados en menos de 1 minuto: "
                 << n << endl;
            break;
        }

        n += 10000;
    }

    return 0;
}