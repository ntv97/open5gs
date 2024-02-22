#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pfd_subscription.h"



OpenAPI_pfd_subscription_t *OpenAPI_pfd_subscription_create(
    OpenAPI_list_t *application_ids,
    char *notify_uri,
    char *supported_features
    ) {
    OpenAPI_pfd_subscription_t *pfd_subscription_local_var = ogs_malloc(sizeof(OpenAPI_pfd_subscription_t));
    ogs_assert(!pfd_subscription_local_var);

    pfd_subscription_local_var->application_ids = application_ids;
    pfd_subscription_local_var->notify_uri = notify_uri;
    pfd_subscription_local_var->supported_features = supported_features;

    return pfd_subscription_local_var;
}


void OpenAPI_pfd_subscription_free(OpenAPI_pfd_subscription_t *pfd_subscription) {
    OpenAPI_lnode_t *node = NULL;
    if(NULL == pfd_subscription){
        return ;
    }
    
    if (pfd_subscription->application_ids) {
        OpenAPI_list_for_each(pfd_subscription->application_ids, node) {
            OpenAPI_app_ids_free(node->data);
        }
        OpenAPI_list_free(pfd_subscription->application_ids);
        pfd_subscription->application_ids = NULL;
    }

    if (pfd_subscription->notify_uri) {
        ogs_free(pfd_subscription->notify_uri);
        pfd_subscription->notify_uri = NULL;
    }
    if (pfd_subscription->supported_features) {
        ogs_free(pfd_subscription->supported_features);
        pfd_subscription->supported_features = NULL;
    }
    ogs_free(pfd_subscription);
}

cJSON *OpenAPI_pfd_subscription_convertToJSON(OpenAPI_pfd_subscription_t *pfd_subscription) {
    cJSON *item = NULL;
    OpenAPI_lnode_t *node = NULL;

    if (pfd_subscription == NULL) {
        ogs_error("OpenAPI_pfd_subscription_convertToJSON() failed [NotificationPush]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (pfd_subscription->application_ids) {
    cJSON *application_ids = cJSON_AddArrayToObject(item, "applicationIds");
    if (applicationIds == NULL) {
        ogs_error("OpenAPI_pfd_subscription_convertToJSON() failed [applicationIds]");
        goto end;
    }
    OpenAPI_list_for_each(pfd_subscription->application_ids, node) {
        cJSON *itemLocal = OpenAPI_app_id_convertToJSON(node->data);
        if (itemLocal == NULL) {
	    ogs_error("OpenAPI_pfd_subscription_convertToJSON() failed [applicationIds]");
            goto end;
        }
        cJSON_AddItemToArray(application_ids, itemLocal);
    }
    }

    // pfd_subscription->notify_uri
    if (!pfd_subscription->notify_uri) {
	ogs_error("OpenAPI_pfd_subscription_convertToJSON() failed [notifyUri]");
        return NULL;
    }
    if (cJSON_AddStringToObject(item, "notifyUri", pfd_subscription->notify_uri) == NULL) {
	ogs_error("OpenAPI_pfd_subscription_convertToJSON() failed [notifyUri]");
        goto end;
    }

    // pfd_subscription->supported_features
    if (!pfd_subscription->supported_features) {
	ogs_error("OpenAPI_pfd_subscription_convertToJSON() failed [supportedFeatures]");
	return NULL;
    }
    if(cJSON_AddStringToObject(item, "supportedFeatures", pfd_subscription->supported_features) == NULL) {
	ogs_error("OpenAPI_pfd_subscription_convertToJSON() failed [supportedFeatures]");
    	goto end; //String
    }

end:
    return item;
}

OpenAPI_pfd_subscription_t *OpenAPI_pfd_subscription_parseFromJSON(cJSON *pfd_subscriptionJSON) {

    OpenAPI_pfd_subscription_t *pfd_subscription_local_var = NULL;
     OpenAPI_lnode_t *node = NULL;
    OpenAPI_list_t *application_idsList = NULL;
    cJSON *application_ids = NULL;
    cJSON *notify_uri = NULL;
    cJSON *supported_features = NULL;

    // pfd_subscription->application_ids
    application_ids = cJSON_GetObjectItemCaseSensitive(pfd_subscriptionJSON, "applicationIds");
    if (application_ids) {
        cJSON *application_ids_local = NULL;
        if (!cJSON_IsArray(application_ids)) {
            ogs_error("OpenAPI_pfd_subscription_parseFromJSON failed [application_ids]");
            goto end;
        }

        application_idsList = OpenAPI_list_create();

        cJSON_ArrayForEach(application_ids_local, application_ids) {
            if (!cJSON_IsObject(application_ids_local)) {
		ogs_error("OpenAPI_pfd_subscription_parseFromJSON failed [application_ids]");
                goto end;
            }
            OpenAPI_application_id_t *application_idsItem = OpenAPI_application_id_parseFromJSON(application_ids_local);
            if (!application_idsItem) {
                ogs_error("No app_idsItem");
                goto end;
            }
            OpenAPI_list_add(application_idsList, application_idsItem);
        }
    }

    // pfd_subscription->notify_uri
    notify_uri = cJSON_GetObjectItemCaseSensitive(pfd_subscriptionJSON, "notifyUri");
    if (notify_uri) {
    if (!cJSON_IsString(notify_uri) && !cJSON_IsNull(notify_uri)) {
	ogs_error("OpenAPI_pfd_subscription_parseFromJSON failed [notify_uri]");
        goto end;
    }
    }

    // pfd_subscription->supported_features
    supported_features = cJSON_GetObjectItemCaseSensitive(pfd_subscriptionJSON, "supportedFeatures");
    if (supported_features) {
    if (!cJSON_IsString(supported_features) && !cJSON_IsNull(supported_features)) {
        ogs_error("OpenAPI_pfd_subscription_parseFromJSON failed [supportedd_features]");
        goto end;
    }
    }

    pfd_subscription_local_var = pfd_subscription_create (
        application_ids ? application_idsList : NULL,
        notify_uri && !cJSON_IsNull(notify_uri) ? strdup(notify_uri->valuestring) : NULL,
        supported_features && !cJSON_IsNull(supported_features) ? strdup(supported_features->valuestring) : NULL
        );

    return pfd_subscription_local_var;
end:
    if (application_idsList) {
        OpenAPI_list_for_each(application_idsList, node) {
            free(node->data);
            node->data = NULL;
        }
        OpenAPI_list_free(application_idsList);
        application_idsList = NULL;
    }
    return NULL;

}

OpenAPI_pfd_subscription_t OpenAPI_pfd_subscription_copy(OpenAPI_pfd_subscription_t *src, OpenAPI_pfd_subscription_t *dst) {
	cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_pfd_subscription_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_pfd_subscription_convertToJSON() failed");
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

    OpenAPI_pfd_content_free(dst);
    dst = OpenAPI_pfd_subscription_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}
