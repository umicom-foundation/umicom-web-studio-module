/*-----------------------------------------------------------------------------
 * Umicom Web Studio Module
 * File: src/productisation_contribution.c
 *
 * PURPOSE:
 *   Bind product identity and executable evidence to canonical Framework
 *   application definitions without copying shared implementation.
 *
 * Created by: Sammy Hegab
 * Organisation: Umicom Foundation
 * Licence: MIT
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

const UmiProductApplicationAdoption *
umi_web_studio_productisation_contribution(void)
{
    return &ADOPTION;
}

UmiStatus umi_web_studio_productisation_snapshot(
    UmiProductApplicationAdoptionSnapshot *out_snapshot)
{
    return umi_product_application_adoption_snapshot(
        &ADOPTION, out_snapshot);
}
