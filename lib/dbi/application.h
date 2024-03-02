#if !defined(OGS_DBI_INSIDE) && !defined(OGS_DBI_COMPILATION)
#error "This header cannot be included directly."
#endif

#ifndef OGS_DBI_APPLICATION_H
#define OGS_DBI_APPLICATION_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_dbi_pfd_data_s {
   char*	application_id;
   // pfds array
   char*	caching_time;
   char*	supp_feat;
   // resets_ids array
   bool		is_allowed_delay;
   int		allowed_delay;
} ogs_dbi_pfd_data_t;

int ogs_dbi_pfd_data(char *application_id, ogs_dbi_pfd_data_t *pfd_data);

#ifdef __cplusplus
}
#endif

#endif /* OGS_DBI_APPLICATION_H */
