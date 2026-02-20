#include "ft_ssl.h"
#include "utils/colors.h"
#include <string.h> // strcmp()
#include <stdio.h> // fprintf(), stderr


/*
 * Macros
 */

#define INVALID_COMMAND_FORMAT RED "%s: Error: '%s' is an invalid command.\n" RST

#define HELP_FORMAT \
BOLD CYN "Usage:\n" RST \
"  %s [command] [flags] [files]\n" \
BOLD CYN "\nMessage digest commands:\n" RST \
"  md5\n" \
"  sha256\n" \
"  whirlpool\n" \
BOLD CYN "\nFlags:\n" RST \
"  -p -q -r -s\n" \


/*
 * Functions
 */

static int do_cmd(int argc, char **argv)
{
	int i = 0;

	while (g_cmds[i].name) {
		if (strcmp(g_cmds[i].name, argv[1]) == 0)
			return (g_cmds[i].func(argc, argv));
		i += 1;
	}

	fprintf(stderr, INVALID_COMMAND_FORMAT, argv[0], argv[1]);
	fprintf(stderr, HELP_FORMAT, argv[0]);

	return (1);
}


int main(int argc, char **argv)
{
	int ret;

	if (argc < 2) {
		return (1);
	}

	ret = do_cmd(argc, argv);

	return (!ret);
}
