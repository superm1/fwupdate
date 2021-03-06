/*
 * libfw - library interface to apply firmware updates
 *
 * Copyright 2015 Red Hat, Inc.
 *
 * See "COPYING" for license terms.
 *
 * Author: Peter Jones <pjones@redhat.com>
 */
#ifndef LIBFW_H
#define LIBFW_H

#include <dirent.h>
#include <efivar.h>
#include <errno.h>
#include <sys/types.h>
#include <time.h>

extern int fwup_supported(void);

#define FWUP_RESOURCE_TYPE_UNKNOWN		0
#define FWUP_RESOURCE_TYPE_SYSTEM_FIRMWARE	1
#define FWUP_RESOURCE_TYPE_DEVICE_FIRMWARE	2
#define FWUP_RESOURCE_TYPE_UEFI_DRIVER		3
#define FWUP_RESOURCE_TYPE_FMP			4

#define FWUP_LAST_ATTEMPT_STATUS_SUCCESS			0x00000000
#define FWUP_LAST_ATTEMPT_STATUS_ERROR_UNSUCCESSFUL		0x00000001
#define FWUP_LAST_ATTEMPT_STATUS_ERROR_INSUFFICIENT_RESOURCES	0x00000002
#define FWUP_LAST_ATTEMPT_STATUS_ERROR_INCORRECT_VERSION	0x00000003
#define FWUP_LAST_ATTEMPT_STATUS_ERROR_INVALID_FORMAT		0x00000004
#define FWUP_LAST_ATTEMPT_STATUS_ERROR_AUTH_ERROR		0x00000005
#define FWUP_LAST_ATTEMPT_STATUS_ERROR_PWR_EVT_AC		0x00000006
#define FWUP_LAST_ATTEMPT_STATUS_ERROR_PWR_EVT_BATT		0x00000007

typedef struct fwup_resource_s fwup_resource;
typedef struct fwup_resource_iter_s fwup_resource_iter;

extern int fwup_resource_iter_next(fwup_resource_iter *iter,
				   fwup_resource **re);
extern int fwup_resource_iter_create(fwup_resource_iter **iter);
extern int fwup_resource_iter_destroy(fwup_resource_iter **iter);

extern int fwup_set_up_update(fwup_resource *re, uint64_t hw_inst, int infd);
extern int fwup_set_up_update_with_buf(fwup_resource *re, uint64_t hw_inst,
				       const void *buf, size_t sz);
extern int fwup_clear_status(fwup_resource *re);
extern int fwup_get_guid(fwup_resource *re, efi_guid_t **guid);
extern int fwup_get_fw_type(fwup_resource *re, uint32_t *type);
extern int fwup_get_fw_version(fwup_resource *re, uint32_t *version);
extern int fwup_get_lowest_supported_fw_version(fwup_resource *re,
						uint32_t *version);
extern int fwup_get_last_attempt_info(fwup_resource *re, uint32_t *version,
			   uint32_t *status, time_t *when);
extern const char *fwup_last_attempt_status_to_string (uint64_t status);
extern int fwup_print_update_info(void);

#endif /* LIBFW_H */
