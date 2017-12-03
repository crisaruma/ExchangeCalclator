

#ifndef __FC_TRADE_LOG_ZAIF_H__
#define __FC_TRADE_LOG_ZAIF_H__


//	Zaif の取引ログ集計用クラス

#include "FCTradeLog.h"



//	ザイフの入金履歴解析
class CZaifBase : public FCTradeLog
{
public:
	typedef FCTradeLog	FClsBase;

public:
	CZaifBase();
	virtual ~CZaifBase();

	virtual void Initialize(void);
	virtual void Finalize(void);

	virtual const char* GetOptionWord(void) { return "-zaifbase"; }
	virtual const char* GetRegistKey(void) { return "CZaifBase"; }
	virtual const Sint32 GetRegistID(void) { return CHash::CRC32(GetRegistKey()); }


	virtual const Sint32 ConvertDate(const CSysData* _pDateTime);
	virtual const Sint32 ConVertTime(const CSysData* _pDateTime);

};


//	ザイフの取引履歴解析
class CTradeLogZaif : public CZaifBase
{
public:
	typedef CZaifBase	FClsBase;

protected:

public:
	static CTradeLogZaif* Create(void);

	CTradeLogZaif();
	virtual ~CTradeLogZaif();

	virtual void Initialize(void);
	virtual void Finalize(void);

	virtual const char* GetOptionWord(void) { return "-zaif"; }
	virtual const char* GetRegistKey(void) { return "CTradeLogZaif"; }
	virtual const Sint32 GetRegistID(void) { return CHash::CRC32(GetRegistKey()); }


	virtual void Dump(void);

	//	CSVテーブルを買い/売りのリストにコンバートする
	virtual void DoConvert(void);
	virtual bool DoCalclate(void);

	virtual bool DoSwap(const FCTradeItem::TradeType& _src, const FCTradeItem::TradeType& _dst, FCTradeItem* _pTrade, CTradeArray* _pAry);

};




#endif