#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#define MAX_BUFFER 20

int get_random(unsigned short max);
int *generate_array(int* array, unsigned short size, unsigned short max_number);
int exist_dir(char* dir_path);
void generate_file(char* file_name, unsigned short size, int* data);


int main(void) {
    int number_file, max_number, step, validator, i, size, temp;
    int *data;
    char buffer[MAX_BUFFER];
    char* num;

    number_file = max_number = validator = size = 0;
    data = NULL;
    num = NULL;
    validator = 1;

    printf("*****************************\n*                           *\n* File Number Generator     *\n* Author: Alex Testa        *\n*                           *\n*****************************\n");
    printf("\nInsert data\n");
    printf("[*]How many file, do you want generate? : ");
    validator = scanf("%d", &number_file);
    /* Validation */
    while(validator != 1)
    {
        while((temp=getchar()) != EOF && temp != '\n');
        printf("\n[*]You must only inset integer number!!!please, retry : ");
        validator = scanf("%d", &number_file);
        fflush(stdin);
    }

    printf("[*]How many steps? : ");
    validator = scanf("%d", &step);

    /* Validation */
    while(validator != 1)
    {
        while((temp=getchar()) != EOF && temp != '\n');
        printf("\n[*]You must only inset integer number!!!please, retry : ");
        validator = scanf("%d", &step);
        fflush(stdin);
    }

    printf("[*]What's the max of number tolerate? : ");
    validator = scanf("%d", &max_number);

    /* Validation */
    while(validator != 1)
    {
        while((temp=getchar()) != EOF && temp != '\n');
        printf("\n[*]You must only inset integer number!!!please, retry : ");
        validator = scanf("%d", &max_number);
        fflush(stdin);
    }

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

int exist_dir(char* dir_path)
{
    DIR* dir = opendir(dir_path);
    if (dir) {
        closedir(dir);
        return EXIT_SUCCESS;
    } else if (ENOENT == errno) {
        printf("[!]The directory %s not exist, please create directory named 'file'", dir_path);
    } else {
        printf("[!]The directory %s not openable, please control the privileges", dir_path);
        exit (EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}

void generate_file(char* file_name, unsigned short size, int* data)
{
    int i;
    FILE *file;
    
    if(exist_dir("file") == EXIT_SUCCESS)
    {
        file = fopen(file_name, "w");
         fprintf(file,"%d\n", size);

        for(i = 0; i < size; i++)
        {
            fprintf(file,"%d\n", data[i]);
        }
    
        printf("Completed!!!\n");
        fclose(file);
    }else
    {
        printf("[!]Something, wrong\n");
    }
}