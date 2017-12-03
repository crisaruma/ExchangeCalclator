

#include "FCTradeLogZaif.h"

#include <iostream>
#include <fstream>
#include <Windows.h>





//	ザイフベース
CZaifBase::CZaifBase()
: FClsBase()
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




//	ザイフの取引履歴解析
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



//	
void CTradeLogZaif::Dump(void) 
{
	CTradeList* pExchange = this->GetTradeList(FCTradeItem::TradeTypeExchange);
	string stream;

	OutputDebugStringA("-----------------------------------------------\n");
	{//	ラベルの出力
		string label = "マーケット,取引種別,価格,数量,合計数,手数料,コスト,損益,日時\n";
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
				CSysData prmDateYear((dateValue / 10000) );			// 年
				CSysData prmDateMonth((dateValue % 10000) / 100 );	// 月
				CSysData prmDateDay((dateValue % 100));				// 日

				const Sint32 timeValue = IteAry->GetTime();
				CSysData prmTimeHour( (timeValue/10000));			// 時
				CSysData prmTimeMinutes((timeValue%10000)/100);		// 分
				CSysData prmTimeSecond((timeValue%100));			// 秒

				CSysData prmPrice(IteAry->GetPrice());				// 取引価格
				CSysData prmAmount(IteAry->GetAmount());			// 数量
				CSysData prmTransAmount(IteAry->GetTransAmount());	// 転送総数
				CSysData prmFee(IteAry->GetFee());					// 手数料
				CSysData prmCost(IteAry->GetCost());				// コスト
				CSysData prmMargin(IteAry->GetMargin());			// 損益

				string line = "";

				line += IteAry->GetMarket();					//	マーケット
				line += ",";

				switch (IteAry->GetType()) {
					case FCTradeItem::TradeTypeBuy		: {	line += "買い";}	break;
					case FCTradeItem::TradeTypeSell		: {	line += "売り";}	break;
					case FCTradeItem::TradeTypeDeposit	: { line += "入金";}	break;
					case FCTradeItem::TradeTypeWithdraw	: { line += "送金";}	break;
				}
				line += ",";

				//	取引価格
				line += prmPrice.GetAsStr();
				line += ",";

				//	数量
				line += prmAmount.GetAsStr();
				line += ",";

				//	合計数
				line += prmTransAmount.GetAsStr();
				line += ",";

				//	手数料
				line += prmFee.GetAsStr();
				line += ",";

				//	コスト
				line += prmCost.GetAsStr();
				line += ",";

				//	損益
				line += prmMargin.GetAsStr();
				line += ",";

				{//	取引日時
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


//	CSVテーブルを買い/売りのリストにコンバートする
void CTradeLogZaif::DoConvert(void)
{
	mTradeTable.Initialize();

	CSysIntMap typeTrade;
	typeTrade.AddParam(CHash::CRC32("買い"), FCTradeItem::TradeTypeBuy);
	typeTrade.AddParam(CHash::CRC32("売り"), FCTradeItem::TradeTypeSell);
	typeTrade.AddParam(CHash::CRC32("入金"), FCTradeItem::TradeTypeDeposit);
	typeTrade.AddParam(CHash::CRC32("送金"), FCTradeItem::TradeTypeWithdraw);

	//	基軸通貨
	CSysIntMap typeCurrency;
	typeCurrency.AddParam(CHash::CRC32("btc_jpy"), FCTradeItem::CurrencyTypeJpy);


	CTradeList* pTradeListAll = this->GetTradeList(FCTradeItem::TradeTypeAll );

	for (First(); !IsEof(); Next() ) 
	{
		//	マーケットを取得する
		const CSysData* pCurrencyType = this->GetParam("マーケット");
		const CSysData* pTradeType = this->GetParam("取引種別");
		const CSysData* pPrice = this->GetParam("価格");
		const CSysData* pAmount = this->GetParam("数量");
		const CSysData* pDate = this->GetParam("日時");
		const CSysData* pFee = this->GetParam("取引手数料");

		if (!pCurrencyType || !pTradeType || !pPrice || !pAmount || !pDate || !pFee )
		{
			continue;
		}

		const Sint32* pType = typeTrade.SearchParam(CHash::CRC32(pTradeType->GetAsStr()));
		if (!pType)
		{//	サポート買いの取引種別
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

		//	日時単位の取引リストを取得
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
		//	日時取引を処理
		CTradeDate::CIte IteAllDate = IteAll->second.begin();
		for (; IteAllDate != IteAll->second.end(); IteAllDate++ )
		{
			CTradeDate* pExcDate = pExchange->GetParam(IteAll->first);

			CTradeArray::CIte IteAllAry = IteAllDate->second.begin();
			for (; IteAllAry != IteAllDate->second.end(); IteAllAry++ )
			{
				CTradeArray* pExcAry = pExcDate->GetParam(IteAllDate->first);

				//	時間別取引リストを計算する
				switch (IteAllAry->GetType())
				{
					case FCTradeItem::TradeTypeBuy:
					{//	買い
						pExcAry->AddParam( *IteAllAry );
					}	break;

					case FCTradeItem::TradeTypeSell:
					{//	売り
					 //	売りのキューを消化するまで、買いのキューを食いつぶす
						FCTradeItem* pSellQueue = &(*IteAllAry);
						while (0.0f < pSellQueue->GetAmount() )
						{
							CTradeList* pBuyList = this->GetTradeList( FCTradeItem::TradeTypeBuy );

							//	一番古い購入キューを取得する
							CTradeList::CIte IteBuyDate = pBuyList->begin();
							if (IteBuyDate == pBuyList->end())
							{//	資産マイナス？
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

							//	売却差数を計算
							double tradeAmount = 0.0f;
							const double sellAmount = tradeQueue.GetAmount();
							const double buyAmount = buyQueue.GetAmount();
							if (buyAmount < sellAmount)
							{//	購入が少ない = このノードは処理完済
								tradeAmount = buyAmount;
							}
							else
							{//	購入数が多い = このノードは残留する
								tradeAmount = sellAmount;
							}

							//	売却キューの残数を設定
							pSellQueue->SetAmount(sellAmount - tradeAmount);

							const double nextAmount = (buyAmount - sellAmount);
							if (nextAmount <= 0.0f) 
							{//	購入ノード削除
								IteBuyTime->second.RemoveParam(0);

								if (IteBuyTime->second.count() <= 0) 
								{//	削除して要素がなくなったので、削除
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

							//	購入時価格を設定する
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
					{//	送金時：buyリストから、送金リストへ移動する
						this->DoSwap(FCTradeItem::TradeTypeBuy, FCTradeItem::TradeTypePool, &(*IteAllAry) , pExcAry );
					}	break;

					case FCTradeItem::TradeTypeDeposit:
					{//	入金時：送金リストから、buyリストへ移動する
						this->DoSwap(FCTradeItem::TradeTypePool, FCTradeItem::TradeTypeBuy, &(*IteAllAry), pExcAry);
					}	break;


				}

			}

		}

	}

	return true;
}



bool CTradeLogZaif::DoSwap(const FCTradeItem::TradeType& _src, const FCTradeItem::TradeType& _dst, FCTradeItem* _pTrade, CTradeArray* _pAry)
{
	if (!_pTrade) {
		return false;
	}

	CTradeList* pSrcList = this->GetTradeList(_src);

	//	転送先のリストを取得する
	CTradeList* pDstList = this->GetTradeList(_dst);
	CTradeDate* pDstDate = pDstList->GetParam(_pTrade->GetDate());
	CTradeArray* pExcAry = pDstDate->GetParam(_pTrade->GetTime());

	//	売りのキューを消化するまで、買いのキューを食いつぶす
	FCTradeItem* pSellQueue = _pTrade;
	double fee = _pTrade->GetFee();
	double transAmount = 0.0f;
	while (0.0f < pSellQueue->GetAmount())
	{

		//	一番古い購入キューを取得する
		CTradeList::CIte IteSrcDate = pSrcList->begin();
		if (IteSrcDate == pSrcList->end())
		{//	出金したことないけど、入金がある
		//	他取引所などからの入金
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
		FCTradeItem tradeQueue = *pSellQueue;

		//	売却差数を計算
		double tradeAmount = 0.0f;
		const double sellAmount = tradeQueue.GetAmount();
		const double buyAmount = buyQueue.GetAmount();

		if (buyAmount < sellAmount)
		{//	購入が少ない = このノードは処理完済
			tradeAmount = buyAmount;
		}
		else
		{//	購入数が多い = このノードは残留する
			tradeAmount = sellAmount;
		}

		transAmount += (tradeAmount + fee);

		//	売却キューの残数を設定
		pSellQueue->SetAmount(sellAmount - tradeAmount);

		//	購入時価格を設定する
		const double sellPrice = tradeQueue.GetPrice() * tradeAmount;
		const double buyPrice = buyQueue.GetPrice() * tradeAmount;
		const double tradeMargin = 0;

		if (_dst == FCTradeItem::TradeTypeBuy)
		{//	購入リストに戻す場合
			CTradeDate* pTempDate = pDstList->GetParam(buyQueue.GetBuyDate());
			pExcAry = pTempDate->GetParam(buyQueue.GetBuyTime());
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
		{//	出金/入金の取引途中なので、手数料なし
			tradeQueue.SetFee(0.0f);
			tradeQueue.SetTransAmount(0.0f);
		}

		//----------------------------------------------------------------------
		const double subAmount = (sellAmount + fee);
		const double nextAmount = (buyAmount - subAmount);
		if (nextAmount <= 0.000000001f)
		{//	購入ノード削除

			IteSrcTime->second.RemoveParam(0);

			if (IteSrcTime->second.count() <= 0)
			{//	削除して要素がなくなったので、削除
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









