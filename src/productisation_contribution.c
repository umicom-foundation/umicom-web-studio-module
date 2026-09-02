/*-----------------------------------------------------------------------------
 * Umicom Web Studio Module
 * File: src/productisation_contribution.c
 *
 * PURPOSE:
 *   Bind product identity and executable evidence to canonical Framework
 *   application definitions without copying shared implementation.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "umicom/web_studio/productisation_contribution.h"

static const UmiProductApplicationAdoption ADOPTION = {
    sizeof(UmiProductApplicationAdoption),
    "web-studio",
    "org.umicom.web-studio",
    "Umicom Web Studio",
    "umicom-web-studio-console",
    UMI_PRODUCT_FRONTEND_FLAG_CONSOLE | UMI_PRODUCT_FRONTEND_FLAG_WEB,
    1,
    1,
    1,
    1
};

/*
 * Provide the web studio productisation contribution operation used by this module and its
 * client applications.
 */
const UmiProductApplicationAdoption *
umi_web_studio_productisation_contribution(void)
{
    return &ADOPTION;
}

/*
 * Provide the web studio productisation snapshot operation used by this module and its
 * client applications.
 */
UmiStatus umi_web_studio_productisation_snapshot(
    UmiProductApplicationAdoptionSnapshot *out_snapshot)
{
    return umi_product_application_adoption_snapshot(
        &ADOPTION, out_snapshot);
}

/* Start this product through the Framework-owned session command plane. */
UmiStatus umi_web_studio_product_session_init(
    UmiProductApplicationSession *out_session)
{
    return umi_product_application_session_init(
        &ADOPTION, out_session);
}

/* Prepare Framework-owned workspace choices for this product's welcome UI. */
UmiStatus umi_web_studio_product_workspace_guide(
    UmiProductWorkspaceGuide *out_guide)
{
    return umi_product_workspace_guide_build(&ADOPTION, out_guide);
}
