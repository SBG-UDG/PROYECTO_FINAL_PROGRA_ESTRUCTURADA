/*

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct{
    student_type students[MAX_STUDENTS];
    char name[MAX_STRING_SIZE];
    char initials[6];
    int amount_of_students;
} school_type;

void print_main_menu();
void enter_new_student(school_type *school_p);
void dump_students_to_file(char dump_file_name[MAX_STRING_SIZE], school_type school);

int main(){
    school_type school;
    student_type school_students[MAX_STUDENTS];

    int option = 0;
    school.amount_of_students = 0;
    strcpy(school.initials, "CUCEI");
    strcpy(school.name, "Centro Universitario de Ciencias Exactas e Ingenierias");

    while(option != 6){
        print_main_menu();
        scanf("%d", &option);
        getchar();

        switch(option){
            case 1:
                enter_new_student(&school_students);
                break;
            case 5:
                dump_students_to_file(FILE_NAME, school);
                printf("Datos guardados en el archivo [%s]\n", FILE_NAME);
                break;
            case 6:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
                break;
        }
    }
    
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

void enter_new_student(school_type *school_p){

    int student_number = school_p->amount_of_students;
    printf("%i", student_number);
    student_type *student_p = &school_p->students[student_number];

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

    school_p->amount_of_students++;
}

void dump_students_to_file(char dump_file_name[MAX_STRING_SIZE], school_type school){
    
    FILE *f = fopen(dump_file_name, "w");
    
    if(f == NULL){
        printf("Error opening file '%s' for writing.\n", dump_file_name);
        exit(1);
    }

    student_type *students_data = school.students;

    fprintf(f, "<< Estudiantes %s >>\n", school.name);
    fprintf(f, "-----------------------\n");
    for(int i = 0; i < school.amount_of_students; i++){
        fprintf(f, "Numero de estudiante: %d:\n", i + 1);
        fprintf(f, "Nombre: %s\n", students_data[i].name);
        fprintf(f, "Edad: %d\n", students_data[i].age);
        fprintf(f, "Semestre: %d\n", students_data[i].semester);
        fprintf(f, "Carrera: %s\n", students_data[i].degree);
        fprintf(f, "Promedio: %.2f\n", students_data[i].avg_grade);
        fprintf(f, "-----------------------\n");
    }

    fclose(f);
}