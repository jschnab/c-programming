#include <stdio.h>

int main() {
    char text[] = "hello world";
    char *pointer = "hello world";
    printf("size of text: %ld\n", sizeof(text));
    printf("size of pointer: %ld\n", sizeof(pointer));
    printf("address of text: %p\n", &text);
    printf("address of pointer: %p\n", &pointer);
    printf("text: %s\n", text);
    printf("pointer: %s\n", pointer);
    printf("text[0]: %c\n", text[0]);
    printf("pointer[0]: %c\n", pointer[0]);
    printf("address of text[0]: %p\n", &text[0]);
    printf("address of pointer[0]: %p\n", &pointer[0]);
    text[0] = 'm';
    printf("text: %s\n", text);
    pointer[0] = 'm';
    printf("pointer: %s\n", pointer);
    return 0;
}
