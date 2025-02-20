#include "utils-random.h"

// https://stackoverflow.com/questions/6127503/shuffle-array-in-c
/* Arrange the N elements of ARRAY in random order.
   Only effective if N is much smaller than RAND_MAX;
   if this may not be the case, use a better random
   number generator. */
void shuffleIntArray(int *array, size_t n)
{
    int i;

    for (i = 0; i < n - 1; i++)
    {
        size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
        int t = array[j];
        array[j] = array[i];
        array[i] = t;
    }
}

void shuffleCharArray(char *array, size_t n)
{
    int i;

    for (i = 0; i < n - 1; i++)
    {
        size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
        char t = array[j];
        array[j] = array[i];
        array[i] = t;
    }
}