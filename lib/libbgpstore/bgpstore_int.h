/*
 * bgpwatcher
 *
 * Chiara Orsini, CAIDA, UC San Diego
 * corsaro-info@caida.org
 *
 * Copyright (C) 2014 The Regents of the University of California.
 *
 * This file is part of bgpwatcher.
 *
 * bgpwatcher is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * bgpwatcher is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with bgpwatcher.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __BGPSTORE_INT_H
#define __BGPSTORE_INT_H

#include "bgpstore_lib.h"
#include "bgpstore_bgpview.h"
#include "khash.h"


KHASH_INIT(timebgpview, char*, bgpview_t*, 1,
	   kh_int_hash_func, kh_int_hash_equal);

struct bgpstore {
  int registered_clients;
  khash_t(timebgpview) *bgp_timeseries;

};

#endif /* __BGPSTORE_INT_H */
