#include "parameters.h"

Parameters* get_parameters(int argc, const char* argv[])
{
	Parameters* params = (Parameters*)malloc(sizeof(Parameters));
	params->inputFileCount = argc - 4;
	params->inputFileNames = malloc(sizeof(char*) * params->inputFileCount);
	
	for (int i = 1; i < argc;)
	{
		if (argv[i][0] == '-')
		{
			if (argv[i][1] == 'a' || argv[i][1] == 'A')
			{
				i++;
				params->alphabetFileName = malloc(sizeof(char) * strlen(argv[i]));
				params->alphabetFileName = argv[i];
				i++;
			}
			else if (argv[i][1] == 'i' || argv[i][1] == 'I')
			{
				int j = 0;
				i++;
				while (i < argc && argv[i][0] != '-')
				{
					params->inputFileNames[j] = malloc(sizeof(char) * strlen(argv[i]));
					strcpy(params->inputFileNames[j], argv[i]);
					j++;
					i++;
				}
			}
		}
	}
	return params;
}
