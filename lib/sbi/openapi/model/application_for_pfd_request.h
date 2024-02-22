/*
 * application_for_pfd_request.h
 *
 * Contains the application identifier(s) for the PFD(s) request.
 */

#ifndef _OpenAPI_application_for_pfd_request_H_
#define _OpenAPI_application_for_pfd_request_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_application_for_pfd_request_s OpenAPI_application_for_pfd_request_t;
typedef struct OpenAPI_application_for_pfd_request_s {
    char *application_id; // string
    char *pfd_timestamp; //date time

} OpenAPI_application_for_pfd_request_t;

OpenAPI_application_for_pfd_request_t *OpenAPI_application_for_pfd_request_create(
    char *application_id,
    char *pfd_timestamp
);

void OpenAPI_application_for_pfd_request_free(OpenAPI_application_for_pfd_request_t *application_for_pfd_request);
OpenAPI_application_for_pfd_request_t *OpenAPI_application_for_pfd_request_parseFromJSON(cJSON *application_for_pfd_requestJSON);
cJSON *OpenAPI_application_for_pfd_request_convertToJSON(OpenAPI_application_for_pfd_request_t *application_for_pfd_request);
OpenAPI_application_for_pfd_request_t *OpenAPI_application_for_pfd_copy(OpenAPI_application_for_pfd_request_t *dst, OpenAPI_application_for_pfd_request_t *src);

#ifdef __cplusplus
}
#endif
#endif /* _application_for_pfd_request_H_ */

