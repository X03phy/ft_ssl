#include "ft_ssl.h"
#include "colors.h" // COLORS
#include <string.h> // memset(), strcmp()
#include <stdio.h> // fprintf(), stderr


#define USAGE_FORMAT "usage: %s command [flags] [file/string]\n"
#define INVALID_COMMAND_FORMAT RED "%s: Error: '%s' is an invalid command\n" RST


int main(int argc, char **argv)
{
	t_ssl_wfunc wfunc = NULL;

	memset(&cmd, 0, sizeof(t_ssl_cmd));

	if (argc < 2) {
		fprintf(stderr, USAGE_FORMAT HELP_FORMAT, argv[0]);
		return (1);
	}

	if (argc == 2 && strcmp("help", argv[1]) == 0) {
		fprintf(stderr, HELP_FORMAT);
		return (0);
	}

	cmd.name = argv[1];
	wfunc = parse_cmd(&cmd, argv[1]);
	if (!wfunc) {
		fprintf(stderr, INVALID_COMMAND_FORMAT HELP_FORMAT, argv[0], argv[1]);
		return (1);
	}

	return (wfunc(argc, argv, &cmd));
}
