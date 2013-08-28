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

#ifndef _GEOCLUE_SATELLITE_INFO_H
#define _GEOCLUE_SATELLITE_INFO_H

#include <geoclue/geoclue-provider.h>
#include <geoclue/geoclue-types.h>

G_BEGIN_DECLS

#define GEOCLUE_SATELLITE_INFO (dbus_g_type_get_struct ("GValueArray", G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_INVALID))
#define GEOCLUE_SATELLITE_INFO_ARRAY (dbus_g_type_get_collection ("GPtrArray", GEOCLUE_SATELLITE_INFO))

G_END_DECLS

#endif

