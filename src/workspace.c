/*-----------------------------------------------------------------------------
 * Umicom Web Studio Module
 * File: src/workspace.c
 *
 * PURPOSE:
 *   Project canonical Framework layouts and next-feature planning through the thin application boundary.
 *
 * Created by: Sammy Hegab
 * Organisation: Umicom Foundation
 * Licence: MIT
 *---------------------------------------------------------------------------*/

#include "umicom/web_studio/workspace.h"

#include "umicom/web_studio/application.h"
#include "umicom/application/experience_plan.h"

size_t umi_web_studio_workspace_layout_count(void)
{
    const UmiApplicationExperienceDefinition *definition =
        umi_web_studio_application_experience();
    return definition != NULL ? definition->layout_count : 0U;
}

const UmiExperienceLayoutDefinition *umi_web_studio_workspace_layout_at(
    size_t index)
{
    const UmiApplicationExperienceDefinition *definition =
        umi_web_studio_application_experience();
    return definition != NULL && index < definition->layout_count
        ? &definition->layouts[index] : NULL;
}

const UmiExperienceLayoutDefinition *umi_web_studio_workspace_default(void)
{
    const UmiApplicationExperienceDefinition *definition =
        umi_web_studio_application_experience();
    return definition != NULL
        ? umi_application_experience_layout_find(
            definition, definition->default_layout_id)
        : NULL;
}

const UmiExperienceFeatureDefinition *umi_web_studio_workspace_next_feature(
    void)
{
    return umi_application_experience_next_feature(
        umi_web_studio_application_experience());
}
