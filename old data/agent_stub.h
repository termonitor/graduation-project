/* Generated by dbus-binding-tool; do not edit! */


#ifndef __dbus_glib_marshal_my_agent_MARSHAL_H__
#define __dbus_glib_marshal_my_agent_MARSHAL_H__

#include	<glib-object.h>

G_BEGIN_DECLS

#ifdef G_ENABLE_DEBUG
#define g_marshal_value_peek_boolean(v)  g_value_get_boolean (v)
#define g_marshal_value_peek_char(v)     g_value_get_schar (v)
#define g_marshal_value_peek_uchar(v)    g_value_get_uchar (v)
#define g_marshal_value_peek_int(v)      g_value_get_int (v)
#define g_marshal_value_peek_uint(v)     g_value_get_uint (v)
#define g_marshal_value_peek_long(v)     g_value_get_long (v)
#define g_marshal_value_peek_ulong(v)    g_value_get_ulong (v)
#define g_marshal_value_peek_int64(v)    g_value_get_int64 (v)
#define g_marshal_value_peek_uint64(v)   g_value_get_uint64 (v)
#define g_marshal_value_peek_enum(v)     g_value_get_enum (v)
#define g_marshal_value_peek_flags(v)    g_value_get_flags (v)
#define g_marshal_value_peek_float(v)    g_value_get_float (v)
#define g_marshal_value_peek_double(v)   g_value_get_double (v)
#define g_marshal_value_peek_string(v)   (char*) g_value_get_string (v)
#define g_marshal_value_peek_param(v)    g_value_get_param (v)
#define g_marshal_value_peek_boxed(v)    g_value_get_boxed (v)
#define g_marshal_value_peek_pointer(v)  g_value_get_pointer (v)
#define g_marshal_value_peek_object(v)   g_value_get_object (v)
#define g_marshal_value_peek_variant(v)  g_value_get_variant (v)
#else /* !G_ENABLE_DEBUG */
/* WARNING: This code accesses GValues directly, which is UNSUPPORTED API.
 *          Do not access GValues directly in your code. Instead, use the
 *          g_value_get_*() functions
 */
#define g_marshal_value_peek_boolean(v)  (v)->data[0].v_int
#define g_marshal_value_peek_char(v)     (v)->data[0].v_int
#define g_marshal_value_peek_uchar(v)    (v)->data[0].v_uint
#define g_marshal_value_peek_int(v)      (v)->data[0].v_int
#define g_marshal_value_peek_uint(v)     (v)->data[0].v_uint
#define g_marshal_value_peek_long(v)     (v)->data[0].v_long
#define g_marshal_value_peek_ulong(v)    (v)->data[0].v_ulong
#define g_marshal_value_peek_int64(v)    (v)->data[0].v_int64
#define g_marshal_value_peek_uint64(v)   (v)->data[0].v_uint64
#define g_marshal_value_peek_enum(v)     (v)->data[0].v_long
#define g_marshal_value_peek_flags(v)    (v)->data[0].v_ulong
#define g_marshal_value_peek_float(v)    (v)->data[0].v_float
#define g_marshal_value_peek_double(v)   (v)->data[0].v_double
#define g_marshal_value_peek_string(v)   (v)->data[0].v_pointer
#define g_marshal_value_peek_param(v)    (v)->data[0].v_pointer
#define g_marshal_value_peek_boxed(v)    (v)->data[0].v_pointer
#define g_marshal_value_peek_pointer(v)  (v)->data[0].v_pointer
#define g_marshal_value_peek_object(v)   (v)->data[0].v_pointer
#define g_marshal_value_peek_variant(v)  (v)->data[0].v_pointer
#endif /* !G_ENABLE_DEBUG */


/* BOOLEAN:POINTER */
extern void dbus_glib_marshal_my_agent_BOOLEAN__POINTER (GClosure     *closure,
                                                         GValue       *return_value,
                                                         guint         n_param_values,
                                                         const GValue *param_values,
                                                         gpointer      invocation_hint,
                                                         gpointer      marshal_data);
void
dbus_glib_marshal_my_agent_BOOLEAN__POINTER (GClosure     *closure,
                                             GValue       *return_value G_GNUC_UNUSED,
                                             guint         n_param_values,
                                             const GValue *param_values,
                                             gpointer      invocation_hint G_GNUC_UNUSED,
                                             gpointer      marshal_data)
{
  typedef gboolean (*GMarshalFunc_BOOLEAN__POINTER) (gpointer     data1,
                                                     gpointer     arg_1,
                                                     gpointer     data2);
  register GMarshalFunc_BOOLEAN__POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;
  gboolean v_return;

  g_return_if_fail (return_value != NULL);
  g_return_if_fail (n_param_values == 2);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_BOOLEAN__POINTER) (marshal_data ? marshal_data : cc->callback);

  v_return = callback (data1,
                       g_marshal_value_peek_pointer (param_values + 1),
                       data2);

  g_value_set_boolean (return_value, v_return);
}

/* BOOLEAN:BOXED,UINT,UCHAR,POINTER */
extern void dbus_glib_marshal_my_agent_BOOLEAN__BOXED_UINT_UCHAR_POINTER (GClosure     *closure,
                                                                          GValue       *return_value,
                                                                          guint         n_param_values,
                                                                          const GValue *param_values,
                                                                          gpointer      invocation_hint,
                                                                          gpointer      marshal_data);
void
dbus_glib_marshal_my_agent_BOOLEAN__BOXED_UINT_UCHAR_POINTER (GClosure     *closure,
                                                              GValue       *return_value G_GNUC_UNUSED,
                                                              guint         n_param_values,
                                                              const GValue *param_values,
                                                              gpointer      invocation_hint G_GNUC_UNUSED,
                                                              gpointer      marshal_data)
{
  typedef gboolean (*GMarshalFunc_BOOLEAN__BOXED_UINT_UCHAR_POINTER) (gpointer     data1,
                                                                      gpointer     arg_1,
                                                                      guint        arg_2,
                                                                      guchar       arg_3,
                                                                      gpointer     arg_4,
                                                                      gpointer     data2);
  register GMarshalFunc_BOOLEAN__BOXED_UINT_UCHAR_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;
  gboolean v_return;

  g_return_if_fail (return_value != NULL);
  g_return_if_fail (n_param_values == 5);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_BOOLEAN__BOXED_UINT_UCHAR_POINTER) (marshal_data ? marshal_data : cc->callback);

  v_return = callback (data1,
                       g_marshal_value_peek_boxed (param_values + 1),
                       g_marshal_value_peek_uint (param_values + 2),
                       g_marshal_value_peek_uchar (param_values + 3),
                       g_marshal_value_peek_pointer (param_values + 4),
                       data2);

  g_value_set_boolean (return_value, v_return);
}

/* BOOLEAN:BOXED,STRING,POINTER */
extern void dbus_glib_marshal_my_agent_BOOLEAN__BOXED_STRING_POINTER (GClosure     *closure,
                                                                      GValue       *return_value,
                                                                      guint         n_param_values,
                                                                      const GValue *param_values,
                                                                      gpointer      invocation_hint,
                                                                      gpointer      marshal_data);
void
dbus_glib_marshal_my_agent_BOOLEAN__BOXED_STRING_POINTER (GClosure     *closure,
                                                          GValue       *return_value G_GNUC_UNUSED,
                                                          guint         n_param_values,
                                                          const GValue *param_values,
                                                          gpointer      invocation_hint G_GNUC_UNUSED,
                                                          gpointer      marshal_data)
{
  typedef gboolean (*GMarshalFunc_BOOLEAN__BOXED_STRING_POINTER) (gpointer     data1,
                                                                  gpointer     arg_1,
                                                                  gpointer     arg_2,
                                                                  gpointer     arg_3,
                                                                  gpointer     data2);
  register GMarshalFunc_BOOLEAN__BOXED_STRING_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;
  gboolean v_return;

  g_return_if_fail (return_value != NULL);
  g_return_if_fail (n_param_values == 4);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_BOOLEAN__BOXED_STRING_POINTER) (marshal_data ? marshal_data : cc->callback);

  v_return = callback (data1,
                       g_marshal_value_peek_boxed (param_values + 1),
                       g_marshal_value_peek_string (param_values + 2),
                       g_marshal_value_peek_pointer (param_values + 3),
                       data2);

  g_value_set_boolean (return_value, v_return);
}

/* BOOLEAN:STRING,POINTER */
extern void dbus_glib_marshal_my_agent_BOOLEAN__STRING_POINTER (GClosure     *closure,
                                                                GValue       *return_value,
                                                                guint         n_param_values,
                                                                const GValue *param_values,
                                                                gpointer      invocation_hint,
                                                                gpointer      marshal_data);
void
dbus_glib_marshal_my_agent_BOOLEAN__STRING_POINTER (GClosure     *closure,
                                                    GValue       *return_value G_GNUC_UNUSED,
                                                    guint         n_param_values,
                                                    const GValue *param_values,
                                                    gpointer      invocation_hint G_GNUC_UNUSED,
                                                    gpointer      marshal_data)
{
  typedef gboolean (*GMarshalFunc_BOOLEAN__STRING_POINTER) (gpointer     data1,
                                                            gpointer     arg_1,
                                                            gpointer     arg_2,
                                                            gpointer     data2);
  register GMarshalFunc_BOOLEAN__STRING_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;
  gboolean v_return;

  g_return_if_fail (return_value != NULL);
  g_return_if_fail (n_param_values == 3);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_BOOLEAN__STRING_POINTER) (marshal_data ? marshal_data : cc->callback);

  v_return = callback (data1,
                       g_marshal_value_peek_string (param_values + 1),
                       g_marshal_value_peek_pointer (param_values + 2),
                       data2);

  g_value_set_boolean (return_value, v_return);
}

/* BOOLEAN:BOXED,UINT,POINTER */
extern void dbus_glib_marshal_my_agent_BOOLEAN__BOXED_UINT_POINTER (GClosure     *closure,
                                                                    GValue       *return_value,
                                                                    guint         n_param_values,
                                                                    const GValue *param_values,
                                                                    gpointer      invocation_hint,
                                                                    gpointer      marshal_data);
void
dbus_glib_marshal_my_agent_BOOLEAN__BOXED_UINT_POINTER (GClosure     *closure,
                                                        GValue       *return_value G_GNUC_UNUSED,
                                                        guint         n_param_values,
                                                        const GValue *param_values,
                                                        gpointer      invocation_hint G_GNUC_UNUSED,
                                                        gpointer      marshal_data)
{
  typedef gboolean (*GMarshalFunc_BOOLEAN__BOXED_UINT_POINTER) (gpointer     data1,
                                                                gpointer     arg_1,
                                                                guint        arg_2,
                                                                gpointer     arg_3,
                                                                gpointer     data2);
  register GMarshalFunc_BOOLEAN__BOXED_UINT_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;
  gboolean v_return;

  g_return_if_fail (return_value != NULL);
  g_return_if_fail (n_param_values == 4);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_BOOLEAN__BOXED_UINT_POINTER) (marshal_data ? marshal_data : cc->callback);

  v_return = callback (data1,
                       g_marshal_value_peek_boxed (param_values + 1),
                       g_marshal_value_peek_uint (param_values + 2),
                       g_marshal_value_peek_pointer (param_values + 3),
                       data2);

  g_value_set_boolean (return_value, v_return);
}

/* BOOLEAN:BOXED,POINTER,POINTER */
extern void dbus_glib_marshal_my_agent_BOOLEAN__BOXED_POINTER_POINTER (GClosure     *closure,
                                                                       GValue       *return_value,
                                                                       guint         n_param_values,
                                                                       const GValue *param_values,
                                                                       gpointer      invocation_hint,
                                                                       gpointer      marshal_data);
void
dbus_glib_marshal_my_agent_BOOLEAN__BOXED_POINTER_POINTER (GClosure     *closure,
                                                           GValue       *return_value G_GNUC_UNUSED,
                                                           guint         n_param_values,
                                                           const GValue *param_values,
                                                           gpointer      invocation_hint G_GNUC_UNUSED,
                                                           gpointer      marshal_data)
{
  typedef gboolean (*GMarshalFunc_BOOLEAN__BOXED_POINTER_POINTER) (gpointer     data1,
                                                                   gpointer     arg_1,
                                                                   gpointer     arg_2,
                                                                   gpointer     arg_3,
                                                                   gpointer     data2);
  register GMarshalFunc_BOOLEAN__BOXED_POINTER_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;
  gboolean v_return;

  g_return_if_fail (return_value != NULL);
  g_return_if_fail (n_param_values == 4);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_BOOLEAN__BOXED_POINTER_POINTER) (marshal_data ? marshal_data : cc->callback);

  v_return = callback (data1,
                       g_marshal_value_peek_boxed (param_values + 1),
                       g_marshal_value_peek_pointer (param_values + 2),
                       g_marshal_value_peek_pointer (param_values + 3),
                       data2);

  g_value_set_boolean (return_value, v_return);
}

G_END_DECLS

#endif /* __dbus_glib_marshal_my_agent_MARSHAL_H__ */

#include <dbus/dbus-glib.h>
static const DBusGMethodInfo dbus_glib_my_agent_methods[] = {
  { (GCallback) my_agent_release, dbus_glib_marshal_my_agent_BOOLEAN__POINTER, 0 },
  { (GCallback) my_agent_request_pin_code, dbus_glib_marshal_my_agent_BOOLEAN__BOXED_POINTER_POINTER, 27 },
  { (GCallback) my_agent_request_passkey, dbus_glib_marshal_my_agent_BOOLEAN__BOXED_POINTER_POINTER, 84 },
  { (GCallback) my_agent_display_passkey, dbus_glib_marshal_my_agent_BOOLEAN__BOXED_UINT_UCHAR_POINTER, 143 },
  { (GCallback) my_agent_request_confirmation, dbus_glib_marshal_my_agent_BOOLEAN__BOXED_UINT_POINTER, 212 },
  { (GCallback) my_agent_authorize, dbus_glib_marshal_my_agent_BOOLEAN__BOXED_STRING_POINTER, 274 },
  { (GCallback) my_agent_confirm_mode_change, dbus_glib_marshal_my_agent_BOOLEAN__STRING_POINTER, 323 },
  { (GCallback) my_agent_cancel, dbus_glib_marshal_my_agent_BOOLEAN__POINTER, 369 },
};

const DBusGObjectInfo dbus_glib_my_agent_object_info = {  1,
  dbus_glib_my_agent_methods,
  8,
"org.bluez.Agent\0Release\0S\0\0org.bluez.Agent\0RequestPinCode\0S\0device\0I\0o\0pin\0O\0F\0N\0s\0\0org.bluez.Agent\0RequestPasskey\0S\0device\0I\0o\0value\0O\0F\0N\0u\0\0org.bluez.Agent\0DisplayPasskey\0S\0device\0I\0o\0passkey\0I\0u\0entered\0I\0y\0\0org.bluez.Agent\0RequestConfirmation\0S\0device\0I\0o\0passkey\0I\0u\0\0org.bluez.Agent\0Authorize\0S\0device\0I\0o\0uuid\0I\0s\0\0org.bluez.Agent\0ConfirmModeChange\0S\0mode\0I\0s\0\0org.bluez.Agent\0Cancel\0S\0\0\0",
"\0",
"\0"
};
