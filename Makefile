#
# Copyright 2009 Jonathan Wilson.
#
# This Program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTIBILITY
# or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
# for more details.
#
# This program is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation; either version 2 of the License, or (at your
# option) any later version. You should have received a copy of the GNU
# General Public License along with this program; if not, write to the
# Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA
#
# Filename: Makefile
# 
# Purpose: This is the Makefile to build the notedump executable
# 
# ChangeLog:
# Date (mm/dd/yyyy)        Author          Comment
# 25/02/2009               Jonathan Wilson Initial Creation
# 
#

include $(BOOTSTRAP)

CFLAGS=-O2 -Wall -I$(STD_INCPATH) -L$(STD_LIBPATH)

notedump = $(BUILDTOP)/notedump

api_build: ;

impl: $(notedump) 

$(notedump): notedump.c
	$(CC) $(CFLAGS) $^ -o $@ -lezxdb2 

