// ExchangeCalclator.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include <stdlib.h>


#include "src/System/CSystem.h"
#include "src/System/CSysTable.h"

//	
#include "src/Object/FCTradeLogZaif.h"


int main(int argc, char *argv[])
{
	CArg::Create(argc, argv);

	CArg* pInst = CArg::GetInstance();

	CZaifWithdrawLog::Create();
	CZaifDepositLog::Create();
	CZaifTradeLog::Create();

	FCTradeLogManager* pLogMngr = FCTradeLogManager::GetInstance();
	pLogMngr->DoInit();

	pLogMngr->DoLoad(pInst->GetArg("-zaifdraw"));	// 出金履歴
	pLogMngr->DoLoad(pInst->GetArg("-zaifdepo"));	// 入金履歴
	pLogMngr->DoLoad(pInst->GetArg("-zaif"));		// 取引履歴

	pLogMngr->DoConvert();
	pLogMngr->DoCalclate();

	pLogMngr->DoDump();

	pLogMngr->Finalize();

    return 0;
}

