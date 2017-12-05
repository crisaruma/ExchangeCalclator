

#ifndef __FC_TRADE_LOG_ZAIF_H__
#define __FC_TRADE_LOG_ZAIF_H__


//	取引履歴の総括の取引ログ集計用クラス
#include "FCTradeLog.h"
#include "FCTradeLogZaif.h"

//============================================================================================================
//	ザイフベース
class CGeneralTradeLog : public FCTradeLog
{
public:
	typedef FCTradeLog	FClsBase;

public:
	CGeneralTradeLog();
	CGeneralTradeLog(FCTradeLog* _pInst);
	virtual ~CGeneralTradeLog();

	virtual void Initialize(void);
	virtual void Finalize(void);

	virtual const char* GetOptionWord(void) { return "-zaifbase"; }
	virtual const char* GetRegistKey(void) { return "CGeneralTradeLog"; }

};




#endif