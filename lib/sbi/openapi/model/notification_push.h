/*
 * notification_push.h
 *
 * Represents the information to be used by the NF service consumer to retrieve the PFDs and/or remove the PFDs of the applicable application identifier(s). 
 */

#ifndef _OpenAPI_notification_push_H_
#define _OpenAPI_notification_push_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "pfd_operation.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_notification_push_s OpenAPI_notification_push_t;
typedef struct OpenAPI_notification_push_s {
    OpenAPI_list_t *app_ids; //primitive container
    int allowed_delay; //numeric
    OpenAPI_pfd_operation_t *pfd_op; //model

} OpenAPI_notification_push_t;

OpenAPI_notification_push_t *OpenAPI_notification_push_create(
    OpenAPI_list_t *app_ids,
    int allowed_delay,
    OpenAPI_pfd_operation_t *pfd_op
);

void OpenAPI_notification_push_free(OpenAPI_notification_push_t *notification_push);
OpenAPI_notification_push_t *OpenAPI_notification_push_parseFromJSON(cJSON *notification_pushJSON);
cJSON *OpenAPI_notification_push_convertToJSON(OpenAPI_notification_push_t *notification_push);
OpenAPI_notification_push_t OpenAPI_notification_push_copy(OpenAPI_notification_push_t *src, OpenAPI_notification_push_t *dst);

#ifdef __cplusplus
}
#endif
#endif /* _notification_push_H_ */

