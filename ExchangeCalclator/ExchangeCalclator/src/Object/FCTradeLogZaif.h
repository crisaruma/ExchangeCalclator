

#ifndef __FC_TRADE_LOG_ZAIF_H__
#define __FC_TRADE_LOG_ZAIF_H__


//	Zaif の取引ログ集計用クラス

#include "FCTradeLog.h"

//============================================================================================================
//	ザイフベース
class CZaifBase : public FCTradeLog
{
public:
	typedef FCTradeLog	FClsBase;

public:
	CZaifBase();
	CZaifBase(FCTradeLog* _pInst);
	virtual ~CZaifBase();

	virtual void Initialize(void);
	virtual void Finalize(void);

	virtual const char* GetOptionWord(void) { return "-zaifbase"; }
	virtual const char* GetRegistKey(void) { return "CZaifBase"; }


	virtual const Sint32 ConvertDate(const CSysData* _pDateTime);
	virtual const Sint32 ConVertTime(const CSysData* _pDateTime);

};

//============================================================================================================
//	ザイフの入金履歴解析
class CZaifDepositLog : public CZaifBase 
{
public:
	typedef CZaifBase	FClsBase;

protected:
public:
	static CZaifDepositLog* Create(void) {
		CZaifDepositLog* pInst = new CZaifDepositLog();
		pInst->RegistManager();
		return pInst;
	}

	CZaifDepositLog();
	CZaifDepositLog(FCTradeLog* _pInst);
	virtual ~CZaifDepositLog();

	virtual void Initialize(void);
	virtual void Finalize(void);

	virtual const char* GetOptionWord(void) { return "-zaifdepo"; }
	virtual const char* GetRegistKey(void) { return "CZaifDepositLog";  }
};


//============================================================================================================
//	ザイフの出金履歴解析
class CZaifWithdrawLog : public CZaifBase
{
public:
	typedef CZaifBase	FClsBase;

protected:
public:
	static CZaifWithdrawLog* Create(void) {
		CZaifWithdrawLog* pInst = new CZaifWithdrawLog();
		pInst->RegistManager();
		return pInst;
	}

	CZaifWithdrawLog();
	CZaifWithdrawLog(FCTradeLog* _pInst);
	virtual ~CZaifWithdrawLog();

	virtual void Initialize(void);
	virtual void Finalize(void);

	virtual const char* GetOptionWord(void) { return "-zaifdraw"; }
	virtual const char* GetRegistKey(void) { return "CZaifWithdrawLog"; }
};



//============================================================================================================
//	ザイフの取引履歴解析
class CZaifTradeLog : public CZaifBase
{
public:
	typedef CZaifBase	FClsBase;

protected:

public:
	static CZaifTradeLog* Create(void){
		CZaifTradeLog* pInst = new CZaifTradeLog();
		pInst->RegistManager();
		return pInst;
	}

	CZaifTradeLog();
	CZaifTradeLog(FCTradeLog* _pInst);
	virtual ~CZaifTradeLog();

	virtual void Initialize(void);
	virtual void Finalize(void);

	virtual const char* GetOptionWord(void) { return "-zaif"; }
	virtual const char* GetRegistKey(void) { return "CZaifTradeLog"; }


	virtual void Dump(void);

	//	CSVテーブルを買い/売りのリストにコンバートする
	virtual void DoConvert(void);
	virtual bool DoCalclate(void);

	virtual bool DoSwap(const FCTradeItem::TradeType& _src, const FCTradeItem::TradeType& _dst, FCTradeItem* _pTrade, CTradeArray* _pAry);

	virtual bool DoImportDepositTable(FCTradeLog* _pTbl);
	virtual bool DoImportWithdrawTable(FCTradeLog* _pTbl);

};




#endif