

#ifndef __CSYS_TABLE_H__
#define __CSYS_TABLE_H__

#include "CSystem.h"


//===================================================
//	CSysTable
//===================================================
class CSysTable
{
public:
	//	1åèÇÃÉåÉRÅ[ÉhèÓïÒ
	class CRecord {
		public:
		protected:
			CSysDataMap	mParam;

		public:
			CRecord();
			~CRecord();

			void Initialize(void);
			void Finalize(void);

			void AddParam(const CSysData& _param);

			bool Assign(const char* _pCsv);

			CSysData* GetField(const Sint32& _index);
			const CSysData* GetField(const Sint32& _index) const ;
	};


	typedef CSysMap<Sint32, CRecord>	CRecordList;


protected:
	CSysIntMap			mIndex;
	CRecord				mLabel;

	CRecordList			mTable;
	CRecordList::CIte	mCurrent;

public:
	CSysTable();
	virtual ~CSysTable();

	virtual void Initialize(void);
	virtual void Finalize(void);

	virtual bool LoadCsv(const char* _path);

	virtual void AssignIndex(const char* _pCSV);
	virtual void AssignRecord(const char* _pCSV);

	virtual void Dump(void);

	virtual void First(void);
	virtual void Next(void);
	virtual bool IsEof(void);


};


#endif