/*
 * Copyright (c) 2014, Quentin Schwerkolt
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <sys/types.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#include "config.h"

#include "upkg.h"

const char* program_name = NULL;
uint8_t	verbose_lvl = 0;

static struct upkg_command command[] = {
	{ "autoremove",	"Remove unneeded automatically installed pacages.",	NULL },
	{ "install",    "Install new packages.",                            NULL },
	{ "keep",	    "Mark packages as non-automatically installed.",    NULL },
	{ "list",       "List installed packages.",                         NULL },
	{ "refresh",    "Refresh information about remote repositories.",	NULL },
	{ "remove",	    "Remove installed packages.",                       NULL },
	{ "unkeep",	    "Mark packages as automatically installed.",		NULL },
	{ "upgrade",	"Upgrade installed packages.",                      NULL },
	{ NULL,          NULL,                                              NULL }
};

static void version(void)
{
	printf("upkg version %s\n", VERSION);
}

static void usage(void)
{
	printf("Usage: %s command [options]\n", program_name);
	printf("\nCommands:\n");

	for(int i = 0; command[i].name != NULL; i++)
	{
		printf("    %-10s    - %s\n", command[i].name,
		       command[i].description);
	}
}

int main(int argc, char **argv)
{
	int ch;

	program_name = argc > 0 ? argv[0] : "upkg";

	while((ch = getopt(argc, argv, "hVv")) != -1)
	{
		switch (ch)
		{
		case 'h':
			usage();
			return (0);
		case 'V':
			version();
			return (0);
		case 'v':
			++verbose_lvl;
			break;
		default:
			usage();
			return (2);
		}
	}

	if((argc - optind) < 1)
	{
		usage();

		return 2;
	}

	for(int i = 0; command[i].name != NULL; i++)
	{
		if(strcmp(argv[optind], command[i].name) == 0)
		{
			if(command[i].main == NULL)
			{
				fprintf(stderr, "internal error: unimplemented command '%s'\n", command[i].name);

				return 1;
			}

			return (command[i].main(argc - optind, argv + optind));
		}
	}

	return 0;
}
