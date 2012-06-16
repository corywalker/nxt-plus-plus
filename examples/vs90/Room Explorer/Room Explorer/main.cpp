#include "NXT++.h"
#include <iostream>
using namespace std;

void BackUp();

Comm::NXTComm comm;

int main()
{
	srand(NULL);
	cout << "Aquiring signal... this should take a minute or so.\n";
	if(NXT::OpenBT(&comm)) //initialize the NXT and continue if it succeeds
	{
		cout << "Signal found!";
		NXT::Sensor::SetTouch(&comm, IN_1);
		NXT::Sensor::SetSonar(&comm, IN_4);
		NXT::Motor::SetForward(&comm, OUT_A, 50);
		NXT::Motor::SetForward(&comm, OUT_C, 50);
		while(1) 
		{
			if(NXT::Sensor::GetSonarValue(&comm, IN_4) < 35)
			{
				int port = rand() % 2;
				if(port == 1)
					port = 2;
				NXT::Motor::SetReverse(&comm, port, 50);
				while(NXT::Sensor::GetSonarValue(&comm, IN_4) < 27){}
				NXT::Motor::SetForward(&comm, port, 50);
			}
			if(NXT::Sensor::GetValue(&comm, IN_1))
				BackUp();
		}
	}
	NXT::Close(&comm); //close the NXT
	return 0;
}

void BackUp()
{
	NXT::Motor::SetReverse(&comm, OUT_A, 50);
	NXT::Motor::SetReverse(&comm, OUT_C, 50);
	Wait(1500);
	if(rand() % 2 == 0)
	{
		NXT::Motor::SetForward(&comm, OUT_A, 50);
		Wait(500);
		NXT::Motor::SetForward(&comm, OUT_C, 50);
	}
	else
	{
		NXT::Motor::SetForward(&comm, OUT_C, 50);
		Wait(500);
		NXT::Motor::SetForward(&comm, OUT_A, 50);
	}
}