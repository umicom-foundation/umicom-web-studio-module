/*-----------------------------------------------------------------------------
 * Umicom Web Studio Module
 * File: include/umicom/web_studio/application.h
 *
 * PURPOSE:
 *   Expose the thin Umicom Web Studio composition over the Framework-owned
 *   application experience, runtime, readiness and workbench services.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#ifndef UMICOM_WEB_STUDIO_APPLICATION_H
#define UMICOM_WEB_STUDIO_APPLICATION_H

#include "umicom/application/experience.h"
#include "umicom/application/experience_status.h"
#include "umicom/application/thin_client.h"

#ifdef __cplusplus
extern "C" {
#endif

#define WEB_STUDIO_APPLICATION_ID "org.umicom.web-studio"

/* Return the canonical Framework application identifier used by this product. */
const char *umi_web_studio_application_id(void);

/**
 * Provide the web studio application experience operation used by this module and its
 * client applications.
 */
const UmiApplicationExperienceDefinition *
umi_web_studio_application_experience(void);
/*
 * Initialise the product through the shared Framework thin-client helper.
 * The module does not create duplicate services, storage or workbench models.
 */
UmiStatus umi_web_studio_application_init(
    UmiApplicationThinClient *out_client);

/**
 * Provide the web studio application status operation used by this module and its client
 * applications.
 */
UmiStatus umi_web_studio_application_status(
    UmiApplicationExperienceStatus *out_status);

#ifdef __cplusplus
}
#endif
#endif
