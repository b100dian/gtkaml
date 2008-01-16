/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * gtkaml
 * Copyright (C) Vlad Grecescu 2007 <b100dian@gmail.com>
 * 
 * gtkaml is free software.
 * 
 * You may redistribute it and/or modify it under the terms of the
 * GNU General Public License, as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option)
 * any later version.
 * 
 * main.c is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with main.c.  If not, write to:
 * 	The Free Software Foundation, Inc.,
 * 	51 Franklin Street, Fifth Floor
 * 	Boston, MA  02110-1301, USA.
 */

#include "config.h"

#include <stdio.h>
#include <string.h>

#include <glib.h>

#include "gtkaml-saxparser.h"



int main( int argc, char *argv[] )
{
	gboolean version = 0;
	gchar * output_file = 0;
	gchar * output_file_basename = 0;
	gchar * input_file = 0;
	GMappedFile * mapped_input;

	/* command-line arguments parsing */
	GOptionEntry entries[] = 
	{
		{ "output-file", 'o', 0, G_OPTION_ARG_FILENAME, &output_file, "specify the name of the output .vala file", "OUTPUT_FILE" },
		{ "version"    , 'v', 0, G_OPTION_ARG_NONE    , &version, "prints version and exits", 0 },
		{ NULL }
	};	
	GOptionContext *context = 0;
	GError * error = 0;

	context = g_option_context_new (" INPUT_FILE");
	g_option_context_add_main_entries (context, entries, 0);
	g_option_context_set_summary(context, "Gtkaml is an xml preprocessor that outputs Gtk+ Vala source code");
  	g_option_context_parse (context, &argc, &argv, &error);
  	g_option_context_free(context);
  	if (error) {
  		fprintf(stderr, "Error parsing command line: %s\n", error->message);
  		g_error_free(error);
  		return 1;
	}
	
	/* command-line arguments logic */
	if (version) {
		fprintf(stdout,"Gtkaml " VERSION "\n");
		return 0;
	}
	if (argc < 2 || argv[argc-1][0]=='-' )
	{
		fprintf(stderr, "No input file specified\n");
		return 1;
	}
	if (!g_file_test(argv[argc-1], G_FILE_TEST_IS_REGULAR))
	{
		fprintf(stderr, "File not found: %s\n", argv[argc-1]);
		return 1;
	}
	input_file = g_strdup(argv[argc-1]);
	if (!output_file)
	{
		if (g_strrstr(input_file, ".")) {
			output_file_basename = g_strndup(input_file, g_strrstr(input_file, ".") - input_file);
			output_file = g_strconcat( output_file_basename, ".vala", NULL );
			g_free( output_file_basename );
		} else {
			output_file = g_strconcat( input_file, ".vala", NULL );
		}
	}
	
	mapped_input = g_mapped_file_new( input_file, 0, &error );
	if (error) {
		fprintf(stderr, "Error opening input file: %s\n", error->message);
		g_error_free(error);
		return 1;
	}

	GString * result = gtkaml_parse_sax2_test( g_mapped_file_get_contents(mapped_input), g_mapped_file_get_length(mapped_input) );
	
	g_mapped_file_free( mapped_input );
	
	g_file_set_contents( output_file, result->str, result->len, &error );
	if (error) {
		fprintf(stderr, "Error writing output: %s", error->message);
		return 1;
	}
	
	g_string_free( result, TRUE );
	g_free( input_file );
	g_free( output_file );

	
	return (0);
}
