
//==========================================================================//
//============================ FICHIERS INCLUS =============================//

#include "Steady_Class.h"


//==========================================================================//
//=========================== VARIABLES GLOBALES ===========================//

unsigned int g_tocFrame = 0;
bool g_steady2 = false, g_steady5 = false, g_steady10 = false, g_steady15 = false, g_steady20 = false;
bool g_steady2Enable = false, g_steady5Enable = false, g_steady10Enable = false, g_steady15Enable = false, g_steady20Enable = false;
bool g_notSteady = false;

bool g_reset2 = false, g_reset5 = false, g_reset10 = false, g_reset15 = false, g_reset20 = false;
bool g_signalResetSteadies = false;


//==========================================================================//
//================================ M�THODES ================================//

// -------------- Constructeur(s) ---------------- //

SteadyClass::SteadyClass(void)
{
	m_compteurTimer = 0;
}


// ------------------- Main ---------------------- //

void SteadyClass::SteadyCheck(const Point3D& handPt, const Point3D& lastHandPt)
{
	Point3D seuil(2,2,2,"seuil");
	if (handPt.Z() > 2000)
		seuil*=2;

	Point3D lim1(lastHandPt-seuil/2,"lim1");
	Point3D lim2(lastHandPt+seuil/2,"lim2");

	//lim1.Print();
	//lim2.Print();
	//handPt.Print();
	//cout << endl;

	// Si le handPoint n'a pas boug� (sur une frame)
	if (EstDansZone(handPt,lim1,lim2) && !g_signalResetSteadies)
	{
		g_notSteady = false;
		EnclenchementTimer(m_compteurTimer);
	}
	else
	{
		g_notSteady = true;
		ResetSteadies();
		IncrementCompteurTimer();
		g_signalResetSteadies = false;
	}
	SetTocFrame(m_compteurTimer);
}


// ------------------ Steadies ------------------- //

void SteadyClass::ResetSteadies(void)
{
	g_steady2 = false;
	g_steady5 = false;
	g_steady10 = false;
	g_steady15 = false;
	g_steady20 = false;
}

void SteadyClass::SignalResetSteadies()
{
	g_signalResetSteadies = true;
	ResetSteadies();
}

bool SteadyClass::Steady2(void) const
{
	return g_steady2;
}
bool SteadyClass::Steady5(void) const
{
	return g_steady5;
}
bool SteadyClass::Steady10(void) const
{
	return g_steady10;
}
bool SteadyClass::Steady15(void) const
{
	return g_steady15;
}
bool SteadyClass::Steady20(void) const
{
	return g_steady20;
}
bool SteadyClass::NotSteady(void) const
{
	return g_notSteady;
}


// ------------------ Compteur ------------------- //

void SteadyClass::IncrementCompteurTimer(void)
{
	if (m_compteurTimer++ >= MAX_TOC_FRAME_VALUE)
		m_compteurTimer = 0;
}


//==========================================================================//
//============================== FONCTIONS =================================//

void SetTocFrame(unsigned int tocFrame)
{
	g_tocFrame = tocFrame;
}

void EnclenchementTimer(unsigned int ticFrame)
{
	if (g_steady2Enable)
		glutTimerFunc( 200, Steady2,ticFrame);

	if (g_steady5Enable)
		glutTimerFunc( 500, Steady5,ticFrame);

	if (g_steady10Enable)
		glutTimerFunc(1000,Steady10,ticFrame);

	if (g_steady15Enable)
		glutTimerFunc(1500,Steady15,ticFrame);

	if (g_steady20Enable)
		glutTimerFunc(2000,Steady20,ticFrame);
}

void Steady2(int ticFrame)
{
	if (ticFrame == g_tocFrame)
		g_steady2 = true;
	if (!g_steady2Enable)
		g_steady2 = false;
}
void Steady5(int ticFrame)
{
	if (ticFrame == g_tocFrame)
		g_steady5 = true;
	if (!g_steady5Enable)
		g_steady5 = false;
}
void Steady10(int ticFrame)
{
	if (ticFrame == g_tocFrame)
		g_steady10 = true;
	if (!g_steady10Enable)
		g_steady10 = false;
}
void Steady15(int ticFrame)
{
	if (ticFrame == g_tocFrame)
		g_steady15 = true;
	if (!g_steady15Enable)
		g_steady15 = false;
}
void Steady20(int ticFrame)
{
	if (ticFrame == g_tocFrame)
		g_steady20 = true;
	if (!g_steady20Enable)
		g_steady20 = false;
}


void SteadyAllEnable(void)
{
	g_steady2Enable = true;
	g_steady5Enable = true;
	g_steady10Enable = true;
	g_steady15Enable = true;
	g_steady20Enable = true;
	cout << "Steady 2, 5, 10, 15, 20 Enable" << endl;
}
void Steady2Enable(void)
{
	if (!g_steady2Enable)
	{
		g_steady2Enable = true;
		cout << "Steady 2 Enable" << endl;
	}
}
void Steady5Enable(void)
{
	if (!g_steady5Enable)
	{
		g_steady5Enable = true;
		cout << "Steady 5 Enable" << endl;
	}
}
void Steady10Enable(void)
{
	if (!g_steady10Enable)
	{
		g_steady10Enable = true;
		cout << "Steady 10 Enable" << endl;
	}
}
void Steady15Enable(void)
{
	if (!g_steady15Enable)
	{
		g_steady15Enable = true;
		cout << "Steady 15 Enable" << endl;
	}
}
void Steady20Enable(void)
{
	if (!g_steady20Enable)
	{
		g_steady20Enable = true;
		cout << "Steady 20 Enable" << endl;
	}
}


void SteadyAllDisable(void)
{
	g_steady2Enable = false;
	g_steady5Enable = false;
	g_steady10Enable = false;
	g_steady15Enable = false;
	g_steady20Enable = false;
	cout << "Steady 2, 5, 10, 15, 20 Disable" << endl;
}
void Steady2Disable(void)
{
	if (g_steady2Enable)
	{
		g_steady2Enable = false;
		cout << "Steady 2 Disable" << endl;
	}
}
void Steady5Disable(void)
{
	if (g_steady5Enable)
	{
		g_steady5Enable = false;
		cout << "Steady 5 Disable" << endl;
	}
}
void Steady10Disable(void)
{
	if (g_steady10Enable)
	{
		g_steady10Enable = false;
		cout << "Steady 10 Disable" << endl;
	}
}
void Steady15Disable(void)
{
	if (g_steady15Enable)
	{
		g_steady15Enable = false;
		cout << "Steady 15 Disable" << endl;
	}
}
void Steady20Disable(void)
{
	if (g_steady20Enable)
	{
		g_steady20Enable = false;
		cout << "Steady 20 Disable" << endl;
	}
}


//================================= FIN ====================================//







