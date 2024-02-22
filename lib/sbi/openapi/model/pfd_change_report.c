#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pfd_change_report.h"

OpenAPI_pfd_change_report_t *OpenAPI_pfd_change_report_create(
    OpenAPI_problem_details_t *pfd_error,
    OpenAPI_list_t *application_id
    ) {
    OpenAPI_pfd_change_report_t *pfd_change_report_local_var = ogs_malloc(sizeof(OpenAPI_pfd_change_report_t));
    ogs_assert(pfd_change_report_local_var);

    pfd_change_report_local_var->pfd_error = pfd_error;
    pfd_change_report_local_var->application_id = application_id;

    return pfd_change_report_local_var;
}


void OpenAPI_pfd_change_report_free(OpenAPI_pfd_change_report_t *pfd_change_report) {
    OpenAPI_lnode_t *node = NULL;

    if(NULL == pfd_change_report){
        return ;
    }

    if (pfd_change_report->pfd_error) {
	ogs_free(pfd_change_report->pfd_error);
	pfd_change_report->pfd_error = NULL;
    }

    if (pfd_change_report->application_id) {
        OpenAPI_list_for_each(pfd_change_report->application_id, node) {
            OpenAPI_app_ids_free(node->data);
        }
        OpenAPI_list_free(pfd_change_report->application_id);
        pfd_change_report->application_id = NULL;
    }

    ogs_free(pfd_change_report);
}

cJSON *OpenAPI_pfd_change_report_convertToJSON(OpenAPI_pfd_change_report_t *pfd_change_report) {
    cJSON *item = NULL;
    OpenAPI_lnode_t *node = NULL;

    if (pfd_change_report == NULL) {
        ogs_error("OpenAPI_pfd_change_report_convertToJSON failed [PfdChangeReport]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (!pfd_change_report->pfd_error) {
        ogs_error("cJSON *OpenAPI_pfd_change_report_convertToJSON failed [pfdError]");
        return NULL;
    }
    if (cJSON_AddStringToObject(item, "pfdError", pfd_change_report->pfd_error) == NULL) {
        ogs_error("cJSON *OpenAPI_pfd_change_report_convertToJSON [pfdError]");
        goto end;
    }

    if (pfd_change_report->application_id) {
    cJSON *app_ids = cJSON_AddArrayToObject(item, "applicationIds");
    if (appIds == NULL) {
	ogs_error("cJSON *OpenAPI_pfd_change_report_convertToJSON failed [applicationIds]");
        goto end;
    }
    OpenAPI_list_for_each(pfd_change_report->application_id, node) {
        cJSON *itemLocal = OpenAPI_application_id_convertToJSON(node->data);
        if (itemLocal == NULL) {
	    ogs_error("cJSON *OpenAPI_pfd_change_report_convertToJSON failed [applicationIds]");
            goto end;
        }
        cJSON_AddItemToArray(app_ids, itemLocal);
    }
    }

end:
    return item;
}

OpenAPI_pfd_change_report_t *OpenAPI_pfd_change_report_parseFromJSON(cJSON *pfd_change_reportJSON) {
    OpenAPI_pfd_change_report_t *pdf_change_report_local_var = NULL;
    OpenAPI_lnode_t *node = NULL;
    cJSON *application_id = NULL;
    OpenAPI_list_t *application_idList = NULL;
    cJSON *pfd_error = NULL;
    OpenAPI_problem_details_t *pfd_error_local_nonprim = NULL;

    pfd_error = cJSON_GetObjectItemCaseSensitive(pfd_change_reportJSON, "pfdError");
    if (!pfd_op) {
        ogs_error("OpenAPI_pfd_change_report_parseFromJSON  failed [pfdError]");
        goto end;
    }
    pfd_error_local_nonprim = OpenAPI_pfd_op_parseFromJSON(pfd_error);
    if (!pfd_error_local_nonprim) {
	ogs_error("OpenAPI_pfd_change_report_parseFromJSON  failed [pfdError]");
        goto end;
    }
    pfd_error_local_nonprim = problem_details_parseFromJSON(pfd_error); //nonprimitive

    application_id = cJSON_GetObjectItemCaseSensitive(notification_pushJSON, "applicationId");
    if (application_id) {
        cJSON *application_id_local = NULL;
        if (!cJSON_IsArray(application_id)) {
	    ogs_error("OpenAPI_pfd_change_report_parseFromJSON  failed [applicationId]");
            goto end;
        }

        application_idList = OpenAPI_list_create();

        cJSON_ArrayForEach(application_id_local, application_id) {
            if (!cJSON_IsObject(application_id_local)) {
		ogs_error("OpenAPI_pfd_change_report_parseFromJSON  failed [applicationId]");
                goto end;
            }
            OpenAPI_plmn_id_t *application_idItem = OpenAPI_app_id_parseFromJSON(application_id_local);
            if (!application_idItem) {
                ogs_error("No application_idItem");
                goto end;
            }
            OpenAPI_list_add(application_idList, application_idItem);
        }
    }

    pfd_change_report_local_var = pfd_change_report_create (
	pfd_error ? pfd_error_local_nonprim : NULL,
        application_id ? application_idList : NULL
    );

    return pfd_change_report_local_var;
end:
    if (pfd_error_local_nonprim) {
        OpenAPI_problem_details_free(pfd_error_local_nonprim);
        pfd_error_local_nonprim = NULL;
    }
    if (application_idList) {
        OpenAPI_list_for_each(application_idList, node) {
            OpenAPI_app_id_free(node->data);
        }
        OpenAPI_list_free(application_idList);
        application_idList = NULL;
    }
    return NULL;
}

OpenAPI_pfd_change_report_t OpenAPI_pfd_change_report_copy(OpenAPI_pfd_change_report_t* src, OpenAPI_pfd_change_report_t* dst) {
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_pfd_change_report_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_pfd_change_report_convertToJSON failed");
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

    OpenAPI_pfd_change_report_free(dst);
    dst = OpenAPI_notification_push_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}
