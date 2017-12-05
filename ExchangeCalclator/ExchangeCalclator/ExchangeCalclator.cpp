// ExchangeCalclator.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
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

	CZaifBtcWithdrawLog::Create();
	CZaifBtcDepositLog::Create();
	CZaifTradeLog::Create();

	FCTradeLogManager* pLogMngr = FCTradeLogManager::GetInstance();
	pLogMngr->DoInit();

	pLogMngr->DoLoad(pInst->GetArg("-zaifbtcwithdraw"));	// �o������
	pLogMngr->DoLoad(pInst->GetArg("-zaifbtcdeposit"));	// ��������
	pLogMngr->DoLoad(pInst->GetArg("-zaif"));			// �������

	pLogMngr->DoConvert();
	pLogMngr->DoCalclate();

	pLogMngr->DoDump();

	pLogMngr->Finalize();

    return 0;
}

