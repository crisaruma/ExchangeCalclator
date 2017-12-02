

#include "FCTradeLog.h"



//	取引履歴解析用
FCTradeLog* FCTradeLog::Create(void) {
	return new FCTradeLog();
}


FCTradeLog::FCTradeLog()
: FClsTable()
, mThis(this)
{
	mThis->RegistManager();
}


FCTradeLog::~FCTradeLog()
{
	mThis->RemoveManager();
	Finalize();
}


void FCTradeLog::Initialize(void)
{
	FClsTable::Initialize();
}



void FCTradeLog::Finalize(void)
{
	FClsTable::Finalize();
	if (mThis) {
		delete mThis;
	}
	mThis = NULL;
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
	mLogTable.Finalize();
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
	return true;
}



//	
void FCTradeLogManager::DoDump(void) 
{
	CLogTable::CIte IteLog = mLogTable.begin();
	for (; IteLog != mLogTable.end(); IteLog++) {
		IteLog->second->Dump();
	}
}
