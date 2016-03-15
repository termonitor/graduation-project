#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dbus/dbus-glib.h>

int main(int argc, char *argv[])
{
	DBusGConnection *connection;
	GError *error = NULL;
	DBusGProxy *proxy;

	connection = dbus_g_bus_get(DBUS_BUS_SYSTEM, &error);
	if(connection == NULL) {
		g_printerr("get system bus failed: %s\n", error->message);
		g_error_free(error);
		return -1;
	}
	g_print("dbus_g_proxy_new_for_name \n");
	proxy = dbus_g_proxy_new_for_name(connection, "org.bluez", "/xiaoming/agent", "org.bluez.Agent");
	g_print("dbus_g_proxy_call \n");
	gchar *method = "RequestPinCode";
	gchar *ret;
	DBusGObjectPath *path = "/";`
	
	if(!dbus_g_proxy_call(proxy, method, &error,
						  DBUS_TYPE_G_OBJECT_PATH, path,
						  G_TYPE_INVALID,
						  G_TYPE_STRING, &ret,
						  G_TYPE_INVALID)) {
		g_printerr("call %s failed: %s\n", method, error->message);
		g_error_free(error);
		error = NULL;
	}
	g_print("result : %s \n", ret);
}
