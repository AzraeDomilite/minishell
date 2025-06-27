#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void fonction_exec(void (*func)(void *), ...) {
    va_list args;
    va_start(args, func);

    while (func != NULL) {
        // Fetch the next argument to be passed to the function
        void *arg = va_arg(args, void *);
        func(arg); // Call the function with the argument
        func = va_arg(args, void (*)(void *)); // Get the next function
    }

    va_end(args);
}

// Example functions with arguments
void print_message(void *msg) {
    printf("%s\n", (char *)msg);
}

void print_number(void *num) {
    printf("%d\n", *(int *)num);
}

int main() {
    int number = 42;

    // Pass function pointers and their arguments
    fonction_exec((void*)printf, (void*)"Hello\n", print_message, "World", print_number, &number, perror, "test", NULL);

    return 0;
}