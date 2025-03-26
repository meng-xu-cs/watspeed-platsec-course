#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "sgx_trts.h"

#include "Enclave_t.h"

/* 
 * printf: 
 *   Invokes OCALL to display the enclave buffer to the terminal.
 */
int printf(const char* fmt, ...)
{
    char buf[BUFSIZ] = { '\0' };
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, BUFSIZ, fmt, ap);
    va_end(ap);
    ocall_print_string(buf);
    return (int)strnlen(buf, BUFSIZ - 1) + 1;
}

/*
 * ecall_secure_square:
 *   Invokes ECALL for secure computation inside the enclave.
 */
int ecall_secure_square(int input)
{
    printf("[SGX] Got input: %d\n", input);
    return input * input;
}

