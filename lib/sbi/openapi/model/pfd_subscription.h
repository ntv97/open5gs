/*
 * pfd_subscription.h
 *
 * Represents a PFD subscription.
 */

#ifndef _OpenAPI_pfd_subscription_H_
#define _OpenAPI_pfd_subscription_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_pfd_subscription_s OpenAPI_pfd_subscription_t;
typedef struct OpenAPI_pfd_subscription_s {
    OpenAPI_list_t *application_ids; //primitive container
    char *notify_uri; // string
    char *supported_features; // string

} OpenAPI_pfd_subscription_t;

OpenAPI_pfd_subscription_t *OpenAPI_pfd_subscription_create(
    OpenAPI_list_t *application_ids,
    char *notify_uri,
    char *supported_features
);

void OpenAPI_pfd_subscription_free(OpenAPI_pfd_subscription_t *pfd_subscription);
OpenAPI_pfd_subscription_t *OpenAPI_pfd_subscription_parseFromJSON(cJSON *pfd_subscriptionJSON);
cJSON *OpenAPI_pfd_subscription_convertToJSON(OpenAPI_pfd_subscription_t *pfd_subscription);
OpenAPI_pfd_subscription_t OpenAPI_pfd_subscription_copy(OpenAPI_pfd_subscription_t *src, OpenAPI_pfd_subscription_t *dst);

#ifdef __cplusplus
}
#endif
#endif /* _pfd_subscription_H_ */

