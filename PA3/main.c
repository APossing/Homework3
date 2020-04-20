#include "fileReader.h"
#include "parameters.h"

int main(int argc, const char* argv[])
{
	Parameters* params = get_parameters(argc, argv);
	Seq_List* seqList = init_list();

	for (int i = 0; i < params->inputFileCount; i++)
	{
		Sequence* sequence = get_sequence(params->inputFileNames[i]);
		if (insert_seq(seqList, sequence) == false)
		{
			printf("failed to insert into seq list");
			return 0;
		}
	}

	int b = 5;
}
