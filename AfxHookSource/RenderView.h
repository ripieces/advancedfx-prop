#pragma once

// Copyright (c) advancedfx.org
//
// Last changes:
// 2014-04-30 by dominik.matrixstorm.com
//
// First changes:
// 2009-11-01 by dominik.matrixstorm.com


#include "WrpGlobals.h"
#include <shared/CamPath.h>

class Hook_VClient_RenderView;

// global singelton instance:
extern Hook_VClient_RenderView g_Hook_VClient_RenderView;


// Hook_VClient_RenderView /////////////////////////////////////////////////////

class Hook_VClient_RenderView
{
public:
	CamPath m_CamPath;
	double LastCameraOrigin[3];
	double LastCameraAngles[3];

	Hook_VClient_RenderView();
	~Hook_VClient_RenderView();

	bool ExportBegin(wchar_t const *fileName, float frameTime);
	void ExportEnd();

	float GetCurTime();

	float GetImportBasteTime();

	bool ImportBegin(wchar_t const *fileName);
	void ImportEnd();

	void Install(WrpGlobals * globals);

	bool IsInstalled(void);

	void OnViewOverride(float &Tx, float &Ty, float &Tz, float &Rx, float &Ry, float &Rz);

	void SetImportBaseTime(float value);

private:
	bool m_Export;
	float m_FrameTime;
	WrpGlobals * m_Globals;
	bool m_Import;
	float m_ImportBaseTime;
	bool m_IsInstalled;
	float m_LastTime;
	float m_SubTime;

	void Install_cstrike(void);
	void Install_ep2(void);
};

