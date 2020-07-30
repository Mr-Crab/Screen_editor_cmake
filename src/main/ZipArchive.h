#pragma once
#include <QString>

# pragma execution_character_set("utf-8") 

class ZipArchive
{
public:
	static bool CreateFromFolder(const QString& srcFolder, const QString& zipName,const QString& destZipPath = "");
	static bool ClearUnUsedFile(const QString& folder);
};

