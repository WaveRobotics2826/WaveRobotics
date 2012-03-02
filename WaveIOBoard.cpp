#include "WaveIOBoard.hpp"



WaveIOBoard::WaveIOBoard()
{
	m_driverStation = DriverStation::GetInstance();
}

void WaveIOBoard::run()
{
	//Enhanced IO
	//	bool GetDigital(UINT32 channel);
	//	UINT16 GetDigitals();
    DriverStationEnhancedIO &m_cypressBoard = m_driverStation->GetEnhancedIO();

	bool input;
	
	input = m_cypressBoard.GetDigital(1);
	//cout << (UINT32)input;
	input = m_cypressBoard.GetDigital(2);
	//cout << (UINT32)input;
	input = m_cypressBoard.GetDigital(3);
	//cout << (UINT32)input;
	input = m_cypressBoard.GetDigital(4);
	//cout << (UINT32)input;
	input = m_cypressBoard.GetDigital(5);
	//cout << (UINT32)input;
	input = m_cypressBoard.GetDigital(6);
	//cout << (UINT32)input;
	input = m_cypressBoard.GetDigital(7);
	//cout << (UINT32)input;
	input = m_cypressBoard.GetDigital(8);
	//cout << (UINT32)input;
	input = m_cypressBoard.GetDigital(9);
	//cout << (UINT32)input;
	input = m_cypressBoard.GetDigital(10);
	//cout << (UINT32)input;
	input = m_cypressBoard.GetDigital(11);
	//cout << (UINT32)input;
	input = m_cypressBoard.GetDigital(12);
	//cout << (UINT32)input;
	input = m_cypressBoard.GetDigital(13);
	//cout << (UINT32)input;
	input = m_cypressBoard.GetDigital(14);
	//cout << (UINT32)input;
	input = m_cypressBoard.GetDigital(15);
	//cout << (UINT32)input << endl;
	
	
}


