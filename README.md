# umicom-web-studio-module
Thin C23 Umicom Web Studio application composition over Umicom Framework

## Review linked context values

Web Studio exposes Framework's reviewed context changes through
`umi_web_studio_workspace_context_review`, `umi_web_studio_workspace_context_apply`
and `umi_web_studio_workspace_clear_context` in
`umicom/web_studio/workspace_commands.h`. A context group is a named value that
related panels can share; for example, a host could use `web.project` with the sample
value `sample-site`. The host must connect that name to its panel consumers.

1. Use a runtime initialised with this product's canonical experience. Prepare
   the requested changes with the review function; preparation changes no live state.
2. Display the copied Framework summary and rows. Keep the runtime and its
   workbench alive while the user reviews the proposed values. If the summary
   reports UI differences, show the captured UI value beside the cached value.
3. Apply only after acceptance, then destroy the review. If the workspace changed,
   prepare a fresh review. Cancelling only destroys the review.

This is a module API; native review screens are separate host work. Context edits
do not execute product commands or external operations. The shared guide at
`framework/docs/guides/REVIEWING_LINKED_CONTEXTS.html` in the Applications checkout
explains capacity, ownership, thread coordination and recovery in more detail.

The [local C website and API example](docs/LOCAL_WEB_SERVICE.html) connects Framework routing to an explicit loopback listener. It provides a small HTML page, JSON health response and POST echo, plus read-only preview of an explicitly selected website export. Each static file must be smaller than 16 KiB. The terminal server is separate from public deployment and the visual workspace.

Keep page images, copy drafts and reference documents together before adding them to a website. The **Creative workbench → Asset library** page imports complete files, reorders them, saves and reopens a portable collection, and exports selected assets. It is separate from the scene project and never uploads files. See the [shared asset library guide](../../framework/docs/learning/creative-asset-libraries.html) for limits, save steps and recovery.
