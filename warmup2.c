#define _CRT_SECURE_NO_WARNINGS
#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cs402.h"
#include "warmup2.h"

#define NUM_THREADS     2

/*
 *  FUNC: Show error message and usage commandline
 *  ARG: The number of argument
 *  RETURN: None
 *  PRE: i equals 1 or larger 
 *  POST: Terminate program
 */
void showErrorMessage(const int* i)
{
	fprintf(stderr, "Error: Cannnot parse argv[%d].\n", *i);
	fprintf(stderr, "Usage: warmup2 [-lamda lamda] [-mu mu] [-r r] [-B B] [-P P] [-n num] [-t tsfile]");
	exit(EXIT_FAILURE);
}
/*   
 *  FUNC: Get char value into double
 *  ARG: characters from command line, parameter, the number of argument
 *  RETURN: None
 *  PRE: argv is not equal to NULL, i equals 1 or larger
 *  POST: Terminate program
 */
void scanDouble(char* argv, double* value, const int* i)
{
	if (argv == NULL || sscanf(argv, "%lf", value) != 1) {
		/* cannot parse argv[i] to get a double value */
		showErrorMessage(i);
	}
}
/*
 *  FUNC: Get char value into double
 *  ARG: characters from command line, parameter, the number of argument
 *  RETURN: None
 *  PRE: argv is not equal to NULL, i equals 1 or larger
 *  POST: Terminate program
 */
void scanInt(char* argv, int* value, const int* i)
{
	if (argv == NULL || sscanf(argv, "%d", value) != 1) {
		/* cannot parse argv[i] to get a int value */
		showErrorMessage(i);
	}
}
/*
 *
 *
 */
void readFile(char* filename, Parameter* param)
{
	char buf[2048] = { '\0' };
	FILE* fp = fopen(filename, "r");

	if (fp == NULL)
	{
		fprintf(stderr, "ERROR: Input file %s does not exist in the directory.\n", filename);
		exit(EXIT_FAILURE);
	}
	/* read number of packet */
	/*while (fgets(buf, sizeof(buf), fp))
	{
		sscanf(buf, "%d", &(param->num));
	}*/
	if(fscanf(fp, "%d", &(param->num)) != 1)
	{
		fprintf(stderr, "Error: File format is incorrect. First line has one integer.");
		exit(EXIT_FAILURE);
	}
	/* consume newline */
	fgets(buf, sizeof(buf), fp);
	int start_time, token, service_time; /* dummy */
	
	while (fgets(buf, sizeof(buf), fp))
	{
		if(sscanf(buf, "%d %d %d", &start_time, &token, &service_time) != 3)
		{
			fprintf(stderr, "Error: File format is incorrect after second line.");
			fprintf(stderr, "Usage: [integer] [integer] [integer].");
			exit(EXIT_FAILURE);
		}
	}
	fclose(fp);
}
/*
*  FUNC: Update parameter if commandline options are defined
*  ARG: the number of arguments, arguments, emulation parameters
*  RETURN: None
*  PRE: *argc equals to or larger than one.  
*  POST: Terminate program
*/
void parseArgument(const int* argc, char* argv[], Parameter* param)
{
	if (*argc > 1)
	{
		char option[MAXPATHLENGTH] = { '\0' };	/*buffer for option*/
		int i = 1;

		while (i != *argc)
		{
			/* read what is the odd argument is */
			sscanf(argv[i], "%s", option);
			const int arg_len = strlen(option);

			/* read what is the even argument is */
			i++;
			/* read lambda */
			if (strncmp(option, "-lambda", arg_len) == 0 && arg_len == (int)strlen("-lambda"))
			{
				scanDouble(argv[i], &(param->lambda), &i);
			}
			/* read mu */
			else if (strncmp(option, "-mu", arg_len) == 0 && arg_len == (int)strlen("-mu"))
			{
				scanDouble(argv[i], &(param->mu), &i);
			}
			/* read r */
			else if (strncmp(option, "-r", arg_len) == 0 && arg_len == (int)strlen("-r"))
			{
				scanDouble(argv[i], &(param->r), &i);
			}
			/* read B */
			else if (strncmp(option, "-B", arg_len) == 0 && arg_len == (int)strlen("-B"))
			{
				scanInt(argv[i], &(param->B), &i);
			}
			/* read P */
			else if (strncmp(option, "-P", arg_len) == 0 && arg_len == (int)strlen("-P"))
			{
				scanInt(argv[i], &(param->P), &i);
			}
			/* read num */
			else if (strncmp(option, "-n", arg_len) == 0 && arg_len == (int)strlen("-n"))
			{
				scanInt(argv[i], &(param->num), &i);
			}
			/* read tfile */
			else if (strncmp(option, "-t", arg_len) == 0 && arg_len == (int)strlen("-t"))
			{
				readFile(argv[i], param);
			}
			/* invalid command option */
			else
			{
				showErrorMessage(&i);
			}
			i++;
		}
	}
	else
	{
		/* use default parameter */
	}
}

/* PRE: argc equals 1 or larger */
int main(int argc, char* argv[])
{
	/* initialize parameters as default */
	Parameter param = {1.0, 0.350, 1.50, 10, 3, 20};
	
	/* parse commandline argument */
	parseArgument(&argc, argv, &param);
		
	/* Emulation start */
	
	exit(EXIT_SUCCESS);
}