

#ifndef __CSYSTEM_H__
#define __CSYSTEM_H__


#include "type.h"

#include "CSysData.h"

//	
class CSystem
{

};



//	ˆø”ŠÇ—ƒNƒ‰ƒX
class CArg
{
public:
	static CArg*	mInst;
	CSysDataTable	mTable;

protected:
public:
	CArg(const Sint32& _argc , char* _argv[] );
	~CArg();

	static CArg* Create(const Sint32& _argc, char* _argv[]);
	static CArg* GetInstance(void);

	void Initialize(void);
	void Finalize(void);

	void Prepare(const Sint32& _argc, char* _argv[]);

};


//	
class CHash
{
	public:
		static Sint32 CRC32(const char* _pStr);
		static Sint32 CRC32(const void* _pStr, Sint32 _size);

	private:
		static const Uint32 mMask = 0xffffffff;
		static const Uint32 mHashTable[256];
};




//	
class CStr
{
public:
	static wstring MultiToWide(string const& src);
	static string WideToMulti(wstring const& src);

	static string WideToUtf8(wstring const& src);
	static string MultiToUtf8(std::string const& src);

	//	•¶š—ñ’uŠ·
	static string Replace(const string& _src, const string& _dst, const string& _exchange);

	//	•¶š—ñ‚Ì•ª‰ğ
	static const Sint32 Split(CSysDataMap& _result, const string& _src, const string& _delimita);

};


#endif