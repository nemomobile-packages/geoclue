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

#ifndef _GC_IFACE_SATELLITE_H
#define _GC_IFACE_SATELLITE_H

#include <geoclue/geoclue-types.h>
#include <geoclue/geoclue-satellite-info.h>

G_BEGIN_DECLS

#define GC_TYPE_IFACE_SATELLITE (gc_iface_satellite_get_type ())
#define GC_IFACE_SATELLITE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GC_TYPE_IFACE_SATELLITE, GcIfaceSatellite))
#define GC_IFACE_SATELLITE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GC_TYPE_IFACE_SATELLITE, GcIfaceSatelliteClass))
#define GC_IS_IFACE_SATELLITE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GC_TYPE_IFACE_SATELLITE))
#define GC_IS_IFACE_SATELLITE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GC_TYPE_IFACE_SATELLITE))
#define GC_IFACE_SATELLITE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), GC_TYPE_IFACE_SATELLITE, GcIfaceSatelliteClass))

typedef struct _GcIfaceSatellite GcIfaceSatellite; /* Dummy typedef */
typedef struct _GcIfaceSatelliteClass GcIfaceSatelliteClass;

struct _GcIfaceSatelliteClass {
        GTypeInterface base_iface;

	/* signals */
	void (* satellite_changed) (GcIfaceSatellite *gc,
				    int               timestamp,
				    int               satellite_used,
				    int               satellite_visible,
				    GArray           *used_prn,
				    GPtrArray        *sat_info);

	/* vtable */
	gboolean (* get_satellite) (GcIfaceSatellite *gc,
				    int              *timestamp,
				    int              *satellite_used,
				    int              *satellite_visible,
				    GArray          **used_prn,
				    GPtrArray       **sat_info,
				    GError          **error);

	/* vtable */
	gboolean (* get_last_satellite) (GcIfaceSatellite *gc,
					 int              *timestamp,
					 int              *satellite_used,
					 int              *satellite_visible,
					 GArray          **used_prn,
					 GPtrArray       **sat_info,
					 GError          **error);
};

GType gc_iface_satellite_get_type (void);

void gc_iface_satellite_emit_satellite_changed (GcIfaceSatellite *gc,
						int               timestamp,
						int               satellite_used,
						int               satellite_visible,
						GArray           *used_prn,
						GPtrArray        *sat_info);

G_END_DECLS

#endif
