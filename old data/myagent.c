#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dbus/dbus-glib.h>
#include "myagent.h"
#include "agent_stub.h"

gboolean my_agent_release(MyAgent *obj, GError **error)
{
	return TRUE;
}

gboolean my_agent_request_pin_code(MyAgent *obj, DBusGObjectPath *device, gchar **pin, GError **error)
{
	return TRUE;
}

gboolean my_agent_request_passkey(MyAgent *obj, DBusGObjectPath *device, gint32 *ret, GError **error)
{
	return TRUE;
}
gboolean my_agent_display_passkey(MyAgent *obj, DBusGObjectPath *device, gint32 passkey, int entered,GError **error)
{
	return TRUE;
}
gboolean my_agent_request_confirmation(MyAgent *obj, DBusGObjectPath *device, gint32 passkey, GError **error)
{
	return TRUE;
}
gboolean my_agent_authorize(MyAgent *obj, DBusGObjectPath *device, gchar *uuid, GError **error)
{
	return TRUE;
}
gboolean my_agent_confirm_mode_change(MyAgent *obj, gchar *mode, GError **error)
{
	return TRUE;
}
gboolean my_agent_cancel(MyAgent *obj, GError **error)
{
	return TRUE;
}

int main(int argc, char *argv[])
{
	DBusGConnection *bus;
	DBusGProxy *bus_proxy;
	GError *error = NULL;
	GMainLoop *mainloop;
	guint request_name_result;	
	MyAgent *obj;

	g_type_init();
	dbus_g_object_type_install_info(MY_AGENT_TYPE, &dbus_glib_my_agent_object_info);
	mainloop = g_main_loop_new(NULL, FALSE);
	bus = dbus_g_bus_get(DBUS_BUS_SYSTEM, &error);
	if(!bus)
		lose_gerror ("Couldn't connect to system bus", error);
	bus_proxy = dbus_g_proxy_new_for_name(bus, "org.freedesktop.DBus", "/", "org.freedesktop.DBus");
	if(!dbus_g_proxy_call(bus_proxy, "RequestName", &error,
						  G_TYPE_STRING, "org.bluez",
						  G_TYPE_UINT, 0,
						  G_TYPE_INVALID,
						  G_TYPE_UINT, &request_name_result,
						  G_TYPE_INVALID)) {
		lose_gerror ("Failed to acquire org.bluez", error);
	}
	obj = g_object_new(MY_AGENT_TYPE, NULL);
	dbus_g_connection_register_g_object(bus, "/MyAgent", G_OBJECT(obj));
	g_printf ("service is running \n");
	g_main_loop_run(mainloop);
}
