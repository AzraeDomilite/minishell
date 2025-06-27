#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void add_argument(char ***argv, int *argc, const char *arg) {
	*argv = realloc(*argv, (*argc + 2) * sizeof(char *));
	(*argv)[*argc] = strdup(arg);
	(*argc)++;
	(*argv)[*argc] = NULL;
}

char **parse_arguments(const char *input) {
	char **argv = NULL;
	int argc = 0;
	const char *ptr = input;
	char buffer[1024];
	int buf_index = 0;
	char quote = '\0';

	while (*ptr) {
		if (quote) {
			if (*ptr == quote) {
				quote = '\0';
			} else if (*ptr == '\\' && quote == '"') {
				ptr++;
				if (*ptr) buffer[buf_index++] = *ptr;
			} else {
				buffer[buf_index++] = *ptr;
			}
		} else {
			if (*ptr == '\'' || *ptr == '"') {
				quote = *ptr;
			} else if (isspace(*ptr)) {
				if (buf_index > 0) {
					buffer[buf_index] = '\0';
					add_argument(&argv, &argc, buffer);
					buf_index = 0;
				}
			} else {
				buffer[buf_index++] = *ptr;
			}
		}
		ptr++;
	}

	if (buf_index > 0) {
		buffer[buf_index] = '\0';
		add_argument(&argv, &argc, buffer);
	}

	return argv;
}

void free_arguments(char **argv) {
	for (int i = 0; argv[i] != NULL; i++) {
		free(argv[i]);
	}
	free(argv);
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "Usage: %s \"<command string>\"\n", argv[0]);
		return 1;
	}

	const char *input = argv[1];
	char **parsed_argv = parse_arguments(input);

	for (int i = 0; parsed_argv[i] != NULL; i++) {
		printf("argv[%d]: %s\n", i, parsed_argv[i]);
	}

	free_arguments(parsed_argv);

	return 0;
}
