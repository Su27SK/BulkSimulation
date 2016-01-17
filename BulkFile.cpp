#include "BulkFile.h"
BulkFile::BulkFile() 
{
	DIR * dir;
	struct dirent * ptr;
	int i;
	dir = opendir(".");
	while((ptr = readdir(dir)) != NULL)
	{
		printf("d_name : %s\n", ptr->d_name);
	}
	closedir(dir);
}

BulkFile::BulkFile(string dirname)
{
	this->_defaultDirname = dirname;
}


