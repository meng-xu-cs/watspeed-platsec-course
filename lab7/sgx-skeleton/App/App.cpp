#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

#include "sgx_urts.h"
#include "Enclave_u.h"

#define ENCLAVE_FILENAME "enclave.signed.so"

/* Global EID shared by multiple threads */
sgx_enclave_id_t global_eid = 0;

/* Initialize the enclave:
 *   Call sgx_create_enclave to initialize an enclave instance
 */
int initialize_enclave(void)
{
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;

    /* Call sgx_create_enclave to initialize an enclave instance */
    /* Debug Support: set 2nd parameter to 1 */
    ret = sgx_create_enclave(ENCLAVE_FILENAME, SGX_DEBUG_FLAG, NULL, NULL, &global_eid, NULL);
    if (ret != SGX_SUCCESS) {
        return -1;
    }

    return 0;
}

/* OCall functions */
void ocall_print_string(const char *str)
{
    printf("%s", str);
}


/* Application entry */
int SGX_CDECL main(int argc, char *argv[])
{
    (void)(argc);
    (void)(argv);

    /* Take input */
    printf("Please enter an integer: \n");

    int input = 0;
    if (scanf("%d", &input) <= 0) {
        printf("Invalid input, aborting...\n");
	return -1;
    }

    /* Initialize the enclave */
    if(initialize_enclave() < 0){
        printf("Failed to initialize the enclave, aborting...\n");
        return -1;
    }

    /* TODO: call into the enclave for secure square computation and print the result */

    /* Destroy the enclave */
    sgx_destroy_enclave(global_eid);

    printf("Goodbye!\n");
    return 0;
}

