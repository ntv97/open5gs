#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "application_for_pfd_request.h"

OpenAPI_application_for_pfd_request_t *OpenAPI_application_for_pfd_request_create(
    char *application_id,
    char *pfd_timestamp
) {
    OpenAPI_application_for_pfd_request_t *application_for_pfd_request_local_var = ogs_malloc(sizeof(OpenAPI_application_for_pfd_request_t));
    ogs_assert(application_for_pfd_request_local_var);

    application_for_pfd_request_local_var->application_id = application_id;
    application_for_pfd_request_local_var->pfd_timestamp = pfd_timestamp;

    return application_for_pfd_request_local_var;
}


void OpenAPI_application_for_pfd_request_free(OpenAPI_application_for_pfd_request_t *application_for_pfd_request) {
    OpenAPI_lnode_t *node = NULL;

    if(NULL == application_for_pfd_request){
        return ;
    }
    if (application_for_pfd_request->application_id) {
        ogs_free(application_for_pfd_request->application_id);
        application_for_pfd_request->application_id = NULL;
    }
    if (application_for_pfd_request->pfd_timestamp) {
        ogs_free(application_for_pfd_request->pfd_timestamp);
        application_for_pfd_request->pfd_timestamp = NULL;
    }
    ogs_free(application_for_pfd_request);
}

cJSON *OpenAPI_application_for_pfd_request_convertToJSON(OpenAPI_application_for_pfd_request_t *application_for_pfd_request) {
    cJSON *item = NULL;
    OpenAPI_lnode_t *node = NULL;

    if (application_for_pfd_request == NULL) {
        ogs_error("OpenAPI_application_for_pfd_request_convertToJSON() failed [ApplicationForPfd]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (!application_for_pfd_request->application_id) {
	ogs_error("OpenAPI_application_for_pfd_request_convertToJSON() failed [applicationid]");
        return NULL;
    }
    if (cJSON_AddStringToObject(item, "applicationId", application_for_pfd_request->application_id) == NULL) {
        ogs_error("OpenAPI_application_for_pfd_request_convertToJSON() failed [applicationid]");
        goto end;
    }

    if (!application_for_pfd_request->pfd_timestamp) {
        ogs_error("OpenAPI_application_for_pfd_request_convertToJSON() failed [pfdTimestamp]");
        return NULL;
    }
    if (cJSON_AddStringToObject(item, "pfdTimestamp", application_for_pfd_request->application_id) == NULL) {
        ogs_error("OpenAPI_application_for_pfd_request_convertToJSON() failed [pfdTimestamp]");
        goto end;
    }

end:
    return item;
}

OpenAPI_application_for_pfd_request_t *OpenAPI_application_for_pfd_request_parseFromJSON(cJSON *application_for_pfd_requestJSON) {

    OpenAPI_application_for_pfd_request_t *application_for_pfd_request_local_var = NULL;
    OpenAPI_lnode_t *node = NULL;
    cJSON *application_id = NULL;
    cJSON *pfd_timestamp = NULL;

    application_id = cJSON_GetObjectItemCaseSensitive(application_for_pfd_requestJSON, "applicationId");
    if (!application_id) {
        ogs_error("OpenAPI_application_for_pfd_request_parseFromJSON(cJSON failed [applicationId]");
        goto end;
    }
    if (!cJSON_IsString(application_id)) {
        ogs_error("OpenAPI_application_for_pfd_request_parseFromJSON(cJSON failed [applicationId]");
        goto end;
    }

    pfd_timestamp = cJSON_GetObjectItemCaseSensitive(application_for_pfd_requestJSON, "pfdTimestamp");
    if (!pfd_timestamp) {
        ogs_error("OpenAPI_application_for_pfd_request_parseFromJSON(cJSON failed [pfdTimestamp]");
        goto end;
    }
    if (!cJSON_IsString(pfd_timestamp)) {
        ogs_error("OpenAPI_application_for_pfd_request_parseFromJSON(cJSON failed [pfdTimestamp]");
        goto end;
    }

    application_for_pfd_request_local_var = OpenAPI_application_for_pfd_request_create (
        ogs_strdup(application_id->valuestring),
	ogs_strdup(pfd_timestamp->valuestring),
    );

    return application_for_pfd_request_local_var;
end:
    return NULL;
}

OpenAPI_application_for_pfd_request_t *OpenAPI_application_for_pfd_copy(OpenAPI_application_for_pfd_request_t *dst, OpenAPI_application_for_pfd_request_t *src) {
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_application_for_pfd_request_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_application_for_pfd_request_convertToJSON() failed");
        return NULL;
    }	

    content = cJSON_Print(item);
    cJSON_Delete(item);

    if (!content) {
        ogs_error("cJSON_Print() failed");
        return NULL;
    }

    item = cJSON_Parse(content);
    ogs_free(content);
    if (!item) {
        ogs_error("cJSON_Parse() failed");
        return NULL;
    }

    OpenAPI_application_for_pfd_request_free(dst);
    dst = OpenAPI_application_for_pfd_request_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}
