#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "notification_push.h"

OpenAPI_notification_push_t *OpenAPI_notification_push_create (
    OpenAPI_list_t *app_ids,
    int allowed_delay,
    OpenAPI_pfd_operation_t *pfd_op
    ) {
    OpenAPI_notification_push_t *notification_push_local_var = ogs_malloc(sizeof(OpenAPI_notification_push_t));
    ogs_assert(notification_push_local_var);

    notification_push_local_var->app_ids = app_ids;
    notification_push_local_var->allowed_delay = allowed_delay;
    notification_push_local_var->pfd_op = pfd_op;

    return notification_push_local_var;
}


void OpenAPI_notification_push_free(OpenAPI_notification_push_t *notification_push) {
    OpenAPI_lnode_t *node = NULL;

    if(NULL == notification_push){
        return ;
    }

    if (notification_push->app_ids) {
        OpenAPI_list_for_each(notification_push->app_ids, node) {
            OpenAPI_app_ids_free(node->data);
        }
        OpenAPI_list_free(notification_push->app_ids);
        notification_push->app_ids = NULL;
    }
    if (notification_push->pfd_op) {
        ogs_free(notification_push->pfd_op);
        notification_push->pfd_op = NULL;
    }
    ogs_free(notification_push);
}

cJSON *OpenAPI_notification_push_convertToJSON(OpenAPI_notification_push_t *notification_push) {
    cJSON *item = NULL;
    OpenAPI_lnode_t *node = NULL;

    if (notification_push == NULL) {
        ogs_error("OpenAPI_notification_push_convertToJSON() failed [NotificationPush]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (notification_push->app_ids) {
    cJSON *app_ids = cJSON_AddArrayToObject(item, "appIds");
    if (appIds == NULL) {
	ogs_error("OpenAPI_notification_push_convertToJSON() failed [appIds]");
        goto end;
    }
    OpenAPI_list_for_each(notification_push->app_ids, node) {
        cJSON *itemLocal = OpenAPI_app_id_convertToJSON(node->data);
        if (itemLocal == NULL) {
	    ogs_error("OpenAPI_notification_push_convertToJSON() failed [appIds]");
            goto end;
        }
        cJSON_AddItemToArray(app_ids, itemLocal);
    }
    }

    if (!notification_push->allowed_delay) {
	ogs_error("OpenAPI_notification_push_convertToJSON() failed [allowedDelay]");
        return NULL;
    }
    if (cJSON_AddStringToObject(item, "allowedDelay", notification_push->allowed_delay) == NULL) {
        ogs_error("OpenAPI_application_for_pfd_request_convertToJSON() failed [pfdTimestamp]");
        goto end;
    }

    if (!notification_push->pfd_op) {
        ogs_error("OpenAPI_notification_push_convertToJSON() failed [pfdOp]");
        return NULL;
    }
    if (cJSON_AddStringToObject(item, "pfdOp", notification_push->pfd_op) == NULL) {
        ogs_error("OpenAPI_application_for_pfd_request_convertToJSON() failed [pfdOp]");
        goto end;
    }

end:
    return item;
}

OpenAPI_notification_push_t *OpenAPI_notification_push_parseFromJSON(cJSON *notification_pushJSON) {
    OpenAPI_notification_push_t *notification_push_local_var = NULL;
    OpenAPI_lnode_t *node = NULL;
    cJSON *app_ids = NULL;
    OpenAPI_list_t *app_idsList = NULL;
    cJSON *allowed_delay = NULL;
    cJSON *pfd_ops = NULL;
    OpenAPI_pfd_operation_t *pfd_op_local_nonprim = NULL;


    app_ids = cJSON_GetObjectItemCaseSensitive(notification_pushJSON, "appIds");
    if (app_ids) {
        cJSON *app_ids_local = NULL;
        if (!cJSON_IsArray(app_ids)) {
            ogs_error("OpenAPI_notification_push_parseFromJSON failed [app_ids]");
            goto end;
        }

        app_idsList = OpenAPI_list_create();

        cJSON_ArrayForEach(app_ids_local, app_ids) {
            if (!cJSON_IsObject(app_ids_local)) {
		ogs_error("OpenAPI_notification_push_parseFromJSON failed [app_ids]");
                goto end;
            }
            OpenAPI_app_id_t *app_idsItem = OpenAPI_app_id_parseFromJSON(app_ids_local);
            if (!app_idsItem) {
                ogs_error("No app_idsItem");
                goto end;
            }
            OpenAPI_list_add(app_idsList, app_idsItem);
        }
    }

    allowed_delay = cJSON_GetObjectItemCaseSensitive(notification_pushJSON, "allowedDelay");
    if (!allowed_delay) {
	ogs_error("OpenAPI_notification_push_parseFromJSON failed [allowedDelay]");
        goto end;
    }
    if (!cJSON_IsNumber(allowed_delay)) {
	ogs_error("OpenAPI_notification_push_parseFromJSON failed [allowedDelay]");
        goto end;
    }

    pfd_op = cJSON_GetObjectItemCaseSensitive(notification_pushJSON, "pfdOp");
    if (!pfd_op) {
	ogs_error("OpenAPI_notification_push_parseFromJSON failed [pfdOp]");
        goto end;
    }
    pfd_op_local_nonprim = OpenAPI_pfd_op_parseFromJSON(pfd_op);
    if (!pfd_op_local_nonprim) {
	ogs_error("OpenAPI_notification_push_parseFromJSON failed [pfdOp]");
        goto end;
    }

    notification_push_local_var = OpenAPI_access_token_req_create (
	app_ids ? app_idsList :  NULL,
	allowed_delay ? allowed_delay->valueint : 0,
	pfd_ops ? pfd_op_local_nonprim : NULL	
    );

    return notification_push_local_var;
end:
    if (app_idsList) {
        OpenAPI_list_for_each(app_idsList, node) {
            OpenAPI_app_id_free(node->data);
        }
        OpenAPI_list_free(app_idsList);
        app_idsList = NULL;
    }
    if (pfd_op_local_nonprim) {
        OpenAPI_pfd_operation_free(pfd_op_local_nonprim);
        pfd_op_local_nonprim = NULL;
    }
    return NULL;

}

OpenAPI_notification_push_t OpenAPI_notification_push_copy(OpenAPI_notification_push_t *src, OpenAPI_notification_push_t *dst) {
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_notification_push_convertToJSON(src);
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

    OpenAPI_notification_push_free(dst);
    dst = OpenAPI_notification_push_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}
