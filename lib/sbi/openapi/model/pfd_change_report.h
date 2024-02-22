/*
 * pfd_change_report.h
 *
 * Represents an error report on PFD change.
 */

#ifndef OpenAPI__pfd_change_report_H_
#define OpenAPI__pfd_change_report_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "problem_details.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct OpenAPI_pfd_change_report_s OpenAPI_pfd_change_report_t;
typedef struct OpenAPI_pfd_change_report_s {
    OpenAPI_problem_details_t *pfd_error; //model
    OpenAPI_list_t *application_id; //primitive container

} OpenAPI_pfd_change_report_t;

OpenAPI_pfd_change_report_t *OpenAPI_pfd_change_report_create(
    OpenAPI_problem_details_t *pfd_error,
    OpenAPI_list_t *application_id
);

void OpenAPI_pfd_change_report_free(OpenAPI_pfd_change_report_t *pfd_change_report);
OpenAPI_pfd_change_report_t *OpenAPI_pfd_change_report_parseFromJSON(cJSON *pfd_change_reportJSON);
cJSON *OpenAPI_pfd_change_report_convertToJSON(OpenAPI_pfd_change_report_t *pfd_change_report);
OpenAPI_pfd_change_report_t OpenAPI_pfd_change_report_copy(OpenAPI_pfd_change_report_t* src, OpenAPI_pfd_change_report_t* dst);

#ifdef __cplusplus
}
#endif
#endif /* _pfd_change_report_H_ */

