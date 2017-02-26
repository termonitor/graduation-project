#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dbus/dbus-glib.h>
#include <dbus/dbus.h>
#include <unistd.h>


int main(int argc, char** argv)
{
	DBusMessage* msg;  
    DBusMessageIter args;  
    DBusConnection* conn;  
    DBusError err;  
    DBusPendingCall* pending;  
    int ret;   
	dbus_bool_t stat;
    dbus_uint32_t level;
	char ret1[1024] = "";

	printf("Calling remote method \n");
	// initialiset the errors  
   	dbus_error_init(&err);

	// connect to the system bus and check for errors  
   	conn = dbus_bus_get(DBUS_BUS_SYSTEM, &err);  
  	if (dbus_error_is_set(&err)) {   
    	fprintf(stderr, "Connection Error (%s)\n", err.message);   
      	dbus_error_free(&err);  
   	}  
   	if (NULL == conn) {   
     	exit(1);   
   	}
/*
	ret = dbus_bus_request_name(conn, "org.bluez", DBUS_NAME_FLAG_REPLACE_EXISTING , &err);
	if (dbus_error_is_set(&err)) {   
     	fprintf(stderr, "Name Error (%s)\n", err.message);   
     	dbus_error_free(&err);  
   	}  
   	if (DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER != ret) {   
      	exit(1);  
   	}
*/
	msg = dbus_message_new_method_call("org.bluez", "/", "org.bluez.Manager", "ListAdapters");
	if(NULL == msg) {
		fprintf(stderr, "Message Null\n");
		exit(1);
	}
/*
	dbus_message_iter_init_append(msg, &args);	
	if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &stat)) {  
      	fprintf(stderr, "Out Of Memory! 111\n");   
      	exit(1);  
   	}
*/
	if (!dbus_connection_send_with_reply (conn, msg, &pending, -1)) { // -1 is default timeout  
      	fprintf(stderr, "Out Of Memory! 222\n");   
      	exit(1);  
   	}  
   	if (NULL == pending) {   
      	fprintf(stderr, "Pending Call Null\n");   
      	exit(1);   
   	}  
       
   	// block until we recieve a reply  
   	dbus_pending_call_block(pending);  
   
   	// get the reply message  
   	msg = dbus_pending_call_steal_reply(pending);  
   	if (NULL == msg) {  
     	fprintf(stderr, "Reply Null\n");   
     	exit(1);   
   	}
	// free the pending message handle  
   	dbus_pending_call_unref(pending);

	char* objectPaths = (char*)malloc(100*sizeof(char));
	int a;

	// read the parameters  
	if(!dbus_message_iter_init(msg, &args))
		fprintf(stderr, "Message has no arguments!\n");
	else if(DBUS_TYPE_ARRAY == dbus_message_iter_get_arg_type(&args)) {
//		printf("%d \n", dbus_message_iter_get_arg_type(&args));
		DBusMessageIter subargs;
		dbus_message_iter_recurse(&args, &subargs);
		strcat(ret1, " [ ");
		while (dbus_message_iter_get_arg_type(&subargs)
                    != DBUS_TYPE_INVALID) {
			printf("%d \n", dbus_message_iter_get_arg_type(&subargs));		
			printf("%d \n", DBUS_TYPE_OBJECT_PATH);
			dbus_message_iter_get_basic(&subargs, &objectPaths);
			printf("%s \n", objectPaths);
			dbus_message_iter_next(&subargs);
		}
		strcat(ret1, " ] ");
	}
/*
   	if (!dbus_message_iter_init(msg, &args))  
      	fprintf(stderr, "Message has no arguments!\n");   
   	else if (DBUS_TYPE_BOOLEAN != dbus_message_iter_get_arg_type(&args))   
      	fprintf(stderr, "Argument is not boolean!\n");   
   	else 
      	dbus_message_iter_get_basic(&args, &stat);  
   
   	if (!dbus_message_iter_next(&args))  
      	fprintf(stderr, "Message has too few arguments!\n");   
   	else if (DBUS_TYPE_UINT32 != dbus_message_iter_get_arg_type(&args))   
      	fprintf(stderr, "Argument is not int!\n");   
   	else 
      	dbus_message_iter_get_basic(&args, &level);  
   
   	printf("Got Reply: %d, %d\n", stat, level);	
*/	
	// free reply   
   	dbus_message_unref(msg);
	
	msg = dbus_message_new_method_call("org.bluez", objectPaths, "org.bluez.Adapter", "setProperties");
	if(NULL == msg) {
		fprintf(stderr, "Message Null\n");
		exit(1);
	}
	
	char* arg1 = "Powered";
	dbus_bool_t arg2 = TRUE;
	dbus_message_iter_init_append(msg, &args);	
	if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &stat)) {  
      	fprintf(stderr, "Out Of Memory! string\n");   
      	exit(1);  
   	}
	if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_VARIANT, &stat)) {  
      	fprintf(stderr, "Out Of Memory! boolean\n");   
      	exit(1);  
   	}
	
	if (!dbus_connection_send_with_reply (conn, msg, &pending, -1)) { // -1 is default timeout  
      	fprintf(stderr, "Out Of Memory! 222\n");   
      	exit(1);  
   	}  
   	if (NULL == pending) {   
      	fprintf(stderr, "Pending Call Null\n");   
      	exit(1);   
   	}  

	// free the pending message handle  
   	dbus_pending_call_unref(pending);
	
	dbus_connection_flush(conn);  
       
   	printf("Request Sent\n");  
       
   	// free message  
   	dbus_message_unref(msg);  
	return 0;
}
