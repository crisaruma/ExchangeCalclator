

#ifndef __FC_TRADE_LOG_H__
#define __FC_TRADE_LOG_H__


#include "../System/CSysTable.h"


//	取引履歴解析用
class FCTradeLog : public CSysTable
{
public:
	typedef CSysTable	FClsTable;

	//	トレード情報
	class FCTradeItem
	{
		public:
			enum TradeType {
				TradeTypeInvalid = 0	,
				TradeTypeAll			,
				TradeTypeBuy			,
				TradeTypeSell			,
				TradeTypeDeposit		,
				TradeTypeWithdraw		,
				TradeTypeExchange		,
			};

			enum CurrencyType {
				CurrencyTypeInvalid = 0,
				CurrencyTypeJpy ,
				CurrencyTypeBtc ,
				CurrencyTypeAlt ,
			};

		protected:
			CSysDataMap	mParam;

		public:
			FCTradeItem();
			FCTradeItem(const CSysDataMap& _param);
			~FCTradeItem();

			void Initialize(void);
			void Finalize(void);

			inline const Sint32 TypeHash_Type(void) const { return CHash::CRC32("Type"); }
			inline const Sint32 TypeHash_Currency(void) const { return CHash::CRC32("Currency"); }
			inline const Sint32 TypeHash_Price(void) const { return CHash::CRC32("Price"); }
			inline const Sint32 TypeHash_Amount(void) const { return CHash::CRC32("Amount"); }
			inline const Sint32 TypeHash_Date(void) const { return CHash::CRC32("Date"); }
			inline const Sint32 TypeHash_Time(void) const { return CHash::CRC32("Time"); }
			inline const Sint32 TypeHash_BuyPrice(void) const { return CHash::CRC32("CostPrice"); }	// 購入時価格
			inline const Sint32 TypeHash_Margin(void) const { return CHash::CRC32("Margin"); }		// 取引差益
			inline const Sint32 TypeHash_Market(void) const { return CHash::CRC32("Market"); }
			inline const Sint32 TypeHash_Fee(void) const { return CHash::CRC32("Fee"); }

			void SetParamAsStr(const Sint32& _hash, const char* _pStr , CSysDataMap* _pItem = NULL);
			const char* GetParamAsStr(const Sint32& _hash, const CSysDataMap* _pItem = NULL) const;

			void SetParamAsInt(const Sint32& _hash , const Sint32& _param , CSysDataMap* _pItem = NULL);
			const Sint32 GetParamAsInt(const Sint32& _hash, const CSysDataMap* _pItem = NULL) const ;

			void SetParamAsDbl(const Sint32& _hash, const double& _param, CSysDataMap* _pItem = NULL);
			const double GetParamAsDbl(const Sint32& _hash, const CSysDataMap* _pItem = NULL) const;

			//	マーケット名の設定/取得
			void SetMarket(const char* _pStr , CSysDataMap* _pItem = NULL);
			const char* GetMarket(const CSysDataMap* _pItem = NULL) const;

			//	トレード種別の設定/取得
			void SetType(const TradeType& _type, CSysDataMap* _pItem = NULL);
			const TradeType GetType(const CSysDataMap* _pItem = NULL) const ;

			//	トレード通貨種別の設定/取得
			void SetCurrency(const CurrencyType& _type, CSysDataMap* _pItem = NULL);
			const CurrencyType GetCurrency(const CSysDataMap* _pItem = NULL) const;

			//	トレード価格の設定/取得
			void SetPrice(const double& _price, CSysDataMap* _pItem = NULL);
			const double GetPrice(const CSysDataMap* _pItem = NULL) const ;

			//	購入時の価格の設定/取得
			void SetCost(const double& _price, CSysDataMap* _pItem = NULL);
			const double GetCost(const CSysDataMap* _pItem = NULL) const;

			//	手数料
			void SetFee(const double& _price, CSysDataMap* _pItem = NULL);
			const double GetFee(const CSysDataMap* _pItem = NULL) const;

			//	トレード価格の設定/取得
			void SetMargin(const double& _price, CSysDataMap* _pItem = NULL);
			const double GetMargin(const CSysDataMap* _pItem = NULL) const;

			//	トレード数量の設定/取得
			void SetAmount(const double& _amount , CSysDataMap* _pItem = NULL);
			const double GetAmount(const CSysDataMap* _pItem = NULL) const;

			//	トレード日の設定/取得
			void SetDate(const Sint32& _date, CSysDataMap* _pItem = NULL);
			const Sint32 GetDate(const CSysDataMap* _pItem = NULL) const;

			//	トレード時間の設定/取得
			void SetTime(const Sint32& _time, CSysDataMap* _pItem = NULL);
			const Sint32 GetTime(const CSysDataMap* _pItem = NULL) const;


	};

	typedef CSysArray<FCTradeItem>						CTradeArray;
	typedef CSysMap<Sint32, CTradeArray>				CTradeDate;	//	時間単位の昇順リスト
	typedef CSysMap<Sint32, CTradeDate>					CTradeList;	//	日時単位の昇順リスト
	typedef CSysMap<FCTradeItem::TradeType, CTradeList>	CTradeTable;//	


protected:
	FCTradeLog*	mThis;
	CTradeTable	mTradeTable;

public:
	static FCTradeLog* Create(void);

	FCTradeLog();
	~FCTradeLog();

	virtual void Initialize(void);
	virtual void Finalize(void);
	virtual bool Destroy(void);

	virtual const char* GetOptionWord(void) { return "-sample";}
	virtual const char* GetRegistKey(void) { return "Sample";  }
	virtual const Sint32 GetRegistID(void) { return CHash::CRC32( GetRegistKey() ); }

	virtual void RegistManager(void);
	virtual void RemoveManager(void);

	//	日時パラメータの返還
	virtual const Sint32 ConvertDate(const CSysData* _pDateTime) { return 0; }
	virtual const Sint32 ConVertTime(const CSysData* _pDateTime) { return 0; }

	//	CSVテーブルを買い/売りのリストにコンバートする
	virtual void DoConvert(void);
	virtual bool DoCalclate(void);
	virtual bool DoSwap(void);

	virtual CTradeList* GetTradeList(const FCTradeItem::TradeType& _type);

};




//	取引履歴マネージャー
class FCTradeLogManager
{
public:
	typedef CSysMap<Sint32, FCTradeLog*>	CLogTable;

protected:
	static FCTradeLogManager* mInst;
	CLogTable	mLogTable;

public:
	static FCTradeLogManager* Create(void);
	static FCTradeLogManager* GetInstance(void);

	FCTradeLogManager();
	virtual ~FCTradeLogManager();

	virtual void Initialize(void);
	virtual void Finalize(void);

	virtual bool Regist(FCTradeLog* _pInst);
	virtual bool Remove(FCTradeLog* _pInst);
	virtual bool Release(void);

	virtual void DoInit(void);
	virtual bool DoLoad(const CSysDataArray* _pAry);

	virtual void DoConvert(void);
	virtual void DoCalclate(void);

	virtual void DoDump(void);

};



#endif