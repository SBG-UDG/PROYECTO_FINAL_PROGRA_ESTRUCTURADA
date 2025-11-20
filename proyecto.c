/*
PROYECTO FINAL DE PROGRAMACION ESTRUCTURADA
SISTEMA DE GESTION DE ESTUDIANTES
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <time.h>
    #include <unistd.h>
#endif

#define CLEAR_SCREEN_NEWLINES 20
#define MAX_STUDENTS 200
#define MAX_STRING_SIZE 100
#define FILE_NAME "students.txt"
#define STANDARD_SLEEP_MS 1500

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

// Utility functions
void clear_screen_crude();
void sleep_ms(int milliseconds);
int check_student_exists_by_number_and_students_more_than_zero(school_type school, int student_number);

// Menu and functionality
void print_main_menu();
void enter_new_student(school_type *school_p);
void remove_student_by_number(school_type *school_p);
void show_student_data_by_number(school_type school_p);
void modify_student_by_number(school_type *school_p);
void show_all_students(school_type school);
void dump_students_to_file(const char *dump_file_name, school_type school);

int main(){
    school_type school;
    student_type school_students[MAX_STUDENTS];

    int option = 0;
    school.amount_of_students = 0;
    strcpy(school.initials, "CUCEI");
    strcpy(school.name, "Centro Universitario de Ciencias Exactas e Ingenierias");

    while(option != 6){
        printf("=== %s ===\n", school.initials);
        print_main_menu();
        scanf("%d", &option);
        getchar();

        clear_screen_crude();

        switch(option){
            case 1:
                enter_new_student(&school);
                break;
            case 2:
                remove_student_by_number(&school);
                break;
            case 3:
                modify_student_by_number(&school);
                break;
            case 4:
                show_student_by_number(school);
                break;
            case 5:
                show_all_students(school);
                break;
            case 6:
                dump_students_to_file(FILE_NAME, school);
                printf("Datos guardados en el archivo [%s]\n", FILE_NAME);
                break;
            case 7:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
                break;
        }

        clear_screen_crude();
    }
    
    return 0;
}

void clear_screen_crude(){
    for (int i = 0; i < CLEAR_SCREEN_NEWLINES; i++){
        printf("\n");
    }
}

void sleep_ms(int milliseconds) {
    #ifdef _WIN32
        Sleep(milliseconds);
    #else
        struct timespec ts;
        ts.tv_sec = milliseconds / 1000;
        ts.tv_nsec = (milliseconds % 1000) * 1000000;
        while (nanosleep(&ts, &ts) != 0) {}
    #endif
}

void print_main_menu(){
    printf("=== Menu de opciones ===\n");
    printf("1. Ingresar datos de estudiante\n");
    printf("2. Remover estudiante\n");
    printf("3. Modificar datos de estudiante\n");
    printf("4. Mostrar datos de estudiante\n");
    printf("5. Mostrar todos los estudiantes\n");
    printf("6. Guardar datos en archivo\n");
    printf("7. Salir\n");
    printf("=======================\n");
    printf("Seleccione una opcion: ");
}

int check_student_exists_by_number_and_students_more_than_zero(school_type school, int student_number){
    
    if (school.amount_of_students == 0){
        printf("No hay estudiantes registrados en la escuela.\n");
        //sleep(STANDARD_SLEEP_MS);
        return 0;
    }

    printf("Ingrese el numero de estudiante: ");
    scanf("%d", &student_number);

    if (student_number < 1 || student_number > school.amount_of_students){
        printf("\nError: El estudiante numero %d no existe.\n", student_number);
        //sleep(STANDARD_SLEEP_MS);
        return 0;
    }

    return student_number; // Student exists
}

void enter_new_student(school_type *school_p){

    int student_number = school_p->amount_of_students;
    printf(":::: Estudiante numero: %i ::::\n", student_number);
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

    printf("\nEstudiante agregado!");
    sleep_ms(STANDARD_SLEEP_MS);
}

void remove_student_by_number(school_type *school_p){
    
    int student_number = check_student_exists_by_number_and_students_more_than_zero(*school_p, student_number);
    if (student_number == 0){
        return;
    }

    int index_to_remove = student_number - 1;
    char removed_name[MAX_STRING_SIZE];
    strcpy(removed_name, school_p->students[index_to_remove].name);

    for (int i = index_to_remove; i < school_p->amount_of_students - 1; i++){
        school_p->students[i] = school_p->students[i + 1];
    }

    school_p->amount_of_students--;

    printf("\nEstudiante '%s' (numero %d) eliminado exitosamente.\n", removed_name, student_number);
    printf("Total de estudiantes ahora: %d\n", school_p->amount_of_students);
    sleep_ms(STANDARD_SLEEP_MS);
}

void modify_student_by_number(school_type *school_p){
    
    int student_number = check_student_exists_by_number_and_students_more_than_zero(*school_p, student_number);
    if (student_number == 0){
        return;
    }

    student_type *student_p = &school_p->students[student_number - 1];

    printf("Modificando datos del estudiante [%d] '%s'\n", student_number, student_p->name);
    printf("Ingrese el nuevo nombre del estudiante: ");
    fgets(student_p->name, MAX_STRING_SIZE, stdin);
    printf("Ingrese la nueva edad del estudiante: ");
    scanf("%d", &student_p->age);
    getchar();
    printf("Ingrese el nuevo semestre del estudiante: ");
    scanf("%d", &student_p->semester);
    getchar();
    printf("Ingrese la nueva carrera del estudiante: ");
    fgets(student_p->degree, MAX_STRING_SIZE, stdin);
    printf("Ingrese el nuevo promedio del estudiante: ");
    scanf("%f", &student_p->avg_grade);
    getchar();

    printf("\nDatos del estudiante numero %d modificados exitosamente.\n", student_number);
    //sleep(STANDARD_SLEEP_MS);
}

void show_student_data_by_number(school_type school){

    int student_number = check_student_exists_by_number_and_students_more_than_zero(school, student_number);
    if (student_number == 0){
        return;
    }

    student_type *student_p = &school.students[student_number - 1];

    printf("Datos del estudiante numero %d:\n", student_number);
    printf("Nombre: %s", student_p->name);
    printf("Edad: %d\n", student_p->age);
    printf("Semestre: %d\n", student_p->semester);
    printf("Carrera: %s", student_p->degree);
    printf("Promedio: %.2f\n", student_p->avg_grade);

    printf("\n\nPresione [ENTER] para continuar");
    getchar(); // Clean buffer
    getchar(); // Require ENTER to continue
}

void show_all_students(school_type school){
    if (school.amount_of_students == 0){
        printf("\nNo hay estudiantes registrados para mostrar.\n");
        //sleep(STANDARD_SLEEP_MS);
        return;
    }

    student_type *students_data = school.students;

    int j = 0, k = 0;

    printf("<< Estudiantes %s (%s) >>\n", school.name, school.initials);
    printf("-----------------------\n");
    for(int i = 0; i < school.amount_of_students; i++){
        printf("Numero de estudiante: %d:\n", i + 1);
        printf("Nombre: %s", students_data[i].name);
        printf("Edad: %d\n", students_data[i].age);
        printf("Semestre: %d\n", students_data[i].semester);
        printf("Carrera: %s", students_data[i].degree);
        printf("Promedio: %.2f\n", students_data[i].avg_grade);
        printf("-----------------------\n");
    }

    getchar(); // Require ENTER to continue
}

void dump_students_to_file(const char *dump_file_name, school_type school){
    
    if (school.amount_of_students == 0){
        printf("\nNo hay estudiantes registrados para guardar en el archivo.\n");
        //sleep(STANDARD_SLEEP_MS);
        return;
    }
    
    FILE *f = fopen(dump_file_name, "w");
    
    if(f == NULL){
        printf("\nError abriendo el archivo '%s'.\n", dump_file_name);
        sleep(STANDARD_SLEEP_MS);
        return;
    }

    student_type *students_data = school.students;

    fprintf(f, "<< Estudiantes %s (%s) >>\n", school.name, school.initials);
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

    printf("\nInformacion de estudiantes exportada en: %s", dump_file_name);
    sleep_ms(STANDARD_SLEEP_MS);
}