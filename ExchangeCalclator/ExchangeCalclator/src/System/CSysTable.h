

#ifndef __CSYS_TABLE_H__
#define __CSYS_TABLE_H__

#include "CSystem.h"


//===================================================
//	CSysTable
//===================================================
class CSysTable
{
public:
	//	1���̃��R�[�h���
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
			void SetParam(const Sint32& _index , const CSysData& _param);

			bool Assign(const char* _pCsv);

			CSysData* GetField(const Sint32& _index);
			const CSysData* GetField(const Sint32& _index) const ;

			inline const Sint32 count(void) { return mParam.count(); }

			inline CSysDataMap& GetParam(void) { return mParam; }
			inline const CSysDataMap& GetParam(void) const { return mParam; }
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
	virtual bool IsEof(void) const ;

	const Sint32 GetFieldIndex(const char* _pFieldName);
	const char* GetFieldName(const Sint32& _FieldIndex);
	const CRecord& GetFieldTable(void) { return mLabel;  }

	CRecord* CreateRecord(void);
	CRecord* GetRecord(void);
	const CRecord* GetRecord(void) const;

	const bool AddLabel(const char* _pFieldName);
	const bool AddParam(const char* _pFieldName, const CSysData& _dat);

	//	
	const bool SetParam(const char* _pFieldName, const CSysData& _dat);
	const bool SetParam(const Sint32& _FieldIndex , const CSysData& _dat);

	const CSysData* GetParam(const char* _pFieldName);
	const CSysData* GetParam(const Sint32& _FieldIndex);

	//	���g�̃e�[�u���ɓn���ꂽ�e�[�u������荞��
	virtual bool DoIntegration(CSysTable* _pTbl);

	//	�n���ꂽ�e�[�u���Ɏ��M�̃e�[�u���𓝍�����
	virtual bool DoClone(CSysTable* _pTbl);

};


#endif