/*-----------------------------------------------------------------------------
 * Umicom Web Studio Module
 * File: tests/test_application.c
 *
 * PURPOSE:
 *   Verify Umicom Web Studio resolves its canonical Framework experience and
 *   initialises the shared thin-client runtime without product-local services.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include <assert.h>

#include "umicom/web_studio/application.h"

#include <string.h>

/*
 * Start this command or application, report setup failures, and return a process exit code
 * to the operating system.
 */
int main(void)
{
    UmiApplicationThinClient client;
    UmiStatus status = umi_web_studio_application_init(&client);

    /* Preserve the original failure result so the caller can respond to the correct cause. */
    if (status != UMI_STATUS_OK)
        return 1;
    /* Use the stable identifier comparison to choose the matching record or policy. */
    if (strcmp(umi_web_studio_application_id(), "org.umicom.web-studio") != 0)
        return 2;
    /*
     * Protect caller-owned memory by checking that required state is available before it is
     * used.
     */
    if (client.contract.experience == NULL)
        return 3;
    /* Use the stable identifier comparison to choose the matching record or policy. */
    if (strcmp(client.contract.experience->application_id, "org.umicom.web-studio") != 0)
        return 4;
    /*
     * Protect caller-owned memory by checking that required state is available before it is
     * used.
     */
    if (client.workspace.session.layout == NULL)
        return 5;
    /* Use the stable identifier comparison to choose the matching record or policy. */
    if (strcmp(client.workspace.session.layout->layout_id,
               client.contract.experience->default_layout_id) != 0)
        return 6;
    return 0;
}
