/*
 * Copyright 2009 Jonathan Wilson
 *
 * This Program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTIBILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version. You should have received a copy of the GNU
 * General Public License along with this program; if not, write to the
 * Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA
 *
 * Filename: ezxdb.h
 *
 * Purpose: header file for libezxdb2.so
 *
 * ChangeLog:
 * Date (mm/dd/yyyy)        Author          Comment
 * 25/02/2009               Jonathan Wilson Initial creation
 */

int DB_CSC_Eof(int handle);
int DB_CSC_GetFieldAsBool(int handle, int field);
int DB_HLP_CheckTableExists(char *table);
int DB_CSC_GetFieldAsInteger(int handle,int field);
int DB_CSC_GetRecordNumber(int handle);
int DB_PARAM_BindInteger(int paramhandle,int param,int pos);
int DB_PARAM_Open(int param);
int DB_Query(int *handle,char *query,char *table);
int DB_QueryWithParam(int *handle,int paramhandle,char *query,char *table);
void DB_Close();
void DB_CSC_Close(int handle);
void DB_CSC_MoveFirst(int handle);
void DB_CSC_MoveNext(int handle);
void DB_Open();
void DB_PARAM_Close(int paramhandle);
short *DB_CSC_GetFieldAsUnicode(int handle, int field);
