/*
 * Geoclue
 * geoclue-satellite.h -
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

#ifndef _GEOCLUE_SATELLITE_H
#define _GEOCLUE_SATELLITE_H

#include <geoclue/geoclue-provider.h>
#include <geoclue/geoclue-types.h>
#include <geoclue/geoclue-satellite-info.h>

G_BEGIN_DECLS

#define GEOCLUE_TYPE_SATELLITE (geoclue_satellite_get_type ())
#define GEOCLUE_SATELLITE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GEOCLUE_TYPE_SATELLITE, GeoclueSatellite))
#define GEOCLUE_IS_SATELLITE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GEOCLUE_TYPE_SATELLITE))

#define GEOCLUE_SATELLITE_INTERFACE_NAME "org.freedesktop.Geoclue.Satellite"

typedef struct _GeoclueSatellite {
	GeoclueProvider provider;
} GeoclueSatellite;

typedef struct _GeoclueSatelliteClass {
	GeoclueProviderClass provider_class;

	void (* satellite_changed) (GeoclueSatellite *satellite,
				    int               timestamp,
				    int               satellite_used,
				    int               satellite_visible,
				    GArray           *used_prn,
				    GPtrArray        *sat_info);
} GeoclueSatelliteClass;

GType geoclue_satellite_get_type (void);

GeoclueSatellite *geoclue_satellite_new (const char *service,
					 const char *path);

gboolean geoclue_satellite_get_satellite (GeoclueSatellite *satellite,
					  int              *timestamp,
					  int              *satellite_used,
					  int              *satellite_visible,
					  GArray          **used_prn,
					  GPtrArray       **sat_info,
					  GError          **error);

gboolean geoclue_satellite_get_last_satellite (GeoclueSatellite *satellite,
					       int              *timestamp,
					       int              *satellite_used,
					       int              *satellite_visible,
					       GArray          **used_prn,
					       GPtrArray       **sat_info,
					       GError          **error);

typedef void (*GeoclueSatelliteCallback) (GeoclueSatellite *satellite,
					  int               timestamp,
					  int               satellite_used,
					  int               satellite_visible,
					  GArray           *used_prn,
					  GPtrArray        *sat_info,
					  GError           *error,
					  gpointer          userdata);

void geoclue_satellite_get_satellite_async (GeoclueSatellite        *satellite,
					    GeoclueSatelliteCallback callback,
					    gpointer                 userdata);

G_END_DECLS

#endif
