/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dbus/dbus-glib.h>*/

#ifndef MY_AGENT_H
#define MY_AGENT_H

typedef struct MyAgent MyAgent;
typedef struct MyAgentClass MyAgentClass;

struct MyAgent
{
	GObject parent;
};

struct MyAgentClass
{
	GObjectClass parent;
};

#define MY_AGENT_TYPE		(my_agent_get_type())

GType my_agent_get_type(void);

static void my_agent_init(MyAgent *obj)
{
}

static void my_agent_class_init(MyAgentClass *clazz)
{
}

gboolean my_agent_release(MyAgent *obj, GError **error);
gboolean my_agent_request_pin_code(MyAgent *obj, DBusGObjectPath *device, gchar **pin, GError **error);
gboolean my_agent_request_passkey(MyAgent *obj, DBusGObjectPath *device, gint32 *ret, GError **error);
gboolean my_agent_display_passkey(MyAgent *obj, DBusGObjectPath *device, gint32 passkey, int entered,GError **error);
gboolean my_agent_request_confirmation(MyAgent *obj, DBusGObjectPath *device, gint32 passkey, GError **error);
gboolean my_agent_authorize(MyAgent *obj, DBusGObjectPath *device, gchar *uuid, GError **error);
gboolean my_agent_confirm_mode_change(MyAgent *obj, gchar *mode, GError **error);
gboolean my_agent_cancel(MyAgent *obj, GError **error);
#endif
