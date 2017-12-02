

#ifndef __FC_TRADE_LOG_H__
#define __FC_TRADE_LOG_H__


#include "../System/CSysTable.h"


//	取引履歴解析用
class FCTradeLog : public CSysTable
{
public:
	typedef CSysTable	FClsTable;

protected:
	FCTradeLog*	mThis;

public:
	static FCTradeLog* Create(void);

	FCTradeLog();
	~FCTradeLog();

	virtual void Initialize(void);
	virtual void Finalize(void);

	virtual const char* GetOptionWord(void) { return "-sample";}
	virtual const char* GetRegistKey(void) { return "Sample";  }
	virtual const Sint32 GetRegistID(void) { return CHash::CRC32( GetRegistKey() ); }

	virtual void RegistManager(void);
	virtual void RemoveManager(void);

};




//	取引履歴マネージャー
class FCTradeLogManager
{
public:
	typedef CSysMap<Sint32, FCTradeLog*>	CLogTable;

protected:
	static FCTradeLogManager* mInst;
	CLogTable	mLogTable;

public:
	static FCTradeLogManager* Create(void);
	static FCTradeLogManager* GetInstance(void);

	FCTradeLogManager();
	virtual ~FCTradeLogManager();

	virtual void Initialize(void);
	virtual void Finalize(void);

	virtual bool Regist(FCTradeLog* _pInst);
	virtual bool Remove(FCTradeLog* _pInst);

	virtual void DoInit(void);
	virtual bool DoLoad(const CSysDataArray* _pAry);

	virtual void DoDump(void);
};



#endif