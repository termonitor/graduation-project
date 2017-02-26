#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dbus/dbus-glib.h>
#include "marshal.h"

#define DBUS_TYPE_G_STRING_VALUE_HASHTABLE		\
	dbus_g_type_get_map("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)

//Globa Variable
GMainLoop *mainloop;
DBusGProxy *adapt;
gchar* device_address;

int stop_discovery(DBusGProxy *proxy);

int send_recv_objectpath_array(DBusGProxy *proxy)
{
	char *method;
	GError *error;
	GArray *ret;
	DBusGObjectPath *path;
	gint i;

	method = "ListAdapters";
	g_print("breakpoint\n");

	if(!dbus_g_proxy_call(proxy, method, &error, 
						  G_TYPE_INVALID, 
					      DBUS_TYPE_G_OBJECT_ARRAY, &ret,
						  G_TYPE_INVALID)) {
		g_printerr("call %s failed: %s\n", method, error->message);
		g_error_free(error);
		error = NULL;
		return -1;
	}

	g_print("receive object_path array:\n");
	for(i=0; i<ret->len; i++) {
//		g_print("%s ", g_array_index(ret, DBusGObjectPath, i));
	}
	g_print("ret size : %d \n", ret->len);
	g_print("\n over. \n");

	return 0;
}

DBusGObjectPath* getDefaultAdapter(DBusGProxy *proxy)
{
	char *method;
	GError *error;
	DBusGObjectPath *ret;

	g_print("breakpoint\n");
	method = "DefaultAdapter";
	if(!dbus_g_proxy_call(proxy, method, &error,
						  G_TYPE_INVALID,
						  DBUS_TYPE_G_OBJECT_PATH, &ret,
						  G_TYPE_INVALID)) {
		g_printerr("call %s failed: %s\n", method, error->message);
		g_error_free(error);
		error = NULL;
		return NULL;
	}
	g_print("%s \n", ret);
	return ret;
}

void test_handler(DBusGProxy *proxy, gchar *name, GValue value) {
	g_print("hello world !!!!! \n");
}

gboolean on = FALSE;

int adapt_powered(DBusGProxy *proxy, gboolean status)
{
	char *signal = "PropertyChanged";
	if(!on) {
//		g_print("add_signal \n");
		dbus_g_object_register_marshaller(marshal_VOID__STRING_VARIANT,
										G_TYPE_NONE,
										G_TYPE_STRING,
										G_TYPE_VALUE,
										G_TYPE_INVALID);
/*
		dbus_g_proxy_add_signal(proxy, signal,
								G_TYPE_STRING,
								G_TYPE_VALUE,
								G_TYPE_INVALID);
		dbus_g_proxy_connect_signal(proxy, signal,
									G_CALLBACK(test_handler),
									NULL, NULL);
*/
		on = TRUE;
	}
	GError *error = NULL;
	GValue gval = {0,};
	gchar *key = "Powered";
	char *method = "SetProperty";		

	g_value_init(&gval, G_TYPE_BOOLEAN);
	g_value_set_boolean(&gval, status);
	g_print("breakpoint \n");

	if(!dbus_g_proxy_call(proxy, method, &error,
						  G_TYPE_STRING, key,
						  G_TYPE_VALUE, &gval,
						  G_TYPE_INVALID,
						  G_TYPE_INVALID)) {
		g_printerr("call %s failed: %s\n", method, error->message);
		g_error_free(error);
		error = NULL;
		return -1;
	}

	return 0;
}

void signal_handler(DBusGProxy *proxy, gchar *address, GHashTable *table)
{
	g_print("DeviceFound signal Handler\n");
	//parse device table
	g_print("%s \n", address);
	memcpy(device_address, address, 18);
/*
	GValue *gvalue = g_hash_table_lookup(table, "Address");
	g_print("%s \n", G_VALUE_TYPE_NAME(gvalue));
	const gchar *Address = g_value_get_string(gvalue);
	int i = strlen(Address);
	g_print("%d %s \n", i, Address);
*/	
	GValue *gvalue = g_hash_table_lookup(table, "Name");
	const gchar *name = g_value_get_string(gvalue);
	gvalue = g_hash_table_lookup(table, "Alias");
	const gchar *alias = g_value_get_string(gvalue);
	if(!strcmp(name, "MindWave Mobile") || !strcmp(alias, "MindWave Mobile")) {
		stop_discovery(proxy);
		g_main_loop_quit(mainloop);				
	}
} 

int start_discovery(DBusGProxy *proxy)
{
	char *signal = "DeviceFound";/*
	dbus_g_object_register_marshaller(marshal_VOID__STRING_VARIANT,
										G_TYPE_NONE,
										G_TYPE_STRING,
										G_TYPE_VALUE,
										G_TYPE_INVALID);*/
	//add a signal that is emitted
	dbus_g_proxy_add_signal(proxy, signal,
							G_TYPE_STRING,
							DBUS_TYPE_G_STRING_VALUE_HASHTABLE,
							G_TYPE_INVALID);
	//connect a signal	
	dbus_g_proxy_connect_signal(proxy, signal,
								G_CALLBACK(signal_handler),
								NULL, NULL);

	GError *error = NULL;
	char *method = "StartDiscovery";
	if(!dbus_g_proxy_call(proxy, method, &error,
						  G_TYPE_INVALID,
						  G_TYPE_INVALID)) {
		g_printerr("call %s failed: %s\n", method, error->message);
		g_error_free(error);
		error = NULL;
		return -1;
	}
	
	gchar *address;
	GHashTable *table;
	table = g_hash_table_new(NULL, NULL);
	g_print("Function start_discovery \n");
	return 0;
}

int stop_discovery(DBusGProxy *proxy)
{
	GError *error = NULL;
	char *method = "StopDiscovery";
	if(!dbus_g_proxy_call(proxy, method, &error,
						  G_TYPE_INVALID,
						  G_TYPE_INVALID)) {
		g_printerr("call %s failed: %s\n", method, error->message);
		g_error_free(error);
		error = NULL;
		return -1;
	}
	g_print("Function stop_discovery \n");
	return 0;
}

DBusGObjectPath* create_device(DBusGProxy *proxy)
{
	GError *error = NULL;
	char *method = "CreateDevice";
	DBusGObjectPath *ret;	
	g_print("create_device : %s \n", device_address);
	if(!dbus_g_proxy_call(proxy, method, &error,
						  G_TYPE_STRING, device_address,
						  G_TYPE_INVALID,
						  DBUS_TYPE_G_OBJECT_PATH, &ret,
						  G_TYPE_INVALID)) {
		g_printerr("call %s failed: %s\n", method, error->message);
		g_error_free(error);
		error = NULL;
		return NULL;
	}
	g_print("%s \n", ret);
	return ret;
}

int remove_device(DBusGProxy *proxy, DBusGObjectPath* objectpath)
{
	GError *error = NULL;
	char *method = "RemoveDevice";
	
	if(!dbus_g_proxy_call(proxy, method, &error,
					      DBUS_TYPE_G_OBJECT_PATH, objectpath,
						  G_TYPE_INVALID,
						  G_TYPE_INVALID)) {
		g_printerr("call %s failed: %s\n", method, error->message);
		g_error_free(error);
		error = NULL;
		return -1;
	}
	g_print("remove_device success \n");
	return 0;
}

int create_paired_device(DBusGProxy *proxy)
{
	GError *error = NULL;
	char *method = "CreatePairedDevice";
	DBusGObjectPath *ret;
	device_address = "9C:B7:0D:90:EC:52";
	gchar *des = "dev_9C_B7_0D_90_EC_52";
	g_print("create_paired_device \n");
	while(!dbus_g_proxy_call(proxy, method, &error,
						  G_TYPE_STRING, device_address,
						  DBUS_TYPE_G_OBJECT_PATH, "/test/agent",
						  G_TYPE_STRING, "KeyboardDisplay",
						  G_TYPE_INVALID,
						  DBUS_TYPE_G_OBJECT_PATH, &ret,
						  G_TYPE_INVALID)) {
		g_printerr("call %s failed: %s\n", method, error->message);
		g_error_free(error);
		error = NULL;
		char *p = strchr(ret, 'd');
		if(p) break;
//		return -1;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	DBusGConnection *connection;
	GError *error = NULL;
	DBusGProxy *proxy;
	
	//initial
	device_address = (gchar*)malloc(18*sizeof(gchar));
	
	/* conect system connection and get proxy */
	connection = dbus_g_bus_get(DBUS_BUS_SYSTEM, &error);
	if(connection == NULL) {
		g_printerr("get system bus failed: %s\n", error->message);
		g_error_free(error);
		return -1;
	}

	/* get proxy */
	proxy = dbus_g_proxy_new_for_name(connection, "org.bluez", "/", "org.bluez.Manager");
	
//	send_recv_objectpath_array(proxy);
	DBusGObjectPath *adapt_path = getDefaultAdapter(proxy);

	
	adapt = dbus_g_proxy_new_for_name(connection, "org.bluez", adapt_path, "org.bluez.Adapter");
	
	if(-1 == adapt_powered(adapt, TRUE)) {
		//do something if adapt's power can't up
		//rfkill unblock all
		return 0;
	}

	start_discovery(adapt);
//	stop_discovery(adapt);
//	adapt_powered(adapt, FALSE);
	
	
	mainloop = g_main_loop_new (NULL, FALSE);
	g_main_loop_run (mainloop);

	//if quit mainloop, that means we get a device
//	DBusGObjectPath *device_path = create_device(adapt);
/*	if(device_path != NULL) {
		remove_device(adapt, device_path);
	}*/
	create_paired_device(adapt);
	g_print("connection success\n");
	return 0;
}
