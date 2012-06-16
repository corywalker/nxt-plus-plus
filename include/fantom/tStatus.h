/*!
   \file tStatus.h
   \brief Status code class
*/
/*
   © Copyright 2005-2006,
   National Instruments Corporation.
   All rights reserved.

   File:        tStatus.h
   Originated:  10 March 2005
*/

#ifndef ___fantom_tStatus_h___
#define ___fantom_tStatus_h___

// includes ...

#ifndef ___fantom_platform_h___
   #include "platform.h"
#endif

#include <string.h>


// defines...

#define nFANTOM_mLocation __FILE__, __LINE__

#define nFANTOM_ForceToWarning(s)     (((s) >= 0 ) ? (s) : -(s))
#define nFANTOM_ForceToFatal(s)       (((s) <= 0 ) ? (s) : -(s))

/*!
   \brief The namespace for Fantom 1.0.
*/
namespace nFANTOM100
{
   // forward declarations...

   // typedefs...

   // classes...
   const ViInt32 kStatusOffset = -142000; // 0xFFFDD550
   const ViStatus kStatusSuccess = VI_SUCCESS;
   
   /*!
      \brief Enumeration of Fantom-specific status codes.  NI-VISA status codes may also be
         returned. These are documented in the NI-VISA Programmer Reference Manual which is
         available from <http://ni.com/>.
   */
   enum tFANTOMStatus
   {
      kStatusFirst                        = (kStatusOffset + 0),
      
      //! Error: Bluetooth pairing operation failed.
      //! Warning: You have already paired with that Bluetooth device.
      kStatusPairingFailed                = (kStatusOffset + -5),    // 0x54B
      
      //! Error: Bluetooth search failed.
      kStatusBluetoothSearchFailed        = (kStatusOffset + -6),    // 0x54A
      
      //! Error: System library not found.
      kStatusSystemLibraryNotFound        = (kStatusOffset + -7),    // 0x549
      
      //! Error: Bluetooth unpairing operation failed.
      kStatusUnpairingFailed              = (kStatusOffset + -8),    // 0x548
      
      //! Error: Invalid filename specified.
      kStatusInvalidFilename              = (kStatusOffset + -9),    // 0x547
      
      //! Error: Invalid iterator dereference. (No object to get.)
      kStatusInvalidIteratorDereference   = (kStatusOffset + -10),   // 0x546
      
      //! Error: Resource locking operation failed.
      kStatusLockOperationFailed          = (kStatusOffset + -11),   // 0x545
      
      //! Error: Could not determine the requested size.
      kStatusSizeUnknown                  = (kStatusOffset + -12),   // 0x544
      
      //! Error: Cannot open two objects at once.
      kStatusDuplicateOpen                = (kStatusOffset + -13),   // 0x543
      
      //! Error: File is empty.
      //! Warning: The requested file is empty.
      kStatusEmptyFile                    = (kStatusOffset + -14),   // 0x542
      
      //! Error: Firmware download failed.
      kStatusFirmwareDownloadFailed       = (kStatusOffset + -15),   // 0x541
      
      //! Error: Could not locate virtual serial port.
      kStatusPortNotFound                 = (kStatusOffset + -16),   // 0x540
      
      //! Error: No more items found.
      kStatusNoMoreItemsFound             = (kStatusOffset + -17),   // 0x53F
      
      //! Error: Too many unconfigured devices.
      kStatusTooManyUnconfiguredDevices   = (kStatusOffset + -18),   // 0x53E
      
      //! Error: Command mismatch in firmware response.
      kStatusCommandMismatch              = (kStatusOffset + -19),   // 0x53D
      
      //! Error: Illegal operation.
      kStatusIllegalOperation             = (kStatusOffset + -20),   // 0x53C
      
      //! Error: Could not update local Bluetooth cache with new name.
      //! Warning: Could not update local Bluetooth cache with new name.
      kStatusBluetoothCacheUpdateFailed   = (kStatusOffset + -21),   // 0x53B
      
      //! Error: Selected device is not an NXT.
      kStatusNonNXTDeviceSelected         = (kStatusOffset + -22),   // 0x53A
      
      //! Error: Communication error.  Retry the operation.
      kStatusRetryConnection              = (kStatusOffset + -23),   // 0x539
      
      //! Error: Could not connect to NXT.  Turn the NXT off and then back on before continuing.
      kStatusPowerCycleNXT                = (kStatusOffset + -24),   // 0x538
      
      //! Error: This feature is not yet implemented.
      kStatusFeatureNotImplemented        = (kStatusOffset + -99),   // 0x4ED
      
      //! Error: Firmware reported an illegal handle.
      kStatusFWIllegalHandle              = (kStatusOffset + -189),  // 0x493
      
      //! Error: Firmware reported an illegal file name.
      kStatusFWIllegalFileName            = (kStatusOffset + -190),  // 0x492
      
      //! Error: Firmware reported an out of bounds reference.
      kStatusFWOutOfBounds                = (kStatusOffset + -191),  // 0x491
      
      //! Error: Firmware could not find module.
      kStatusFWModuleNotFound             = (kStatusOffset + -192),  // 0x490
      
      //! Error: Firmware reported that the file already exists.
      kStatusFWFileExists                 = (kStatusOffset + -193),  // 0x48F
      
      //! Error: Firmware reported that the file is full.
      kStatusFWFileIsFull                 = (kStatusOffset + -194),  // 0x48E
      
      //! Error: Firmware reported the append operation is not possible.
      kStatusFWAppendNotPossible          = (kStatusOffset + -195),  // 0x48D
      
      //! Error: Firmware has no write buffers available.
      kStatusFWNoWriteBuffers             = (kStatusOffset + -196),  // 0x48C
      
      //! Error: Firmware reported that file is busy.
      kStatusFWFileIsBusy                 = (kStatusOffset + -197),  // 0x48B
      
      //! Error: Firmware reported the undefined error.
      kStatusFWUndefinedError             = (kStatusOffset + -198),  // 0x48A
      
      //! Error: Firmware reported that no linear space is available.
      kStatusFWNoLinearSpace              = (kStatusOffset + -199),  // 0x489
      
      //! Error: Firmware reported that handle has already been closed.
      kStatusFWHandleAlreadyClosed        = (kStatusOffset + -200),  // 0x488
      
      //! Error: Firmware could not find file.
      kStatusFWFileNotFound               = (kStatusOffset + -201),  // 0x487
      
      //! Error: Firmware reported that the requested file is not linear.
      kStatusFWNotLinearFile              = (kStatusOffset + -202),  // 0x486
      
      //! Error: Firmware reached the end of the file.
      kStatusFWEndOfFile                  = (kStatusOffset + -203),  // 0x485
      
      //! Error: Firmware expected an end of file.
      kStatusFWEndOfFileExpected          = (kStatusOffset + -204),  // 0x484
      
      //! Error: Firmware cannot handle more files.
      kStatusFWNoMoreFiles                = (kStatusOffset + -205),  // 0x483
      
      //! Error: Firmware reported the NXT is out of space.
      kStatusFWNoSpace                    = (kStatusOffset + -206),  // 0x482
      
      //! Error: Firmware could not create a handle.
      kStatusFWNoMoreHandles              = (kStatusOffset + -207),  // 0x481
      
      //! Error: Firmware reported an unknown error code.
      kStatusFWUnknownErrorCode           = (kStatusOffset + -208),  // 0x480
      
      kStatusLast                         = (kStatusOffset + -999)
   };

   /*!
      \brief Class that contains a status code and the file name and line number where that
         status code was generated.
   */
   class tStatus
   {
      public:
      
         // methods

         //! constructor
         /*!
            Creates a tStatus object intialized to success.

            \post The status code is set to VI_SUCCESS.
         */
         inline tStatus( void ) :
               _code( VI_SUCCESS ),
               _lineNumber( 0 )
         {
            _fileName[0] = '\0';
         }


         //! copy constructor
         /*!
            Copies the code, line number, and file name from the specified tStatus object.

            \param status The status object to copy.
         */
         inline tStatus( const tStatus& status ) :
               _code( status._code ),
               _lineNumber( status._lineNumber )
         {
            ::strcpy( _fileName, "" );
            ::strncat( _fileName, status._fileName, kMaxFileNameLength - 1 );
         }


         //! constructor with code, filename, and line number
         /*!
            Creates a tStatus object initialized to the specified code, file name, and line number.
            Note that the nFANTOM_mLocation macro can be used to pass the fileName and lineNumber
               parameters.

            \param code A status code.
            \param fileName The name of the file in which the status code was generated.
            \param lineNumber The line number in the file at which the status code was generated.
         */
         inline tStatus( ViStatus code, const char* fileName, ViUInt32 lineNumber ) :
               _code( code ),
               _lineNumber( lineNumber )
         {
            ::strcpy( _fileName, "" );
            ::strncat( _fileName, reinterpret_cast<const char*>( fileName ), kMaxFileNameLength - 1 );
         }


         //! destructor
         inline ~tStatus()
         {
         }


         //! Returns the status code for this status object.
         /*!
            \return The status code for this status object.
         */
         inline ViStatus getCode( void ) const
         {
            return _code;
         }


         //! Returns the file name in which the status code, for this status object, was generated.
         /*!
            \return The file name in which the status code, for this status object, was generated.
         */
         inline const char* getFileName( void ) const
         {
            return _fileName;
         }


         //! Returns the line number at which the status code, for this status object, was
         //   generated.
         /*!
            \return The line number at which the status code, for this status object, was
               generated.
         */
         inline ViUInt32 getLineNumber( void ) const
         {
            return _lineNumber;
         }


         //! Sets the status code, file name, and line number for this status object, if
         //   appropriate.
         /*!
            Stores the specified status code, file name, and line number in this status object if
               this status object contains a successful status code or if this status object
               contains a warning status code and the specified status code is fatal.  A fatal
               status code is denoted by a negative value.  A successful status code is denoted
               by VI_SUCCESS.

            \param code A status code.
            \param fileName The name of the file in which the status code was generated.
            \param lineNumber The line number in the file at which the status code was generated.
         */
         inline void setCode( ViStatus code, const char* fileName, ViUInt32 lineNumber )
         {
            if(( isSuccess() && code != VI_SUCCESS ) || ( isNotFatal() && code < VI_SUCCESS ))
            {
               _code = code;
               _lineNumber = lineNumber;
               ::strcpy( _fileName, "" );
               ::strncat( _fileName, fileName, kMaxFileNameLength - 1 );
            }
         }


         //! Assigns the specified status object to this status object, if appropriate.
         /*!
            Stores the status code, file name, and line number of the specified status object in
               this status object if this status object contains a successful status code or if
               this status object contains a warning status code and the status code of the
               speciied status object is fatal.  A fatal status code is denoted by a negative
               value.  A successful status code is denoted by VI_SUCCESS.

            \param status The status object to assign.
         */
         inline void assign( const tStatus& status )
         {
            setCode( status.getCode(), status.getFileName(), status.getLineNumber());
         }


         //! Clears the status code for this status object.
         /*!
            \post status The code is set to VI_SUCCESS.
         */
         inline void clear( void )
         {
            _code = VI_SUCCESS;
            _lineNumber = 0;
            _fileName[0] = '\0';
         }


         //! Returns true if this status object contains a status code that is fatal.
         /*!
            A status code with a negative value is considered fatal.

            \return true if this status object contains a status code that is
               fatal; false otherwise.
         */
         inline bool isFatal( void ) const
         {
            return ( _code < VI_SUCCESS );
         }

         //! Returns true if this status object contains a status code that is not fatal.
         /*!
            Any status code with a non-negative (including zero) value is considered non-fatal.

            \return true if this status object contains a non-fatal status code;
               false otherwise.
         */
         inline bool isNotFatal( void ) const
         {
            return !isFatal();
         }


         //! Returns true if this status object contains a status code that is a warning.
         /*!
            A status code with a non-zero, positive value is considered a warning.

            \return true if this status object contains a status code that is a warning; false
               otherwise.
         */
         inline bool isWarning( void ) const
         {
            return ( _code > VI_SUCCESS );
         }


         //! Returns true if this status object contains the status code for success.
         /*!
            A value of VI_SUCCESS represents success.

            \return true if this status object contains the status code for success; false
               otherwise.
         */
         inline bool isSuccess( void ) const
         {
            return ( _code == VI_SUCCESS );
         }

      private:

         // declared private to prevent assignment
         tStatus& operator=(const tStatus& rhs);

         enum
         {
            kMaxFileNameLength = 101
         };

         ViStatus _code;
         ViChar   _fileName[ kMaxFileNameLength ];
         ViUInt32 _lineNumber;
   };


   // declarations for globally-scoped globals...
   inline ViStatus convertStatus( ViUInt8 firmwareStatus )
   {
      ViStatus status;
      switch (firmwareStatus)
      {
      // each of these cases corresponds to a unique status code returned by the firmware
      case 0x00 : status = kStatusSuccess;
         break;
      case 0x81 : status = kStatusFWNoMoreHandles; // No more available handles
         break;
      case 0x82 : status = kStatusFWNoSpace;   // No space
         break;
      case 0x83 : status = kStatusFWNoMoreFiles; // No more files
         break;
      case 0x84 : status = kStatusFWEndOfFileExpected; // End of file expected
         break;
      case 0x85 : status = kStatusFWEndOfFile; // End of file reached
         break;
      case 0x86 : status = kStatusFWNotLinearFile; // Not a linear file
         break;
      case 0x87 : status = kStatusFWFileNotFound; // File not found
         break;
      case 0x88 : status = kStatusFWHandleAlreadyClosed; // Handle is already closed
         break;
      case 0x89 : status = kStatusFWNoLinearSpace; // No linear space available
         break;
      case 0x8A : status = kStatusFWUndefinedError; // Undefined error
         break;
      case 0x8B : status = kStatusFWFileIsBusy; // File is busy
         break;
      case 0x8C : status = kStatusFWNoWriteBuffers; // No write buffers available
         break;
      case 0x8D : status = kStatusFWAppendNotPossible; // Append not possible
         break;
      case 0x8E : status = kStatusFWFileIsFull; // File is full
         break;
      case 0x8F : status = kStatusFWFileExists; // File already exists
         break;
      case 0x90 : status = kStatusFWModuleNotFound; // Module not found
         break;
      case 0x91 : status = kStatusFWOutOfBounds; // Out of module I/O map boundary
         break;
      case 0x92 : status = kStatusFWIllegalFileName; // Illegal file name
         break;
      case 0x93 : status = kStatusFWIllegalHandle; // Illegal handle
         break;
      default :
         status = kStatusFWUnknownErrorCode;
      }
      return status;
   }

   // prototypes...

} // namespace nFANTOM100

// inline functions and function macros...

#endif // ___fantom_tStatus_h___
