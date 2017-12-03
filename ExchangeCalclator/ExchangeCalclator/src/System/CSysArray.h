

#ifndef __CSYS_ARRAY_H__
#define __CSYS_ARRAY_H__

#include "type.h"
#include <stdlib.h>
#include <vector>
#include <map>
#include <string>

using namespace std;

//	リスト要素
template <typename _T>
class CSysArray
{
public:
	typedef std::vector<_T> CArray;

	typedef typename std::vector<_T>::iterator					CIte;
	typedef typename std::vector<_T>::const_iterator			CIteConst;

	typedef typename std::vector<_T>::reverse_iterator			CReIte;
//	typedef typename std::vector<_T>::reverse_const_iterator	CReIteConst;

protected:
	CArray	mArray;

public:

	CSysArray() : mArray()
	{
	}

	~CSysArray(){
		Finalize();
	}

	void Initialize(void){
		mArray = CArray();
	}

	void Finalize(void) {
		mArray = CArray();
	}

	//	要素の設定
	bool set(const Sint32& _index, const _T& _val)
	{
		if (mArray.size() <= _index) 
		{
			return false;
		}
		CIte request = mArray.begin() + _index;
		*request = _val;
		return true;
	}

	//	要素の取得
	CIte get(const Sint32& _index) {
		if (mArray.size() <= _index){
			return mArray.end();
		}
		return mArray.begin() + _index;
	}

	//	先頭からアクセス
	CIte begin(void) { return mArray.begin();  }
	CIteConst begin(void) const { return mArray.cbegin(); }

	CIte end(void) { return mArray.end(); }
	CIteConst end(void) const { return mArray.cend(); }

	//	最後尾からアクセス
	CReIte rbegin(void) { return mArray.rbegin(); }
//	CReIteConst rbegin(void) const { return mArray.rbegin(); }

	CReIte rend(void) { return mArray.rend(); }
//	CReIteConst rend(void) const { return mArray.rend(); }

	const Sint32 count(void) { return mArray.size(); }

	//
	void AddParam(const _T& _val){
		mArray.push_back(_val);
	}

	//	値を取得する
	const _T GetParam(const Sint32& _index) {
		CIte result = this->get(_index);
		if (result == mArray.end()) 
		{
			_T newParam();
			return newParam;
		}
		return *result;
	}

	bool SetParam(const Sint32& _index, const _T& _val){
		return this->set(_index, _val);
	}

	void RemoveParam(const Sint32 _index) {
		mArray.erase(mArray.begin() + _index);
	}

};



typedef CSysArray<Sint32>	CIntArray;
typedef CSysArray<float>	CFltArray;
typedef CSysArray<string>	CStrArray;




//	マップテンプレート
template <typename _KeyT , typename _ValT >
class CSysMap
{
public:
	typedef std::map<_KeyT, _ValT>					CMap;
	typedef typename std::map<_KeyT, _ValT>::iterator		CIte;
	typedef typename std::map<_KeyT, _ValT>::const_iterator	CIteConst;
	typedef typename std::map<_KeyT, _ValT>::value_type		CIteType;


protected:
	CMap	mMap;

public:

	CSysMap()
	: mMap()
	{
	}

	CSysMap(const _KeyT& _key, const _ValT& _val) 
	: mMap()
	{
		AppendParam(_key, _val);
	}

	~CSysMap()
	{
	}

	void Initialize(void) {
		mMap = CMap();
	}

	void Finalize(void) {
		mMap = CMap();
	}

	//	検索
	CIte find(const _KeyT& _key) { return mMap.find(_key); }
	CIteConst find(const _KeyT& _key) const { return mMap.find(_key); }

	//	先頭
	CIte begin(void) { return mMap.begin(); }
	CIteConst begin(void) const { return mMap.begin(); }

	CIte end(void) { return mMap.end(); }
	CIteConst end(void) const { return mMap.end(); }

	const Sint32 count(void) { return mMap.size(); }

	_ValT* AddParam(const _KeyT& _key, const _ValT& _val)
	{
		mMap.insert(CIteType(_key, _val));
		return SearchParam(_key);
	}

	void SetParam(const _KeyT& _key, const _ValT& _val)
	{
		CIte Ite = find(_key);
		if (Ite == end()) {
			AddParam(_key, _val);
		}
		else {
			Ite->second = _val;
		}
	}

	_ValT* GetParam(const _KeyT& _key) {
		_ValT* pRet = SearchParam(_key);
		if (pRet) {
			return pRet;
		}
		return AddParam(_key, _ValT());
	}

	const _ValT* GetParam(const _KeyT& _key) const {
		const _ValT* pRet = SearchParam(_key);
		if (pRet) {
			return pRet;
		}
		return NULL;
	}

	_ValT* SearchParam(const _KeyT& _key) {
		CIte Ite = find(_key);
		if (Ite == end()) {
			return NULL;
		}
		return &(Ite->second);
	}

	const _ValT* SearchParam(const _KeyT& _key) const {
		CIteConst Ite = find(_key);
		if (Ite == end()) {
			return NULL;
		}
		return &(Ite->second);
	}

	const bool RemoveParam(const _KeyT& _key)
	{
		CIte Ite = find(_key);
		if (Ite != end()) {
			mMap.erase(Ite);
			return true;
		}
		return false;
	}

};


//	
typedef CSysMap<Sint32, Sint32>	CSysIntMap;




#endif