

#include "FCTradeLogGeneral.h"

#include <iostream>
#include <fstream>
#include <Windows.h>



//============================================================================================================
//	ëçäáÉçÉO
CGeneralTradeLog::CGeneralTradeLog() 
: FClsBase(this)
{
}

CGeneralTradeLog::CGeneralTradeLog(FCTradeLog* _pInst)
: FClsBase(_pInst)
{
}


CGeneralTradeLog::~CGeneralTradeLog()
{
	Finalize();
}


void CGeneralTradeLog::Initialize(void)
{
	FClsBase::Initialize();
}

void CGeneralTradeLog::Finalize(void)
{
	FClsBase::Finalize();
}


