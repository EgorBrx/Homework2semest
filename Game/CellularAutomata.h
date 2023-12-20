#pragma once
#include "Field.h"
#include <chrono>
class CellularAutomata
{
private:
	Field m_field;
public:
	//CellularAutomata(Field& field) : m_field(field) {}
	CellularAutomata(int32_t rows, int32_t cols) : m_field(Field(rows, cols)) {}
	
        /*
         void runCycle()
    {
        auto start = std::chrono::high_resolution_clock::now();
        Field& field = this->GetField();
        size_t rows = field.getRows();
        size_t cols = field.getCols();
        std::vector<std::vector<Cell*>> newStateField(rows);
        for (size_t n = 0; n < rows; ++n)
        {
            newStateField[n].resize(cols);
            for (size_t m = 0; m < cols; ++m)
            {
                newStateField[n][m] = field.getCell(n, m).determineNextState(field, n, m);
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "funcTime: " << duration.count() << " ms" << std::endl;
        GetField().ChangeAllState(newStateField);
       
    }
        */
    
    /*
          void runCycle()
      {
         


          Field& field = this->GetField();
          size_t rows = field.getRows();
          size_t cols = field.getCols();
          static int thread_count = 3;
          std::vector<std::vector<Cell*>> newStateField(rows);
          auto start = std::chrono::high_resolution_clock::now();
          std::vector<std::thread> threads(thread_count);
          auto end = std::chrono::high_resolution_clock::now();
          auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
          std::cout << "createThreadInRunCycle : " << duration.count() << " ms" << std::endl;
          start = std::chrono::high_resolution_clock::now();
          for (int i = 0; i < thread_count; ++i)
          {
              threads[i] = std::thread([&field, &newStateField, rows, cols, i]() {
                  size_t startRow = (rows / thread_count) * i;
                  size_t endRow = (i == thread_count - 1) ? rows : (rows / thread_count) * (i + 1);
                  for (size_t n = startRow; n < endRow; ++n)
                  {
                      newStateField[n].resize(cols);
                      for (size_t m = 0; m < cols; ++m)
                      {
                          newStateField[n][m] = field.getCell(n, m).determineNextState(field, n, m);
                      }
                  }
                  });
          }


          for (auto& thread : threads)
          {
              thread.join();
          }
          end = std::chrono::high_resolution_clock::now();
          duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
          std::cout << "FuncTime: " << duration.count() << " ms" << std::endl;

          GetField().ChangeAllState(newStateField);

          end = std::chrono::high_resolution_clock::now();
          duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
          std::cout << "ALLFUNCTIME: " << duration.count() << " ms" << std::endl;

      }
    
    */
    void runCycle()
    {
        Field& field = this->GetField();
        size_t rows = field.getRows();
        size_t cols = field.getCols();
        static int thread_count = 3;
        std::vector<std::vector<Cell*>> newStateField(rows);

        std::vector<std::thread> threads(thread_count);

        for (int i = 0; i < thread_count; ++i)
        {
            threads[i] = std::thread([&field, &newStateField, rows, cols, i]() {
                size_t startRow = (rows / thread_count) * i;
                size_t endRow = (i == thread_count - 1) ? rows : (rows / thread_count) * (i + 1);
                for (size_t n = startRow; n < endRow; ++n)
                {
                    newStateField[n].resize(cols);
                    for (size_t m = 0; m < cols; ++m)
                    {
                        newStateField[n][m] = field.getCell(n, m).determineNextState(field, n, m);
                    }
                }
                });
        }

        for (auto& thread : threads)
        {
            thread.join();
        }

        GetField().ChangeAllState(newStateField);
    }
	Field& GetField() { return m_field; }
	void Mix()
	{
		m_field.Mix();
	}
};
