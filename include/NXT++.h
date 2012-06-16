// File: NXT++.h
//
// Copyright (c) 2007 by XXX
// -------------------------------------------------------------------------
// DESCRIPTION
// NXT++.h is a header file containing an interface for programming Lego NXT 
// Mindstorms. 
//
// HISTORY
// Date         By who         Description
// -------------------------------------------------------------------------
// 04/26/2007   maddock     OS specific includes, comment headers
// 05/16/2007   phyizal     Removed fantom function call 

#include "comm.h"

#include <time.h>
#include <math.h>
#include <string>
#include <iostream>
#include <vector>

//! Defines different types of sensors.
enum SensorType
{
	Touch, /*!< A touch sensor. GetValue() returns a boolean.*/
	Sound, /*!< A sound sensor. GetValue() returns a decibel value.*/
	Light, /*!< A light sensor with the infrared light off. GetValue() returns a percent.*/
	ActiveLight, /*!< A light sensor with the infrared light on. GetValue() returns a percent.*/
	Sonar /*!< An ultrasonic sensor. GetValue() returns a distance in centimeters.*/
};

//! Motor port A on the NXT
const int OUT_A = 0;
//! Motor port B on the NXT
const int OUT_B = 1;
//! Motor port C on the NXT
const int OUT_C = 2;
//! Sensor port 1 on the NXT
const int IN_1 = 0;
//! Sensor port 2 on the NXT
const int IN_2 = 1;
//! Sensor port 3 on the NXT
const int IN_3 = 2;
//! Sensor port 4 on the NXT
const int IN_4 = 3;

//! Contains all the functions that have to do with the NXT.
namespace NXT
{
	//! Initiates the NXT connection.
	/*! Returns true if it completed without error. Returns false if it failed. You should not continue to
	use the interface functions if this happens. Refer to example.cpp for info on how to properly handle this.*/
	bool Open(Comm::NXTComm* comm);
	//! Initiates the NXT connection through Bluetooth.
	/*! Returns true if it completed without error. Returns false if it failed. You should not continue to
	use the interface functions if this happens. Refer to example.cpp for info on how to properly handle this.
	Does not work with linux yet.*/
	bool OpenBT(Comm::NXTComm* comm);
	//! Closes the NXT connection.
	void Close(Comm::NXTComm* comm);
	//! Plays a tone.
	/*! \param frequency The frequency in hertz. \param duration The duration in milliseconds.*/
	void PlayTone(Comm::NXTComm* comm, int frequency, int duration);
	//! Returns the current battery level.
	/*! \return The current battery level in millivolts.*/
	int BatteryLevel(Comm::NXTComm* comm);
	//! Gets the name of the NXT.
	/*! \return The name of the NXT.*/
	std::string GetName(Comm::NXTComm* comm);
	//! Gets the amount of availiable flash memory on the NXT.
	/*! Does not work with linux yet. \return The amount of free flash memory in kilobytes.*/
	double GetAvailableFlash(Comm::NXTComm* comm);
	//! Stops the current program if one is running.
	void StopProgram(Comm::NXTComm* comm);
	//! Gets the protocol version of the NXT.
	/*! Does not work with linux yet. \return The protocol version of the NXT.*/
	double GetProtocolVersion(Comm::NXTComm* comm);
	//! Gets the firmware version of the NXT.
	/*! Does not work with linux yet. \return The firmware version of the NXT.*/
	double GetFirmwareVersion(Comm::NXTComm* comm);
	//! Starts a program on the NXT with a specified name.
	/*! \param name The filename of the program you wish to execute. Don't forget to include the '.rxe'!*/
	void StartProgram(Comm::NXTComm* comm, std::string name);
	//! Plays a sound file on the NXT with a specified name.
	/*! \param name The filename of the sound you wish to play. Don't forget to include the '.rso'!*/
	void PlaySoundFile(Comm::NXTComm* comm, std::string name, bool loop);
	//! Stops the currently playing sound.
	void StopSound(Comm::NXTComm* comm);
	//! Resets the internal sleep timer.
	/*! This function is used so the NXT will not automatically turn off while the computer is still
	controlling it. Note: an alternative to this is to set the shutoff time to never in the NXT settings
	menu.*/
	void KeepAlive(Comm::NXTComm* comm);
	//! Sends a direct command to the NXT.
	/*! This low-level function is used to send commands to the NXT - just like all the other functions do.
	The only difference is that this function is harder to use, but in turn, provides much more control of the
	NXT. For a reference about direct commands, look in the PDF titled Appendix 2. \param response Whether or not
	you want to recieve a response from the direct command. \param dc_buf The buffer that contains the direct 
	command. \param dc_buf_size The number of bytes in the direct command buffer. \param re_buf The buffer that
	will contain the response to the direct command if specified. \param re_buf_size The number of bytes in the
	response buffer.*/
	void SendDirectCommand(Comm::NXTComm* comm, ViBoolean response, ViByte * dc_buf, int dc_buf_size, ViByte *re_buf, int re_buf_size);
	
	//! Contains all the functions that have to do with a motor.
	namespace Motor
	{
		//! Returns the rotation of a motor.
		/*! \param port The port that you wish to retrieve the rotation. Can be the numbers 0-2 or OUT_A, OUT_B,
		or OUT_C. \return The rotation of the motor in degrees.*/
		int GetRotationCount(Comm::NXTComm* comm, int port);
		//! Resets the specified motor's rotation count.
		/*! \param port The port that you wish to reset the rotation. Can be the numbers 0-2 or OUT_A, OUT_B,
		or OUT_C. \param relative If true it resets the rotation relative to the last movement. If false it
		resets the rotation to its absolute position.*/
		void ResetRotationCount(Comm::NXTComm* comm, int port, bool relative);
		//! Sets a motor to turn forward at a specified power.
		/*! \param port The port that you wish to set. Can be the numbers 0-2 or OUT_A, OUT_B, or OUT_C. 
		\param power The power level (0-100) that you want the motor to recieve.*/
		void SetForward(Comm::NXTComm* comm, int port, int power);
		//! Sets a motor to turn backward at a specified power.
		/*! \param port The port that you wish to set. Can be the numbers 0-2 or OUT_A, OUT_B, or OUT_C.
		\param power The power level (0-100) that you want the motor to recieve.*/
		void SetReverse(Comm::NXTComm* comm, int port, int power);
		//! Tells a motor to stop turning.
		/*! \param port The port that you wish to turn off. Can be the numbers 0-2 or OUT_A, OUT_B, or OUT_C.
		\param brake Whether or not you want the motor to brake or float.*/
		void Stop(Comm::NXTComm* comm, int port, bool brake);
		//! Tells a motor to turn the brake on.
		/*! \param port The port that you wish to turn the brake on. Can be the numbers 0-2 or OUT_A, OUT_B, or OUT_C.*/
		void BrakeOn(Comm::NXTComm* comm, int port);
		//! Tells a motor to turn the brake off.
		/*! \param port The port that you wish to turn the brake off. Can be the numbers 0-2 or OUT_A, OUT_B, or OUT_C.*/
		void BrakeOff(Comm::NXTComm* comm, int port);
		//! Tells a motor to go to a certian angle and then stop.
		/*! \param port The port that you wish to set. Can be the numbers 0-2 or OUT_A, OUT_B, or OUT_C.
		\param power The power level (0-100) that you want the motor to recieve. \param tacho The rotation
		count (in degrees) that you want the motor to turn to. \param brake Whether or not you want the motor
		to brake or float when it is done turning.*/
		void GoTo(Comm::NXTComm* comm, int port, int power, int tacho, bool brake);
	}
	
	//! Contains all the functions that have to do with a sensor.
	namespace Sensor
	{
		//! Sets a sensor in a specified port to a touch sensor.
		/*! \param port The port that you wish to set as a touch sensor. Can be the numbers 0-3 or IN_1, IN_2,
		IN_3, or IN_4.*/
		void SetTouch(Comm::NXTComm* comm, int port);
		//! Sets a sensor in a specified port to a sound sensor.
		/*! \param port The port that you wish to set as a sound sensor. Can be the numbers 0-3 or IN_1, IN_2,
		IN_3, or IN_4.*/
		void SetSound(Comm::NXTComm* comm, int port);
		//! Sets a sensor in a specified port to a light sensor.
		/*! \param port The port that you wish to set as a light sensor. Can be the numbers 0-3 or IN_1, IN_2,
		IN_3, or IN_4. \param active Whether or not you want the infrared light to be on.*/;
		void SetLight(Comm::NXTComm* comm, int port, bool active);
		//! Sets a sensor in a specified port to a sonar sensor.
		/*! \param port The port that you wish to set as a sonar sensor. Can be the numbers 0-3 or IN_1,
		IN_2, IN_3, or IN_4.*/;
		void SetSonar(Comm::NXTComm* comm, int port);
		//! Sets a sensor in a specified port to a Mind Sensors Compass sensor.
		/*! \param port The port that you wish to set as a compass sensor. Can be the numbers 0-3 or IN_1, IN_2, IN_3,
		or IN_4. */
		void SetCmpsNx(Comm::NXTComm* comm, int port);
		//! Sets a sensor in a specified port to a Mind Sensors Distance sensor.
		/*! \param port The port that you wish to set as a distance sensor. Can be the numbers 0-3 or IN_1, IN_2, IN_3,
		or IN_4. */
		void SetDistNx(Comm::NXTComm* comm, int port);
		//! Sets a sensor to return a raw value (not formatted in any way).
		/*! \param port The port that you wish to set to return a raw value. Can be the numbers 0-3 or IN_1,
		IN_2, IN_3, or IN_4.*/
		void SetRaw(Comm::NXTComm* comm, int port);
		//! Sets a sensor to a specified SensorType.
		/*! \param port The port that you wish perform this operation on. Can be the numbers 0-3 or IN_1, IN_2,
		IN_3, or IN_4. \param type The SensorType that you wish to set the sensor to.*/
		void Set(Comm::NXTComm* comm, int port, SensorType type);
		//! Retrieves the value of a sensor.
		/*! Does not work with the Sonar sensor. \param port The port that you wish to retrieve it's sensor's value from. Can be the numbers 0-3 or
		IN_1, IN_2, IN_3, or IN_4. \return The sensor's current value.*/
		int GetValue(Comm::NXTComm* comm, int port);
		//! Retrieves multiple values of the Mindsensors Compass sensor and averages them.
		/*! \param port The port that you wish to retrieve it's sensor's value from. Can be the numbers 0-3 or IN_1, IN_2,
		IN_3, or IN_4. \param numValues The number of samples to average \param waitTime The time in between samples 
		\return The sensor's current value. */
		int GetAvgCmpsNxValue(Comm::NXTComm* comm, int port, int numValues, int waitTime);
		//! Retrieves the value of the Mindsensors Compass sensor.
		/*! \param port The port that you wish to retrieve it's sensor's value from. Can be the numbers 0-3 or IN_1, IN_2,
		IN_3, or IN_4. \return The sensor's current value. */
		int GetCmpsNxValue(Comm::NXTComm* comm, int port);
		//! Retrieves the value of the Mindsensors Distance sensor.
		/*! \param port The port that you wish to retrieve it's sensor's value from. Can be the numbers 0-3 or IN_1, IN_2,
		IN_3, or IN_4. \return The sensor's current value. */
		int GetDistNxValue(Comm::NXTComm* comm, int port);
		//! Retrieves multiple values of the Mindsensors Distance sensor and averages them.
		/*! \param port The port that you wish to retrieve it's sensor's value from. Can be the numbers 0-3 or IN_1, IN_2,
		IN_3, or IN_4. \return The sensor's current value. */
		int GetCleanDistNxValue(Comm::NXTComm* comm, int port);
		//! Gets the status of the lowspeed port.
		/*! Most users should not need to use this. The function does not get the value of the sensor. Not to be 
		confused with GetSonarValue(). \param port The port that you wish to get the status of. Can be the numbers
		0-3 or IN_1, IN_2, IN_3, or IN_4. \return The status of the specified port.*/
		int LSGetStatus(Comm::NXTComm* comm, int port);
		//! Retrieves the value for sonar sensors.
		/*! \param port The port that contains the sonar sensor. Can be the numbers 0-3 or IN_1, IN_2, IN_3, or IN_4.
		\return The sonar sensor's current value in centimeters.*/
		int GetSonarValue(Comm::NXTComm* comm, int port);
		//! Tells the sonar sensor to stop sending pulses.
		/*! \param port The port that contains the sonar sensor. Can be the numbers 0-3 or IN_1, IN_2, IN_3, or IN_4.*/
		void SetSonarOff(Comm::NXTComm* comm, int port);
		//! Tells the sonar sensor to only send a pulse when you ask it what it's value is.
		/*! \param port The port that contains the sonar sensor. Can be the numbers 0-3 or IN_1, IN_2, IN_3, or IN_4.*/
		void SetSonarSingleShot(Comm::NXTComm* comm, int port);
		//! Tells the sonar sensor to continuously send pulses.
		/*! \param port The port that contains the sonar sensor. Can be the numbers 0-3 or IN_1, IN_2, IN_3, or IN_4.*/
		void SetSonarContinuous(Comm::NXTComm* comm, int port);
		//! Sets the interval at which the sonar sensor sends a pulse.
		/*! \param port The port that contains the sonar sensor. Can be the numbers 0-3 or
		IN_1, IN_2, IN_3, or IN_4. \param interval The interval at which the sonar sensor should send a pulse in
		miliseconds.*/
		void SetSonarContinuousInterval(Comm::NXTComm* comm, int port, int interval);
		//! Writes the command to the I2C sensor
		/*! See the GetDistNxValue() source for an example. \param port The port where the I2C sensor you wish to write
		to is. Can be the numbers 0-3 or IN_1, IN_2, IN_3, or IN_4. \param command The command you want to send, starting
		with the sensor address \param replySz The size of the reply expected to be returned \param tx_length The length
		of the message you are sending. */
		void writeI2C(Comm::NXTComm* comm, int port, ViUInt8 command[], int replySz, int tx_length);
		//! Reads the values from the registers of an I2C sensor
		/*! Always returns an array of length 19. See GetDisNxValue for an example. \param port port The port where the
		I2C sensor you wish to read from is. Can be the numbers 0-3 or IN_1, IN_2, IN_3, or IN_4. */
		ViUInt8* readI2C(Comm::NXTComm* comm, int port);
	}

    
	//! NXT file functions.
	namespace File
	{		
	    //! Defines different types of resource files.
		enum FileType
		{
			ANY,      /*!< *.*, All files. */
			PROGRAM,  /*!< *.rcx, A user define program.  */
			SOUND,    /*!< *.rso A sound file. */
			GRAPHICS, /*!< *.ric. A graphics file. */
		    DATALOG,  /*! < *.rdt. */
		};
		
	    //! Defines different types of file modes.
		enum FileMode
		{
			READ,
			WRITE,
			APPEND,
			DATA_WRITE,			
			LINEAR_WRITE,
		};

		//! Retrieves a specific NXT file pointer by name.
		int getNXTFile(Comm::NXTComm* comm, std::string filename, NXTFile& file);

		//! Retrieves NXT file pointers by name.
		int getNXTFilesByName(Comm::NXTComm* comm, std::string pattern, NXTFileIterator& iter);

		//! Retrieves NXT file pointers by type.
		int getNXTFilesByType(Comm::NXTComm* comm, int fileType, NXTFileIterator& iter);

		//! Destroys a file iterator.
		void destroyFileIterator(Comm::NXTComm* comm, NXTFileIterator &iter);

		//! Destroys a file pointer
		void destroyFile(Comm::NXTComm* comm, NXTFile& file);

	};

	//! NXT module functions.
	namespace Module
	{
		//! Retrieves NXT module pointers by name.
		int getNXTModules(Comm::NXTComm* comm, std::string pattern, NXTModuleIterator &iter);

		//! Retrieves a specific module pointer by name.
		int getNXTModule(Comm::NXTComm* comm, std::string pattern, int moduleID, int moduleSize,
			int ioMapSize, int &status, NXTModule &module);
	};

	//! NXTCam functions
	namespace NxtCam
	{
		void NxtCamFlush(Comm::NXTComm* comm, int port);
		void NxtCamCmd(Comm::NXTComm* comm, int port, ViUInt8 command[], int tx_length);
		void NxtCamInit(Comm::NXTComm* comm, int port);
		std::vector<std::vector<int>> GetNxtCamObjects(Comm::NXTComm* comm, int port, int minArea);
		int GetNxtCamNumObjects(Comm::NXTComm* comm, int port);
	};
}

//! Waits a specified time.
/*! \param time The time to wait in milliseconds.*/;
void Wait(int time);

