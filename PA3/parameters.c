#include "parameters.h"

Parameters* get_parameters(int argc, const char* argv[])
{
	Parameters* params = (Parameters*)malloc(sizeof(Parameters));
	params->inputFileCount = argc - 1;
	params->inputFileNames = malloc(sizeof(char*) * params->inputFileCount);
	
	for (int i = 1; i < argc; i++)
	{
		params->inputFileNames[i-1] = malloc(sizeof(char) * strlen(argv[i]));
		strcpy(params->inputFileNames[i-1], argv[i]);
	}
	return params;
}
