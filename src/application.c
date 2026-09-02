/*-----------------------------------------------------------------------------
 * Umicom Web Studio Module
 * File: src/application.c
 *
 * PURPOSE:
 *   Bind the product identity to the canonical Framework application-experience catalogue.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "umicom/web_studio/application.h"

#include "umicom/application/experience_catalogue.h"

/*
 * Provide the web studio application id operation used by this module and its client
 * applications.
 */
const char *umi_web_studio_application_id(void)
{
    return "org.umicom.web-studio";
}

/*
 * Provide the web studio application experience operation used by this module and its
 * client applications.
 */
const UmiApplicationExperienceDefinition *
umi_web_studio_application_experience(void)
{
    return umi_application_experience_catalogue_find(
        umi_web_studio_application_id());
}

/*
 * Initialise web studio application from caller-provided values so later operations
 * receive a known state.
 */
UmiStatus umi_web_studio_application_init(
    UmiApplicationThinClient *out_client)
{
    return umi_application_thin_client_init(
        umi_web_studio_application_id(), out_client);
}

/*
 * Provide the web studio application status operation used by this module and its client
 * applications.
 */
UmiStatus umi_web_studio_application_status(
    UmiApplicationExperienceStatus *out_status)
{
    const UmiApplicationExperienceDefinition *definition =
        umi_web_studio_application_experience();
    /*
     * Protect caller-owned memory by checking that required state is available before it is
     * used.
     */
    if (definition == NULL) return UMI_STATUS_NOT_FOUND;
    return umi_application_experience_status(definition, out_status);
}
