/*
 * pfd_data_for_app.h
 *
 * Represents the PFDs for an application identifier.
 */

#ifndef OpenAPI_pfd_data_for_app_H_
#define OpenAPI_pfd_data_for_app_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "pfd_content.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct  OpenAPI_pfd_data_for_app_s  OpenAPI_pfd_data_for_app_t;
typedef struct  OpenAPI_pfd_data_for_app_s {
    char *application_id; // string
    OpenAPI_list_t *pfds; //nonprimitive container
    char *caching_time; //date time
    int caching_timer; //numeric
    char *pfd_timestamp; //date time
    int partial_flag; //boolean
    char *supported_features; // string

}  OpenAPI_pfd_data_for_app_t;

OpenAPI_pfd_data_for_app_t *OpenAPI_pfd_data_for_app_create(
    char *application_id,
    OpenAPI_list_t *pfds,
    char *caching_time,
    int caching_timer,
    char *pfd_timestamp,
    int partial_flag,
    char *supported_features
);

void OpenAPI_pfd_data_for_app_free(OpenAPI_pfd_data_for_app_t *pfd_data_for_app);
OpenAPI_pfd_data_for_app_t *OpenAPI_pfd_data_for_app_parseFromJSON(cJSON *pfd_data_for_appJSON);
cJSON *OpenAPI_pfd_data_for_app_convertToJSON(OpenAPI_pfd_data_for_app_t *pfd_data_for_app);
OpenAPI_pfd_data_for_app_t OpenAPI_pfd_data_for_app_copy(OpenAPI_pfd_data_for_app_t *src, OpenAPI_pfd_data_for_app_t *dst);

#ifdef __cplusplus
}
#endif
#endif /* _pfd_data_for_app_H_ */

