/*-----------------------------------------------------------------------------
 * Umicom Web Studio Module
 * File: tests/test_application.c
 *
 * PURPOSE:
 *   Verify Umicom Web Studio resolves its canonical Framework experience and
 *   initialises the shared thin-client runtime without product-local services.
 *
 * Created by: Sammy Hegab
 * Organisation: Umicom Foundation
 * Licence: MIT
 *---------------------------------------------------------------------------*/

#include <assert.h>

#include "umicom/web_studio/application.h"

#include <string.h>

int main(void)
{
    UmiApplicationThinClient client;
    UmiStatus status = umi_web_studio_application_init(&client);

    if (status != UMI_STATUS_OK)
        return 1;
    if (strcmp(umi_web_studio_application_id(), "org.umicom.web-studio") != 0)
        return 2;
    if (client.contract.experience == NULL)
        return 3;
    if (strcmp(client.contract.experience->application_id, "org.umicom.web-studio") != 0)
        return 4;
    if (client.workspace.session.layout == NULL)
        return 5;
    if (strcmp(client.workspace.session.layout->layout_id,
               client.contract.experience->default_layout_id) != 0)
        return 6;
    return 0;
}
