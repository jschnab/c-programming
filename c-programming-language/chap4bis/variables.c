#include <stdio.h>

int external_var;
static int static_ext_var;

void func() {
    int auto_var;
    static int static_auto_var;
    printf("In func()\n");
    printf("auto_var = %d\n", auto_var);
    printf("set auto_var to 1 and increment by 1\n");
    auto_var = 1;
    auto_var++;
    printf("auto_var = %d\n", auto_var);
    printf("address of auto_var = %p\n", &auto_var);
    printf("static_auto_var = %d\n", static_auto_var);
    printf("set static_auto_var if not set and increment by 1\n");
    if (static_auto_var != 2)
        static_auto_var = 1;
    static_auto_var++;
    printf("static_auto_var = %d\n", static_auto_var);
    printf("address of static_auto_var = %p\n", &static_auto_var);
}

int main() {
    printf("external_var = %d\n", external_var);
    printf("set external_var to 1 and increment by 1\n");
    external_var = 1;
    external_var++;
    printf("external_var = %d\n", external_var);
    printf("address of external_var = %p\n", &external_var);
    printf("static_ext_var = %d\n", static_ext_var);
    printf("set static_ext_var to 1 and increment by 1\n");
    static_ext_var = 1;
    static_ext_var++;
    printf("static_ext_var = %d\n", static_ext_var);
    printf("address of static_ext_var = %p\n", &static_ext_var);
    printf("\n");
    func();
    printf("\n");
    func();
}
