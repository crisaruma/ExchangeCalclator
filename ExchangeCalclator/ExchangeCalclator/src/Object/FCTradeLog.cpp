

#include "FCTradeLog.h"



//====================================================================================
//	取引履歴解析用
//====================================================================================

//====================================================================================
//	トレード情報
FCTradeLog::FCTradeItem::FCTradeItem()
: mParam()
{
}

FCTradeLog::FCTradeItem::FCTradeItem(const CSysDataMap& _param)
: mParam(_param)
{
}


FCTradeLog::FCTradeItem::~FCTradeItem()
{
	Finalize();
}


void FCTradeLog::FCTradeItem::Initialize(void) 
{
	mParam.Initialize();
}

void FCTradeLog::FCTradeItem::Finalize(void) 
{
	mParam.Finalize();
}


//	
void FCTradeLog::FCTradeItem::SetParamAsStr(const Sint32& _hash, const char* _pStr, CSysDataMap* _pItem ) 
{
	CSysData* pType = NULL;
	if (_pItem) {
		pType = _pItem->GetParam(_hash);
	}
	else {
		pType = mParam.GetParam(_hash);
	}
	pType->SetAsStr(_pStr ? _pStr : "" );
}


const char* FCTradeLog::FCTradeItem::GetParamAsStr(const Sint32& _hash, const CSysDataMap* _pItem ) const 
{
	const CSysData* pType = NULL;
	if (_pItem) {
		pType = _pItem->GetParam(_hash);
	}
	else {
		pType = mParam.GetParam(_hash);
	}
	if (!pType) {
		return NULL;
	}
	return pType->GetAsStr();
}


//	
void FCTradeLog::FCTradeItem::SetParamAsInt(const Sint32& _hash, const Sint32& _param, CSysDataMap* _pItem )
{
	CSysData* pType = NULL;
	if (_pItem) {
		pType = _pItem->GetParam(_hash );
	}
	else {
		pType = mParam.GetParam(_hash );
	}
	pType->SetAsInt(_param);
}


//	
const Sint32 FCTradeLog::FCTradeItem::GetParamAsInt(const Sint32& _hash, const CSysDataMap* _pItem ) const 
{
	const CSysData* pType = NULL;
	if (_pItem) {
		pType = _pItem->GetParam(_hash);
	}
	else {
		pType = mParam.GetParam(_hash);
	}
	if (!pType) {
		return TradeTypeInvalid;
	}
	return pType->GetAsInt();
}

void FCTradeLog::FCTradeItem::SetParamAsDbl(const Sint32& _hash, const double& _param, CSysDataMap* _pItem ) 
{
	CSysData* pType = NULL;
	if (_pItem) {
		pType = _pItem->GetParam(_hash);
	}
	else {
		pType = mParam.GetParam(_hash);
	}
	pType->SetAsDbl(_param);
}

const double FCTradeLog::FCTradeItem::GetParamAsDbl(const Sint32& _hash, const CSysDataMap* _pItem ) const {
	const CSysData* pType = NULL;
	if (_pItem) {
		pType = _pItem->GetParam(_hash);
	}
	else {
		pType = mParam.GetParam(_hash);
	}
	if (!pType) {
		return TradeTypeInvalid;
	}
	return pType->GetAsDbl();
}


//	マーケット名の設定/取得
void FCTradeLog::FCTradeItem::SetMarket(const char* _pStr , CSysDataMap* _pItem ) 
{
	this->SetParamAsStr(this->TypeHash_Market(), _pStr, _pItem);
}

const char* FCTradeLog::FCTradeItem::GetMarket(const CSysDataMap* _pItem ) const
{
	return this->GetParamAsStr(this->TypeHash_Market(), _pItem);
}


//	トレードタイプの設定/取得
void FCTradeLog::FCTradeItem::SetType(const FCTradeLog::FCTradeItem::TradeType& _type, CSysDataMap* _pItem ){
	this->SetParamAsInt(this->TypeHash_Type(), _type, _pItem);
}

const FCTradeLog::FCTradeItem::TradeType FCTradeLog::FCTradeItem::GetType(const CSysDataMap* _pItem ) const{
	return static_cast<TradeType>(this->GetParamAsInt(this->TypeHash_Type(), _pItem) );
}


//	トレード通貨種別の設定/取得
void FCTradeLog::FCTradeItem::SetCurrency(const CurrencyType& _type, CSysDataMap* _pItem ) {
	this->SetParamAsInt(this->TypeHash_Currency(), _type, _pItem);
}

const FCTradeLog::FCTradeItem::CurrencyType FCTradeLog::FCTradeItem::GetCurrency(const CSysDataMap* _pItem ) const {
	return static_cast<CurrencyType>(this->GetParamAsInt(this->TypeHash_Currency(), _pItem));
}

//	トレード価格の設定/取得
void FCTradeLog::FCTradeItem::SetPrice(const double& _price, CSysDataMap* _pItem ) {
	this->SetParamAsDbl(this->TypeHash_Price(), _price, _pItem);
}

const double FCTradeLog::FCTradeItem::GetPrice(const CSysDataMap* _pItem ) const {
	return this->GetParamAsDbl(this->TypeHash_Price(), _pItem);
}

//	決済価格の設定/取得
void FCTradeLog::FCTradeItem::SetPayment(const double& _price, CSysDataMap* _pItem )
{
	this->SetParamAsDbl(this->TypeHash_PaymentPrice(), _price, _pItem);
}

const double FCTradeLog::FCTradeItem::GetPayment(const CSysDataMap* _pItem ) const 
{
	return this->GetParamAsDbl(this->TypeHash_PaymentPrice(), _pItem);
}


//	購入時の価格の設定/取得
void FCTradeLog::FCTradeItem::SetCost(const double& _price, CSysDataMap* _pItem ) 
{
	this->SetParamAsDbl(this->TypeHash_BuyPrice(), _price, _pItem);
}

const double FCTradeLog::FCTradeItem::GetCost(const CSysDataMap* _pItem ) const 
{
	return this->GetParamAsDbl(this->TypeHash_BuyPrice(), _pItem);
}

//	手数料
void FCTradeLog::FCTradeItem::SetFee(const double& _price, CSysDataMap* _pItem ) 
{
	this->SetParamAsDbl(this->TypeHash_Fee(), _price, _pItem);
}

const double FCTradeLog::FCTradeItem::GetFee(const CSysDataMap* _pItem) const
{
	return this->GetParamAsDbl(this->TypeHash_Fee(), _pItem);
}


//	トレード価格の設定/取得
void FCTradeLog::FCTradeItem::SetMargin(const double& _price, CSysDataMap* _pItem) {
	this->SetParamAsDbl(this->TypeHash_Margin(), _price, _pItem);
}

const double FCTradeLog::FCTradeItem::GetMargin(const CSysDataMap* _pItem ) const
{
	return this->GetParamAsDbl(this->TypeHash_Margin(), _pItem);
}


//	トレード数量の設定/取得
void FCTradeLog::FCTradeItem::SetAmount(const double& _amount, CSysDataMap* _pItem ) {
	this->SetParamAsDbl(this->TypeHash_Amount(), _amount, _pItem);
}


const double FCTradeLog::FCTradeItem::GetAmount(const CSysDataMap* _pItem ) const {
	return this->GetParamAsDbl(this->TypeHash_Amount(), _pItem);
}

//	転送量の総数の設定/取得
void FCTradeLog::FCTradeItem::SetTransAmount(const double& _amount, CSysDataMap* _pItem ){
	this->SetParamAsDbl(this->TypeHash_TransAmount(), _amount, _pItem);
}

const double FCTradeLog::FCTradeItem::GetTransAmount(const CSysDataMap* _pItem ) const
{
	return this->GetParamAsDbl(this->TypeHash_TransAmount(), _pItem);
}


//	トレード日の設定/取得
void FCTradeLog::FCTradeItem::SetDate(const Sint32& _date, CSysDataMap* _pItem )
{
	this->SetParamAsInt(this->TypeHash_Date(), _date, _pItem);
}

const Sint32 FCTradeLog::FCTradeItem::GetDate(const CSysDataMap* _pItem ) const
{
	return this->GetParamAsInt(this->TypeHash_Date(), _pItem);
}

//	トレード時間の設定/取得
void FCTradeLog::FCTradeItem::SetTime(const Sint32& _time, CSysDataMap* _pItem )
{
	this->SetParamAsInt(this->TypeHash_Time(), _time, _pItem);
}

const Sint32 FCTradeLog::FCTradeItem::GetTime(const CSysDataMap* _pItem ) const
{
	return this->GetParamAsInt(this->TypeHash_Time(), _pItem);
}

//	購入日の設定/取得
void FCTradeLog::FCTradeItem::SetBuyDate(const Sint32& _date, CSysDataMap* _pItem) {
	this->SetParamAsInt(this->TypeHash_BuyDate(), _date, _pItem);
}

const Sint32 FCTradeLog::FCTradeItem::GetBuyDate(const CSysDataMap* _pItem) const{
	return this->GetParamAsInt(this->TypeHash_BuyDate(), _pItem);
}

//	購入時間の設定/取得
void FCTradeLog::FCTradeItem::SetBuyTime(const Sint32& _time, CSysDataMap* _pItem ) {
	this->SetParamAsInt(this->TypeHash_BuyTime(), _time, _pItem);
}

const Sint32 FCTradeLog::FCTradeItem::GetBuyTime(const CSysDataMap* _pItem ) const{
	return this->GetParamAsInt(this->TypeHash_BuyTime(), _pItem);
}


//	決済額を計算する
void FCTradeLog::FCTradeItem::CalclatePayment(void)
{
	const double price = this->GetPrice();
	const double amount = this->GetAmount();
	const double paymentPrice = price * amount;
	this->SetPayment(paymentPrice);
}




//====================================================================================
//	トレードオブジェクト
FCTradeLog::FCTradeLog()
: FClsTable()
, mThis(this)
, mTradeTable()
{
}

FCTradeLog::FCTradeLog(FCTradeLog* _pInst)
: FClsTable()
, mThis(_pInst )
, mTradeTable()
{
}


FCTradeLog::~FCTradeLog()
{
	Finalize();
}


void FCTradeLog::Initialize(void)
{
	FClsTable::Initialize();
	mTradeTable.Initialize();
}



void FCTradeLog::Finalize(void)
{
	FClsTable::Finalize();
	mTradeTable.Finalize();
}

bool FCTradeLog::Destroy(void)
{
	if (mThis) {
		mThis->RemoveManager();
		delete mThis;
	}
	return true;
}



void FCTradeLog::RegistManager(void)
{
	FCTradeLogManager* pInst = FCTradeLogManager::GetInstance();
	if (!pInst)
	{
		pInst = FCTradeLogManager::Create();
	}
	pInst->Regist(this);
}


void FCTradeLog::RemoveManager(void)
{
	FCTradeLogManager* pInst = FCTradeLogManager::GetInstance();
	if (!pInst)
	{
		pInst = FCTradeLogManager::Create();
	}
	pInst->Remove(this);
}


//	CSVテーブルを買い/売りのリストにコンバートする
void FCTradeLog::DoConvert(void) {
}

bool FCTradeLog::DoCalclate(void) {
	return true;
}

bool FCTradeLog::DoSwap(const FCTradeItem::TradeType& _src, const FCTradeItem::TradeType& _dst, FCTradeItem* _pTrade, CTradeArray* _pAry)
{
	return true;
}


//
FCTradeLog::CTradeList* FCTradeLog::GetTradeList(const FCTradeItem::TradeType& _type)
{
	return mTradeTable.GetParam(_type);
}


//	
bool FCTradeLog::DoImportDepositTable(FCTradeLog* _pTbl)
{
	return true;
}

//	
bool FCTradeLog::DoImportWithdrawTable(FCTradeLog* _pTbl)
{
	return true;
}




//======================================================================
//	取引履歴マネージャー
//======================================================================
FCTradeLogManager* FCTradeLogManager::mInst = NULL;

FCTradeLogManager* FCTradeLogManager::Create(void)
{
	if (!mInst) {
		mInst = new FCTradeLogManager();
	}
	return mInst;
}


FCTradeLogManager* FCTradeLogManager::GetInstance(void) 
{
	return mInst;
}


FCTradeLogManager::FCTradeLogManager()
: mLogTable()
{
}


FCTradeLogManager::~FCTradeLogManager()
{
	Finalize();
}


void FCTradeLogManager::Initialize(void) 
{
	mLogTable.Initialize();
}


void FCTradeLogManager::Finalize(void) 
{
	this->Release();
}


//	マネージャーにオブジェクトを登録
bool FCTradeLogManager::Regist(FCTradeLog* _pInst)
{
	mLogTable.AddParam( _pInst->GetRegistID() , _pInst);
	return true;
}

//	
bool FCTradeLogManager::Remove(FCTradeLog* _pInst)
{
	mLogTable.RemoveParam(_pInst->GetRegistID());
	return true;
}

//	
bool FCTradeLogManager::Release(void)
{
	CLogTable::CIte IteTbl = mLogTable.begin();
	while (IteTbl != mLogTable.end()){
		IteTbl->second->Destroy();
		IteTbl = mLogTable.begin();
	}
	mLogTable.Finalize();
	return true;
}


//	登録済みのオブジェクト初期化
void FCTradeLogManager::DoInit(void)
{
	CLogTable::CIte IteLog = mLogTable.begin();
	for (; IteLog != mLogTable.end(); IteLog++) {
		IteLog->second->Initialize();
	}
}

//	
bool FCTradeLogManager::DoLoad( const CSysDataArray* _pAry )
{
	if (!_pAry) {
		return false;
	}
	CSysDataArray::CIteConst IteArg = _pAry->begin();
	if (IteArg == _pAry->end())
	{
		return false;
	}

	const char* pOptName = IteArg->GetAsStr();
	const Sint32 hashOptName = CHash::CRC32(pOptName);

	CLogTable::CIte IteLog = mLogTable.begin();
	for (; IteLog != mLogTable.end(); IteLog++ ) 
	{
		FCTradeLog* ppLog = IteLog->second;
		if (!ppLog) 
		{
			continue;
		}

		if (hashOptName == CHash::CRC32(ppLog->GetOptionWord() ))
		{//	オプション名が一致したので、ロード

			//	引数分ロードする
			IteArg++;
			for (; IteArg != _pAry->end(); IteArg++)
			{
				ppLog->LoadCsv(IteArg->GetAsStr());
			}
		}
	}

	this->DoDump();
	return true;
}


void FCTradeLogManager::DoConvert(void)
{
	CLogTable::CIte IteLog = mLogTable.begin();
	for (; IteLog != mLogTable.end(); IteLog++) 
	{
		IteLog->second->DoConvert();
	}
}


//	取引計算を行う
void FCTradeLogManager::DoCalclate(void)
{
	CLogTable::CIte IteLog = mLogTable.begin();
	for (; IteLog != mLogTable.end(); IteLog++)
	{
		IteLog->second->DoCalclate();
	}
}


//	
void FCTradeLogManager::DoDump(void) 
{
	CLogTable::CIte IteLog = mLogTable.begin();
	for (; IteLog != mLogTable.end(); IteLog++) 
	{
		IteLog->second->Dump();
	}
}


//	
FCTradeLog* FCTradeLogManager::GetTradeLog(const char* pName)
{
	const Sint32 hashRegistID = CHash::CRC32(pName);

	CLogTable::CIte IteLog = mLogTable.begin();
	for (; IteLog != mLogTable.end(); IteLog++ ){
		if (hashRegistID == IteLog->second->GetRegistID()){
			return IteLog->second;
		}
	}
	return NULL;
}
