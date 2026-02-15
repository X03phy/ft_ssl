#include "ft_ssl.h"
#include "colors.h"
#include <string.h> // strcmp()
#include <stdio.h> // fprintf(), stderr


/*
 * Macros
*/

#define INVALID_COMMAND_FORMAT RED "%s: Error: '%s' is an invalid command.\n" RST
#define USAGE_FORMAT GRN "\nUsage: %s command [flags] [file/string]\n" RST
#define GLOBAL_HELP_STRING YEL "\n" \
                               "Message Digest commands:\n" \
                               "md5\n" \
                               "sha256\n" \
                               "whirlpool\n" \
                               "\n" \
                               "Flags:\n" \
                               "-p -q -r -s\n" \
                               "\n" \
                               "Cipher commands:\n" \
                               "base64\n" \
                               "\n" RST


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
	fprintf(stderr, USAGE_FORMAT, argv[0]);
	fprintf(stderr, GLOBAL_HELP_STRING);

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
