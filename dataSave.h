#pragma once
#include "tileDataInfo.h"
#include <vector>


class dataSave
{
private:
	typedef vector<tagDataInfo>		      vItemInfo;
	typedef vector<tagDataInfo>::iterator viItemInfo;

	typedef vector<string>		     vString;
	typedef vector<string>::iterator viString;
private:




public:
	HRESULT init();

	void dataSet();
	void itemSet();
	void wallSet();

	void str2IntSave(vItemInfo saveVector, string fileName);
	void txtSave(string saveFileName, vector<string> vStr);
	int txtLoad(string loadFileName, int index, int data);

	void strcatAdd(vString& vStr, string inStr);


	dataSave();
	~dataSave();
};

