

#include "CSysTable.h"
#include <Windows.h>


//===================================================
//	CSysTable
//===================================================
//	1件のレコード情報

CSysTable::CRecord::CRecord()
: mParam()
{
}

CSysTable::CRecord::~CRecord()
{
	Finalize();
}

void CSysTable::CRecord::Initialize(void)
{
	mParam.Initialize();
}

void CSysTable::CRecord::Finalize(void)
{
	mParam.Finalize();
}


void CSysTable::CRecord::AddParam(const CSysData& _param)
{
	mParam.AddParam(mParam.count(), _param);
}


//	CSV形式で、パラメータを設定する
bool CSysTable::CRecord::Assign(const char* _pCsv)
{
	const Sint32 numPrm = CStr::Split(mParam, _pCsv, ",");
	if (numPrm <= 0) {
		return false;
	}
	return true;
}



CSysData* CSysTable::CRecord::GetField(const Sint32& _index)
{
	return mParam.SearchParam(_index);
}


const CSysData* CSysTable::CRecord::GetField(const Sint32& _index) const 
{
	return mParam.SearchParam(_index);
}




CSysTable::CSysTable()
: mIndex()
, mLabel()
, mTable()
, mCurrent()
{
}

CSysTable::~CSysTable()
{
	Finalize();
}

void CSysTable::Initialize(void)
{
	mIndex.Initialize();
	mLabel.Initialize();

	mTable.Initialize();
	mCurrent = CRecordList::CIte();
}


void CSysTable::Finalize(void)
{
	mIndex.Finalize();
	mLabel.Finalize();

	mTable.Finalize();
	mCurrent = CRecordList::CIte();
}

void CSysTable::AssignIndex(const char* _pCSV)
{
	mIndex.Initialize();

	CSysDataMap tempMap;
	CStr::Split(tempMap, _pCSV, ",");
	CSysDataMap::CIte ItePrm = tempMap.begin();
	for (; ItePrm != tempMap.end(); ItePrm++) 
	{
		mIndex.AddParam(CHash::CRC32(ItePrm->second.GetAsStr()), ItePrm->first );
	}
}



//	
bool CSysTable::LoadCsv(const char* _path)
{
	FILE* fp = NULL;
	errno_t error = fopen_s( &fp,_path, "rb");
	if (error) {
		return false;
	}
	if (!fp) {
		return false;
	}

	fseek(fp, 0, SEEK_END);
	Sint32 fileSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	void* pPtr = malloc(fileSize);
	if (pPtr)
	{
		fread(pPtr, fileSize, 1, fp);

		const char* pFile = reinterpret_cast<const char*>(pPtr);

		CStr::Replace(pFile, "\r", "\n");

		CSysDataMap tempFile;
		CStr::Split(tempFile, pFile, "\n");
		free(pPtr);

		CSysDataMap::CIte IteRec = tempFile.begin();
		for (; IteRec != tempFile.end(); IteRec++)
		{
			AssignRecord(IteRec->second.GetAsStr());
		}
	}
	fclose(fp);

	return true;
}


void CSysTable::AssignRecord(const char* _pCSV)
{
	if (mIndex.count() <= 0) 
	{
		mLabel.Assign(_pCSV);
		return AssignIndex(_pCSV );
	}

	CRecord* pNewRecord = mTable.AddParam(mTable.count(), CRecord());
	if (pNewRecord) 
	{
		pNewRecord->Assign(_pCSV);
	}
}


//	
void CSysTable::Dump(void) 
{
	{//	パラメータの印刷
		CRecordList::CIte IteRec = mTable.begin();
		for (; IteRec != mTable.end(); IteRec++) 
		{
			CSysIntMap::CIte IteIndex = mIndex.begin();
			for (; IteIndex != mIndex.end(); IteIndex++)
			{
				const CSysData* pLabel = mLabel.GetField(IteIndex->second);
				const CSysData* pParam = IteRec->second.GetField(IteIndex->second);
				if (!pParam) 
				{
					continue;
				}

				string lineText;
				lineText += pLabel->GetAsStr();
				lineText += ":";
				lineText += pParam->GetAsStr();
				lineText += "\n";
				OutputDebugStringA(lineText.c_str());
			}
		}
	}
}


void CSysTable::First(void){
	mCurrent = mTable.begin();
}

void CSysTable::Next(void) {
	mCurrent++;
}


bool CSysTable::IsEof(void) {
	if (mCurrent == mTable.end()) {
		return true;
	}
	return false;
}
