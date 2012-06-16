/*!
   \file iNXT.h
   \brief Interface for a LEGO MINDSTORMS NXT and declaration of its factory.
*/
/*
   © Copyright 2005-2006,
   National Instruments Corporation.
   All rights reserved.

   File:        iNXT.h
   Originated:  12 May 2005
*/

#ifndef ___fantom_iNXT_h___
#define ___fantom_iNXT_h___


// includes...

#ifndef ___fantom_platform_h___
   #include "platform.h"
#endif

#ifndef ___fantom_iFile_h___
   #include "iFile.h"
#endif

#ifndef ___fantom_iFileIterator_h___
   #include "iFileIterator.h"
#endif

#ifndef ___fantom_iModule_h___
   #include "iModule.h"
#endif

#ifndef ___fantom_iModuleIterator_h___
   #include "iModuleIterator.h"
#endif

#ifndef ___fantom_iNXTIterator_h___
   #include "iNXTIterator.h"
#endif

#ifndef ___fantom_tStatus_h___
   #include "tStatus.h"
#endif

// defines...


namespace nFANTOM100
{
   // forward declarations...

   // typedefs...

   // classes...

   /*!
      \class iNXT
      \brief Interface to a LEGO MINDSTORMS NXT.
   */
   class iNXT
   {
      // methods
   protected:

         //! Destructor
         virtual ~iNXT() = 0;

   public:

         //! Enumeration of buffer types on the NXT
         enum tBuffer
         {
            // The buffer associated with the standard port.
            kBufferStandard,
            
            // The buffer associated with the high-speed port.
            kBufferHighSpeed
         };

         //! Creates a file object for the file with the specified name on this NXT.
         /*!
            Invoking this method does not actually create a file on the NXT.  Rather, this method
               creates a file object which may be used to open a file on this NXT, for reading or
               writing, or may be used to delete a file on the NXT.
            A file is not created if the specified status is fatal.
            The returned file object should be destroyed using the iNXT::destroyFile method.

            \param fileName Name of the file.  The file name must conform to the 15.3 naming
               convention and be NULL-terminated.
            \param status Status chaining object.
            \return A pointer to the iFile object that was created.
         */
         virtual iFile* createFile( ViConstString fileName, tStatus& status ) = 0;


         //! Destroys the specified file object.
         /*!
            Invoking this method does not actually delete a file on the NXT.  Rather, this method
               destroys a file object which may have been used to open a file on this NXT for
               reading or writing, or may have been used to delete a file on the NXT.

            \param filePtr Pointer to the file object to destroy.
         */
         virtual void destroyFile( iFile* filePtr ) = 0;


         //! Creates an iterator to the files on this NXT.
         /*!
            The iterator traverses those files on this NXT that match the specified file name
               pattern.
            The iterator is not created if the specified status is fatal.
            The returned file iterator object should be destroyed using the
               iNXT::destroyFileIterator method.

            \param fileNamePattern The file name pattern against which to match when iterating
               over the files on this NXT.  The file name pattern may contain wildcards.  The
               wildcards may be used in the following manner: *.* (all files on this NXT);
               fileBaseName.* (all files on this NXT with the specified base name regardless of
               extension); *.fileExtension (all files on this NXT with the specified extension,
               regardless of basename); fileBaseName.fileExtension (the file on this NXT with the
               specified base name and extension).
            \param status Status chaining object.
            \return A pointer to the iFileIterator object that was created.
         */
         virtual iFileIterator* createFileIterator( ViConstString fileNamePattern,
               tStatus& status ) = 0;


         //! Destroys the specified file iterator.
         /*!
            \param fileIteratorPtr A pointer to the file iterator to destroy.
         */
         virtual void destroyFileIterator( iFileIterator* fileIteratorPtr ) = 0;

         //! Creates a module object for the module with the specified name on this NXT.
         /*!
            Invoking this method does not actually create a module on the NXT.  Rather, this
               method creates a module object which may be used to access an I/O map on this NXT.
            A module is not created if the specified status is fatal.
            The returned module object should be destroyed using the iNXT::destroyModule method.

            \param moduleName The name of the module.  The module name must conform to the 15.3
               naming convention and be NULL-terminated.
            \param moduleID The NXT-internal ID of the module.
            \param moduleSizeInBytes The number of bytes the module occupies.
            \param ioMapSizeInBytes The number of bytes the module's I/O map occupies.
            \param status Status chaining object.
            \return A pointer to the iModule object that was created.
         */
         virtual iModule* createModule( ViConstString moduleName, ViUInt32 moduleID,
               ViUInt32 moduleSizeInBytes, ViUInt32 ioMapSizeInBytes, tStatus& status ) = 0;

         //! Destroys the specified module object.
         /*!
            Invoking this method does not actually delete a module on this NXT.  Rather, this
               method destroys a module object which may have been used to access an I/O map on
               this NXT.

            \param modulePtr Pointer to the module object to destroy.
         */
         virtual void destroyModule( iModule* modulePtr ) = 0;


         //! Creates an iterator to the modules on this NXT.
         /*!
            The iterator traverses those modules on this NXT that match the specified module name
               pattern.
            The iterator is not created if the specified status is fatal.
            The returned module iterator object should be destroyed using the
               iNXT::destroyModuleIterator method.

            \param moduleNamePattern The module name pattern against which to match.  The module
               name pattern may contain wildcards.  Since extensions are implicit in the case of
               modules, a wildcard may only be used for the module name, as in "*.mod".
            \param status Status chaining object.
            \return A pointer to an iModuleIterator object that was created.
         */
         virtual iModuleIterator* createModuleIterator( ViConstString moduleNamePattern,
               tStatus& status ) = 0;


         //! Destroys the specified module iterator.
         /*!
            \param moduleIteratorPtr A pointer to the module iterator object to destroy.
         */
         virtual void destroyModuleIterator( iModuleIterator* moduleIteratorPtr ) = 0;

         //! Retrieves the firmware version of this NXT.
         /*!
            Returns the protocol and firmware versions installed on this NXT.
            The current version of this driver supports a protocol major version number of 1 and a
               firmware major version number of 1.  If either of these major version numbers is a
               value other than 1, the driver will not attempt to communicate to the NXT.
            The returned versions are undefined if the specified status is fatal.

            \param protocolVersionMajorRef Reference to parameter that will be populated with the
               major protocol version.
            \param protocolVersionMinorRef Reference to parameter that will be populated with the
               minor protocol version.
            \param firmwareVersionMajorRef Reference to parameter that will be populated with the
               major firmware verison.
            \param firmwareVersionMinorRef Reference to parameter that will be populated with the
               minor firmware verison.
            \param status Status chaining object.
         */
         virtual void getFirmwareVersion( ViUInt8& protocolVersionMajorRef,
               ViUInt8& protocolVersionMinorRef, ViUInt8& firmwareVersionMajorRef,
               ViUInt8& firmwareVersionMinorRef, tStatus& status ) = 0;


         //! Sends the specified direct command to this NXT.
         /*!
            For more information on direct commands, refer to the LEGO MINDSTORMS NXT Direct
               commands document.
            The command is not sent if the specified status is fatal.
            The command buffer must be non-NULL and the command buffer size in bytes must be
               non-zero.
            If require response is set to true, the response buffer must be non-NULL and the
               response buffer size in bytes must be non-zero.
            If require response is set to false, the response buffer must be NULL and the
               response buffer size in bytes must be zero.
            Both of the buffer size parameters must be small enough to fit in one packet for
               whichever bus the NXT is connected over (USB or Bluetooth).  This means the
               maximum length for a direct command over USB is 63 bytes; over Bluetooth, 65,533
               bytes.
            If any of these requirements are violated, VI_ERROR_USER_BUF will be returned.

            \param requireResponse Boolean flag indicating if a response is required.
            \param commandBufferPtr Buffer containing the direct command to send to the NXT.
            \param commandBufferSizeInBytes Number of bytes in the command buffer.
            \param responseBufferPtr Buffer that will be populated with the response to the direct
               command.
            \param responseBufferSizeInBytes Capacity of the response buffer in bytes.
            \param status Status chaining object.
            \return Number of bytes written to the response buffer.
         */
         virtual ViUInt32 sendDirectCommand( ViBoolean requireResponse, const ViByte commandBufferPtr[],
               ViUInt32 commandBufferSizeInBytes, ViPBuf responseBufferPtr,
               ViUInt32 responseBufferSizeInBytes, tStatus& status ) = 0;

         //! Downloads firmware to this NXT.
         /*!
            The NXT must already be in firmware-download mode.

            \param firmwareBufferPtr The buffer containing the new firmware binary image.
            \param firmwareBufferSizeInBytes The number of bytes in the new firmware image.
            \param status Status chaining object.
         */
         virtual void downloadFirmware( const ViByte firmwareBufferPtr[],
               ViUInt32 firmwareBufferSizeInBytes, tStatus& status ) = 0;


         //! Writes, in a generic fashion, to this NXT.
         /*!
            Writes a command directly to this NXT.  In general, this method isn't used and,
               instead, the sendDirectCommand and other more specific methods are invoked when
               communication to the NXT.
            The write doesn not occur if the specified status is fatal.

            \param bufferPtr A pointer to the buffer that contains the command that will be
               written.
            \param numberOfBytes Size of the buffer.
            \param status Status chaining object.
            \return The number of bytes actually written to the NXT.
         */
         virtual ViUInt32 write( const ViByte bufferPtr[], ViUInt32 numberOfBytes,
               tStatus& status ) = 0;

         //! Reads, in a generic fashion, from this NXT.
         /*!
            Reads a response directly from this NXT.  In general, this method isn't used and,
               instead, the sendDirectCommand and other more specific methods are invoked when
               communication to the NXT.
            The command is not sent if the specified status is fatal.

            \param bufferPtr A pointer to the buffer that will be populated with the response.
            \param numberOfBytes Number of bytes expected to be read from this NXT.
            \param status Status chaining object.
            \return The number of bytes actually read from this NXT.
         */
         virtual ViUInt32 read ( ViPBuf bufferPtr, ViUInt32 numberOfBytes, tStatus& status ) = 0;

         //! Reboots this NXT into firmware-download mode.
        /*!
           This is required before invoking the downloadFirmware method.
           The reboot does not occur is the specified status is fatal.

           \param status Status chaining object.
        */
         virtual void bootIntoFirmwareDownloadMode( tStatus& status ) = 0;

         //! Sets the name of this NXT.
        /*!
           The specified name will be displayed on the NXT, show up during Bluetooth scans, and
            returned when the getDeviceInfo method is called.

           \param newName The name for the NXT.  The name can be at most 15 characters.  However,
            the NXT can only display 8 characters.  The string must be NULL terminated.
           \param status Status chaining object.
        */
         virtual void setName( ViConstString newName, tStatus& status ) = 0;

         //! Retrieves basic information about this NXT.
         /*!
            Retrieves the name of this NXT, its Bluetooth address, the Bluetooth signal strength,
               and the number of bytes available.
            Information retrieval is not done if specified status is fatal.

            \param name Populated with the name of this NXT.  The name character array must be
               able to accomodate a NULL-terminated 15 character name.  That is, it must have a
               capacity of 16 bytes.
            \param bluetoothAddress Populated with this NXT's Bluetooth address.  The bluetooth
               address array must have a capacity of six bytes.
            \param signalStrength Populated with strength of the signal for this NXT's four
               Bluetooth conenctions.  The signal strength array must have a capacity of four
               bytes.
            \param availableFlash Populated with the amount of memory in bytes that is not
               occupied by firmware or user files.
            \param status Status chaining object.
        */
         virtual void getDeviceInfo( ViChar name[], ViByte bluetoothAddress[],
               ViUInt8 signalStrength[], ViUInt32 &availableFlash, tStatus& status ) = 0;

         //! Erases all files from this NXT, leaving only the firmware.
         /*!
            All programs, sounds, and data logs are erased.
            The erasure does not occur if specified status is fatal.

            \param status Status chaining object.
         */
         virtual void eraseUserFlash( tStatus& status ) = 0;

         //! Polls the data buffer on this NXT for the number of bytes available to be read.
         /*
            The data buffer is not polled if the specified status is fatal.

            \param bufferSelector The buffer from which to read.
            \param status Status chaining object.
            \return The number of bytes in the buffer available to be read.
         */
         virtual ViUInt32 pollAvailableLength( tBuffer bufferSelector, tStatus& status ) = 0;

         //! Reads data from the data buffer on this NXT.
         /*!
            Data is not read if the specified status is fatal.
            
            \param dataBuffer Populated with the data that is read from the specified buffer.
            \param bufferSelector The buffer from which to read.
            \param numberOfBytesToRead The number of bytes to read from the data buffer.
            \param status Status chaining object.
            \return The number of bytes actually read from the data buffer.
         */
         virtual ViUInt32 readBufferData( ViPBuf dataBuffer, tBuffer bufferSelector,
               ViUInt32 numberOfBytesToRead, tStatus& status ) = 0;

         //! Retrieves the resource string for this NXT's session.
         /*
            An example resource string could look like the one of the following:
               BTH::LEGOBrick::00:16:53:04:05:06::5
               BTH::LEGOBrick::00:16:53:04:05:06::1
               BTH::Brick2::00:16:53:44:FF:66
               USB0::0x0694::0x0002::0016535127BA::RAW
            
            \param resourceString Populated with the resource string. The resource string must
               have a capacity of 256 bytes.
            \param status Status chaining object.
         */
         virtual void getResourceString( ViChar resourceString[], tStatus& status ) = 0;

         //! Resets the Bluetooth module on this NXT to its factory settings.
         /*
            \param status Status chaining object.
         */
         virtual void bluetoothFactoryReset( tStatus& status ) = 0;

         //! Creates an NXT object
         /*!
            Creates an NXT object representing the specified NXT.
            The NXT object is not created if the specified status is fatal.
            The returned NXT object should be destroyed using the iNXT::destroyNXT method.

            \param resourceString A string identifying which resource should be opened.  A list
               of possible strings can be obtained using an iNXTIterator (refer to the
               createNXTIterator method).
            \param status Status chaining object.
            \param checkFirmwareVersion A boolean flag that specifies whether version validation
               should occur (defaults to true).
            \return A pointer to the iNXT object that was created.
         */
         nFANTOM100_kExport static iNXT* _VI_FUNCC createNXT( ViConstString resourceString,
               tStatus& status, ViBoolean checkFirmwareVersion = true );

         //! Destroys an NXT object
         /*!
            \param nxtPtr A pointer to the NXT object to destroy; may be NULL
         */
         nFANTOM100_kExport static void _VI_FUNCC destroyNXT( iNXT* nxtPtr );

         //! Creates an NXT iterator.
         /*!
            The NXT iterator can be used to find all NXTs that are connected (USB) or in range
               (Bluetooth).
            The NXT iterator is not created if the specified status is fatal.
            The returned NXT iterator object should be destroyed using the
               iNXT::destroyNXTIterator method.

            \param searchBluetooth A boolean flag that specifies if the iterator should traverse
               NXTs via Bluetooth.
            \param bluetoothSearchTimeoutInSeconds The minimum number of seconds that should be
               spent waiting for Bluetooth devices to respond.
            \param status Status chaining object.
            \return A pointer to the iNXTIterator object that was created.
         */
         nFANTOM100_kExport static iNXTIterator* _VI_FUNCC createNXTIterator(
               ViBoolean searchBluetooth, ViUInt32 bluetoothSearchTimeoutInSeconds,
               tStatus& status );

         //! Destroys an NXT iterator object.
         /*
            \param iterPtr A pointer to the iNXTIterator object to destroy.
         */
         nFANTOM100_kExport static void _VI_FUNCC destroyNXTIterator( iNXTIterator* iterPtr );

         //! Pairs with an NXT via Bluetooth.
         /*!
            Programmatically pairs the specified NXT to this computer and, on Windows, creates a
               virtual serial port to use for communication with that NXT.  However, clients
               should not depend on the creation of this virtual serial port.
            The pairing is not done if the specified status is fatal.

            \param resourceName The resource string that specifies the NXT with which to pair.
            \param passkey A string containing the passkey the computer should exchange with the
               device.  The passkey cannot be longer than 15 characters and must be
               NULL-terminated.
            \param pairedResourceName A Bluetooth resource string representing the paired device.
               On Windows, the specified resourceName is suffixed with the COM port; On Mac OS X,
               the RFCOMM channel identifier. The resource string must have a capacity of 256
               bytes.
            \param status Status chaining object.
         */
         nFANTOM100_kExport static void _VI_FUNCC pairBluetooth( ViConstString resourceName,
               ViConstString passkey, ViChar pairedResourceName[], tStatus& status );

         //! Unpairs with an NXT via Bluetooth.
         /*!
            Programmatically destroys the Bluetooth pairing that was previously established
               between this computer and the specified NXT.  On Mac OS X, this method has no
               effect and doesn't generate a fatal status.
            The unpairing is not done if the specified status is fatal.

            \param resourceName The resource string that specifies the NXT with which to unpair.
            \param status Status chaining object.
         */
         nFANTOM100_kExport static void _VI_FUNCC unpairBluetooth( ViConstString resourceName,
               tStatus& status );

         //! Determines if the NXT associated with the specified resource string is paired.
         /*!
            The determination is not done if the specified status is fatal.
            
            \param resourceName A resource string that specifies the NXT for which to check its
               pairing status.
            \param status Status chaining object.
            \return VI_TRUE if the NXT is paired with this computer (or if it is connected via
               USB); VI_FALSE otherwise.
         */
         nFANTOM100_kExport static ViBoolean _VI_FUNCC isPaired( ViConstString resourceName,
               tStatus& status );
         
         //! Finds the NXT that is currently in firmware-download mode.
         /*!
            Note that only a single NXT may be in firmware-download mode at a time.

            \param resourceName Populated with the resource string. The resource string must
               have a capacity of 256 bytes.
            \param status Status chaining object.
         */
         nFANTOM100_kExport static void findDeviceInFirmwareDownloadMode( ViChar resourceName[],
               tStatus& status );


      private:

   };

   // constants...

} // namespace nFANTOM100


   // declarations for globally-scoped globals...

   // typedefs...
   typedef ViObject nFANTOM100_iNXT;

   // prototypes...
   extern "C"
   {

      nFANTOM100_kExport nFANTOM100_iNXTIterator _VI_FUNCC nFANTOM100_createNXTIterator(
            ViBoolean   searchBluetooth,
            ViUInt32    bluetoothSearchTimeoutInSeconds,
            ViStatus*   status );

      nFANTOM100_kExport void _VI_FUNCC nFANTOM100_destroyNXTIterator(
            nFANTOM100_iNXTIterator iterPtr,
            ViStatus* status );

      nFANTOM100_kExport void _VI_FUNCC nFANTOM100_pairBluetooth(
            ViConstString    resourceName,
            ViConstString    passkey,
            ViChar    pairedResourceName[],
            ViStatus*   status );

      nFANTOM100_kExport void _VI_FUNCC nFANTOM100_unpairBluetooth(
            ViConstString    resourceName,
            ViStatus*   status );

      nFANTOM100_kExport ViBoolean _VI_FUNCC nFANTOM100_isPaired(
            ViConstString  resourceName,
            ViStatus*      status );

      nFANTOM100_kExport nFANTOM100_iNXT _VI_FUNCC nFANTOM100_createNXT(
            ViConstString    resourceString,
            ViStatus*   status,
            ViBoolean   checkFirmwareVersion );

      nFANTOM100_kExport void _VI_FUNCC nFANTOM100_destroyNXT(
            nFANTOM100_iNXT  nxtPtr,
            ViStatus*      status );

      nFANTOM100_kExport nFANTOM100_iFile _VI_FUNCC nFANTOM100_iNXT_createFile(
            nFANTOM100_iNXT  nxtPtr,
            ViConstString       fileName,
            ViStatus*      status );

      nFANTOM100_kExport void _VI_FUNCC nFANTOM100_iNXT_destroyFile(
            nFANTOM100_iNXT  nxtPtr,
            nFANTOM100_iFile filePtr,
            ViStatus*      status );

      nFANTOM100_kExport nFANTOM100_iFileIterator _VI_FUNCC nFANTOM100_iNXT_createFileIterator(
            nFANTOM100_iNXT  nxtPtr,
            ViConstString       fileNamePattern,
            ViStatus*      status );

      nFANTOM100_kExport void _VI_FUNCC nFANTOM100_iNXT_destroyFileIterator(
            nFANTOM100_iNXT           nxtPtr,
            nFANTOM100_iFileIterator  fileIteratorPtr,
            ViStatus*               status );

      nFANTOM100_kExport nFANTOM100_iModule _VI_FUNCC nFANTOM100_iNXT_createModule(
            nFANTOM100_iNXT  nxtPtr,
            ViConstString       moduleName,
            ViUInt32       moduleID,
            ViUInt32       moduleSize,
            ViUInt32       ioMapSizeInBytes,
            ViStatus*      status );

      nFANTOM100_kExport void _VI_FUNCC nFANTOM100_iNXT_destroyModule(
            nFANTOM100_iNXT     nxtPtr,
            nFANTOM100_iModule  modulePtr,
            ViStatus*         status );

      nFANTOM100_kExport nFANTOM100_iModuleIterator _VI_FUNCC nFANTOM100_iNXT_createModuleIterator(
            nFANTOM100_iNXT  nxtPtr,
            ViConstString       moduleNamePattern,
            ViStatus*      status );

      nFANTOM100_kExport void _VI_FUNCC nFANTOM100_iNXT_destroyModuleIterator(
            nFANTOM100_iNXT              nxtPtr,
            nFANTOM100_iModuleIterator   moduleIteratorPtr,
            ViStatus*                  status );

      nFANTOM100_kExport void _VI_FUNCC nFANTOM100_iNXT_getFirmwareVersion(
            nFANTOM100_iNXT  nxtPtr,
            ViUInt8*       protocolVersionMajorPtr,
            ViUInt8*       protocolVersionMinorPtr,
            ViUInt8*       firmwareVersionMajorPtr,
            ViUInt8*       firmwareVersionMinorPtr,
            ViStatus*      status );

      nFANTOM100_kExport ViUInt32 _VI_FUNCC nFANTOM100_iNXT_sendDirectCommand(
            nFANTOM100_iNXT  nxtPtr,
            ViBoolean      requireResponse,
            const ViByte   commandBufferPtr[],
            ViUInt32       commandBufferSizeInBytes,
            ViPBuf         responseBufferPtr,
            ViUInt32       responseBufferSizeInBytes,
            ViStatus*      status );

      nFANTOM100_kExport void _VI_FUNCC nFANTOM100_iNXT_findDeviceInFirmwareDownloadMode(
            ViChar resourceString[],
            ViStatus*   status );

      nFANTOM100_kExport void _VI_FUNCC nFANTOM100_iNXT_downloadFirmware(
            nFANTOM100_iNXT nxtPtr,
            const ViByte    firmwareBufferPtr[],
            ViUInt32    firmwareBufferSize,
            ViStatus*   status );

      nFANTOM100_kExport ViUInt32 _VI_FUNCC nFANTOM100_iNXT_write(
            nFANTOM100_iNXT  nxtPtr,
            const ViByte         bufferPtr[],
            ViUInt32       numberOfBytes,
            ViStatus*      status );

      nFANTOM100_kExport ViUInt32 _VI_FUNCC nFANTOM100_iNXT_read(
            nFANTOM100_iNXT  nxtPtr,
            ViPBuf         bufferPtr,
            ViUInt32       numberOfBytes,
            ViStatus*      status );

      nFANTOM100_kExport void _VI_FUNCC nFANTOM100_iNXT_bootIntoFirmwareDownloadMode(
            ViConstString    resouceName,
            ViStatus*   status );

      nFANTOM100_kExport void _VI_FUNCC nFANTOM100_iNXT_setName(
            nFANTOM100_iNXT  nxtPtr,
            ViConstString       newName,
            ViStatus*      status );

      nFANTOM100_kExport void _VI_FUNCC nFANTOM100_iNXT_getDeviceInfo(
            nFANTOM100_iNXT  nxtPtr,
            ViChar       name[],
            ViByte        bluetoothAddress[],
            ViUInt8       signalStrength[],
            ViUInt32*      availableFlash,
            ViStatus*      status );

      nFANTOM100_kExport void _VI_FUNCC nFANTOM100_iNXT_eraseUserFlash(
            nFANTOM100_iNXT  nxtPtr,
            ViStatus*      status );

      nFANTOM100_kExport ViUInt32 _VI_FUNCC nFANTOM100_iNXT_pollAvailableLength(
            nFANTOM100_iNXT  nxtPtr,
            ViUInt32        bufferIndex,
            ViStatus*      status );

      nFANTOM100_kExport ViUInt32 _VI_FUNCC nFANTOM100_iNXT_readBufferData(
            nFANTOM100_iNXT  nxtPtr,
            ViPBuf         dataBuffer,
            ViUInt32       bufferIndex,
            ViUInt32       numberOfBytesToRead,
            ViStatus*      status );

      nFANTOM100_kExport void _VI_FUNCC nFANTOM100_iNXT_getResourceString(
            nFANTOM100_iNXT   nxtPtr,
            ViChar            resourceString[],
            ViStatus*         status );

      nFANTOM100_kExport void _VI_FUNCC nFANTOM100_iNXT_bluetoothFactoryReset(
            nFANTOM100_iNXT   nxtPtr,
            ViStatus*         status );


   }  // extern "C"


// inline functions and function macros...


#endif // ___fantom_iNXT_h___
