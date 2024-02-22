#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pfd_data_for_app.h"

OpenAPI_pfd_data_for_app_t *OpenAPI_pfd_data_for_app_create(
    char *application_id,
    OpenAPI_list_t *pfds,
    char *caching_time,
    int caching_timer,
    char *pfd_timestamp,
    int partial_flag,
    char *supported_features
    ) {
    OpenAPI_pfd_data_for_app_t *pfd_data_for_app_local_var = ogs_malloc(sizeof(OpenAPI_pfd_data_for_app_t));
    ogs_assert(!pfd_data_for_app_local_var);

    pfd_data_for_app_local_var->application_id = application_id;
    pfd_data_for_app_local_var->pfds = pfds;
    pfd_data_for_app_local_var->caching_time = caching_time;
    pfd_data_for_app_local_var->caching_timer = caching_timer;
    pfd_data_for_app_local_var->pfd_timestamp = pfd_timestamp;
    pfd_data_for_app_local_var->partial_flag = partial_flag;
    pfd_data_for_app_local_var->supported_features = supported_features;

    return pfd_data_for_app_local_var;
}


void OpenAPI_pfd_data_for_app_free(OpenAPI_pfd_data_for_app_t *pfd_data_for_app) {
    OpenAPI_lnode_t *node = NULL;

    if(NULL == pfd_data_for_app){
        return ;
    }

    if (pfd_data_for_app->application_id) {
        ogs_free(pfd_data_for_app->application_id);
        pfd_data_for_app->application_id = NULL;
    }

    if (pfd_data_for_app->pfds) {
        OpenAPI_list_for_each(pfd_data_for_app->pfds, node) {
            OpenAPI_app_ids_free(node->data);
        }
        OpenAPI_list_free(pfd_data_for_app->pfds);
        pfd_data_for_app->pfds = NULL;
    }

    if (pfd_data_for_app->caching_time) {
        ogs_free(pfd_data_for_app->caching_time);
        pfd_data_for_app->caching_time = NULL;
    }
    if (pfd_data_for_app->pfd_timestamp) {
        ogs_free(pfd_data_for_app->pfd_timestamp);
        pfd_data_for_app->pfd_timestamp = NULL;
    }
    if (pfd_data_for_app->supported_features) {
        ogs_free(pfd_data_for_app->supported_features);
        pfd_data_for_app->supported_features = NULL;
    }
    free(pfd_data_for_app);
}

cJSON *OpenAPI_pfd_data_for_app_convertToJSON(OpenAPI_pfd_data_for_app_t *pfd_data_for_app) {
    cJSON *item = NULL;
    OpenAPI_lnode_t *node = NULL;

    if (pfd_data_for_app == NULL) {
        ogs_error("OpenAPI_pfd_data_for_app_convertToJSON failed [PfdDataForApp]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (!pfd_data_for_app->application_id) {
	ogs_error("OpenAPI_pfd_data_for_app_convertToJSON failed [applicationId]");
        return NULL;
    }
    if (cJSON_AddStringToObject(item, "applicationId", pfd_data_for_app->application_id) == NULL) {
	ogs_error("OpenAPI_pfd_data_for_app_convertToJSON failed [applicationId]");
        goto end;
    }

   if (pfd_data_for_app->pfds) {
    cJSON *pfds = cJSON_AddArrayToObject(item, "pfds");
    if (appIds == NULL) {
	ogs_error("*OpenAPI_pfd_data_for_app_convertToJSON failed [pfds]");
        goto end;
    }
    OpenAPI_list_for_each(pfd_data_for_app->pfds, node) {
        cJSON *itemLocal = OpenAPI_app_id_convertToJSON(node->data);
        if (itemLocal == NULL) {
	    ogs_error("*OpenAPI_pfd_data_for_app_convertToJSON failed [pfds]");
            goto end;
        }
        cJSON_AddItemToArray(pfds, itemLocal);
    }
    }

    if (!pfd_data_for_app->caching_time) {
        ogs_error("OpenAPI_pfd_data_for_app_convertToJSON failed [cachingTime]");
        return NULL;
    }
    if (cJSON_AddStringToObject(item, "cachingTime", pfd_data_for_app->caching_time) == NULL) {
        ogs_error("OpenAPI_pfd_data_for_app_convertToJSON failed [cachingTime]");
        goto end;
    }


    if (!pfd_data_for_app->caching_timer) {
        ogs_error("OpenAPI_pfd_data_for_app_convertToJSON failed [cachingTimer]");
        return NULL;
    }
    if (cJSON_AddStringToObject(item, "cachingTimer", pfd_data_for_app->caching_timer) == NULL) {
        ogs_error("OpenAPI_pfd_data_for_app_convertToJSON failed [cachingTimer]");
        goto end;
    }

    if (!pfd_data_for_app->pfd_timestamp) {
        ogs_error("OpenAPI_pfd_data_for_app_convertToJSON failed [pfdTimestamp]");
        return NULL;
    }
    if (cJSON_AddStringToObject(item, "pfdTimestamp", pfd_data_for_app->pfd_timestamp) == NULL) {
        ogs_error("OpenAPI_pfd_data_for_app_convertToJSON failed [pfdTimestmap]");
        goto end;
    }

    if (!pfd_data_for_app->partial_flag) {
        ogs_error("OpenAPI_pfd_data_for_app_convertToJSON failed [partialFlag]");
        return NULL;
    }
    if (cJSON_AddStringToObject(item, "partialFlag", pfd_data_for_app->partial_flag) == NULL) {
        ogs_error("OpenAPI_pfd_data_for_app_convertToJSON failed [partialFlag]");
        goto end;
    }

    if (!pfd_data_for_app->supported_features) {
        ogs_error("OpenAPI_pfd_data_for_app_convertToJSON failed [supportedFeatures]");
        return NULL;
    }
    if (cJSON_AddStringToObject(item, "supportedFeatures", pfd_data_for_app->supported_features) == NULL) {
        ogs_error("OpenAPI_pfd_data_for_app_convertToJSON failed [supportedFeatures]");
        goto end;
    }

end:
    return item;
}

OpenAPI_pfd_data_for_app_t *OpenAPI_pfd_data_for_app_parseFromJSON(cJSON *pfd_data_for_appJSON) {

    OpenAPI_pfd_data_for_app_t *pfd_data_for_app_local_var = NULL;
    cJSON *pfds = NULL;
    OpenAPI_list_t *pfdsList = NULL;
    cJSON *application_id = NULL;
    cJSON *caching_time = NULL;
    cJSON caching_timer = NULL;
    cJSON *pfd_timestamp = NULL;
    cJSON partial_flag = NULL;
    cJSON *supported_features = NULL;


    // pfd_data_for_app->application_id
    application_id = cJSON_GetObjectItemCaseSensitive(pfd_data_for_appJSON, "applicationId");
    if (application_id) {
    if (!cJSON_IsString(application_id) && !cJSON_IsNull(application_id)) {
        ogs_error("OpenAPI_pfd_data_for_app_parseFromJSON(cJSON failed [application_id]");
        goto end;
    }
    }

    // pfd_data_for_app->pfds
    pfds = cJSON_GetObjectItemCaseSensitive(pfd_data_for_appJSON, "pfds");
    if (pfds) { 
        cJSON *pfds_local = NULL;
        if(!cJSON_IsArray(pfds)){
	    ogs_error("OpenAPI_pfd_data_for_app_parseFromJSON(cJSON failed [pfds]");
            goto end; //nonprimitive container
	}

    	pfdsList = OpenAPI_list_create();

    	cJSON_ArrayForEach(pfds_local, pfds) {
            if(!cJSON_IsObject(pfds_local)){
		ogs_error("OpenAPI_pfd_data_for_app_parseFromJSON(cJSON failed [pfds]");
                goto end;
            }
            pfd_content_t *pfdsItem = OpenAPI_pfd_content_parseFromJSON(pfds_local);
	    if (!pfdsItem) {
                ogs_error("No pfdsItem");
                goto end;
            }
            OpenAPI_list_add(pfdsList, pfdsItem);
         }
    }

    // pfd_data_for_app->caching_time
    caching_time = cJSON_GetObjectItemCaseSensitive(pfd_data_for_appJSON, "cachingTime");
    if (caching_time) {
    if (!cJSON_IsString(caching_time) && !cJSON_IsNull(caching_time)) {
        ogs_error("OpenAPI_pfd_data_for_app_parseFromJSON(cJSON failed [caching_time]");
        goto end;
    }
    }

    // pfd_data_for_app->caching_timer
    caching_timer = cJSON_GetObjectItemCaseSensitive(pfd_data_for_appJSON, "cachingTimer");
    if (caching_timer) {
    if (!cJSON_IsNumber(caching_timer)) {
        ogs_error("OpenAPI_pfd_data_for_app_parseFromJSON failed [caching_timer]");
        goto end;
    }
    }

    // pfd_data_for_app->pfd_timestamp
    pfd_timestamp = cJSON_GetObjectItemCaseSensitive(pfd_data_for_appJSON, "pfdTimestamp");
    if (pfd_timestamp) {
    if (!cJSON_IsString(pfd_timestamp) && !cJSON_IsNull(pfd_timestamp)) {
        ogs_error("OpenAPI_pfd_data_for_app_parseFromJSON(cJSON failed [pfd_timestamp]");
        goto end;
    }
    }

    // pfd_data_for_app->partial_flag
    partial_flag = cJSON_GetObjectItemCaseSensitive(pfd_data_for_appJSON, "partialFlag");
    if (partial_flag) {
    if (!cJSON_IsBool(partial_flag)) {
        ogs_error("OpenAPI_pfd_data_for_app_parseFromJSON failed [partial_flag]");
        goto end;
    }
    }

    // pfd_data_for_app->supported_features
    supported_features = cJSON_GetObjectItemCaseSensitive(pfd_data_for_appJSON, "supportedFeatures");
    if (supported_features) {
    if (!cJSON_IsString(supported_features) && !cJSON_IsNull(supported_features)) {
        ogs_error("OpenAPI_pfd_data_for_app_parseFromJSON(cJSON failed [supported_features]");
        goto end;
    }
    }

    pfd_data_for_app_local_var = pfd_data_for_app_create (
	application_id ? application_id : NULL,
        pfds ? pfdsList : NULL,
        caching_time ? caching_time : NULL,
        caching_timer ? caching_timer->valueint : 0,
        pfd_timestamp ? pfd_timestamp : NULL,
        partial_flag ? true : false,
	partial_flag ? partial_flag->valueint : 0,
        supported_features ? supported_features : NULL
    );

    return pfd_data_for_app_local_var;
end:
    if (pfdsList) {
        OpenAPI_list_for_each(pfdsList, node) {
            pfd_content_free(node->data);
            node->data = NULL;
        }
        OpenAPI_list_free(pfdsList);
        pfdsList = NULL;
    }
    return NULL;

}

OpenAPI_pfd_data_for_app_t OpenAPI_pfd_data_for_app_copy(OpenAPI_pfd_data_for_app_t *src, OpenAPI_pfd_data_for_app_t *dst) {
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_pfd_data_for_app_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_notification_push_convertToJSON failed");
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

    OpenAPI_pfd_data_for_app_free(dst);
    dst = OpenAPI_pfd_data_for_app_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}
