#include "ogs-dbi.h"

int ogs_dbi_pfd_data(char *application_id, ogs_dbi_pfd_data_t *pfd_data) {
    int rv = OGS_OK;
    mongoc_cursor_t *cursor = NULL;
    bson_t *query = NULL;
    bson_error_t error;
    const bson_t *document;
    bson_iter_t iter;
    bson_iter_t inner_iter;
    char buf[OGS_KEY_LEN];
    char *utf8 = NULL;
    uint32_t length = 0;

    ogs_assert(application_id);
    ogs_assert(pfd_data);

    query = BCON_NEW("application_id", BCON_UTF8(application_id));
#if MONGOC_MAJOR_VERSION >= 1 && MONGOC_MINOR_VERSION >= 5
    cursor = mongoc_collection_find_with_opts(
            ogs_mongoc()->collection.application, query, NULL, NULL);
#else
    cursor = mongoc_collection_find(ogs_mongoc()->collection.application,
            MONGOC_QUERY_NONE, 0, 0, 0, query, NULL, NULL);
#endif
    if (!mongoc_cursor_next(cursor, &document)) {
        ogs_info("[%s] Cannot find APPICATION_ID in DB", application_id);

        rv = OGS_ERROR;
        goto out;
    }

    if (mongoc_cursor_error(cursor, &error)) {
        ogs_error("Cursor Failure: %s", error.message);

        rv = OGS_ERROR;
        goto out;
    }

    if (!bson_iter_init(&inner_iter, document)) {
        ogs_error("bson_iter_init failed in this document");

        rv = OGS_ERROR;
        goto out;
    }

    memset(pfd_data, 0, sizeof(ogs_dbi_pfd_data_t));
    pfd_data->is_allowed_delay = false;
    //bson_iter_recurse(&iter, &inner_iter);

    while (bson_iter_next(&inner_iter)) {
		const char *key = bson_iter_key(&inner_iter);

        if (!strcmp(key, OGS_APPLICATION_ID_STRING) && BSON_ITER_HOLDS_UTF8(&inner_iter)) {
            utf8 = (char *)bson_iter_utf8(&inner_iter, &length);
			pfd_data->application_id = 
					ogs_strndup(utf8, ogs_min(length, OGS_KEY_LEN) + 1);
        } else if (!strcmp(key, OGS_PFDS_STRING) && BSON_ITER_HOLDS_UTF8(&inner_iter))  {
			// pfds
			//pfd_data->pfds = OpenAPI_list_create();
        } else if (!strcmp(key, OGS_CACHING_TIME_STRING) &&
                BSON_ITER_HOLDS_UTF8(&inner_iter)) {
            utf8 = (char *)bson_iter_utf8(&inner_iter, &length);
			pfd_data->caching_time = 
					ogs_strndup(utf8, ogs_min(length, OGS_KEY_LEN) + 1);
        } else if (!strcmp(key, OGS_SUPPORTED_FEATURES_STRING) &&
                BSON_ITER_HOLDS_UTF8(&inner_iter)) {
            utf8 = (char *)bson_iter_utf8(&inner_iter, &length);
			pfd_data->supp_feat = 
					ogs_strndup(utf8, ogs_min(length, OGS_KEY_LEN) + 1);
        } else if (!strcmp(key, OGS_RESET_IDS_STRING) &&
                BSON_ITER_HOLDS_UTF8(&inner_iter)) {
			// reset ids
			//pfd_data->reset_ids = OpenAPI_list_create();
        } else if (!strcmp(key, OGS_ALLOWED_DELAY_STRING) &&
                BSON_ITER_HOLDS_INT32(&inner_iter)) {
	    pfd_data->is_allowed_delay = 1;
            pfd_data->allowed_delay = bson_iter_int32(&inner_iter);
        } else if (!strcmp(key, "_id")) {
			continue;
	}
    }

out:
    if (query) bson_destroy(query);
    if (cursor) mongoc_cursor_destroy(cursor);

    return rv;
}
