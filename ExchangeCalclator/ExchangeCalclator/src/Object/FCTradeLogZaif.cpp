

#include "FCTradeLogZaif.h"



//	�U�C�t�̎���������
CTradeLogZaif* CTradeLogZaif::Create(void)
{
	return new CTradeLogZaif();
}


CTradeLogZaif::CTradeLogZaif()
: FClsBase()
{
}


CTradeLogZaif::~CTradeLogZaif()
{
	Finalize();
}


void CTradeLogZaif::Initialize(void)
{
	FClsBase::Initialize();
}

void CTradeLogZaif::Finalize(void)
{
	FClsBase::Finalize();
}
