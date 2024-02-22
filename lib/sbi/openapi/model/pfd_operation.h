/*
 * pfd_operation.h
 *
 * Indicates the operation to be applied on PFD(s).
 */

#ifndef _OpenAPI_pfd_operation_H_
#define _OpenAPI_pfd_operation_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_pfd_operation_s OpenAPI_pfd_operation_t;
typedef struct OpenAPI_pfd_operation_s {

} OpenAPI_pfd_operation_t;

OpenAPI_pfd_operation_t *OpenAPI_pfd_operation_create(
);

void OpenAPI_pfd_operation_free(OpenAPI_pfd_operation_t *pfd_operation);
OpenAPI_pfd_operation_t *OpenAPI_pfd_operation_parseFromJSON(cJSON *pfd_operationJSON);
cJSON *OpenAPI_pfd_operation_convertToJSON(OpenAPI_pfd_operation_t *pfd_operation);

#ifdef __cplusplus
}
#endif
#endif /* _pfd_operation_H_ */

