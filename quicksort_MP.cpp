#include<iostream>
#include<time.h>
#include<omp.h>

#define dimension 1500

using namespace std;

int particion(int arr[], int limIzq, int limDer){
    int pivot = arr[limDer];
    int i = (limIzq - 1), temp;
    #pragma omp parallel for
    for (int j = limIzq; j <= limDer - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;

        }
    }
    temp = arr[i + 1];
    arr[i + 1] = arr[limDer];
    arr[limDer] = temp;
    return (i + 1);
}

void quicksort(int arr[], int limIzq, int limDer) {
    int j;
    if (limIzq < limDer){
        j = particion(arr, limIzq, limDer);
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                quicksort(arr, limIzq, j - 1);
            }
            #pragma omp section
            {
                quicksort(arr, j + 1, limDer);
            }
        }
    }
}

int main(){
    unsigned t0, t1;
    t0 = clock();
    int *arr, i;
    arr = new int[dimension];
    srand(time(NULL));
    for (i = 0; i < dimension; i++) {
        arr[i] = 1 + rand() % (100);
    }
    for (i = 0; i < dimension; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    quicksort(arr, 0, dimension - 1);
    for (i = 0; i < dimension; i++){
        cout << arr[i] << " ";
    }
    cout << "\n";
    t1 = clock();
    double time = (double(t1 - t0) / CLOCKS_PER_SEC);
    cout << "Tiempo de Ejecucion: " << time << endl;
    return 0;
}