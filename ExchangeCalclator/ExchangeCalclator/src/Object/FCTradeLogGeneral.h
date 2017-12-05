

#ifndef __FC_TRADE_LOG_ZAIF_H__
#define __FC_TRADE_LOG_ZAIF_H__


//	��������̑����̎�����O�W�v�p�N���X
#include "FCTradeLog.h"
#include "FCTradeLogZaif.h"

//============================================================================================================
//	�U�C�t�x�[�X
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