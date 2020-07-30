#include "ZipArchive.h"
#include "zip.h"|
#include <QDir>
#include <QFileInfoList>
#include <QFileInfo>
#include <filesystem>

using namespace std;

bool ZipArchive::CreateFromFolder(const QString& srcFolder, const QString& zipName, const QString& destZipPath /*= ""*/)
{
	QDir _dir(srcFolder);
	QDir _dirZip(destZipPath);

	if (!_dir.exists())
		return false;
	
	QString _tempZipFile = "";
	if (destZipPath == "")
		_tempZipFile = srcFolder + "/" + zipName + ".zip";
	else
		_tempZipFile = destZipPath + "/" + zipName + ".zip";

	if (!_dirZip.exists())
	{
		_tempZipFile = srcFolder + "/" + zipName + ".zip";
	}

	zip_t* pArchive = zip_open(_tempZipFile.toLocal8Bit(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');

	int zipCode = 0;
	QFileInfoList _fileList = _dir.entryInfoList(QDir::Files);
	for (int i = 0; i < _fileList.count(); i++)
	{
		QFileInfo _fileInfo = _fileList[i];
		QString _suffix = _fileInfo.suffix();
		if(_suffix == "zip")
			continue;

		QString _relativeName = zipName + "/" + _fileInfo.fileName();
		zipCode = zip_entry_open(pArchive, _relativeName.toUtf8());
		if(zipCode !=0 )
			break;

		zipCode = zip_entry_fwrite(pArchive, _fileInfo.filePath().toLocal8Bit());

		if (zipCode != 0)
		{
			zip_entry_close(pArchive);
			break;
		}
		zip_entry_close(pArchive);
	}
	zip_close(pArchive);

	return true;
}

bool ZipArchive::ClearUnUsedFile(const QString& folder)
{
	QDir _dir(folder);

	if (!_dir.exists())
		return false;

	QFileInfoList _fileList = _dir.entryInfoList(QDir::Files);
	for (int i = 0; i < _fileList.count(); i++)
	{
		QFileInfo _fileInfo = _fileList[i];
		QString _suffix = _fileInfo.suffix();
		if (_suffix == "png" || _suffix == "xml")
			continue;

		QFile _file(_fileInfo.filePath());
		if (!_file.remove())
			return false;
	}

	return true;
}
