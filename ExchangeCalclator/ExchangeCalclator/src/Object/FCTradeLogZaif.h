

#ifndef __FC_TRADE_LOG_ZAIF_H__
#define __FC_TRADE_LOG_ZAIF_H__


//	Zaif �̎�����O�W�v�p�N���X

#include "FCTradeLog.h"



//	�U�C�t�̎���������
class CTradeLogZaif : public FCTradeLog
{
public:
	typedef FCTradeLog	FClsBase;

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

};




#endif