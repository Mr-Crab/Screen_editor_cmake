#pragma once

#include <QString>

class ButtonInfo
{
public:
	QString m_buttonName;
	QString m_pageName;
	QString m_message;
	int m_posX;
	int m_posY;
	int m_width;
	int m_height;

	ButtonInfo()
	{
		m_buttonName = "";
		m_pageName = "";
		m_message = "";
		m_posX = 0;
		m_posY = 0;
		m_width = 0;
		m_height = 0;
	}

	ButtonInfo(ButtonInfo* info)
	{
		m_buttonName = info->m_buttonName;
		m_pageName = info->m_pageName;
		m_message = info->m_message;
		m_posX = info->m_posX;
		m_posY = info->m_posY;
		m_width = info->m_width;
		m_height = info->m_height;
	}

	void copeInfo(ButtonInfo* info)
	{
		m_buttonName = info->m_buttonName;
		m_pageName = info->m_pageName;
		m_message = info->m_message;
		m_posX = info->m_posX;
		m_posY = info->m_posY;
		m_width = info->m_width;
		m_height = info->m_height;
	}
};

enum ButtonType
{
	CREATE = 0,
	CHANGE,
};

enum sourceType
{
	ENTITY = 0,
	NODE,
	TITLE_H,
	PROP,
};