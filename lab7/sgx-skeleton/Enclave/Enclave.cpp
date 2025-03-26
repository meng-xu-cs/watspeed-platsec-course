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

    /* TODO: complete printf implementation using OCALL below */

    return (int)strnlen(buf, BUFSIZ - 1) + 1;
}

/*
 * ecall_secure_square:
 *   Securely compute the square of an integer (int) inside the enclave.
 *   TODO: to be implemented
 */
int ecall_secure_square(int input)
{
    /* TODO: step 1: print out the input received */

    /* TODO: step 2: change the return value to the correct computation result */
    return input;
}
