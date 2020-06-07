#include <stdio.h>
#include <string.h>


#define LENGTH 40


struct persona {
    int age;
    char name[LENGTH];
} persona;


int main() {
    struct persona p;
    p.age = 34;
    strcpy(p.name, "Jonathan");
    printf("name = %s, age = %d\n", p.name, p.age);
    return 0;
}
