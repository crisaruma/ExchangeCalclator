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

	CTradeLogZaif::Create();

	FCTradeLogManager* pLogMngr = FCTradeLogManager::GetInstance();
	pLogMngr->DoInit();
	pLogMngr->DoLoad( pInst->GetArg("-zaif") );

	pLogMngr->DoDump();

	//CSysTable newCsv;
	//const CSysDataArray* pZaif = pInst->GetArg("-zaif");
	//if (pZaif) {

	//	CSysDataArray::CIteConst IteZaif = pZaif->begin()+1;
	//	for (; IteZaif != pZaif->end() ; IteZaif++)
	//	{
	//		newCsv.LoadCsv(IteZaif->GetAsStr() );
	//	}

	//	newCsv.Dump();
	//}

    return 0;
}

