/*

*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_STUDENTS 200
#define MAX_STRING_SIZE 100
#define FILE_NAME "students.txt"

typedef struct{
    int age;
    int semester;
    char degree[MAX_STRING_SIZE];
    float avg_grade;
} student;

void dump_students_to_file(char dump_file_name[MAX_STRING_SIZE], student school_data[MAX_STUDENTS]);

int main(){

    student school[MAX_STUDENTS];

    return 0;
}

void dump_students_to_file(char dump_file_name[MAX_STRING_SIZE], student school_data[MAX_STUDENTS]){
    FILE *f = fopen(dump_file_name, "w");
    
}