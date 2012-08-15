
#include "stdafx.h" 

#include "..\include\NXT++.h"

using namespace NXT;
using namespace NXT::File;
using namespace NXT::Module;
using namespace NXT::Motor;
using namespace NXT::Sensor;
using namespace NXT::NxtCam;

bool NXT::Open(Comm::NXTComm* comm)
{
	return comm->Open();
}

// New in v0.7
// David Butterworth, May 2012
bool NXT::OpenNXTDevice(Comm::NXTComm* comm, std::string device, bool searchBT)
{
	return (bool)comm->OpenNXTDevice(device, searchBT);
}

bool NXT::OpenBT(Comm::NXTComm* comm)
{
	return comm->OpenBT();
}

bool NXT::OpenBT(Comm::NXTComm* comm, char * name)
{
	return comm->OpenBT(name);
}

void NXT::Close(Comm::NXTComm* comm)
{
	comm->Close();
}

void NXT::PlayTone(Comm::NXTComm* comm, int frequency, int duration)
{
	// This is a direct command to play a tone.
	ViUInt8 directCommandBuffer[] = { 0x03, frequency%256, (frequency-(frequency%256))/256, duration%256, (duration-(duration%256))/256 };
	
	// Send the direct command to the NXT.
	comm->SendDirectCommand( false /* a response is not required for this direct command */,
		reinterpret_cast< ViByte* >( directCommandBuffer ), sizeof( directCommandBuffer ),
		NULL /* no response buffer */, 0 /* no response buffer, specify 0 for size */);
}

int NXT::BatteryLevel(Comm::NXTComm* comm)
{
	ViUInt8 directCommandBuffer[] = { 0x0B };
	ViUInt8 responseBuffer[] = { 0x01, 0x01, 0x01, 0x01 };

	// Send the direct command to the NXT.
	comm->SendDirectCommand( true, reinterpret_cast< ViByte* >( directCommandBuffer ), sizeof( directCommandBuffer ),
		reinterpret_cast< ViByte* >( responseBuffer ), sizeof( responseBuffer ));

	return responseBuffer[3]*256+responseBuffer[2];
}

double NXT::GetAvailableFlash(Comm::NXTComm* comm)
{
	return comm->GetAvailableFlash();
}

void NXT::StopProgram(Comm::NXTComm* comm)
{
	ViUInt8 directCommandBuffer[] = { 0x01 };
	comm->SendDirectCommand( false, reinterpret_cast< ViByte* >( directCommandBuffer ), sizeof( directCommandBuffer ), NULL, 0);
}

double NXT::GetProtocolVersion(Comm::NXTComm* comm)
{
	return comm->GetProtocolVersion();
}

double NXT::GetFirmwareVersion(Comm::NXTComm* comm)
{
	return comm->GetFirmwareVersion();
}

// New in v0.7
// David Butterworth, May 2012
std::string NXT::GetName(Comm::NXTComm* comm)
{
	return (std::string)comm->GetName();
}
bool NXT::SetName(Comm::NXTComm* comm, char* name)  // Comm::NXTComm* comm
{
	return (bool)comm->SetName(name);
}

void NXT::StartProgram(Comm::NXTComm* comm, std::string name)
{
	char fname[20];
	strcpy(fname, name.c_str());
	ViUInt8 directCommandBuffer[21];
	directCommandBuffer[0] = 0x00;
	for(int i = 0; i < 20; i++)
		directCommandBuffer[i+1] = fname[i];
	comm->SendDirectCommand( false, reinterpret_cast< ViByte* >( directCommandBuffer ), sizeof( directCommandBuffer ), NULL, 0);
}

void NXT::PlaySoundFile(Comm::NXTComm* comm, std::string name, bool loop)
{
	char fname[20];
	strcpy(fname, name.c_str());
	ViUInt8 directCommandBuffer[21];
	directCommandBuffer[0] = 0x02;
	directCommandBuffer[1] = loop;
	for(int i = 0; i < 20; i++)
		directCommandBuffer[i+2] = fname[i];
	comm->SendDirectCommand( false, reinterpret_cast< ViByte* >( directCommandBuffer ), sizeof( directCommandBuffer ), NULL, 0);
}

void NXT::StopSound(Comm::NXTComm* comm)
{
	ViUInt8 directCommandBuffer[] = { 0x0C };
	comm->SendDirectCommand( false, reinterpret_cast< ViByte* >( directCommandBuffer ), sizeof( directCommandBuffer ), NULL, 0);
}

void NXT::SendDirectCommand(Comm::NXTComm* comm, ViBoolean response, ViByte * dc_buf, int dc_buf_size, ViByte *re_buf, int re_buf_size) 
{
	comm->SendDirectCommand(response, dc_buf, dc_buf_size, re_buf, re_buf_size);
}

void NXT::KeepAlive(Comm::NXTComm* comm)
{
	ViUInt8 directCommandBuffer[] = { 0x0D };
	comm->SendDirectCommand( false, reinterpret_cast< ViByte* >( directCommandBuffer ), sizeof( directCommandBuffer ), NULL, 0);
}

//
int NXT::Motor::GetRotationCount(Comm::NXTComm* comm, int port)
{
	ViUInt8 directCommandBuffer[] = { 0x06, port };
	ViInt8 responseBuffer[] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };

	// Send the direct command to the NXT.
	comm->SendDirectCommand( true, reinterpret_cast< ViByte* >( directCommandBuffer ), sizeof( directCommandBuffer ),
		reinterpret_cast< ViByte* >( responseBuffer ), sizeof( responseBuffer ));

	int i = responseBuffer[20];
	if(i < 0)
		i = 256 + i;
	if(responseBuffer[22] == -1)
		responseBuffer[22] = 0;
	if(responseBuffer[23] == -1)
		responseBuffer[23] = 0;

	int tacho = responseBuffer[23]*16777216+responseBuffer[22]*65536+responseBuffer[21]*256+i;

	return tacho;
}

void NXT::Motor::ResetRotationCount(Comm::NXTComm* comm, int port, bool relative)
{
	ViUInt8 directCommandBuffer[] = { 0x0A, port, relative };
	comm->SendDirectCommand( false, reinterpret_cast< ViByte* >( directCommandBuffer ), sizeof( directCommandBuffer ), NULL, 0);
}

void NXT::Motor::SetForward(Comm::NXTComm* comm, int port, int power)
{
	ViUInt8 directCommandBuffer[] = { 0x04, port, power, 0x01 | 0x04, 0x01, 0, 0x20, 0, 0, 0, 0 };
	comm->SendDirectCommand( false, reinterpret_cast< ViByte* >( directCommandBuffer ), sizeof( directCommandBuffer ), NULL, 0);
}

void NXT::Motor::SetReverse(Comm::NXTComm* comm, int port, int power)
{
	ViUInt8 directCommandBuffer[] = { 0x04, port, -power, 0x01 | 0x04, 0x01, 0, 0x20, 0, 0, 0, 0 };
	comm->SendDirectCommand( false, reinterpret_cast< ViByte* >( directCommandBuffer ), sizeof( directCommandBuffer ), NULL, 0);
}

void NXT::Motor::Stop(Comm::NXTComm* comm, int port, bool brake)
{
	if(brake)
	{
		ViUInt8 directCommandBuffer[] = { 0x04, port, 0, 0x01 | 0x02 | 0x04, 0x01, 0, 0x20, 0, 0, 0, 0 };
		comm->SendDirectCommand( false, reinterpret_cast< ViByte* >( directCommandBuffer ), sizeof( directCommandBuffer ), NULL, 0);
	}
	else
	{
		ViUInt8 directCommandBuffer[] = { 0x04, port, 0, 0x00, 0x00, 0, 0x00, 0, 0, 0, 0};
		comm->SendDirectCommand( false, reinterpret_cast< ViByte* >( directCommandBuffer ), sizeof( directCommandBuffer ), NULL, 0);
	}
}

void NXT::Motor::BrakeOn(Comm::NXTComm* comm, int port)
{
	ViUInt8 directCommandBuffer[] = { 0x04, port, 0, 0x01 | 0x02 | 0x04, 0x01, 0, 0x20, 0, 0, 0, 0 };
	comm->SendDirectCommand( false, reinterpret_cast< ViByte* >( directCommandBuffer ), sizeof( directCommandBuffer ), NULL, 0);
}

void NXT::Motor::BrakeOff(Comm::NXTComm* comm, int port)
{
	ViUInt8 directCommandBuffer[] = { 0x04, port, 0, 0x00, 0x00, 0, 0x00, 0, 0, 0, 0};
	comm->SendDirectCommand( false, reinterpret_cast< ViByte* >( directCommandBuffer ), sizeof( directCommandBuffer ), NULL, 0);
}

void NXT::Motor::GoTo(Comm::NXTComm* comm, int port, int power, int tacho, bool brake)
{
	if(tacho >= GetRotationCount(comm, port))
	{
		SetForward(comm, port, power);
		while(GetRotationCount(comm, port) < tacho) {}
		Stop(comm, port, brake);
	}
	else
	{
		SetReverse(comm, port, power);
		while(GetRotationCount(comm, port) > tacho) {}
		Stop(comm, port, brake);
	}
}

void NXT::Sensor::SetTouch(Comm::NXTComm* comm, int port)
{
	ViUInt8 directCommandBuffer[] = { 0x05, port, 0x01, 0x20 };
	comm->SendDirectCommand( false, reinterpret_cast< ViByte* >( directCommandBuffer ), sizeof( directCommandBuffer ), NULL, 0);
}

void NXT::Sensor::SetSound(Comm::NXTComm* comm, int port)
{
	ViUInt8 directCommandBuffer[] = { 0x05, port, 0x07, 0x80 };
	comm->SendDirectCommand( false, reinterpret_cast< ViByte* >( directCommandBuffer ), sizeof( directCommandBuffer ), NULL, 0);
}

void NXT::Sensor::SetLight(Comm::NXTComm* comm, int port, bool active)
{
	if(active)
	{
		ViUInt8 directCommandBuffer[] = { 0x05, port, 0x05, 0x80 };
		comm->SendDirectCommand( false, reinterpret_cast< ViByte* >( directCommandBuffer ), sizeof( directCommandBuffer ), NULL, 0);
	}
	else
	{
		ViUInt8 directCommandBuffer[] = { 0x05, port, 0x06, 0x80 };
		comm->SendDirectCommand( false, reinterpret_cast< ViByte* >( directCommandBuffer ), sizeof( directCommandBuffer ), NULL, 0);
	}
}

void NXT::Sensor::SetSonar(Comm::NXTComm* comm, int port)
{
	ViUInt8 directCommandBuffer[] = { 0x05, port, 0x0B, 0x00 };
	comm->SendDirectCommand( false, reinterpret_cast< ViByte* >( directCommandBuffer ), sizeof( directCommandBuffer ), NULL, 0);
}

void NXT::Sensor::SetCmpsNx(Comm::NXTComm* comm, int port)
{
	ViUInt8 directCommandBuffer[] = { 0x05, port, 0x0B, 0x00 };
	comm->SendDirectCommand( false, reinterpret_cast< ViByte* >( directCommandBuffer ), sizeof( directCommandBuffer ), NULL, 0);
}

void NXT::Sensor::SetDistNx(Comm::NXTComm* comm, int port)
{
	ViUInt8 directCommandBuffer[] = { 0x05, port, 0x0B, 0x00 };
	comm->SendDirectCommand( false, reinterpret_cast< ViByte* >( directCommandBuffer ), sizeof( directCommandBuffer ), NULL, 0);

	ViUInt8 directCommandBuffer2[] = { 0x02, 0x41, 0x34 };
	writeI2C(comm, port, directCommandBuffer2, 2, 3);

	ViUInt8 directCommandBuffer3[] = { 0x02, 0x41, 0x45 };
	writeI2C(comm, port, directCommandBuffer3, 2, 3);
}

void NXT::Sensor::SetRaw(Comm::NXTComm* comm, int port)
{
	ViUInt8 directCommandBuffer[] = { 0x05, port, 0x07, 0x00 };
	comm->SendDirectCommand( false, reinterpret_cast< ViByte* >( directCommandBuffer ), sizeof( directCommandBuffer ), NULL, 0);
}

void NXT::Sensor::Set(Comm::NXTComm* comm, int port, SensorType type)
{
	int msgtype, mode;
	switch (type)
	{
	case Touch:
		msgtype = 0x01;
		mode = 0x20;
		break;
	case Sound:
		msgtype = 0x07;
		mode = 0x80;
		break;
	case Light:
		msgtype = 0x06;
		mode = 0x80;
		break;
	case ActiveLight:
		msgtype = 0x05;
		mode = 0x80;
		break;
	case Sonar:
		msgtype = 0x0B;
		mode = 0x00;
		break;
	}
	ViUInt8 directCommandBuffer[] = { 0x05, port, msgtype, mode };
	comm->SendDirectCommand( false, reinterpret_cast< ViByte* >( directCommandBuffer ), sizeof( directCommandBuffer ), NULL, 0);
}

int NXT::Sensor::GetValue(Comm::NXTComm* comm, int port)
{
	ViUInt8 directCommandBuffer[] = { 0x07, port };
	ViUInt8 responseBuffer[] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };

	comm->SendDirectCommand( true, reinterpret_cast< ViByte* >( directCommandBuffer ), sizeof( directCommandBuffer ),
		reinterpret_cast< ViByte* >( responseBuffer ), sizeof( responseBuffer ));

	return responseBuffer[12]*256+responseBuffer[11];
}

int NXT::Sensor::GetCmpsNxValue(Comm::NXTComm* comm, int port)
{
	return GetAvgCmpsNxValue(comm, port, 1, 0);
}

int NXT::Sensor::GetAvgCmpsNxValue(Comm::NXTComm* comm, int port, int numValues, int waitTime)
{
	int returnValue = 0;
	ViUInt8 Heading = 0;

	// This sets the compass into the 0-255 range (within 1.4 degrees, maps to 0-360).  
	// There is a mode for 0-3600 (within 0.1) but I find it pretty useless, since even in 
	// the 0-255 range the compass will bounce back and forth between 2-3 degrees so more precision
	// gains you nothing
	ViUInt8 command[] = { 0x02, 0x41, 0x42};
	ViUInt8 command2[] = {0x02, 0x42};
	ViUInt8 *response;
	double doubleValue = 0.0;

	// the compass will oscillate over a 2-3 degree range, so get a few values and average them
	// Change the number of values and wait time below for your application
	for (int i=0;i<numValues;i++) {
		writeI2C(comm, port, command, 2, 3);

		int bytesRead = 0;

		do {
	
			writeI2C(comm, port, command2, 2, 2);
		    bytesRead = LSGetStatus(comm, port);

		} while (bytesRead < 1);

		response = readI2C(comm, port);
	
		Heading = response[4];
		doubleValue += ((int)Heading * 1.41);
		Wait(waitTime);
	}
	return (int)(doubleValue/numValues);
}

int NXT::Sensor::GetCleanDistNxValue(Comm::NXTComm* comm, int port)
{
	const int numValues = 10;
	int total = 0;
	int avg = 0;
	int values[numValues];
	int absPointTotal = 0, pointTotal = 0;
	int volatilityRatioThreshold = 1;
	int volatilityThreshold = 45;
	int volatilityRatio;
	int minValue = 0, maxValue = 0;

	for (int i=0;i < numValues; i++) {
		values[i] = GetDistNxValue(comm, port);
		if (minValue == 0) {
			minValue = values[i];
			maxValue = values[i];
		}
		if (values[i] < minValue) {
			minValue = values[i];
		}
		if (values[i] > maxValue) {
			maxValue = values[i];
		}

		total += values[i];
		printf("value: %d\n",values[i]);
//		if (i > 0) {
//
//			absPointTotal += abs(values[i - 1] - values[i]);
//			pointTotal += (values[i - 1] - values[i]);
//		}
	}

	avg = total/numValues;
//	if (pointTotal == 0) {
//		return 0;
//	}
//	volatilityRatio = absPointTotal/abs(pointTotal);

	if (((maxValue - minValue) > volatilityThreshold) || avg < 200)
		return 0;
	else
		return avg;
}

int NXT::Sensor::GetDistNxValue(Comm::NXTComm* comm, int port)
{
	ViUInt8 command[] = { 0x02, 0x42 };
	ViUInt8 *responseBuffer;
	int bytesRead = 0;

	do {
		writeI2C(comm, port, command, 2, 2);
	    bytesRead = LSGetStatus(comm, port);
	} while (bytesRead < 1);

	responseBuffer = readI2C(comm, port);

	if (responseBuffer[2] == 2)
		return (int)responseBuffer[4]*256 + (int)responseBuffer[3];
	else
		return (int)responseBuffer[3];
}

int NXT::Sensor::LSGetStatus(Comm::NXTComm* comm, int port)
{
	ViUInt8 directCommandBuffer[] = {0x0E, port};
	ViUInt8 responseBuffer[] = {1,1,1};


	comm->SendDirectCommand( true, reinterpret_cast< ViByte* >( directCommandBuffer ), sizeof( directCommandBuffer),
		   reinterpret_cast< ViByte* >( responseBuffer ), sizeof( responseBuffer ));

	return (int)responseBuffer[2];
}

int NXT::Sensor::GetSonarValue(Comm::NXTComm* comm, int port)
{

	ViUInt8 directCommandBuffer[] = {0x0F, port, 0x03, 0x00, 0x02, 0x41, 0x02};
	ViUInt8 responseBuffer[] = { 1,1};

	comm->SendDirectCommand( true, reinterpret_cast< ViByte* >( directCommandBuffer ), sizeof( directCommandBuffer ),
		reinterpret_cast< ViByte* >( responseBuffer ), sizeof( responseBuffer ));

	int bytesRead = 0;

	do {

	    ViUInt8 directCommandBuffer[] = {0x0F, port, 0x02, 0x01, 0x02, 0x42};
	    ViUInt8 responseBuffer[] = {1, 1};


	    comm->SendDirectCommand( true, reinterpret_cast< ViByte* >( directCommandBuffer ), sizeof( directCommandBuffer ),
		        reinterpret_cast< ViByte* >( responseBuffer ), sizeof( responseBuffer));

         bytesRead = LSGetStatus(comm, port);

	} while (bytesRead < 1);
	
	ViUInt8 directCommandBuffer2[] = {0x10, port};
	ViUInt8 responseBuffer2[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};


	comm->SendDirectCommand( true, reinterpret_cast< ViByte* >( directCommandBuffer2 ), sizeof( directCommandBuffer2 ),
		reinterpret_cast< ViByte* >( responseBuffer2 ), sizeof( responseBuffer2 ));

	return (int)responseBuffer2[3];
	  
}

void NXT::Sensor::SetSonarOff(Comm::NXTComm* comm, int port)
{
	ViUInt8 directCommandBuffer[] = {0x0F, port, 0x03, 0x00, 0x02, 0x41, 0x00};
	ViUInt8 responseBuffer[] = { 1,1};

	comm->SendDirectCommand( true, reinterpret_cast< ViByte* >( directCommandBuffer ), sizeof( directCommandBuffer ),
		reinterpret_cast< ViByte* >( responseBuffer ), sizeof( responseBuffer ));
}

void NXT::Sensor::SetSonarSingleShot(Comm::NXTComm* comm, int port)
{
	ViUInt8 directCommandBuffer[] = {0x0F, port, 0x03, 0x00, 0x02, 0x41, 0x01};
	ViUInt8 responseBuffer[] = { 1,1};

	comm->SendDirectCommand( true, reinterpret_cast< ViByte* >( directCommandBuffer ), sizeof( directCommandBuffer ),
		reinterpret_cast< ViByte* >( responseBuffer ), sizeof( responseBuffer ));
}

void NXT::Sensor::SetSonarContinuous(Comm::NXTComm* comm, int port)
{
	ViUInt8 directCommandBuffer[] = {0x0F, port, 0x03, 0x00, 0x02, 0x41, 0x02};
	ViUInt8 responseBuffer[] = { 1,1};

	comm->SendDirectCommand( true, reinterpret_cast< ViByte* >( directCommandBuffer ), sizeof( directCommandBuffer ),
		reinterpret_cast< ViByte* >( responseBuffer ), sizeof( responseBuffer ));
}

void NXT::Sensor::SetSonarContinuousInterval(Comm::NXTComm* comm, int port, int interval)
{
	ViUInt8 directCommandBuffer[] = {0x0F, port, 0x03, 0x00, 0x02, 0x40, interval};
	ViUInt8 responseBuffer[] = { 1,1};

	comm->SendDirectCommand( true, reinterpret_cast< ViByte* >( directCommandBuffer ), sizeof( directCommandBuffer ),
		reinterpret_cast< ViByte* >( responseBuffer ), sizeof( responseBuffer ));
}

void NXT::Sensor::writeI2C(Comm::NXTComm* comm, int port, ViUInt8 command[], int replySz, int tx_length)
{
	int i=0;
    ViUInt8 commandBuffer[24];
	ViUInt8 response[] = { 1,1 };
        
    while(i < tx_length){
        commandBuffer[i+4]=command[i];
        i++;          
    }
    commandBuffer[0]=0x0F;
    commandBuffer[1]=port;
        
    commandBuffer[2]=i;
    commandBuffer[3]=replySz;
	//Comm::SendDirectCommand(true, reinterpret_cast< ViByte* >( commandBuffer ), sizeof( commandBuffer ),
	//	reinterpret_cast< ViByte* >( response ), 2);
	comm->SendDirectCommand(true, reinterpret_cast< ViByte* >( commandBuffer ), 4 + tx_length,
		reinterpret_cast< ViByte* >( response ), 2);
}

ViUInt8* NXT::Sensor::readI2C(Comm::NXTComm* comm, int port)
{
	ViUInt8 commandBuffer[] = { 0x10, port };
	static ViUInt8 response[19] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

	comm->SendDirectCommand( true, reinterpret_cast< ViByte* >( commandBuffer ), sizeof( commandBuffer ),
		reinterpret_cast< ViByte* >( response ), sizeof( response ));

	return response;
}

//! Retrieves a specific NXT file pointer by name.
int NXT::File::getNXTFile(Comm::NXTComm* comm, std::string filename, NXTFile& file)
{
	bool isFatal;
	file = comm->GetNXTFile(filename, isFatal);

	if (! isFatal)
		return 0;

	return -1;
}

//! Retrieves NXT file pointers by name.
int NXT::File::getNXTFilesByName(Comm::NXTComm* comm, std::string pattern, NXTFileIterator& iter)
{			
	bool isFatal;
	iter = comm->GetFileIterator(pattern, isFatal);
	
	if (!isFatal)
		return 0;
				
	//TODO: tStatus error code tranlation
	return IteratorFailed;
		
}

//! Retrieves NXT file pointers by type.
int NXT::File::getNXTFilesByType(Comm::NXTComm* comm, int fileType, NXTFileIterator& iter)
{
	switch(fileType)
	{
	  case ANY:
		  return getNXTFilesByName(comm, "*.*", iter);
		  break;
	  case PROGRAM:
		  return getNXTFilesByName(comm, "*.rxe", iter);
		  break;

	  case SOUND:
		  return getNXTFilesByName(comm, "*.rso", iter);
		  break;

	  case GRAPHICS:
		  return getNXTFilesByName(comm, "*.ric", iter);
		  break;

	  case DATALOG:
		  return getNXTFilesByName(comm, "*.rdt", iter);
		  break;

	  default:
		  return UnsupportedType;

	}
	return 0;
}

//! Destroys a file iterator.
void NXT::File::destroyFileIterator(Comm::NXTComm* comm, NXTFileIterator &iter)
{
	comm->destroyFileIterator(iter);
}

//! Destroys a file pointer
void NXT::File::destroyFile(Comm::NXTComm* comm, NXTFile& file)
{
	comm->destroyFile(file);
}



//! Retrieves NXT module pointers by name.
int NXT::Module::getNXTModules(Comm::NXTComm* comm, std::string pattern, NXTModuleIterator &iter)
{
	int status = 0;
	iter = comm->GetModuleIterator(pattern, status);

	return status;
}

//! Retrieves a specific module pointer by name.
int NXT::Module::getNXTModule(Comm::NXTComm* comm, std::string pattern, int moduleID, int moduleSize,
	int ioMapSize, int &status, NXTModule &module) 
{
	status = 0;
	module = comm->GetModule(pattern, moduleID, moduleSize, ioMapSize, status);

	return status;			
}

void NXT::NxtCam::NxtCamFlush(Comm::NXTComm* comm, int port)
{
	int bytesRead = 0;

	do {
		NXT::Sensor::readI2C(comm, port);
	    bytesRead = NXT::Sensor::LSGetStatus(comm, port);
	} while (bytesRead > 0);
}

void NXT::NxtCam::NxtCamCmd(Comm::NXTComm* comm, int port, ViUInt8 command[], int tx_length)
{
	int temp1, temp2, temp3, temp4;
	temp1 = command[0];
	temp2 = command[1];
	temp3 = command[2];
	temp4 = command[3];
	NXT::Sensor::writeI2C(comm, port, command, 0, tx_length);
	int temp = sizeof(command)/sizeof(ViUInt8);
//	NxtCamFlush(port);
}

void NXT::NxtCam::NxtCamInit(Comm::NXTComm* comm, int port)
{
	ViUInt8 directCommandBuffer[] = { 0x05, port, 0x0B, 0x00 };
	int temp;
	comm->SendDirectCommand( false, reinterpret_cast< ViByte* >( directCommandBuffer ), sizeof( directCommandBuffer ), NULL, 0);

	// sort by size
	ViUInt8 command1[] = { 0x02, 0x41, 0x41 };
	temp = sizeof(command1)/sizeof(ViUInt8);
	NXT::Sensor::writeI2C(comm, port, command1, 0, 3);
//	NxtCamFlush(port);
	//NxtCamCmd(port, command1);

	// start blob tracking
	ViUInt8 command2[] = { 0x02, 0x41, 0x45 };
	NXT::Sensor::writeI2C(comm, port, command2, 0, 3);
//	NxtCamFlush(port);
	//NxtCamCmd(port, command2);

}

std::vector<std::vector<int>> NXT::NxtCam::GetNxtCamObjects(Comm::NXTComm* comm, int port, int minArea)
{
	int numBlobs = GetNxtCamNumObjects(comm, port);
	//printf("Num Objects: %d\n",numBlobs);
	ViUInt8 *response;
	std::vector<std::vector<int>> blobs(8, std::vector<int>(5));
	int x1, x2, y1, y2;
	int vectorIndex = 0;

	NxtCamFlush(comm, port);

	for (int i = 0; i < numBlobs; i++) {
		int bytesRead = 0;

		do {

			ViUInt8 command[] = {0x02, 0x43 + i * 5};
			NXT::Sensor::writeI2C(comm, port, command, 5, 2);

			bytesRead = NXT::Sensor::LSGetStatus(comm, port);

		} while (bytesRead < 1);

		response = NXT::Sensor::readI2C(comm, port);
		x1 = (int)response[4];
		y1 = (int)response[5];
		x2 = (int)response[6];
		y2 = (int)response[7];
		if (((y2 - y1) * (x2 - x1)) > minArea) {
			blobs[vectorIndex][0] = (int)response[3];
			blobs[vectorIndex][1] = (int)response[4];
			blobs[vectorIndex][2] = (int)response[5];
			blobs[vectorIndex][3] = (int)response[6];
			blobs[vectorIndex++][4] = (int)response[7];
		}
	}

	return blobs;
}

int NXT::NxtCam::GetNxtCamNumObjects(Comm::NXTComm* comm, int port)
{
//	NxtCamFlush(port);
	ViUInt8 *response;
	int temp;

	int bytesRead = 0;

	do {

	    ViUInt8 command[] = {0x02, 0x42};
		NXT::Sensor::writeI2C(comm, port, command, 1, 2);

		bytesRead = NXT::Sensor::LSGetStatus(comm, port);
		Wait(100);

	} while (bytesRead < 1);

	response = NXT::Sensor::readI2C(comm, port);
	temp = (int)response[0];
	temp = (int)response[1];
	temp = (int)response[2];
	temp = (int)response[3];
	temp = (int)response[4];

	return (int)response[3];

}

void Wait(int time)
{
	int starttime = clock();
	while(clock()-starttime <= time) {}
}
