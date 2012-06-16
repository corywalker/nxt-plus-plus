#include "comm.h"
#include "time.h"


// global variable
nFANTOM100::tStatus status;
nFANTOM100::iNXTIterator* nxtIteratorPtr = NULL;
nFANTOM100::iNXT* nxtPtr = NULL;
//For fetching list of files
nFANTOM100::iFileIterator* fileIteratorPtr = NULL;

//! Checks to see if an NXT file is valid.
bool NXTFile::isValid()
{
	return file != NULL;
}

//! Opens an NXT file.
int NXTFile::open(int mode, int size)
{	
	bool iswrite = false;

	if (!isValid())
		return InvalidFileHandler;

	nFANTOM100::tStatus status;

	switch(mode)
	{
	case 0:
		//read
		file->openForRead(status);
		//printf("%s\n", status.isNotFatal());
		break;

	case 1:
		//write
		file->openForWrite(size, status);
		iswrite = true;
		break;

	case 2:
		//append
		file->openForDataAppend(status);
		iswrite = true;
		break;

	case 3:
		//dataWrite
		file->openForDataWrite(size, status);
		iswrite = true;
		break;

	case 4:
		file->openForLinearWrite(size, status);
		iswrite = true;
		break;

	default:
		return UnsupportedType;

	}

	if (status.isNotFatal())
	{
		isOpen = true;
		isWriteable = iswrite;
		return 0;
		//printf("win\n");
	}

	isOpen = false;
	isWriteable = false;

	return FileOpenFailed;
}

//! Deletes a file from the NXT.
int NXTFile::remove() 
{
     if (!isValid())
		 return InvalidFileHandler;

	 nFANTOM100::tStatus status;
	 file->remove(status);

	 if (status.isNotFatal())
		 return 0;

	 return -1;

}

//! Reads the file into a buffer.
int NXTFile::read(char *buff, int size) 
{
	if (!isValid())
		return InvalidFileHandler;

	if (!isOpen)
		return FileNotOpen;

	nFANTOM100::tStatus status;
	file->read(reinterpret_cast<ViPBuf> (buff), size, status);

	if (status.isNotFatal())
		return 0;

	return ReadFailed;

}

//! Writes data to the file.
int NXTFile::write(char *buff, int size)
{
	if (!isValid())
		return InvalidFileHandler;

	if (!isOpen)
		return FileNotOpen;

	if (!isWriteable)
		return WriteNotEnabled;

	if (size < 0)
		return WriteBufferIllegalSize;

	nFANTOM100::tStatus status;
    file->write(reinterpret_cast<ViPBuf> (buff), size, status);

	if (status.isNotFatal())
		return 0;

	return WriteFailed;
}

//! Closes the NXTFile.
int NXTFile::close()
{
	if (!isValid())
		return 0;

	nFANTOM100::tStatus status;
	file->close(status);

	return 0;
}

const char* NXTFileIterator::getCurrFileName()
{
	if (!isValid())
		return NULL;

	nFANTOM100::tStatus status;
	char *name = (char*) malloc(20);
	
	iter->getName(name, status);	

	if (status.isNotFatal())
		return name;

	return NULL;
}

int NXTFileIterator::getCurrFileSize()
{
	if (!isValid())
		return InvalidFileIterator;

	nFANTOM100::tStatus status;
	int size = iter->getSize(status);

	if (status.isNotFatal())
		return size;

	return -1;
}

int NXTFileIterator::getFile(NXTFile& file)
{
	if (!isValid())
		return InvalidFileIterator;

	nFANTOM100::tStatus status;
	nFANTOM100::iFile *fptr = iter->getFile(status);

	if (status.isNotFatal())
		file = NXTFile(fptr);
    else
		return -1;

	return 0;
}

int NXTFileIterator::next()
{
	if (!isValid())
		return InvalidFileIterator;

	nFANTOM100::tStatus status;
	iter->advance(status);

	if (status.isNotFatal()) 
		return 0;

	return IteratorAdvanceFailed;
}

bool NXTFileIterator::isValid()
{
	return iter != NULL;
}

int NXTModuleIterator::next()
{
	int res = 0;
	nFANTOM100::tStatus status;
	if (internalIter != NULL)
	{
		internalIter->advance(status);
		if(status.isNotFatal())
			res = 0;
		else
			res = -1;
	}
	else res = -1;

	return res;
}

int NXTModuleIterator::getModule(NXTModule &module)
{
	if (internalIter == NULL)
		return -1;

	int res = 0;
	nFANTOM100::tStatus status;
	nFANTOM100::iModule *m = internalIter->getModule(status);

	if (status.isNotFatal())
	    module = NXTModule(m);
	else
		res = -1;

	return res;
}

int NXTModuleIterator::getName(std::string &s)
{
	if (internalIter == NULL)
		return -1;

	int res = 0;
	nFANTOM100::tStatus status;
	char *name = (char *)malloc(20);
	internalIter->getName(name, status);

	if (status.isNotFatal())
	{
	    s = name;
		
	}
	else
		res = status.getCode();

	return res;
}

int NXTModule::getName(std::string &s)
{
	if (internalModule == NULL)
		return -1;

	int res = 0;
	//nFANTOM100::tStatus status;
	char *name = (char *)malloc(20);
	internalModule->getName(name);

	/*if (status.isNotFatal())
	    s = name;
	else
		res = -1;*/

	return res;
}

int NXTModule::getModuleID(int &id)
{
	if (internalModule == NULL)
		return -1;

	int res = 0;
	//nFANTOM100::tStatus status;	
	id = internalModule->getModuleID();

	/*if (status.isFatal())
	    res = -1;*/

	return res;
}

int NXTModule::getModuleSize(int &size)
{
	if (internalModule == NULL)
		return -1;

	int res = 0;
	//nFANTOM100::tStatus status;	
	size = internalModule->getModuleSize();

	/*if (status.isFatal())
	    res = -1;*/

	return res;
}

int NXTModule::getIOMapSize(int &size)
{
	if (internalModule == NULL)
		return -1;

	int res = 0;
	//nFANTOM100::tStatus status;	
	size = internalModule->getModuleIOMapSize();

	/*if (status.isFatal())
	    res = -1;*/

	return res;
}

int NXTModule::readIOMap(ViPByte buffer, int offset, int bytes)
{
	if (internalModule == NULL)
		return -1;

	int res = 0;
	nFANTOM100::tStatus status;	
	internalModule->readIOMap(offset, bytes, buffer, status);

	if (status.isFatal())
	    res = -1;

	return res;
}

int NXTModule::writeIOMap(ViPByte buffer, int offset, int bytes)
{
	if (internalModule == NULL)
		return -1;

	int res = 0;
	nFANTOM100::tStatus status;	
	internalModule->writeIOMap(offset, bytes, buffer, status);

	if (status.isFatal())
	    res = -1;

	return res;
}

// Searches for robots in the area and places their names in an array of strings
void Comm::SearchBT(std::vector<std::string> *names) 
{ 
	bool first = false;
	char* tmp;
	ViChar resourceName[256]; 
	ViChar lastName[256]; 
	nxtIteratorPtr = nFANTOM100::iNXT::createNXTIterator(true, 1, status ); 
	if( status.isNotFatal()) { 
		while(!first) { 
			strcpy(lastName, resourceName); 
			nxtIteratorPtr->getName(resourceName, status);  
			if(!strcmp(lastName, resourceName)) { // if the advance reached the end 
				first = true; 
			} else {
				if (status.isNotFatal() >= 0) {
					tmp = strtok(resourceName, "::");
					tmp = strtok(NULL, "::");
					names->push_back(tmp); 
				}
				nFANTOM100::iNXT::destroyNXT( nxtPtr );
				nxtIteratorPtr->advance(status);
			}
		} 
	}
	nFANTOM100::iNXT::destroyNXTIterator( nxtIteratorPtr );
} 

bool Comm::NXTComm::Open()
{
	// Create an NXT iterator object which is used to find all accessible NXT devices.
	nxtIteratorPtr = nFANTOM100::iNXT::createNXTIterator(
		false /* don't search for NXTs over Bluetooth (only search USB) */,
		1 /* timeout for Bluetooth discovery ignored */, status );

	// Creating the NXT iterator object could fail, better check status before dereferencing a
	//    potentially NULL pointer.
	if( status.isNotFatal())
	{
		// Create an NXT object for the first NXT that was found.  Note that if a NXT is found
		//    over BT, the computer and the NXT must be paired before an NXT object can be
		//    created.  This can be done programatically using the iNXT::pairBluetooth method.
		nxtPtr = nxtIteratorPtr->getNXT( status );

		// Destroy the NXT iterator object which we no longer need
		nFANTOM100::iNXT::destroyNXTIterator( nxtIteratorPtr );
	}
	return status.isNotFatal();
}

bool Comm::NXTComm::OpenBT()
{
	// Create an NXT iterator object which is used to find all accessible NXT devices.
	nxtIteratorPtr = nFANTOM100::iNXT::createNXTIterator(
		true /* don't search for NXTs over Bluetooth (only search USB) */,
		1 /* timeout for Bluetooth discovery ignored */, status );
			
	// Creating the NXT iterator object could fail, better check status before dereferencing a
	// potentially NULL pointer.
	if( status.isNotFatal())
	{
		// Create an NXT object for the first NXT that was found.  Note that if a NXT is found
		//    over BT, the computer and the NXT must be paired before an NXT object can be
		//    created.  This can be done programatically using the iNXT::pairBluetooth method.
		nxtPtr = nxtIteratorPtr->getNXT( status );

		// Destroy the NXT iterator object which we no longer need
		nFANTOM100::iNXT::destroyNXTIterator( nxtIteratorPtr );
	}
	return status.isNotFatal();
}

bool Comm::NXTComm::OpenBT(char * name) 
{ 
	bool first = false; 
	ViChar resourceName[256]; 
	ViChar lastName[256]; 
	nxtIteratorPtr = nFANTOM100::iNXT::createNXTIterator(true, 1, status ); 
	if( status.isNotFatal()) { 
		while(!first) { 
			strcpy(lastName, resourceName); 
			nxtIteratorPtr->getName(resourceName, status); 
			if(!(strstr(resourceName, name))) { 
				//printf("get next: %s\n", resourceName); 
				nxtIteratorPtr->advance(status); 
				if(!strcmp(lastName, resourceName)) { // if the advance reached the end 
					printf("failed to connect to $s\n", name); 
					first = true; 
				} 
			} else { 
				first = true; 
			} 
		} 
		if( status.isNotFatal()) { // make sure the advance didn't fail 
			nxtPtr = nxtIteratorPtr->getNXT( status ); 
			// Destroy the NXT iterator object which we no longer need 
			nFANTOM100::iNXT::destroyNXTIterator( nxtIteratorPtr ); 
		} else {
			nFANTOM100::iNXT::destroyNXTIterator( nxtIteratorPtr );
		}
	} 
	return status.isNotFatal(); 
} 

void Comm::NXTComm::Close()
{
	// Destroy the NXT object.
	nFANTOM100::iNXT::destroyNXT( nxtPtr );
}

void Comm::NXTComm::SendDirectCommand(ViBoolean response, ViByte * dc_buf, int dc_buf_size, ViByte *re_buf, int re_buf_size) 
{
	nxtPtr->sendDirectCommand( response /* a response is not required for this direct command */,
		dc_buf, dc_buf_size,
		re_buf /* no response buffer */, re_buf_size /* no response buffer, specify 0 for size */, status );
}

double Comm::NXTComm::GetProtocolVersion()
{
	ViUInt8 protocolVersionMajor, protocolVersionMinor, firmwareVersionMajor, firmwareVersionMinor;
	nxtPtr->getFirmwareVersion( protocolVersionMajor, protocolVersionMinor, firmwareVersionMajor, firmwareVersionMinor, status );
	double version = protocolVersionMinor;
	while(version >= 1)
		version /= 10;
	version += protocolVersionMajor;
	return version;
}

double Comm::NXTComm::GetFirmwareVersion()
{
	ViUInt8 protocolVersionMajor, protocolVersionMinor, firmwareVersionMajor, firmwareVersionMinor;
	nxtPtr->getFirmwareVersion( protocolVersionMajor, protocolVersionMinor, firmwareVersionMajor, firmwareVersionMinor, status );
	double version = firmwareVersionMinor;
	while(version >= 1)
		version /= 10;
	version += firmwareVersionMajor;
	return version;
}

std::string Comm::NXTComm::GetName()
{
	ViChar name[16];
	ViByte bluetoothAddress[6];
	ViUInt8 signalStrength[4];
	ViUInt32 availableFlash;
	nxtPtr->getDeviceInfo( name, bluetoothAddress, signalStrength, availableFlash, status );
	name[15] = NULL;
	return (std::string)name;
}
// Sets the name of the nxt
bool Comm::NXTComm::SetName(char* name) {
	ViConstString newName = name;
	nxtPtr->setName(newName, status);
	return status.isNotFatal();
}
//! Returns the amount of flash memory left
double Comm::NXTComm::GetAvailableFlash()
{
	ViChar name[16];
	ViByte bluetoothAddress[6];
	ViUInt8 signalStrength[4];
	ViUInt32 availableFlash;
	nxtPtr->getDeviceInfo( name, bluetoothAddress, signalStrength, availableFlash, status );
	return (double)availableFlash/1024;
}

//! Retrieves a specified file into an NXTFile.
NXTFile Comm::NXTComm::GetNXTFile(std::string filename, bool &isFatal)
{
	isFatal = true;
	nFANTOM100::tStatus status;

	NXTFile file;		
	nFANTOM100::iFile* iFile = nxtPtr->createFile(filename.c_str(), status);

	if (status.isNotFatal())
	{
		file = NXTFile(iFile);
		isFatal = false;
	}

	return file;

}

//! Searches for files on the NXT and stores the results in an NXTFileIterator.
NXTFileIterator Comm::NXTComm::GetFileIterator(std::string pattern, bool &isFatal) 
{
	isFatal = true;
	nFANTOM100::tStatus status;

	NXTFileIterator iter;		
	nFANTOM100::iFileIterator* fileI = nxtPtr->createFileIterator(pattern.c_str(), status);
	
	if (status.isNotFatal())
	{		    
	    iter.iter = fileI;
		isFatal = false;
	}		

	return iter;
}

//!Destroys an NXTFileIterator.
void Comm::NXTComm::destroyFileIterator(NXTFileIterator &iter)
{
	if (iter.isValid())
		nxtPtr->destroyFileIterator(iter.iter);
}

//! Destroys an NXTFile.
void Comm::NXTComm::destroyFile(NXTFile &file)
{
	if (file.isValid())
		nxtPtr->destroyFile(file.file);
}

//! Searches for modules on the NXT and stores the results in an NXTModuleIterator.
NXTModuleIterator Comm::NXTComm::GetModuleIterator(std::string pattern, int &statusCode)
{
	statusCode = 0;
	nFANTOM100::tStatus stat;

	NXTModuleIterator iter;		
	nFANTOM100::iModuleIterator* moduleI = nxtPtr->createModuleIterator(pattern.c_str(), stat);

	if (stat.isNotFatal())
		iter = NXTModuleIterator (moduleI);
	else
		statusCode = stat.getCode();	
	return iter;
}

//! Destroys an NXTModuleIterator.
void Comm::NXTComm::destroyModuleIterator(NXTModuleIterator &iter)
{
	nxtPtr->destroyModuleIterator(iter.internalIter);
}

//! Retrieves a specified module into an NXTModule.
NXTModule Comm::NXTComm::GetModule(std::string moduleName, int moduleID, int moduleSize, int ioMapSize, int &statCode)
{
	statCode = 0;
	nFANTOM100::tStatus status;

	NXTModule internalMod;
	char *mname = const_cast<char*> (moduleName.data());
	nFANTOM100::iModule* module = 
		nxtPtr->createModule(mname, moduleID, moduleSize, ioMapSize, status);

	if (status.isNotFatal())
		internalMod.internalModule = module;
	else
		statCode = status.getCode();

	return internalMod;
}

//! Destroys an NXTModule.
void Comm::NXTComm::destroyModule(NXTModule &module)
{
	nxtPtr->destroyModule(module.internalModule);
}