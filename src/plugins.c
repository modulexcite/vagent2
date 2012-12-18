#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "ipc.h"

struct agent_plugin_t *plugin_find(struct agent_core_t *core, const char *name)
{
	struct agent_plugin_t *plug;
	for (plug = core->plugins; plug != NULL; plug = plug->next) {
		if (!strcmp(name,plug->name))
			return plug;
	}
	return NULL;
}
struct agent_plugin_t *plugin_find_last(struct agent_core_t *core)
{
	struct agent_plugin_t *plug;
	for (plug = core->plugins; plug != NULL; plug = plug->next) {
		if (plug->next == NULL)
			return plug;
	}
	assert("Not reachable!");
	return NULL;
}

void plugin_alloc(char *name, struct agent_core_t *core)
{
	struct agent_plugin_t *plug = calloc(1, sizeof(struct agent_plugin_t));
	plug->ipc = calloc(1, sizeof(struct ipc_t ));
	ipc_init(plug->ipc);
	plug->name = strdup(name);
	plug->next = core->plugins;
	core->plugins = plug;
}
