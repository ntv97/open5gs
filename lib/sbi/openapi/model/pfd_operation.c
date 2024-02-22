#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pfd_operation.h"



OpenAPI_pfd_operation_t *OpenAPI_pfd_operation_create(
    ) {
    OpenAPI_pfd_operation_t *pfd_operation_local_var = ogs_malloc(sizeof(pfd_operation_t));
    ogs_assert(pfd_operation_local_var)

    return pfd_operation_local_var;
}


void OpenAPI_pfd_operation_free(OpenAPI_pfd_operation_t *pfd_operation) {
    OpenAPI_lnode_t *node = NULL;
    if(NULL == pfd_operation){
        return ;
    }
    free(pfd_operation);
}

cJSON *OpenAPI_pfd_operation_convertToJSON(OpenAPI_pfd_operation_t *pfd_operation) {
    cJSON *item = NULL;
    OpenAPI_lnode_t *node = NULL;

    if (pfd_operation == NULL) {
        ogs_error("OpenAPI_pfd_operation_convertToJSON() failed [PfdOperation]");
        return NULL;
    }

    item = cJSON_CreateObject();
end:
    return item;
}

OpenAPI_pfd_operation_parseFromJSON(cJSON *pfd_operationJSON) {
    pfd_operation_t *pfd_operation_local_var = NULL;

    pfd_operation_local_var = pfd_operation_create (
    );

    return pfd_operation_local_var;
end:
    return NULL;

}
