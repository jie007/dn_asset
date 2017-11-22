#include "EquipSuit.h"

EquipSuit::EquipSuit(void)
{
	name = UNITY_STREAM_PATH + "Table/EquipSuit.bytes";
}

void EquipSuit::ReadTable()
{
	LOG("read:"+name);
	Open(name.c_str());
	long long filesize =0;
	int lineCnt = 0;
	Read(&filesize);
	Read(&lineCnt);
	m_data.clear();
	for(int i=0;i<lineCnt;i++)
	{
		EquipSuitRow *row = new EquipSuitRow();
		Read(&(row->suitid));
		ReadString(row->suitname);
		Read(&(row->level));
		Read(&(row->profid));
		Read(&(row->suitquality));
		Read(&(row->iscreate));
		ReadArray(row->euipid);
		ReadString(row->effect1);
		ReadString(row->effect2);
		ReadString(row->effect3);
		ReadString(row->effect4);
		ReadString(row->effect5);
		ReadString(row->effect6);
		ReadString(row->effect7);
		ReadString(row->effect8);
		ReadString(row->effect9);
		ReadString(row->effect10);
		Read(&(row->sortid));
		LOG("read vlue:"+tostring(row->suitid));
		m_data.push_back(*row);
	}
	this->Close();
}

void EquipSuit::GetRow(int id,EquipSuitRow* row)
{
	size_t len = m_data.size();
	for(size_t i=0;i<len;i++)
	{
		if(m_data[i].suitid==id)
		{
			*row = m_data[i];
		}
	}
}


extern "C"
{
	EquipSuit *equipsuit;

	void  iReadEquipSuitList()
	{
		if(equipsuit==NULL)
		{
			equipsuit = new EquipSuit();
		}
		equipsuit->ReadTable();
	}

	void iGetEquipSuitRow(int suitid,EquipSuitRow* row)
	{
		if(equipsuit) equipsuit->GetRow(suitid,row);
	}
}