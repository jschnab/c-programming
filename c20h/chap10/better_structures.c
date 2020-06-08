#include <stdio.h>
#include <string.h>


#define LENGTH 40


typedef struct {
    int age;
    char name[LENGTH];
} persona;


int main() {
    persona p;
    printf("Enter your name: ");
    (void) scanf("%s%*c", p.name);
    printf("Enter your age: ");
    (void) scanf("%d%*c", &p.age);
    printf("name = %s, age = %d\n", p.name, p.age);
    return 0;
}
