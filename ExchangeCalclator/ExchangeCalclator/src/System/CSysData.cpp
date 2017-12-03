

#include "CSysData.h"


string CSysData::mTempStr="";

//	汎用パラメータ
CSysData::CSysData()
: mType(TypeInvalid)
, mInt(0)
, mFlt(0.0f)
, mStr()
{
}

CSysData::CSysData(const Sint32& _val)
: mType(TypeSint32)
, mInt(_val)
, mFlt(0.0f)
, mStr()
{
}

CSysData::CSysData(const float& _val)
: mType(TypeFloat)
, mInt(0)
, mFlt(_val)
, mStr()
{
}

CSysData::CSysData(const double& _val)
: mType(TypeDouble)
, mInt(0)
, mFlt(_val)
, mStr()
{
}


CSysData::CSysData(const char* _pVal)
: mType(TypeString)
, mInt(0)
, mFlt(0.0)
, mStr(_pVal ? _pVal : "" )
{
}

void CSysData::Initialize(void)
{
	mType = TypeInvalid;
	mInt = 0;
	mFlt = 0.0f;
	mStr = string();
}

void CSysData::Finalize(void)
{
	mType = TypeInvalid;
	mInt = 0;
	mFlt = 0.0f;
	mStr = string();
}


const CSysData::Type& CSysData::GetType(void) const
{
	return mType;
}


void CSysData::SetAsInt(const Sint32& _val)
{
	mInt = _val;
	mType = TypeSint32;
}

const Sint32 CSysData::GetAsInt(void) const
{
	switch (mType) {
		case TypeSint32:{
			return mInt;
		}	break;

		case TypeFloat:
		case TypeDouble:
		{
			return static_cast<Sint32>(mFlt);
		}	break;

		case TypeString:{
			return atoi(mStr.c_str());
		}	break;
	}
	return 0;
}

void CSysData::SetAsFlt(const float& _val)
{
	mFlt = _val;
	mType = TypeFloat;
}

const float CSysData::GetAsFlt(void) const
{
	switch (mType) {
	case TypeSint32: {
		return static_cast<float>(mInt);
	}	break;

	case TypeFloat: 
	case TypeDouble:
	{
		return static_cast<float>(mFlt);
	}	break;

	case TypeString: {
		return static_cast<float>(atof(mStr.c_str()) );
	}	break;
	}
	return 0.0f;
}


void CSysData::SetAsDbl(const double& _val) 
{
	mFlt = _val;
	mType = TypeFloat;
}

const double CSysData::GetAsDbl(void) const 
{
	switch (mType) {
	case TypeSint32: {
		return static_cast<double>(mInt);
	}	break;

	case TypeFloat: 
	case TypeDouble:
	{
		return mFlt;
	}	break;

	case TypeString: {
		return atof(mStr.c_str());
	}	break;
	}
	return 0.0f;
}



void CSysData::SetAsStr(const char* _pVal)
{
	mStr = _pVal ? _pVal : "";
	mType = TypeString;
}


const char* CSysData::GetAsStr(void) const
{
	char buf[256];
	switch (mType) 
	{
		case TypeSint32: {
			sprintf_s(buf, "%d", mInt);
			mTempStr = buf;
			return mTempStr.c_str();
		}	break;

		case TypeFloat: 
		case TypeDouble:
		{
			sprintf_s(buf, "%f", mFlt);
			mTempStr = buf;
			return mTempStr.c_str();
		}	break;
	}
	return mStr.c_str();
}



