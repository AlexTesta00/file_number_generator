#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAX_BUFFER 20

int get_random(unsigned short max);
int *generate_array(int* array, unsigned short size, unsigned short max_number);
void generate_file(char* file_name, unsigned short size, int* data);


int main(void) {
    int number_file, max_number, step, validator, i, size;
    int *data;
    char buffer[MAX_BUFFER];
    char* num;

    number_file = max_number = validator = size = 0;
    data = NULL;
    num = NULL;

    printf("[*]How many file, do you want generate? : ");
    validator = scanf("%d", &number_file);

    printf("[*]How many steps? : ");
    validator = scanf("%d", &step);

    printf("[*]What's the max of number tolerate? : ");
    validator = scanf("%d", &max_number);

    printf("\n[*]Just a moment...i create the files\n");
    for(i = 0; i < number_file; i++)
    {
        size += step;
        data = generate_array(data, (unsigned short) size, (unsigned short) max_number);
        asprintf(&num, "%d", size);
        strcat(strcpy(buffer, "file/File"),num);
        strcat(buffer, ".txt");
        printf("Generate %s...", buffer);
        generate_file(buffer, (unsigned short) size, data);
        printf("Completed!!!.\n");
    }

    printf("Generation Complete!!!.\n");
    free(data);
    return 0;
}

int get_random(unsigned short max)
{
    return rand() % max;
}

int * generate_array(int* array, unsigned short size, unsigned short max_number)
{
    int i;

    array = (int*)calloc(size, sizeof(int));

    for (i = 0; i < size; i++)
    {
        array[i] = get_random(max_number);
    }

    return array;
}

void generate_file(char* file_name, unsigned short size, int* data)
{
    int i;
    FILE *file;

    file = fopen(file_name, "w");
    
    fprintf(file,"%d\n", size);

    for(i = 0; i < size; i++)
    {
        fprintf(file,"%d\n", data[i]);
    }

    fclose(file);
}