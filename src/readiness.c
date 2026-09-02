/*-----------------------------------------------------------------------------
 * Umicom Web Studio Module
 * File: src/readiness.c
 *
 * PURPOSE:
 *   Project the canonical Framework feature backlog without product-local roadmap duplication.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "umicom/web_studio/readiness.h"

#include "umicom/web_studio/runtime.h"
#include "umicom/application/experience_plan.h"

/*
 * Provide the web studio readiness report operation used by this module and its client
 * applications.
 */
UmiStatus umi_web_studio_readiness_report(
    UmiApplicationReadinessReport *out_report)
{
    const UmiApplicationExperienceDefinition *experience =
        umi_web_studio_runtime_experience();
    /*
     * Protect caller-owned memory by checking that required state is available before it is
     * used.
     */
    if (experience == NULL) return UMI_STATUS_NOT_FOUND;
    return umi_application_readiness_report(experience, out_report);
}

/*
 * Provide the web studio readiness next feature operation used by this module and its
 * client applications.
 */
const UmiExperienceFeatureDefinition *umi_web_studio_readiness_next_feature(void)
{
    return umi_application_experience_next_feature(
        umi_web_studio_runtime_experience());
}
