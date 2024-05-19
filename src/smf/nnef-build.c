#include "nnef-build.h"

ogs_sbi_request_t *smf_nnef_pdf_management_build_get(smf_sess_t *sess, void *data)
{
    smf_ue_t *smf_ue = NULL;
    ogs_sbi_message_t message;
    ogs_sbi_request_t *request = NULL;

    ogs_assert(sess);
    //smf_ue = sess->smf_ue;
    //ogs_assert(smf_ue);
    //ogs_assert(smf_ue->supi);

    memset(&message, 0, sizeof(message));
    message.h.method = (char *)OGS_SBI_HTTP_METHOD_GET;
    message.h.service.name = (char *)OGS_SBI_SERVICE_NAME_NNEF_PFDMANAGEMENT;
    message.h.api.version = (char *)OGS_SBI_API_V2;
    message.h.resource.component[0] = OGS_SBI_RESOURCE_NAME_APPLICATIONS;
    message.h.resource.component[1] = "addpId";

    //message.param.single_nssai_presence = true;
    //memcpy(&message.param.s_nssai, &sess->s_nssai,
    //        sizeof(message.param.s_nssai));

    //if (sess->session.name)
    //    message.param.dnn = sess->session.name;

    request = ogs_sbi_build_request(&message);
    ogs_expect(request);

    return request;
}
