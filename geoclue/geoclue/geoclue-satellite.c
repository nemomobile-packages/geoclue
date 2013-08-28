/*
 * Geoclue
 * geoclue-satellite.c - Client API for accessing GcIfaceSatellite
 *
 * Author: Sagnho Park <sangho.g.park@samsung.com>, Youngae Kang <youngae.kang@samsung.com>,
 *         Yunhan Kim <yhan.kim@samsung.com>, Genie Kim <daejins.kim@samsung.com>
 * Copyright (c) 2000 - 2011 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 */

#include <geoclue/geoclue-satellite.h>
#include <geoclue/geoclue-marshal.h>

#include "gc-iface-satellite-bindings.h"

typedef struct _GeoclueSatellitePrivate {
	int dummy;
} GeoclueSatellitePrivate;

enum {
	SATELLITE_CHANGED,
	LAST_SIGNAL
};

static guint32 signals[LAST_SIGNAL] = {0, };

#define GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), GEOCLUE_TYPE_SATELLITE, GeoclueSatellitePrivate))

G_DEFINE_TYPE (GeoclueSatellite, geoclue_satellite, GEOCLUE_TYPE_PROVIDER);

static void
finalize (GObject *object)
{
	G_OBJECT_CLASS (geoclue_satellite_parent_class)->finalize (object);
}

static void
dispose (GObject *object)
{
	G_OBJECT_CLASS (geoclue_satellite_parent_class)->dispose (object);
}

static void
satellite_changed (DBusGProxy       *proxy,
		   int               timestamp,
		   int               satellite_used,
		   int               satellite_visible,
		   GArray           *used_prn,
		   GPtrArray        *sat_info,
		   GeoclueSatellite *satellite)
{
	g_signal_emit (satellite, signals[SATELLITE_CHANGED], 0, timestamp, satellite_used, satellite_visible,
		       used_prn,sat_info);
}

static GObject *
constructor (GType                  type,
	     guint                  n_props,
	     GObjectConstructParam *props)
{
	GObject *object;
	GeoclueProvider *provider;

	object = G_OBJECT_CLASS (geoclue_satellite_parent_class)->constructor (type, n_props, props);
	provider = GEOCLUE_PROVIDER (object);

	dbus_g_proxy_add_signal (provider->proxy, "SatelliteChanged",
				 G_TYPE_INT,
				 G_TYPE_INT,
				 G_TYPE_INT,
				 DBUS_TYPE_G_INT_ARRAY,
				 GEOCLUE_SATELLITE_INFO_ARRAY,
				 G_TYPE_INVALID);
	dbus_g_proxy_connect_signal (provider->proxy, "SatelliteChanged",
				     G_CALLBACK (satellite_changed),
				     object, NULL);

	return object;
}

static void
geoclue_satellite_class_init (GeoclueSatelliteClass *klass)
{
	GObjectClass *o_class = (GObjectClass *) klass;

	o_class->finalize = finalize;
	o_class->dispose = dispose;
	o_class->constructor = constructor;

	g_type_class_add_private (klass, sizeof (GeoclueSatellitePrivate));

	signals[SATELLITE_CHANGED] = g_signal_new ("satellite-changed",
						   G_TYPE_FROM_CLASS (klass),
						   G_SIGNAL_RUN_FIRST |
						   G_SIGNAL_NO_RECURSE,
						   G_STRUCT_OFFSET (GeoclueSatelliteClass, satellite_changed),
						   NULL, NULL,
						   geoclue_marshal_VOID__INT_INT_INT_POINTER_POINTER,
						   G_TYPE_NONE, 5,
						   G_TYPE_INT, G_TYPE_INT, G_TYPE_INT,
						   G_TYPE_POINTER, G_TYPE_POINTER);
}

static void
geoclue_satellite_init (GeoclueSatellite *satellite)
{
}

GeoclueSatellite *
geoclue_satellite_new (const char *service,
		       const char *path)
{
	return g_object_new (GEOCLUE_TYPE_SATELLITE,
			     "service", service,
			     "path", path,
			     "interface", GEOCLUE_SATELLITE_INTERFACE_NAME,
			     NULL);
}

gboolean
geoclue_satellite_get_satellite (GeoclueSatellite *satellite,
				 int              *timestamp,
				 int              *satellite_used,
				 int              *satellite_visible,
				 GArray          **used_prn,
				 GPtrArray       **sat_info,
				 GError          **error)
{
	GeoclueProvider *provider = GEOCLUE_PROVIDER (satellite);
	if (!org_freedesktop_Geoclue_Satellite_get_satellite (provider->proxy,
							      timestamp, satellite_used, satellite_visible,
							      used_prn, sat_info, error)) {
		return FALSE;
	}

	return TRUE;
}

gboolean
geoclue_satellite_get_last_satellite (GeoclueSatellite *satellite,
				      int              *timestamp,
				      int              *satellite_used,
				      int              *satellite_visible,
				      GArray          **used_prn,
				      GPtrArray       **sat_info,
				      GError          **error)
{
	GeoclueProvider *provider = GEOCLUE_PROVIDER (satellite);
	if (!org_freedesktop_Geoclue_Satellite_get_last_satellite (provider->proxy,
								   timestamp, satellite_used, satellite_visible,
								   used_prn, sat_info, error)) {
		return FALSE;
	}

	return TRUE;
}


typedef struct _GeoclueSatelliteAsyncData {
	GeoclueSatellite *satellite;
	GCallback         callback;
	gpointer          userdata;
} GeoclueSatelliteAsyncData;

static void
get_satellite_async_callback (DBusGProxy                *proxy,
			      int                        timestamp,
			      int                        satellite_used,
			      int                        satellite_visible,
			      GArray                    *used_prn,
			      GPtrArray                 *sat_info,
			      GError                    *error,
			      GeoclueSatelliteAsyncData *data)
{
	(*(GeoclueSatelliteCallback)data->callback) (data->satellite,
						     timestamp,
						     satellite_used,
						     satellite_visible,
						     used_prn,
						     sat_info,
						     error,
						     data->userdata);

	g_free (data);
}

void
geoclue_satellite_get_satellite_async (GeoclueSatellite        *satellite,
				       GeoclueSatelliteCallback callback,
				       gpointer                 userdata)
{
	GeoclueProvider *provider = GEOCLUE_PROVIDER (satellite);
	GeoclueSatelliteAsyncData *data;

	data = g_new (GeoclueSatelliteAsyncData, 1);
	data->satellite = satellite;
	data->callback = G_CALLBACK (callback);
	data->userdata = userdata;

	org_freedesktop_Geoclue_Satellite_get_satellite_async (provider->proxy,
			(org_freedesktop_Geoclue_Satellite_get_satellite_reply)get_satellite_async_callback,
			data);
}
