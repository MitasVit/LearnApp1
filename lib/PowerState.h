#pragma once
#include <iostream>
#include <stdlib.h>
#include <Windows.h>

enum PowerState
{
	POWERSTATE_UNKNOWN,
	POWERSTATE_ON_BATTERY,
	POWERSTATE_NO_BATTERY,
	POWERSTATE_CHARGING,
	POWERSTATE_CHARGED
};

std::string PowerStateToString(PowerState state)
{
	switch (state)
	{
	case POWERSTATE_UNKNOWN:
		return std::string("Unknown");
		break;
	case POWERSTATE_NO_BATTERY:
		return std::string("No Battery");
		break;
	case POWERSTATE_CHARGED:
		return std::string("Charged");
		break;
	case POWERSTATE_CHARGING:
		return std::string("Charging");
		break;
	case POWERSTATE_ON_BATTERY:
		return std::string("On Battery");
		break;
	default:
		return std::string("Error");
		break;
	}
}

class WindowsPower
{
public:
	WindowsPower();
	virtual ~WindowsPower();

	PowerState GetPowerState();
	int GetPowerSecondsLeft();
	int GetPowerPercentageLeft();

private:
	int m_NumberSecondsLeft;
	int m_PercentageLeft;
	PowerState m_PowerState;

	bool GetPowerInfo_Windows(/*PowerState * state, int *seconds, int *percent*/);
	bool UpdatePowerInfo();
};

WindowsPower::WindowsPower() :
	m_NumberSecondsLeft(-1),
	m_PercentageLeft(-1),
	m_PowerState(POWERSTATE_UNKNOWN)
{
}

WindowsPower::~WindowsPower()
{
}

bool WindowsPower::GetPowerInfo_Windows()
{
	SYSTEM_POWER_STATUS status;
	bool needDetails = FALSE;

	/* This API should exist back to Win95. */
	if (!GetSystemPowerStatus(&status)) {
		/* !!! FIXME: push GetLastError() into GetError() */
		m_PowerState = POWERSTATE_UNKNOWN;
	}
	else if (status.BatteryFlag == 0xFF) { /* unknown state */
		m_PowerState = POWERSTATE_UNKNOWN;
	}
	else if (status.BatteryFlag & (1 << 7)) { /* no battery */
		m_PowerState = POWERSTATE_NO_BATTERY;
	}
	else if (status.BatteryFlag & (1 << 3)) { /* charging */
		m_PowerState = POWERSTATE_CHARGING;
		needDetails = TRUE;
	}
	else if (status.ACLineStatus == 1) {
		m_PowerState = POWERSTATE_CHARGED; /* on AC, not charging. */
		needDetails = TRUE;
	}
	else {
		m_PowerState = POWERSTATE_ON_BATTERY; /* not on AC. */
		needDetails = TRUE;
	}

	m_PercentageLeft = -1;
	m_NumberSecondsLeft = -1;
	if (needDetails)
	{
		const int pct = (int)status.BatteryLifePercent;
		const int secs = (int)status.BatteryLifeTime;

		if (pct != 255) { /* 255 == unknown */
			m_PercentageLeft = (pct > 100) ? 100 : pct; /* clamp between 0%, 100% */
		}
		if (secs != (int)0xFFFFFFFF) { /* ((DWORD)-1) == unknown */
			m_NumberSecondsLeft = secs;
		}
	}

	return TRUE; /* always the definitive answer on Windows. */
}

bool WindowsPower::UpdatePowerInfo()
{
	if (GetPowerInfo_Windows())
	{
		return true;
	}
	return false;
}

PowerState WindowsPower::GetPowerState()
{
	if (UpdatePowerInfo())
	{
		return m_PowerState;
	}
	else
	{
		return POWERSTATE_UNKNOWN;
	}
}

int WindowsPower::GetPowerSecondsLeft()
{
	if (UpdatePowerInfo())
	{
		return m_NumberSecondsLeft;
	}
	else
	{
		return -1;
	}
}

int WindowsPower::GetPowerPercentageLeft()
{
	if (UpdatePowerInfo())
	{
		return m_PercentageLeft;
	}
	else
	{
		return -1;
	}
}
