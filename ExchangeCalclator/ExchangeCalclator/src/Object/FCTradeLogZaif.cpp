

#include "FCTradeLogZaif.h"

#include <iostream>
#include <fstream>
#include <Windows.h>

/*

-zaif $(USERPROFILE)\Assets\logZaif[btc].csv,$(USERPROFILE)\Assets\logZaif[eth].csv,$(USERPROFILE)\Assets\logZaif[zaif].csv
-zaifbtcdeposit $(USERPROFILE)\Assets\logZaifdepo[btc].csv
-zaifbtcwithdraw $(USERPROFILE)\Assets\btc_withdraw.csv

-zaif $(USERPROFILE)\Assets\logZaif[zaif].csv
-zaif $(USERPROFILE)\Assets\logZaif[eth].csv -zaifbtcwithdraw $(USERPROFILE)\Assets\logZaifdraw[eth].csv
-zaif $(USERPROFILE)\Assets\logZaif[btc].csv -zaifbtcdeposit $(USERPROFILE)\Assets\logZaifdepo[btc].csv -zaifbtcwithdraw $(USERPROFILE)\Assets\logZaifdraw[btc].csv

*/



//============================================================================================================
//	�U�C�t�x�[�X
CZaifBase::CZaifBase()
: FClsBase(this)
{
}

CZaifBase::CZaifBase(FCTradeLog* _pInst)
: FClsBase(_pInst)
{
}

CZaifBase::~CZaifBase()
{
	Finalize();
}

void CZaifBase::Initialize(void)
{
	FClsBase::Initialize();
}

void CZaifBase::Finalize(void)
{
	FClsBase::Finalize();
}


const Sint32 CZaifBase::ConvertDate(const CSysData* _pDateTime)
{
	if (!_pDateTime) {
		return 0;
	}
	string dateTime = _pDateTime->GetAsStr();

	CSysDataMap result;
	CStr::Split(result, dateTime, " ");

	CSysDataMap::CIte IteDate = result.begin();
	if (IteDate == result.end())
	{
		return 0;
	}
	CSysDataMap retDate;
	CStr::Split(retDate, IteDate->second.GetAsStr(), "-");

	string dateName = "";
	CSysDataMap::CIte IteDatePrm = retDate.begin();
	for (; IteDatePrm != retDate.end(); IteDatePrm++)
	{
		dateName += IteDatePrm->second.GetAsStr();
	}
	CSysData resultParam(dateName.c_str());
	return resultParam.GetAsInt();
}

const Sint32 CZaifBase::ConVertTime(const CSysData* _pDateTime)
{
	if (!_pDateTime) {
		return 0;
	}
	string dateTime = _pDateTime->GetAsStr();

	CSysDataMap result;
	CStr::Split(result, dateTime, " ");

	CSysDataMap::CIte IteDate = result.begin();
	if (IteDate == result.end()) { return 0; }
	IteDate++;
	if (IteDate == result.end()) { return 0; }

	CSysDataMap retDate;
	CStr::Split(retDate, IteDate->second.GetAsStr(), ":");

	string dateName = "";
	CSysDataMap::CIte IteDatePrm = retDate.begin();
	for (; IteDatePrm != retDate.end(); IteDatePrm++)
	{
		dateName += IteDatePrm->second.GetAsStr();
	}
	CSysData resultParam(dateName.c_str());
	return resultParam.GetAsInt();
}



//============================================================================================================
//	�U�C�t�̓����������
CZaifBtcDepositLog::CZaifBtcDepositLog()
: FClsBase(this)
{
}

CZaifBtcDepositLog::CZaifBtcDepositLog(FCTradeLog* _pInst)
: FClsBase(_pInst)
{
}

CZaifBtcDepositLog::~CZaifBtcDepositLog(){
	Finalize();
}

void CZaifBtcDepositLog::Initialize(void){
	FClsBase::Initialize();
}

void CZaifBtcDepositLog::Finalize(void){
	FClsBase::Finalize();
}




//============================================================================================================
//	�U�C�t�̏o���������
CZaifBtcWithdrawLog::CZaifBtcWithdrawLog()
: FClsBase(this)
{
}

CZaifBtcWithdrawLog::CZaifBtcWithdrawLog(FCTradeLog* _pInst)
: FClsBase(_pInst)
{
}

CZaifBtcWithdrawLog::~CZaifBtcWithdrawLog()
{
	Finalize();
}

void CZaifBtcWithdrawLog::Initialize(void)
{
	FClsBase::Initialize();
}

void CZaifBtcWithdrawLog::Finalize(void)
{
	FClsBase::Finalize();
}





//============================================================================================================
//	�U�C�t�̎���������
CZaifTradeLog::CZaifTradeLog() 
: FClsBase(this)
{
}

CZaifTradeLog::CZaifTradeLog(FCTradeLog* _pInst)
: FClsBase(_pInst)
{
}


CZaifTradeLog::~CZaifTradeLog()
{
	Finalize();
}


void CZaifTradeLog::Initialize(void)
{
	FClsBase::Initialize();
}

void CZaifTradeLog::Finalize(void)
{
	FClsBase::Finalize();
}



//	
void CZaifTradeLog::Dump(void) 
{
	CTradeList* pExchange = this->GetTradeList(FCTradeItem::TradeTypeExchange);
	string stream;

	OutputDebugStringA("-----------------------------------------------\n");
	{//	���x���̏o��
		string label = "�}�[�P�b�g,������,���i,����,�萔��,���v��,�R�X�g,���ϊz,���v,����\n";
		stream += label;
		OutputDebugStringA( label.c_str() );
	}

	CTradeList::CIte IteTbl = pExchange->begin();
	for (; IteTbl != pExchange->end(); IteTbl++)
	{
		CTradeDate::CIte IteDate = IteTbl->second.begin();
		for (; IteDate != IteTbl->second.end(); IteDate++ )
		{
			CTradeArray::CIte IteAry = IteDate->second.begin();
			for (; IteAry != IteDate->second.end(); IteAry++)
			{
				const Sint32 dateValue = IteAry->GetDate();
				CSysData prmDateYear((dateValue / 10000) );			// �N
				CSysData prmDateMonth((dateValue % 10000) / 100 );	// ��
				CSysData prmDateDay((dateValue % 100));				// ��

				const Sint32 timeValue = IteAry->GetTime();
				CSysData prmTimeHour( (timeValue/10000));			// ��
				CSysData prmTimeMinutes((timeValue%10000)/100);		// ��
				CSysData prmTimeSecond((timeValue%100));			// �b

				CSysData prmPrice(IteAry->GetPrice());				// ������i
				CSysData prmAmount(IteAry->GetAmount());			// ����
				CSysData prmTransAmount(IteAry->GetTransAmount());	// �]������
				CSysData prmFee(IteAry->GetFee());					// �萔��
				CSysData prmCost(IteAry->GetCost());				// �R�X�g
				CSysData prmPayment(IteAry->GetPayment());			//���ϊz
				CSysData prmMargin(IteAry->GetMargin());			// ���v

				string line = "";

				line += IteAry->GetMarket();					//	�}�[�P�b�g
				line += ",";

				string typeTrade,typePayment;
				switch (IteAry->GetType()) {
					case FCTradeItem::TradeTypeBuy		: {	line += "����"; typeTrade = "+"; typePayment = "-"; }	break;
					case FCTradeItem::TradeTypeSell		: {	line += "����"; typeTrade = "-"; typePayment = "+"; }	break;
					case FCTradeItem::TradeTypeDeposit	: { line += "����"; typeTrade = "+"; typePayment = "-"; }	break;
					case FCTradeItem::TradeTypeWithdraw	: { line += "����"; typeTrade = "-"; typePayment = "+"; }	break;
				}
				line += ",";

				//	������i
				line += prmPrice.GetAsStr();
				line += ",";

				//	����
				line += typeTrade;
				line += prmAmount.GetAsStr();
				line += ",";

				//	�萔��
				line += typeTrade;
				line += prmFee.GetAsStr();
				line += ",";

				//	���v��
				line += typeTrade;
				line += prmTransAmount.GetAsStr();
				line += ",";

				//	�R�X�g
				line += prmCost.GetAsStr();
				line += ",";

				//	���ϊz
				line += typePayment;
				line += prmPayment.GetAsStr();
				line += ",";
				

				//	���v
				line += prmMargin.GetAsStr();
				line += ",";

				{//	�������
					line += prmDateYear.GetAsStr();
					line += "-";
					line += prmDateMonth.GetAsStr();
					line += "-";
					line += prmDateDay.GetAsStr();
					line += " ";

					line += prmTimeHour.GetAsStr();
					line += ":";
					line += prmTimeMinutes.GetAsStr();
					line += ":";
					line += prmTimeSecond.GetAsStr();
				}
				line += ",";

				line += "\n";
				OutputDebugStringA(line.c_str());

				stream += line;
			}
		}
	}

	{
		ofstream newStream("zaifLog.csv");
		if (!newStream.bad()) {
			newStream << stream;
			newStream.close();
		}
	}

	OutputDebugStringA( "-----------------------------------------------\n" );
}


//	CSV�e�[�u���𔃂�/����̃��X�g�ɃR���o�[�g����
void CZaifTradeLog::DoConvert(void)
{
	this->DoImportBtcWithdrawTable( FCTradeLogManager::GetInstance()->GetTradeLog("CZaifBtcWithdrawLog"));
	this->DoImportBtcDepositTable( FCTradeLogManager::GetInstance()->GetTradeLog("CZaifBtcDepositLog"));

	mTradeTable.Initialize();

	CSysIntMap typeTrade;
	typeTrade.AddParam(CHash::CRC32("����"), FCTradeItem::TradeTypeBuy);
	typeTrade.AddParam(CHash::CRC32("����"), FCTradeItem::TradeTypeSell);
	typeTrade.AddParam(CHash::CRC32("����"), FCTradeItem::TradeTypeDeposit);
	typeTrade.AddParam(CHash::CRC32("����"), FCTradeItem::TradeTypeWithdraw);

	//	��ʉ�
	CSysIntMap typeCurrency;
	typeCurrency.AddParam(CHash::CRC32("btc_jpy"), FCTradeItem::CurrencyTypeJpy);


	CTradeList* pTradeListAll = this->GetTradeList(FCTradeItem::TradeTypeAll );

	for (First(); !IsEof(); Next() ) 
	{
		//	�}�[�P�b�g���擾����
		const CSysData* pCurrencyType = this->GetParam("�}�[�P�b�g");
		const CSysData* pTradeType = this->GetParam("������");
		const CSysData* pPrice = this->GetParam("���i");
		const CSysData* pAmount = this->GetParam("����");
		const CSysData* pDate = this->GetParam("����");
		const CSysData* pFee = this->GetParam("����萔��");

		if (!pCurrencyType || !pTradeType || !pPrice || !pAmount || !pDate || !pFee )
		{
			continue;
		}

		const Sint32* pType = typeTrade.SearchParam(CHash::CRC32(pTradeType->GetAsStr()));
		if (!pType)
		{//	�T�|�[�g�����̎�����
			continue;
		}
		FCTradeItem::TradeType type = static_cast<FCTradeItem::TradeType>(*pType);
		CTradeList* pTradeList = this->GetTradeList(type);

		FCTradeItem newItem;
		newItem.SetType(type);
		newItem.SetMarket(pCurrencyType->GetAsStr());
		newItem.SetCurrency( static_cast<FCTradeItem::CurrencyType>( *typeCurrency.GetParam(CHash::CRC32(pCurrencyType->GetAsStr())) ) );

		newItem.SetPrice(pPrice->GetAsDbl());
		newItem.SetAmount(pAmount->GetAsDbl());
		newItem.SetDate(ConvertDate(pDate));
		newItem.SetTime(ConVertTime(pDate));
		newItem.SetFee(pFee->GetAsDbl());

		//	�����P�ʂ̎�����X�g���擾
		{
			CTradeDate* pDateList = pTradeList->GetParam(newItem.GetDate());

			CTradeArray* pTradeAry = pDateList->GetParam(newItem.GetTime());
			pTradeAry->AddParam(newItem);
		}
		{
			CTradeDate* pDateList = pTradeListAll->GetParam(newItem.GetDate());
			CTradeArray* pTradeAry = pDateList->GetParam(newItem.GetTime());
			pTradeAry->AddParam(newItem);
		}
	}

}



//	
bool CZaifTradeLog::DoCalclate(void)
{
	CTradeList* pTradeListAll = this->GetTradeList(FCTradeItem::TradeTypeAll);
	if (!pTradeListAll) {
		return false;
	}
	CTradeList* pExchange = this->GetTradeList(FCTradeItem::TradeTypeExchange);
	pExchange->Initialize();

	CTradeList::CIte IteAll = pTradeListAll->begin();
	for (; IteAll != pTradeListAll->end() ; IteAll++ )
	{
		//	�������������
		CTradeDate::CIte IteAllDate = IteAll->second.begin();
		for (; IteAllDate != IteAll->second.end(); IteAllDate++ )
		{
			CTradeDate* pExcDate = pExchange->GetParam(IteAll->first);

			CTradeArray::CIte IteAllAry = IteAllDate->second.begin();
			for (; IteAllAry != IteAllDate->second.end(); IteAllAry++ )
			{
				CTradeArray* pExcAry = pExcDate->GetParam(IteAllDate->first);

				//	���ԕʎ�����X�g���v�Z����
				switch (IteAllAry->GetType())
				{
					case FCTradeItem::TradeTypeBuy:
					{//	����
						IteAllAry->CalclatePayment();
						pExcAry->AddParam( *IteAllAry );
					}	break;

					case FCTradeItem::TradeTypeSell:
					{//	����
					 //	����̃L���[����������܂ŁA�����̃L���[��H���Ԃ�
						FCTradeItem* pSellQueue = &(*IteAllAry);
						while (0.0f < pSellQueue->GetAmount() )
						{
							CTradeList* pBuyList = this->GetTradeList( FCTradeItem::TradeTypeBuy );

							//	��ԌÂ��w���L���[���擾����
							CTradeList::CIte IteBuyDate = pBuyList->begin();
							if (IteBuyDate == pBuyList->end())
							{//	���Y�}�C�i�X�H
								break;
							}

							CTradeDate::CIte IteBuyTime = IteBuyDate->second.begin();
							if (IteBuyTime == IteBuyDate->second.end())
							{
								pBuyList->RemoveParam(IteBuyDate->first);
								continue;
							}

							CTradeArray::CIte IteExcAry = IteBuyTime->second.begin();
							if (IteExcAry == IteBuyTime->second.end()) 
							{
								IteBuyDate->second.RemoveParam(IteBuyTime->first);
								continue;
							}

							FCTradeItem buyQueue = *IteExcAry;
							FCTradeItem tradeQueue = *pSellQueue;

							//	���p�������v�Z
							double tradeAmount = 0.0f;
							const double sellAmount = tradeQueue.GetAmount();
							const double buyAmount = buyQueue.GetAmount();
							if (buyAmount < sellAmount)
							{//	�w�������Ȃ� = ���̃m�[�h�͏�������
								tradeAmount = buyAmount;
							}
							else
							{//	�w���������� = ���̃m�[�h�͎c������
								tradeAmount = sellAmount;
							}

							//	���p�L���[�̎c����ݒ�
							pSellQueue->SetAmount(sellAmount - tradeAmount);

							const double nextAmount = (buyAmount - sellAmount);
							if (nextAmount <= 0.0f) 
							{//	�w���m�[�h�폜
								IteBuyTime->second.RemoveParam(0);

								if (IteBuyTime->second.count() <= 0) 
								{//	�폜���ėv�f���Ȃ��Ȃ����̂ŁA�폜
									IteBuyDate->second.RemoveParam( IteBuyTime->first);

									if (IteBuyDate->second.count() <= 0) 
									{
										pBuyList->RemoveParam(IteBuyDate->first );
									}
								}
							}
							else
							{
								IteExcAry->SetAmount(nextAmount);
							}

							//	�w�������i��ݒ肷��
							const double sellPrice = tradeQueue.GetPrice() * tradeAmount;
							const double buyPrice = buyQueue.GetPrice() * tradeAmount;
							const double tradeMargin = (sellPrice - buyPrice);

							tradeQueue.SetAmount(tradeAmount);
							tradeQueue.SetCost(buyQueue.GetPrice());
							tradeQueue.SetMargin(tradeMargin);
							tradeQueue.SetPayment(sellPrice);

							pExcAry->AddParam( tradeQueue );
						}

					}	break;

					case FCTradeItem::TradeTypeWithdraw:
					{//	�������Fbuy���X�g����A�������X�g�ֈړ�����
						this->DoSwap(FCTradeItem::TradeTypeBuy, FCTradeItem::TradeTypePool, &(*IteAllAry) , pExcAry );
					}	break;

					case FCTradeItem::TradeTypeDeposit:
					{//	�������F�������X�g����Abuy���X�g�ֈړ�����
						this->DoSwap(FCTradeItem::TradeTypePool, FCTradeItem::TradeTypeBuy, &(*IteAllAry), pExcAry);
					}	break;


				}

			}

		}

	}

	return true;
}



bool CZaifTradeLog::DoSwap(const FCTradeItem::TradeType& _src, const FCTradeItem::TradeType& _dst, FCTradeItem* _pTrade, CTradeArray* _pAry)
{
	if (!_pTrade) {
		return false;
	}

	CTradeList* pSrcList = this->GetTradeList(_src);

	//	�]����̃��X�g���擾����
	CTradeList* pDstList = this->GetTradeList(_dst);
	CTradeDate* pDstDate = pDstList->GetParam(_pTrade->GetDate());
	CTradeArray* pExcAry = pDstDate->GetParam(_pTrade->GetTime());

	//	����̃L���[����������܂ŁA�����̃L���[��H���Ԃ�
	FCTradeItem* pSellQueue = _pTrade;
	double fee = _pTrade->GetFee();
	double transAmount = 0.0f;
	double preAmount = pSellQueue->GetAmount();
	while (0.0f < pSellQueue->GetAmount())
	{
		FCTradeItem tradeQueue = *pSellQueue;

		//	��ԌÂ��w���L���[���擾����
		CTradeList::CIte IteSrcDate = pSrcList->begin();
		if (IteSrcDate == pSrcList->end())
		{//	�o���������ƂȂ����ǁA����������
		//	��������Ȃǂ���̓���
			pExcAry->AddParam(*pSellQueue);
			_pAry->AddParam(*pSellQueue);
			break;
		}

		CTradeDate::CIte IteSrcTime = IteSrcDate->second.begin();
		if (IteSrcTime == IteSrcDate->second.end())
		{
			pSrcList->RemoveParam(IteSrcDate->first);
			continue;
		}

		CTradeArray::CIte IteExcAry = IteSrcTime->second.begin();
		if (IteExcAry == IteSrcTime->second.end())
		{
			IteSrcDate->second.RemoveParam(IteSrcTime->first);
			continue;
		}

		FCTradeItem buyQueue = *IteExcAry;

		//	���p�������v�Z
		double tradeAmount = 0.0f;
		const double sellAmount = tradeQueue.GetAmount();
		const double buyAmount = buyQueue.GetAmount();

		if (buyAmount < sellAmount)
		{//	�w�������Ȃ� = ���̃m�[�h�͏�������
			tradeAmount = buyAmount;
		}
		else
		{//	�w���������� = ���̃m�[�h�͎c������
			tradeAmount = sellAmount;
		}

		transAmount += (tradeAmount + fee);

		//	���p�L���[�̎c����ݒ�
		pSellQueue->SetAmount(sellAmount - tradeAmount);

		//	�w�������i��ݒ肷��
		const double sellPrice = tradeQueue.GetPrice() * tradeAmount;
		const double buyPrice = buyQueue.GetPrice() * tradeAmount;
		const double tradeMargin = 0;

		if (_dst == FCTradeItem::TradeTypeBuy)
		{//	�w�����X�g�ɖ߂��ꍇ
			CTradeDate* pTempDate = pDstList->GetParam(buyQueue.GetBuyDate());
			pExcAry = pTempDate->GetParam(buyQueue.GetBuyTime());
		}
		const double checkPrice = buyQueue.GetPrice();
		if (checkPrice <= 0.000000001f)
		{
			tradeQueue.SetPrice(buyQueue.GetPrice());
		}

		tradeQueue.SetPrice(buyQueue.GetPrice());
		tradeQueue.SetCost(buyQueue.GetPrice());
		tradeQueue.SetAmount(tradeAmount);
		tradeQueue.SetMargin(0);
		tradeQueue.SetFee(tradeQueue.GetFee());
		tradeQueue.SetBuyDate(buyQueue.GetDate());
		tradeQueue.SetBuyTime(buyQueue.GetTime());
		tradeQueue.SetTransAmount(transAmount);


		if (0.000000001f < pSellQueue->GetAmount())
		{//	�o��/�����̎���r���Ȃ̂ŁA�萔���Ȃ�
			tradeQueue.SetFee(0.0f);
			tradeQueue.SetTransAmount(0.0f);
		}

		//----------------------------------------------------------------------
		const double subAmount = (sellAmount + fee);
		const double nextAmount = (buyAmount - subAmount);
		if (nextAmount <= 0.000000001f)
		{//	�w���m�[�h�폜

			IteSrcTime->second.RemoveParam(0);

			if (IteSrcTime->second.count() <= 0)
			{//	�폜���ėv�f���Ȃ��Ȃ����̂ŁA�폜
				IteSrcDate->second.RemoveParam(IteSrcTime->first);

				if (IteSrcDate->second.count() <= 0)
				{
					pSrcList->RemoveParam(IteSrcDate->first);
				}
			}
		}
		else
		{
			IteExcAry->SetAmount(nextAmount);
		}

		pExcAry->AddParam(tradeQueue);
		if (_pAry) {
			_pAry->AddParam(tradeQueue);
		}
		fee = 0.0f;
	}

	return true;
}




//	�������O����荞��
bool CZaifTradeLog::DoImportBtcDepositTable(FCTradeLog* _pTbl)
{
//	����:2017-11-30 05:28:15.552586
//	TX: 0e35407b9e3d72e1d38daeef803db0cf31956656ac11290a9a9d471fc9b62530
//	���z : 0.00974589
	CSysData typeDeposit("����");

	for (_pTbl->First(); !_pTbl->IsEof(); _pTbl->Next())
	{
		const CSysData* pDate = _pTbl->GetParam("����");
		const CSysData* pPrice = _pTbl->GetParam("���z");

		if (!pDate || !pPrice) {
			continue;
		}

		if (this->CreateRecord())
		{
			this->SetParam("����", *pDate );
			this->SetParam("����", *pPrice);
			this->SetParam("������", typeDeposit );
		}
	}
	return true;
}


//	�o�����O����荞��
bool CZaifTradeLog::DoImportBtcWithdrawTable(FCTradeLog* _pTbl)
{
	//	����:2017-11-30 05:28:15.552586
	//	TX: 0e35407b9e3d72e1d38daeef803db0cf31956656ac11290a9a9d471fc9b62530
	//	���z : 0.00974589
	CSysData typeDeposit("����");

	for (_pTbl->First(); !_pTbl->IsEof(); _pTbl->Next())
	{
		const CSysData* pDate = _pTbl->GetParam("����");
		const CSysData* pPrice = _pTbl->GetParam("���z");
		const CSysData* pTxFee = _pTbl->GetParam("�萔��");

		if (!pDate || !pPrice || !pTxFee ){
			continue;
		}

		if (this->CreateRecord())
		{
			this->SetParam("����", *pDate);
			this->SetParam("����", *pPrice);
			this->SetParam("������", typeDeposit);
			this->SetParam("����萔��", *pTxFee );
		}
	}
	return true;
}

