/*-----------------------------------------------------------------------------
 * Umicom Web Studio Module
 * File: tests/test_workspace.c
 *
 * PURPOSE:
 *   Verify the module exposes Framework-owned layouts without duplicating workbench logic.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include <assert.h>

#include "umicom/web_studio/workspace.h"

/*
 * Start this command or application, report setup failures, and return a process exit code
 * to the operating system.
 */
int main(void)
{
    const UmiExperienceLayoutDefinition *layout =
        umi_web_studio_workspace_default();
    assert(umi_web_studio_workspace_layout_count() > 0U);
    assert(layout != NULL);
    assert(layout->panel_count > 0U);
    assert(umi_web_studio_workspace_layout_at(0U) != NULL);
    return 0;
}
