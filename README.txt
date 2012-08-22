+------------------------------------------------------------------------------+
|                                                                              |
|                                NXT++  v0.7                                   |
|                                                                              |
+------------------------------------------------------------------------------+


ABOUT
-----

NXT++ is an interface written in C++ that allows control of LEGO MINDSTORMS 
robots directly through a USB or Bluetooth connection. 
The interface is intended to be simple and easy to use, and can be used in any 
C++ program.

http://nxtpp.sourceforge.net


AUTHOR
------
Written by cmwslw (Cory Walker) in 2007.
Updates by maddock, phyizal, and others.
Additions and updates by David Butterworth in 2012.


LICENSE
-------
GNU General Public License version 2.0 (GPLv2)
In summary, you are free to use, edit, and distribute this code.


NEW FEATURES in v0.7
--------------------

NXT++ now supports multiple NXT bricks via USB and/or Bluetooth!

Compatibility remains with earlier versions of NXT++.


New functions:

   std::vector<std::vector<std::string> > ListNXTDevices(bool searchBT);

      Lists the Device Name and MAC Address of all NXT Devices connected 
      via USB and Bluetooth.


   bool OpenNXTDevice(std::string device, bool searchBT);

      Opens a connection to a specific NXT Device, by providing either the 
      Device Name or MAC Address.

      Compatible with multiple NXT Devices!
      You can open simultaneous connections to devices connected by both
      USB or Bluetooth.


Completed in this version:

   std::string NXT::GetName(Comm::NXTComm* comm)
   bool NXT::SetName(Comm::NXTComm* comm, char* name)

      Read the Device Name of an NXT Brick, or
      Set a new Device Name.

      These functions are now fully implemented in this version.


Fixed bugs:

   double NXT::GetFirmwareVersion(Comm::NXTComm* comm)

      Now returns the correct minor version number.


REQUIREMENTS
------------

1. Windows: A standard C++ compiler

   Linux:  NXT++ < v0.6
           libusb (http://libusb.sourceforge.net)

2. The knowledge of basic compiling operations in your compiler


HOW TO CREATE A NEW PROJECT IN MSVC++ 2010
------------------------------------------

1. Install the Fantom Driver
You can find it here: 
http://mindstorms.lego.com/en-us/support/files/Driver.aspx
The Fantom driver was designed for OSX and win32 applications, so if you are
using 64-bit, you will need to create a win32 application and link to the
32-bit fantom.lib file.

2. Install the Mindstorms NXT Driver
This is available for 32 and 64-bit systems.
If you can't find it, it should be located in the "/Products" directory of
the Fantom Driver zip file.

3. Create a new project e.g. 32-bit console application

4. Copy the "nxtpp_07" directory into the location of the main *.cpp source file
for the new project.
In the Solution Explorer window on the left-hand side of MSVC we need to add
the source and header files for NXT++ to the project.

5. Right-click on the "Source Files" folder, click "Add" and select 
"Existing Item". 
Add the "comm.cpp" and "nxt++.cpp" files from the "nxtpp_07/src" directory.

6. Right-click on the "Header Files" folder, click "Add" and select 
"Existing Item". 
Add the "comm.h", "NXT++.h", and "visatype.h" files from the "nxtpp_07/include" 
directory.

7. Check the top of all the *.h and *.cpp files to ensure that the include paths 
are specified correctly, e.g.:
#include "nxtpp_07\include\NXT++.h"
#pragma comment (lib, "nxtpp_07/lib/fantom.lib" )

8. To test NXT++, you may copy the code from inside the "nxtpp_07_demo.txt" file 
in the "examples" folder and paste it into your project's main source file.

9. Build the project
MSVC may give you lots of warning about "unsafe" functions, but you can ignore
this.

10. Connect your NXT via USB cable.

10. Run the demo
If everything is working, the program will output a list of all connected NXT
Devices.

You should study the source code so you know how the demo works, then proceed
to read the Tutorials and API Documentation on the NXT++ website.


WHERE TO GET HELP
-----------------
1. NXT++'s documentation (http://nxtpp.sourceforge.net/docs/index.html)
2. NXT++ wiki (http://nxtpp.wetter61169.de/mediawiki-1.6.9/index.php/Main_Page)
3. NXT++'s website (http://nxtpp.sourceforge.net)
4. The example programs
5. The source itself (NXT++.h)
6. The NXT++ community (http://sourceforge.net/forum/?group_id=193451)


WANT TO HELP?
-------------

You can contribute to the NXT++ project.

Future work includes:
   * Automatically pair with Bluetooth devices
   * Add function to write to LCD on NXT


+------------------------------------------------------------------------------+
