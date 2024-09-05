#include <stdio.h>
#include <stdlib.h>

int calculate_multiple(int a, int b);
void odd_even(int a, FILE *fptr);

int main()
{
    int *arr1;
    int *arr2;
    int size;

    printf("Enter the array size: ");
    scanf("%d", &size);

    arr1 = (int *)malloc(size * sizeof(int));
    arr2 = (int *)malloc(size * sizeof(int));

    printf("Address of arr1 after allocation: %p", &arr1);
    printf("\n");

    int *ptr = arr1;
    printf("Size of pointer arr1: %zu\n", sizeof(ptr));

    printf("Input content of arr1:\n");
    for (int i = 0; i < size; i++)
    {
        int num = 0;
        printf("enter value of arr1[%d]: ", i);
        scanf("%d", &num);
        arr1[i] = num;
    }

    printf("Input content of arr2:\n");
    for (int i = 0; i < size; i++)
    {
        int num = 0;
        printf("enter value of arr2[%d]: ", i);
        scanf("%d", &num);
        arr2[i] = num;
    }

    FILE *fptr;
    fptr = fopen("hw1_output.txt", "w"); // open file

    int a = calculate_multiple(arr1[0], arr2[0]);
    int b = calculate_multiple(arr1[1], arr2[1]);
    int c = calculate_multiple(arr1[2], arr2[2]);

    fprintf(fptr, "value of arr1[0]*arr2[0]: %d\n", a);
    odd_even(a, fptr);

    fprintf(fptr, "value of arr1[1]*arr2[1]: %d\n", b);
    odd_even(b, fptr);

    fprintf(fptr, "value of arr1[2]*arr2[2]: %d\n", c);
    odd_even(c, fptr);

    fclose(fptr); // close file

    FILE *f;
    char ch;

    f = fopen("hw1_output.txt", "r");
    printf("Content of the file:\n");

    while ((ch = fgetc(f)) != EOF)
    {
        printf("%c", ch);
    }

    fclose(f);

    return 0;
}

int calculate_multiple(int a, int b)
{
    return a * b;
}

void odd_even(int a, FILE *fptr)
{
    if (a % 2 == 0)
    {
        fprintf(fptr, "     %d is an even number\n", a);
    }
    else
    {
        fprintf(fptr, "     %d is an odd number\n", a);
    }
}