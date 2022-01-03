#include "ZiboB738.h"
#include "logger.h"


ZiboB738::ZiboB738()
	: LaminarB738()
{
	m_refApDisplayedSpeed = XPLMFindDataRef("laminar/B738/autopilot/mcp_speed_dial_kts_mach");
	m_refApDisplayedAltitude = XPLMFindDataRef("laminar/B738/autopilot/mcp_alt_dial");

	// Steal right-hand TOGA button to use as the Mach c/o button
	m_refAptToGa2 = findCommandRef("sim/autopilot/knots_mach_toggle");

	m_refHdgNNNup = findCommandRef("laminar/B738/autopilot/heading_up");
	m_refHdgNNNdn = findCommandRef("laminar/B738/autopilot/heading_dn");

	m_refEfisModeDown = findCommandRef("laminar/B738/EFIS_control/capt/map_mode_dn");
	m_refEfisModeUp = findCommandRef("laminar/B738/EFIS_control/capt/map_mode_up");

	m_refEfisZoomIn = findCommandRef("laminar/B738/EFIS_control/capt/map_range_dn");
	m_refEfisZoomOut = findCommandRef("laminar/B738/EFIS_control/capt/map_range_up");

	m_refEfisMinsUp   = findCommandRef("laminar/B738/pfd/dh_pilot_up");
	m_refEfisMinsDown = findCommandRef("laminar/B738/pfd/dh_pilot_dn");
	m_refEfisBaroUp   = findCommandRef("laminar/B738/pilot/barometer_up");
	m_refEfisBaroDown = findCommandRef("laminar/B738/pilot/barometer_down");

	m_refObsUp = findCommandRef("laminar/B738/autopilot/course_pilot_up");
	m_refObsDown = findCommandRef("laminar/B738/autopilot/course_pilot_dn");
}

bool ZiboB738::isLoaded()
{
	return (XPLMFindDataRef("laminar/B738/irs_left1") != nullptr);
}

#define COMMAND(a) case BaseDeviceHandler::##a: scheduleCommand(m_ref##a); return true;

bool ZiboB738::handleCommand(BaseDeviceHandler::VriCommandParameters command)
{
	switch (command.m_command)
	{

		COMMAND(HdgNNNup);
		COMMAND(HdgNNNdn);

	default:
		return LaminarB738::handleCommand(command);
	}
}