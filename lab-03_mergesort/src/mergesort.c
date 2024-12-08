//
// alkaev on 06.12.2023.
//
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>



int int_comparator(const void *a, const void *b) {
    return *(int*)b - *(int*)a;  // Сортировка массива по убыванию.
}


int char_comparator(const void *a, const void *b) {
    return *(char*)b - *(char*)a;

}


int string_comparator(const void *a, const void *b) {
    return strcmp(a, b);
}


void merge(void *arr, size_t element_size,
           int l, int m, int r,
           int (*comparator)(const void *, const void *))
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays
    char* L = malloc (n1 * element_size);
    char* R = malloc (n2 * element_size);


    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        *((char*)(L +element_size * i)) = *((char*)(arr + (l + i) * element_size));
    for (j = 0; j < n2; j++)
        *((char*)( R + j * element_size )) = *((char*)( arr + (m + 1 + j) * element_size));

    // Merge the temp arrays back into arr[l..r
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if ( comparator(*(( char* ) (L + element_size * i )), *(( char* ) (R + element_size * j ))) <= 0 ) {
            *(( char* ) (arr + element_size * k )) = *(( char* ) (L + element_size * i ));
            i++;
        }
        else {
            *(( char* ) (arr + element_size * k )) = *(( char* ) (R + element_size * j )));
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[],
    // if there are any
    while (i < n1) {
        *(( char* ) (arr + element_size * k )) = *(( char* ) (L + element_size * i ));
        i++;
        k++;
    }

    // Copy the remaining elements of R[],
    // if there are any
    while (j < n2) {
        *(( char* ) (arr + element_size * k )) = *(( char* ) (R + element_size * j )));
        j++;
        k++;
    }
}

// l is for left index and r is right index of the
// sub-array of arr to be sorted

void mergesort( void *array,
                size_t elements, size_t element_size,
                int (*comparator)(const void *, const void *)
)
{
    for (int i = 1; i < elements;  i *= 2){
        for (j = 0 to n - i, j += 2 * i){
            merge(*array, element_size, j, j + i, min(j + 2 * i, n))
        }
    }
}