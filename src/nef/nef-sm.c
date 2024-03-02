/*
 * Copyright (C) 2019-2023 by Sukchan Lee <acetcom@gmail.com>
 *
 * This file is part of Open5GS.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "sbi-path.h"
#include "nnef-handler.h"
#include <stdio.h>

void nef_state_initial(ogs_fsm_t *s, nef_event_t *e)
{
    nef_sm_debug(e);

    ogs_assert(s);

    OGS_FSM_TRAN(s, &nef_state_operational);
}

void nef_state_final(ogs_fsm_t *s, nef_event_t *e)
{
    nef_sm_debug(e);

    ogs_assert(s);
}

void nef_state_operational(ogs_fsm_t *s, nef_event_t *e)
{
    int rv;

    ogs_sbi_stream_t *stream = NULL;
    ogs_sbi_request_t *request = NULL;

    ogs_sbi_nf_instance_t *nf_instance = NULL;
    ogs_sbi_subscription_data_t *subscription_data = NULL;
    ogs_sbi_response_t *response = NULL;
    ogs_sbi_message_t message;

    nef_sm_debug(e);

    ogs_assert(s);

    switch (e->h.id) {
    case OGS_FSM_ENTRY_SIG:
        break;

    case OGS_FSM_EXIT_SIG:
        break;

    case OGS_EVENT_SBI_SERVER:
        request = e->h.sbi.request;
        ogs_assert(request);
        stream = e->h.sbi.data;
        ogs_assert(stream);

        rv = ogs_sbi_parse_request(&message, request);
        if (rv != OGS_OK) {
            /* 'message' buffer is released in ogs_sbi_parse_request() */
            ogs_error("cannot parse HTTP message");
            ogs_assert(true ==
                ogs_sbi_server_send_error(
                    stream, OGS_SBI_HTTP_STATUS_BAD_REQUEST,
                    NULL, "cannot parse HTTP message", NULL));
            break;
        }

        if (strcmp(message.h.api.version, OGS_SBI_API_V1) != 0) {
            ogs_error("Not supported version [%s]", message.h.api.version);
            ogs_assert(true ==
                ogs_sbi_server_send_error(
                    stream, OGS_SBI_HTTP_STATUS_BAD_REQUEST,
                    &message, "Not supported version", NULL));
            ogs_sbi_message_free(&message);
            break;
        }

	SWITCH(message.h.service.name)
	CASE(OGS_SBI_SERVICE_NAME_NNEF_PFDMANAGEMENT)
		ogs_error("NEFFFFFF PFDMANAGEMENT \n");

		SWITCH(message.h.resource.component[0])
		CASE(OGS_SBI_RESOURCE_NAME_APPLICATIONS)
			ogs_error("NEFFFFFF APPLICATIONS RESOURCE \n");
			SWITCH(message.h.resource.component[1])

		CASE(OGS_SBI_RESOURCE_NAME_PARTIAL_PULL)
			ogs_error("Partial Pull\n");
			nnef_pfd_managemnet_handle_fetch_partial_pull(
				stream, &message);
			break;
		DEFAULT
			ogs_error("Invalid HTTP method [%s]",
                                    message.h.method);
		END
			break;
		CASE(OGS_SBI_RESOURCE_NAME_SUBSCRIPTIONS)
			ogs_error("Subscriptions\n");
			SWITCH(message.h.method)
            CASE(OGS_SBI_HTTP_METHOD_POST)
					nnef_pfd_management_handle_create_subscription(
              			      stream, &message);
                break;
			DEFAULT
				ogs_error("Method [%s] not implemented", message.h.method);
			END
				break;
	   	 DEFAULT
			ogs_error("Invalid resource name [%s]",
                        message.h.resource.component[0]);
	    END
			ogs_sbi_message_free(&message);
	    	break;

    DEFAULT
        ogs_error("Invalid API name [%s]", message.h.service.name);
        ogs_assert(true ==
            ogs_sbi_server_send_error(stream,
                OGS_SBI_HTTP_STATUS_BAD_REQUEST, &message,
                "Invalid API name", message.h.resource.component[0]));
    END
        ogs_sbi_message_free(&message);
        break;

    default:
        ogs_error("No handler for event %s", nef_event_get_name(e));
        break;
    }
}
