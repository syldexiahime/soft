#include "preprocessor/preprocessor.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 1024

char * get_stdin ()
{
	char buffer[BUF_SIZE];
	size_t contentSize = 1; // includes NULL
	char * content = malloc(sizeof(char) * BUF_SIZE);

	if (content == NULL) {
		perror("Failed to allocate content");
		exit(1);
	}

	content[0] = '\0'; // make null-terminated

	while (fgets(buffer, BUF_SIZE, stdin)) {
		char *old = content;
		contentSize += strlen(buffer);
		content = realloc(content, contentSize);
		if(content == NULL) {
			perror("Failed to reallocate content");
			free(old);
			exit(2);
		}
		strcat(content, buffer);
	}

	if (ferror(stdin)) {
		free(content);
		perror("Error reading from stdin.");
		exit(3);
	}

	return content;
}

char * get_from_file (char * filename)
{
	char * buffer = NULL;
	size_t buflen = 0;

	FILE * f = fopen(filename, "rb");

	if (f) {
		if (!fseek(f, 0, SEEK_END)) {
			// Handle error
		}

		buflen = ftell(f);

		if (!buflen) {
			// Handle error
		}

		if (!fseek(f, 0, SEEK_SET)) {
			// Handle error
		}

		buffer = malloc(buflen);

		if (buffer)
			fread(buffer, 1, buflen, f);

		fclose (f);
	}

	return buffer;
}

int main (int argc, char ** argv)
{
	char * infile = NULL;
	char * outfile = NULL;
	int E_flag = false;
	int index;
	int c;

	opterr = 0;

	while (optind < argc) {
		if ((c = getopt (argc, argv, "Ei:o:")) != -1) {
			switch (c) {
				case 'E':
					E_flag = true;
					break;
				case 'o':
					outfile = optarg;
					break;
				case '?':
					if (optopt == 'i' || optopt == 'o')
						fprintf (stderr, "Option -%c requires an argument.\n", optopt);
					else if (isprint (optopt))
						fprintf (stderr, "Unknown option `-%c'.\n", optopt);
					else
						fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
					return 1;
				default:
					abort();
			}
		}
		else {
			infile = argv[optind];
			optind++;
		}
	}

	for (index = optind; index < argc; index++)
		printf ("Non-option argument %s\n", argv[index]);

	bool binout   = false;
	char * buffer = NULL;
	size_t buflen = 0;

	buffer = infile ? get_from_file(infile) : get_stdin();

	char * output = NULL;

	if (!buffer)
		return 1;

	struct soft_preprocessor * preprocessor = soft_preprocessor_init();
	output = soft_preprocessor_preprocess(buffer);

	if (E_flag)
		goto success;

	binout = true;

	success: ;

	if (outfile) {
		FILE *f = fopen(outfile, "w");

		if (f == NULL)
			return 1;

		if (fputs(output, f) != EOF) {
			fclose(f);

			return 1;
		}

		fclose(f);
	}
	else {
		if (!binout)
			printf("%s", output);
	}

	return 0;
}
