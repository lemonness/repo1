#include <stdlib.h>
#include <stdio.h>

void swap(int arr[], int a, int b)
{
    int temp;
    temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

void quicksort(int arr[],int low,int high)
{
    if(low>=high)
        return;
    
    int i ,last;
    last = low;
    for(i=low+1;i<=high;i++)
        if (arr[i]<arr[low])
            swap(arr,++last,i);
    swap(arr,low,last);

    quicksort(arr,low,last-1);
    quicksort(arr,last+1,high);    
    
}

void display(int array[], int maxlen)
{
    int i;
    for (i = 0; i < maxlen; i++)
        printf("%-3d", array[i]);
    printf("\n");
}

int main()
{
    int demo[7] = {25, 12, 4, 65, 27, 14, 33};
    display(demo, 7);
    quicksort(demo, 0, 6);
    display(demo, 7);
}