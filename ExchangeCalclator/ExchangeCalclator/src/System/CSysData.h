

#ifndef __CSYSDATA_H__
#define __CSYSDATA_H__

#include "CSysArray.h"


//	汎用パラメータ
class CSysData
{
public:
	enum Type
	{
		TypeInvalid = 0	,
		TypeSint32	= 1	,
		TypeFloat	= 2	,
		TypeDouble  = 3 ,
		TypeString	= 4	,
	};

protected:
	Type	mType;
	Sint32	mInt;
	double	mFlt;
	string  mStr;
	static string mTempStr;

public:
	CSysData();
	CSysData(const Sint32& _val );
	CSysData(const float& _val);
	CSysData(const double& _val);
	CSysData(const char* _pVal );

	void Initialize(void);
	void Finalize(void);

	const Type& GetType(void) const;

	void SetAsInt(const Sint32& _val);
	const Sint32 GetAsInt(void) const ;

	void SetAsFlt(const float& _val);
	const float GetAsFlt(void) const;

	void SetAsDbl(const double& _val);
	const double GetAsDbl(void) const;

	void SetAsStr(const char* _pVal);
	const char* GetAsStr(void) const ;

};


//	
typedef CSysArray<CSysData>				CSysDataArray;

typedef CSysMap<Sint32, CSysData>		CSysDataMap;
typedef CSysMap<Sint32, CSysDataArray>	CSysDataTable;




#endif