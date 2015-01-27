/*
 * bgp-common
 *
 * Chiara Orsini, CAIDA, UC San Diego
 * chiara@caida.org
 *
 * Copyright (C) 2014 The Regents of the University of California.
 *
 * This file is part of bgp-common.
 *
 * bgp-common is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * bgp-common is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with bgp-common.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "bl_pfx_set.h"
#include "bl_pfx_set_int.h"
#include <stdio.h>
#include "utils.h"
#include <assert.h>
#include <khash.h>


bl_pfx_storage_set_t *bl_pfx_storage_set_create() 
{
  bl_pfx_storage_set_t *ip_prefix_set =  (bl_pfx_storage_set_t *) malloc(sizeof(bl_pfx_storage_set_t));
  ip_prefix_set->hash = kh_init(bl_pfx_storage_set);
  return ip_prefix_set;
}

int bl_pfx_storage_set_insert(bl_pfx_storage_set_t *ip_prefix_set, bl_pfx_storage_t prefix) 
{
  int khret;
  khiter_t k;
  if((k = kh_get(bl_pfx_storage_set, ip_prefix_set->hash,
			       prefix)) == kh_end(ip_prefix_set->hash))
    {
      k = kh_put(bl_pfx_storage_set, ip_prefix_set->hash, 
		       prefix, &khret);
      return 1;
    }
  return 0;
}

void bl_pfx_storage_set_reset(bl_pfx_storage_set_t *ip_prefix_set)
{
  kh_clear(bl_pfx_storage_set, ip_prefix_set->hash);
}

int bl_pfx_storage_set_size(bl_pfx_storage_set_t *ip_prefix_set)
{
  return kh_size(ip_prefix_set->hash);
}

void bl_pfx_storage_set_merge(bl_pfx_storage_set_t *union_set, bl_pfx_storage_set_t *part_set)
{
  bl_pfx_storage_t *id;
  khiter_t k;
  for(k = kh_begin(part_set->hash);
      k != kh_end(part_set->hash); ++k)
    {
      if (kh_exist(part_set->hash, k))
	{
	  id = &(kh_key(part_set->hash, k));
	  bl_pfx_storage_set_insert(union_set, *id);
	}
    }
}

void bl_pfx_storage_set_destroy(bl_pfx_storage_set_t *ip_prefix_set)
{
  kh_destroy(bl_pfx_storage_set, ip_prefix_set->hash);
  free(ip_prefix_set);
}


/* ipv4 specific set */

bl_ipv4_pfx_set_t *bl_ipv4_pfx_set_create() 
{
  bl_ipv4_pfx_set_t *ip_prefix_set =  (bl_ipv4_pfx_set_t *) malloc(sizeof(bl_ipv4_pfx_set_t));
  ip_prefix_set->hash = kh_init(bl_ipv4_pfx_set);
  return ip_prefix_set;
}

int bl_ipv4_pfx_set_insert(bl_ipv4_pfx_set_t *ip_prefix_set, bl_ipv4_pfx_t prefix) 
{
  int khret;
  khiter_t k;
  if((k = kh_get(bl_ipv4_pfx_set, ip_prefix_set->hash,
			       prefix)) == kh_end(ip_prefix_set->hash))
    {
      k = kh_put(bl_ipv4_pfx_set, ip_prefix_set->hash, 
		       prefix, &khret);
      return 1;
    }
  return 0;
}

void bl_ipv4_pfx_set_reset(bl_ipv4_pfx_set_t *ip_prefix_set)
{
  kh_clear(bl_ipv4_pfx_set, ip_prefix_set->hash);
}

int bl_ipv4_pfx_set_size(bl_ipv4_pfx_set_t *ip_prefix_set)
{
  return kh_size(ip_prefix_set->hash);
}

void bl_ipv4_pfx_set_merge(bl_ipv4_pfx_set_t *union_set, bl_ipv4_pfx_set_t *part_set)
{
  bl_ipv4_pfx_t *id;
  khiter_t k;
  for(k = kh_begin(part_set->hash);
      k != kh_end(part_set->hash); ++k)
    {
      if (kh_exist(part_set->hash, k))
	{
	  id = &(kh_key(part_set->hash, k));
	  bl_ipv4_pfx_set_insert(union_set, *id);
	}
    }
}


void bl_ipv4_pfx_set_destroy(bl_ipv4_pfx_set_t *ip_prefix_set)
{
  kh_destroy(bl_ipv4_pfx_set, ip_prefix_set->hash);
  free(ip_prefix_set);
}


/* ipv6 specific set */


bl_ipv6_pfx_set_t *bl_ipv6_pfx_set_create() 
{
  bl_ipv6_pfx_set_t *ip_prefix_set =  (bl_ipv6_pfx_set_t *) malloc(sizeof(bl_ipv6_pfx_set_t));
  ip_prefix_set->hash = kh_init(bl_ipv6_pfx_set);
  return ip_prefix_set;
}

int bl_ipv6_pfx_set_insert(bl_ipv6_pfx_set_t *ip_prefix_set, bl_ipv6_pfx_t prefix) 
{
  int khret;
  khiter_t k;
  if((k = kh_get(bl_ipv6_pfx_set, ip_prefix_set->hash,
			       prefix)) == kh_end(ip_prefix_set->hash))
    {
      k = kh_put(bl_ipv6_pfx_set, ip_prefix_set->hash, 
		       prefix, &khret);
      return 1;
    }
  return 0;
}

void bl_ipv6_pfx_set_reset(bl_ipv6_pfx_set_t *ip_prefix_set)
{
  kh_clear(bl_ipv6_pfx_set, ip_prefix_set->hash);
}

int bl_ipv6_pfx_set_size(bl_ipv6_pfx_set_t *ip_prefix_set)
{
  return kh_size(ip_prefix_set->hash);
}

void bl_ipv6_pfx_set_merge(bl_ipv6_pfx_set_t *union_set, bl_ipv6_pfx_set_t *part_set)
{
  bl_ipv6_pfx_t *id;
  khiter_t k;
  for(k = kh_begin(part_set->hash);
      k != kh_end(part_set->hash); ++k)
    {
      if (kh_exist(part_set->hash, k))
	{
	  id = &(kh_key(part_set->hash, k));
	  bl_ipv6_pfx_set_insert(union_set, *id);
	}
    }
}

void bl_ipv6_pfx_set_destroy(bl_ipv6_pfx_set_t *ip_prefix_set)
{
  kh_destroy(bl_ipv6_pfx_set, ip_prefix_set->hash);
  free(ip_prefix_set);
}

