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
    char name[MAX_STRING_SIZE];
    char degree[MAX_STRING_SIZE];
    float avg_grade;
} student_type;

void print_main_menu();
void enter_student_data(student_type *student_p);
void dump_students_to_file(char dump_file_name[MAX_STRING_SIZE], student_type school_data[MAX_STUDENTS]);

int main(){

    student_type school[MAX_STUDENTS];
    dump_students_to_file("student_dump.txt", school);

    return 0;
}

void print_main_menu(){
    printf("=== Menu de opciones ===\n");
    printf("1. Ingresar datos de estudiante\n");
    printf("2. Remover estudiante\n");
    printf("3. Mostrar datos de estudiante\n");
    printf("4. Mostrar todos los estudiantes\n");
    printf("5. Guardar datos en archivo\n");
    printf("6. Salir\n");
    printf("=======================\n");
    printf("Seleccione una opcion: ");
}

void enter_student_data(student_type *student_p){
    printf("Ingrese el nombre del estudiante: ");
    fgets(student_p->name, MAX_STRING_SIZE, stdin);

    printf("Ingrese la edad del estudiante: ");
    scanf("%d", &student_p->age);
    getchar();

    printf("Ingrese el semestre del estudiante: ");
    scanf("%d", &student_p->semester);
    getchar();

    printf("Ingrese la carrera del estudiante: ");
    fgets(student_p->degree, MAX_STRING_SIZE, stdin);

    printf("Ingrese el promedio del estudiante: ");
    scanf("%f", &student_p->avg_grade);
    getchar();
}

void dump_students_to_file(char dump_file_name[MAX_STRING_SIZE], student_type school_data[MAX_STUDENTS]){
    FILE *f = fopen(dump_file_name, "w");
    if(f == NULL){
        printf("Error opening file [%s] for writing.\n", dump_file_name);
        exit(1);
    }

    fprintf(f, "<< Datos de estudiantes >>\n");
    fprintf(f, "-----------------------\n");
    for(int i = 0; i < MAX_STUDENTS; i++){
        fprintf(f, "Numero de estudiante: %d:\n", i + 1);
        fprintf(f, "Nombre: %s\n", school_data[i].name);
        fprintf(f, "Edad: %d\n", school_data[i].age);
        fprintf(f, "Semestre: %d\n", school_data[i].semester);
        fprintf(f, "Carrera: %s\n", school_data[i].degree);
        fprintf(f, "Promedio: %.2f\n", school_data[i].avg_grade);
        fprintf(f, "-----------------------\n");
    }

    fclose(f);
}