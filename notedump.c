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
 * Filename: notedump.c
 *
 * Purpose: Program to dump notepad notes for MOTOMAGX phones
 *
 * ChangeLog:
 * Date (mm/dd/yyyy)        Author          Comment
 * 25/02/2009               Jonathan Wilson Initial creation
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include "ezxdb.h"

int ucharcpy(short *dest,short *src,int len)
{
	int count = 0;
	if (src)
	{
		short c = *src;
		while (count < len && c != 0)
		{
			count++;
			src++;
			*dest = c;
			dest++;
			c = *src;
		}
		*dest = 0;
		return count;
	}
	else
	{
		return 0;
	}
}

int cpystr(char *dest,short *src,int len)
{
	int count = 0;
	if (src)
	{
		short c = *src;
		while (count < len && c != 0)
		{
			count++;
			src++;
			*dest = c;
			dest++;
			c = *src;
		}
		*dest = 0;
		return count;
	}
	else
	{
		return 0;
	}
}

int main(int argc, char **argv)
{
	DB_Open();
	if (!DB_HLP_CheckTableExists("note_table"))
	{
		return 1;
	}
	int handle;
	if (DB_Query(&handle,"sml: declare schema count (count integer);\ndeclare buffer schema count;\ntable $table = open_table('%s');\nbuffer_put(count, $table->get_record_number());\nbuffer_move_next();","note_table"))
	{
		DB_CSC_Close(handle);
		return 1;
	}
	int count = DB_CSC_GetFieldAsInteger(handle,0);
	DB_CSC_Close(handle);
	if (DB_Query(&handle,"sml:declare schema note (UID integer);\ndeclare buffer schema note;\ncursor $c=open_cursor('%s');\nwhile($c->move_next())\n{\n    buffer_put(UID, $c->get_field('UID'));\n    buffer_move_next();\n};","note_index_date"))
	{
		DB_CSC_Close(handle);
	}
	int *ids = calloc(4,count);
	if (ids)
	{
		DB_CSC_MoveFirst(handle);
		int pos = 0;
		while (!DB_CSC_Eof(handle))
		{
			ids[pos++] = DB_CSC_GetFieldAsInteger(handle,0);
			DB_CSC_MoveNext(handle);
		}
		DB_CSC_Close(handle);
	}
	else
	{
		DB_CSC_Close(handle);
		return 1;
	}
	FILE *f = fopen("notes.txt","wt");
	unsigned int i;
	for (i = 0;i < count;i++)
	{
		int ph = DB_PARAM_Open(1);
		DB_PARAM_BindInteger(ph,0,ids[i]);
		int qv = DB_QueryWithParam(&handle,ph,"sml:declare schema note (UID integer, flag bool, body unicode, date integer);\ndeclare buffer schema note;\ncursor $c=open_cursor('%s');\ntuple $key = $c->new_empty_key_tuple();\n$key->set_field('UID', :0);\nif ($c->find($key))\n{\n  buffer_put(UID, $c->get_field('UID'));\n  buffer_put(flag, $c->get_field('flag'));\n  buffer_put(body, $c->get_field('body'));\n  buffer_put(date, $c->get_field('date'));\n  buffer_move_next();\n};","note_table");
		DB_PARAM_Close(ph);
		if (qv)
		{
			fclose(f);
			DB_CSC_Close(handle);
			return 1;
		}
		if (DB_CSC_GetRecordNumber(handle) <= 0)
		{
			fclose(f);
			DB_CSC_Close(handle);
			return 1;
		}
		else
		{
			//int flag = DB_CSC_GetFieldAsBool(handle,1);
			short *str1 = malloc(20002);
			if (str1)
			{
				memset(str1,0,10001);
				short *str2 = DB_CSC_GetFieldAsUnicode(handle,2);
				int length = ucharcpy(str1,str2,10000);
				short *str3 = malloc(2 * length + 2);
				if (str3)
				{
					memset(str3,0,length+1);
					ucharcpy(str3,str1,length);
					free(str1);
					//int date = DB_CSC_GetFieldAsInteger(handle,3);
					DB_CSC_Close(handle);
					char *strx = malloc(length+1);
					memset(strx,0,length+1);
					cpystr(strx,str3,length);
					fprintf(f,"%s\n",strx);
					free(str3);
				}
				else
				{
					DB_CSC_Close(handle);
					free(str1);
				}
			}
			else
			{
				DB_CSC_Close(handle);
			}
		}
	}
	fclose(f);
	DB_Close();
	return 0;
}

