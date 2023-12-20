#pragma once
#include "CellularAutomata.h"
#include "ViewCellularAuto.h"
#include <thread>
#include <chrono>
class GameControl
{
private:
	CellularAutomata& m_CellAuto;
	ViewCellularAuto& m_ViewCellAuto;
public:
	GameControl(CellularAutomata& CellAuto, ViewCellularAuto& ViewCellAuto) : m_CellAuto(CellAuto), m_ViewCellAuto(ViewCellAuto) {}
	void InitCells();
	void rendelAuto();
	void renderCellsAndLines();
	void SetState(int32_t n, int32_t m, int32_t state);
	void GetStateCell(int32_t n, int32_t m);
	void Clean();
	void Mix()
	{
		m_CellAuto.Mix();
	}
	void runCycle()
	{
		m_CellAuto.runCycle();
	}

	void runPeriodicTime(float period)
	{
		
		while (true)
		{
			std::this_thread::sleep_for(std::chrono::duration<double>(period));
			m_CellAuto.runCycle();
		}
	}
	void runPeriodic(float_t period = 1)
	{
		std::thread PeriodicTimer([this, period]() {
			runPeriodicTime(period);
			});
		PeriodicTimer.detach();
	}
};

