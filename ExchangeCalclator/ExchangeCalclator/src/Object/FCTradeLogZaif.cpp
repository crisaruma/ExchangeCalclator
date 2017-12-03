

#include "FCTradeLogZaif.h"

#include <iostream>
#include <fstream>
#include <Windows.h>



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

const Sint32 CTradeLogZaif::ConvertDate(const CSysData* _pDateTime)
{
	if (!_pDateTime) {
		return 0;
	}
	string dateTime = _pDateTime->GetAsStr();

	CSysDataMap result;
	CStr::Split( result, dateTime, " ");

	CSysDataMap::CIte IteDate = result.begin();
	if( IteDate == result.end() )
	{
		return 0;
	}
	CSysDataMap retDate;
	CStr::Split(retDate, IteDate->second.GetAsStr() , "-" );

	string dateName = "";
	CSysDataMap::CIte IteDatePrm = retDate.begin();
	for (; IteDatePrm != retDate.end(); IteDatePrm++ )
	{
		dateName += IteDatePrm->second.GetAsStr();
	}
	CSysData resultParam(dateName.c_str());
	return resultParam.GetAsInt();
}

const Sint32 CTradeLogZaif::ConVertTime(const CSysData* _pDateTime)
{
	if (!_pDateTime) {
		return 0;
	}
	string dateTime = _pDateTime->GetAsStr();

	CSysDataMap result;
	CStr::Split(result, dateTime, " ");

	CSysDataMap::CIte IteDate = result.begin();
	if (IteDate == result.end()){return 0;}
	IteDate++;
	if (IteDate == result.end()){return 0;}

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


//	
void CTradeLogZaif::Dump(void) 
{
	CTradeList* pExchange = this->GetTradeList(FCTradeItem::TradeTypeExchange);
	string stream;

	OutputDebugStringA("-----------------------------------------------\n");
	{//	���x���̏o��
		string label = "�}�[�P�b�g,������,���i,����,�萔��,�R�X�g,���v,����\n";
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
				CSysData prmDate(IteAry->GetDate());	// ��
				CSysData prmTime(IteAry->GetTime());	// ��
				CSysData prmPrice(IteAry->GetPrice());	// ������i
				CSysData prmAmount(IteAry->GetAmount());// ����
				CSysData prmFee(IteAry->GetFee());		//�萔��
				CSysData prmCost(IteAry->GetCost());	// �R�X�g
				CSysData prmMargin(IteAry->GetMargin());// ���v

				string line = "";

				line += IteAry->GetMarket();					//	�}�[�P�b�g
				line += ",";

				switch (IteAry->GetType()) {
					case FCTradeItem::TradeTypeBuy		: {	line += "����";}	break;
					case FCTradeItem::TradeTypeSell		: {	line += "����";}	break;
					case FCTradeItem::TradeTypeDeposit	: { line += "����";}	break;
					case FCTradeItem::TradeTypeWithdraw	: { line += "����";}	break;
				}
				line += ",";

				//	������i
				line += prmPrice.GetAsStr();
				line += ",";

				//	����
				line += prmAmount.GetAsStr();
				line += ",";

				//	�萔��
				line += prmFee.GetAsStr();
				line += ",";

				//	�R�X�g
				line += prmCost.GetAsStr();
				line += ",";

				//	���v
				line += prmMargin.GetAsStr();
				line += ",";

				//	�������
				line += prmDate.GetAsStr();
				line += "-";
				line += prmTime.GetAsStr();
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
void CTradeLogZaif::DoConvert(void)
{
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
bool CTradeLogZaif::DoCalclate(void)
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
						pExcAry->AddParam( *IteAllAry );
					}	break;

					case FCTradeItem::TradeTypeSell:
					{//	����
					 //	����̃L���[����������܂ŁA�����̃L���[��H���Ԃ�
						FCTradeItem* pSellQueue = &(*IteAllAry);
						while (0.0f < pSellQueue->GetAmount() )
						{
							CTradeList* pBuyList = this->GetTradeList(IteAllAry->GetType() );

							//	��ԌÂ��w���L���[���擾����
							CTradeList::CIte IteBuyDate = pBuyList->begin();
							if (IteBuyDate == pBuyList->end())
							{//	���Y�}�C�i�X�H
								break;
							}

							CTradeDate::CIte IteBuyTime = IteBuyDate->second.begin();
							if (IteBuyTime == IteBuyDate->second.end())
							{
								break;
							}

							CTradeArray::CIte IteExcAry = IteBuyTime->second.begin();
							if (IteExcAry == IteBuyTime->second.end()) 
							{
								break;
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

							pExcAry->AddParam( tradeQueue );
						}

					}	break;

					case FCTradeItem::TradeTypeWithdraw:
					{//	�������Fbuy���X�g����A�������X�g�ֈړ�����

					}	break;

					case FCTradeItem::TradeTypeDeposit:
					{//	�������F�������X�g����Abuy���X�g�ֈړ�����
					}	break;


				}

			}

		}

	}

	return true;
}
