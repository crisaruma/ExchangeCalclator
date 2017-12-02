

#include "FCTradeLogZaif.h"



//	ƒUƒCƒt‚Ìæˆø—š—ğ‰ğÍ
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
