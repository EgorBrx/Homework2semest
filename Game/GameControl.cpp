#include "GameControl.h"
#include <chrono>
void GameControl::InitCells()
{
	m_ViewCellAuto.GetFieldVisualizer().InitCells(m_CellAuto.GetField().getRows(), m_CellAuto.GetField().getCols());
}

void GameControl::rendelAuto()
{
	std::lock_guard<std::mutex> lock(m_CellAuto.GetField().mutex);
	renderCellsAndLines();

}

void GameControl::renderCellsAndLines()
{
	m_ViewCellAuto.renderCellsAndLines(m_CellAuto.GetField(), m_CellAuto.GetField().getRows(), m_CellAuto.GetField().getCols());
}

void GameControl::SetState(int32_t n, int32_t m, int32_t state)
{
	m_CellAuto.GetField().getField()[n][m]->SetState(state);
}

void GameControl::GetStateCell(int32_t n, int32_t m)
{		
		std::lock_guard<std::mutex> lock(m_CellAuto.GetField().mutex);
		m_CellAuto.GetField().getField()[n][m]->GetInformation(m_CellAuto.GetField(), n, m);
		return;
}

void GameControl::Clean()
{
	for (int32_t n = 0, rows = m_CellAuto.GetField().getRows(), cols = m_CellAuto.GetField().getCols(); n < rows; ++n)
	{
		for (int32_t m = 0; m < cols; ++m)
		{
			m_CellAuto.GetField().getField()[n][m]->SetState(0);
		}
	}

}
