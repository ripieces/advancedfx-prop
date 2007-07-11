
#ifndef AIMING_H
#define AIMING_H

#ifdef min
#undef min
#undef max
#endif

#include <list>

class Aiming
{
private:
	enum ENT_STATE { ES_NORMAL, ES_TARGET, ES_DEAD };

private:
	std::list<int> m_AimLayers;

	int m_iHighestSlot;
	int m_iCurrentEntity;
	bool m_bActive;

	const static int MAX_ENTITIES = 600;

	int m_ActiveTimes[MAX_ENTITIES];
	int m_VisibleTimes[MAX_ENTITIES];
	int m_LastMsgNums[MAX_ENTITIES];
	Vector m_LastPositions[MAX_ENTITIES];
	int m_EntityStates[MAX_ENTITIES];

	float m_flRealAimSpeed;

public:
	Aiming()
	{
		m_iCurrentEntity = 0;
		m_iHighestSlot = -1;
		m_flRealAimSpeed = 0;
	}

	void addAimLayer(int iSlot, int iEnt);
	void removeAimLayer(int iSlot);
	void showAimLayers();

	void Start();
	void Stop();

	void LookAtCurrentEntity();

	void nextEntity() { m_iCurrentEntity = std::min(m_iCurrentEntity + 1, MAX_ENTITIES); }
	void prevEntity() { m_iCurrentEntity = std::max(m_iCurrentEntity - 1, 0); }
	void setEntity(int i) { m_iCurrentEntity = i; }
	
	bool getValidTarget(Vector &outTarget);
	bool isAiming() { return m_bActive; }
	void aim();
};

#endif