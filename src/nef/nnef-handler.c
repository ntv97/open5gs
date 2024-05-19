/*
 * Copyright (C) 2019,2020 by Sukchan Lee <acetcom@gmail.com>
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

bool nnef_pfd_management_handle_create_subscription(
        ogs_sbi_stream_t *stream, ogs_sbi_message_t *message) {
	ogs_error("Handle create pfd subscription");

	/*char *app_id = message->h.resource.component[1];
	if (app_id) {
		ogs_error("application id: %s", app_id);
	}*/

	OpenAPI_pfd_subscription_t *PfdSubInput = message->PfdSubscription;
        if (!PfdSubInput) {
                ogs_error("No PfdSubscription");
                return OGS_ERROR;
        }
        ogs_error("notify_uri: %s", PfdSubInput->notify_uri);

	ogs_sbi_message_t sendmsg;
        ogs_sbi_response_t *response = NULL;

	char* uri = "{apiRoot}/nnef-pfdmanagement/v1/subscriptions/{subscriptionId}";
        OpenAPI_pfd_data_for_app_t Pfd_App;
	OpenAPI_pfd_subscription_t PfdSubscription;
        memset(&PfdSubscription, 0, sizeof(PfdSubscription));

        PfdSubscription.application_ids = OpenAPI_list_create();
	PfdSubscription.notify_uri = uri; //malloc(2*sizeof(char));
	PfdSubscription.supported_features = malloc(2*sizeof(char));



        memset(&sendmsg, 0, sizeof(sendmsg));

        ogs_assert(stream);
        ogs_assert(recvmsg);

        sendmsg.PfdSubscription = &PfdSubscription;
        response = ogs_sbi_build_response(
                        &sendmsg, OGS_SBI_HTTP_STATUS_OK);
        ogs_assert(response);
        ogs_assert(true == ogs_sbi_server_send_response(stream, response));
        ogs_error("Pfd sent");

        return true;
}

bool nnef_pfd_management_handle_fetch(
	ogs_sbi_stream_t *stream, ogs_sbi_message_t *message)
{
	ogs_error("Handle fetch pfd");
	char *app_id = message->h.resource.component[1];
	if (app_id) {
		//ogs_error("App id: %s\n", app_id);
		return nnef_pfd_management_handle_fetch_individual(stream, message, app_id);
	}
	ogs_error("fetch all pfd");
	ogs_sbi_message_t sendmsg;
    	ogs_sbi_response_t *response = NULL;

	OpenAPI_pfd_data_for_app_t Pfd_App;
	memset(&Pfd_App, 0, sizeof(Pfd_App));

	Pfd_App.application_id = app_id;
	Pfd_App.caching_timer = 99;
	Pfd_App.pfd_timestamp = calloc(2, sizeof(char));
	//Pfd_App.pfd_timestamp[0] = '9';
	Pfd_App.caching_time = calloc(2, sizeof(char));
	//Pfd_App.caching_time[0] = 7;
	Pfd_App.pfds = OpenAPI_list_create();
	Pfd_App.supported_features = calloc(2, sizeof(char));
	//Pfd_App.supported_features[0] = '8';
	Pfd_App.partial_flag = 1;



	memset(&sendmsg, 0, sizeof(sendmsg));

    	ogs_assert(stream);
    	ogs_assert(message);

	sendmsg.PfdDataForApp = &Pfd_App;
	response = ogs_sbi_build_response(
			&sendmsg, OGS_SBI_HTTP_STATUS_OK);
	ogs_assert(response);
	ogs_assert(true == ogs_sbi_server_send_response(stream, response));
	ogs_error("Pfd sent");
	return true;
}

bool nnef_pfd_management_handle_fetch_individual(
        ogs_sbi_stream_t *stream, ogs_sbi_message_t *message, char* app_id) {
	ogs_error("Handle fetch pfd individual- app_id: %s", app_id);
	ogs_sbi_message_t sendmsg;
        ogs_sbi_response_t *response = NULL;

        OpenAPI_pfd_data_for_app_t Pfd_App;
        memset(&Pfd_App, 0, sizeof(Pfd_App));

        Pfd_App.application_id = app_id;
        Pfd_App.caching_timer = 99;
        Pfd_App.pfd_timestamp = calloc(2, sizeof(char));
        //Pfd_App.pfd_timestamp[0] = '9';
        Pfd_App.caching_time = calloc(2, sizeof(char));
        //Pfd_App.caching_time[0] = 7;
        Pfd_App.pfds = OpenAPI_list_create();
        Pfd_App.supported_features = calloc(2, sizeof(char));
        //Pfd_App.supported_features[0] = '8';
        Pfd_App.partial_flag = 1;

        memset(&sendmsg, 0, sizeof(sendmsg));

        ogs_assert(stream);
        ogs_assert(message);

        sendmsg.PfdDataForApp = &Pfd_App;
        response = ogs_sbi_build_response(
                        &sendmsg, OGS_SBI_HTTP_STATUS_OK);
        ogs_assert(response);
        ogs_assert(true == ogs_sbi_server_send_response(stream, response));
        ogs_error("Pfd sent");
        return true;
}

bool nnef_pfd_managemnet_handle_fetch_partial_pull(
        ogs_sbi_stream_t *stream, ogs_sbi_message_t *message) {
	ogs_error("Handle fetch pfd by partial pull");
	OpenAPI_application_for_pfd_request_t *ApplicationForPfdReq = message->ApplicationForPfdRequest;
   	if (!ApplicationForPfdReq) {
        	ogs_error("No ApplicationForPfdReq");
        	return OGS_ERROR;
    	}
	ogs_error("app id: %s", ApplicationForPfdReq->application_id);
	ogs_error("timestamp: %s", ApplicationForPfdReq->pfd_timestamp);
	
        return true;
}
