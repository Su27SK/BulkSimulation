#ifndef _BULKFILE_H_
#define _BULKFILE_H_
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <dirent.h>
struct aPathInfo
{
	string sDirname;
	string sBasename;
	string sExtension;
}pathInfo;

class BulkFile
{
	private:
		string _defaultDirname;
		string _sFilePath;
		string _sTempDirname;
		string _sTempPath;
		FILE* _fileHandle;
		pathInfo* _pathinfo(string sDirname, string sBasename, string sExtension = ".odf");
		void _setFileName(pathInfo* fileNameInfo, string sFileName);
		string _getFileFullPath(pathInfo* fileNameInfo);
	public:
		BulkFile();
		BulkFile(string dirname);
		void addFile(string sBasename, string sDirname = NULL);
		void init();
};
#endif
