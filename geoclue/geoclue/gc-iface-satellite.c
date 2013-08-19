/*
 * Geoclue
 * gc-iface-satellite.c - GInterface for org.freedesktop.Geoclue.Satellite
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

#include <glib.h>

#include <dbus/dbus-glib.h>
#include <geoclue/gc-iface-satellite.h>
#include <geoclue/geoclue-marshal.h>

enum {
	SATELLITE_CHANGED,
	LAST_SIGNAL
};

static guint signals[LAST_SIGNAL] = {0};

static gboolean
gc_iface_satellite_get_satellite (GcIfaceSatellite *satellite,
				  int              *timestamp,
				  int              *satellite_used,
				  int              *satellite_visible,
				  GArray          **used_prn,
				  GPtrArray       **sat_info,
				  GError          **error);

static gboolean
gc_iface_satellite_get_last_satellite (GcIfaceSatellite *satellite,
				       int		*timestamp,
				       int		*satellite_used,
				       int		*satellite_visible,
				       GArray		**used_prn,
				       GPtrArray	**sat_info,
				       GError		**error);

#include "gc-iface-satellite-glue.h"

static void
gc_iface_satellite_base_init (gpointer klass)
{
	static gboolean initialized = FALSE;

	if (initialized) {
		return;
	}
	initialized = TRUE;

	signals[SATELLITE_CHANGED] = g_signal_new ("satellite-changed",
						   G_OBJECT_CLASS_TYPE (klass),
						   G_SIGNAL_RUN_LAST, 0,
						   NULL, NULL,
						   geoclue_marshal_VOID__INT_INT_INT_POINTER_POINTER,
						   G_TYPE_NONE, 5,
						   G_TYPE_INT,
						   G_TYPE_INT,
						   G_TYPE_INT,
						   DBUS_TYPE_G_INT_ARRAY,
						   GEOCLUE_SATELLITE_INFO_ARRAY);
	dbus_g_object_type_install_info (gc_iface_satellite_get_type (),
					 &dbus_glib_gc_iface_satellite_object_info);
}

GType
gc_iface_satellite_get_type (void)
{
	static GType type = 0;

	if (!type) {
		const GTypeInfo info = {
			sizeof (GcIfaceSatelliteClass),
			gc_iface_satellite_base_init,
			NULL,
		};

		type = g_type_register_static (G_TYPE_INTERFACE,
					       "GcIfaceSatellite", &info, 0);
	}

	return type;
}

static gboolean
gc_iface_satellite_get_satellite (GcIfaceSatellite *gc,
				  int              *timestamp,
				  int              *satellite_used,
				  int              *satellite_visible,
				  GArray          **used_prn,
				  GPtrArray       **sat_info,
				  GError          **error)
{
	return GC_IFACE_SATELLITE_GET_CLASS (gc)->get_satellite (gc,
								 timestamp,
								 satellite_used,
								 satellite_visible,
								 used_prn,
								 sat_info,
								 error);
}

static gboolean
gc_iface_satellite_get_last_satellite (GcIfaceSatellite *gc,
				       int              *timestamp,
				       int              *satellite_used,
				       int              *satellite_visible,
				       GArray          **used_prn,
				       GPtrArray       **sat_info,
				       GError          **error)
{
	return GC_IFACE_SATELLITE_GET_CLASS (gc)->get_last_satellite (gc,
								      timestamp,
								      satellite_used,
								      satellite_visible,
								      used_prn,
								      sat_info,
								      error);
}

void
gc_iface_satellite_emit_satellite_changed (GcIfaceSatellite *gc,
					   int               timestamp,
					   int               satellite_used,
					   int               satellite_visible,
					   GArray           *used_prn,
					   GPtrArray        *sat_info)
{
	g_signal_emit (gc, signals[SATELLITE_CHANGED], 0,
		       timestamp, satellite_used, satellite_visible,
		       used_prn, sat_info);
}
