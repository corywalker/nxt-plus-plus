/*!
   \file iModule.h
   \brief Interface for a firmware module on a LEGO MINDSTORMS NXT.
*/
/*
   © Copyright 2005-2006,
   National Instruments Corporation.
   All rights reserved.

   File:        iModule.h
   Originated:  8 Aug 2005
*/

#ifndef ___fantom_iModule_h___
#define ___fantom_iModule_h___

#ifndef ___fantom_platform_h___
   #include "platform.h"
#endif

#ifndef ___fantom_tStatus_h___
   #include "tStatus.h"
#endif


// defines...


namespace nFANTOM100
{

   /*!
      \class iModule
      \brief Interface to a firmware module on a LEGO MINDSTORMS NXT.
   */
   class iModule
   {
      friend class tNXT;
      
      // methods
      protected:
   
         //! Destructor
         virtual ~iModule() = 0;

      public:

         //! Retrieves the name of this module.
         /*!
            \param moduleName Populated with the name of this module. The module name character
               array must be able to accomodate a NULL-terminated, 15.3 formatted module name.
               That is, it must have a capacity of 20 bytes.
         */
         virtual void getName( ViChar moduleName[] ) const = 0;
         
         //! Retrieves the internal module ID of this module.
         /*!
            \return The internal module ID of this module.
         */
         virtual ViUInt32 getModuleID( void ) const = 0;
         
         //! Retrieves the size in bytes of this module.
         /*!
            \return The size in bytes of this module.
         */
         virtual ViUInt32 getModuleSize( void ) const = 0;
         
         //! Retrieves the size in bytes of the I/O map associated with this module.
         /*!
            \return The size in bytes of the I/O map associated with this module.
         */
         virtual ViUInt32 getModuleIOMapSize( void ) const = 0;
         
         //! Reads a portion of this module's I/O map.
         /*!
            Reads the data located at [I/O map address] + [specified offset in bytes] into the
               specified data buffer.  The read will attempt to copy the specified number of
               bytes.  No read occurs if the specified status is fatal.  The ownership of data
               buffer is not transferred to this module object.

            \param offsetInBytes The index of the byte in the I/O map at which to start the read.
            \param numberOfBytes The number of bytes that should be read from the I/O map.
            \param dataBufferPtr A pointer to the data buffer that will be populated with the
               data that is read.  The capacity of the specified data buffer must be at least the
               specified number of bytes.
            \param status Status chaining object.
            \return The number of bytes actually read from the I/O map.
            
            \post The specified data buffer may be deallocated.
         */
         virtual ViUInt32 readIOMap( ViUInt32 offsetInBytes, ViUInt32 numberOfBytes,
               ViPBuf dataBufferPtr, tStatus& status ) = 0;
         
         //! Writes a portion of this module's I/O map.
         /*!
            Writes the specified data into this module's I/O map.  The write starts at  [I/O map
               address] + [specified offset in bytes] and stops after the specified number of
               bytes have been written.  No write occurs if the specified status is fatal.   The
               ownership of data buffer is not transferred to this module object.

            \param offsetInBytes The index of the byte in the I/O map at which to start the write.
            \param numberOfBytes The number of bytes to write into the I/O map.
            \param dataBufferPtr A pointer to the data buffer that contains the data that will be
               written. The capacity of the specified data buffer must be at least the specified
               number of bytes.
            \param status Status chaining object.
            \return The number of bytes actually written into the I/O map.
            
            \post The specified data buffer may be deallocated.
         */
         virtual ViUInt32 writeIOMap( ViUInt32 offsetInBytes, ViUInt32 numberOfBytes,
               const ViByte dataBufferPtr[], tStatus& status ) = 0;

   };

}; // nFANTOM100

typedef ViObject nFANTOM100_iModule;

extern "C"
{
   nFANTOM100_kExport void _VI_FUNCC nFANTOM100_iModule_getName(
         nFANTOM100_iModule modulePtr,
         ViChar moduleName[],
         ViStatus* status );

   nFANTOM100_kExport ViUInt32 _VI_FUNCC nFANTOM100_iModule_getModuleID(
         nFANTOM100_iModule modulePtr,
         ViStatus* status );

   nFANTOM100_kExport ViUInt32 _VI_FUNCC nFANTOM100_iModule_getModuleSize(
         nFANTOM100_iModule modulePtr,
         ViStatus* status );

   nFANTOM100_kExport ViUInt32 _VI_FUNCC nFANTOM100_iModule_getIOMapSize(
         nFANTOM100_iModule modulePtr,
         ViStatus* status );

   nFANTOM100_kExport ViUInt32 _VI_FUNCC nFANTOM100_iModule_readIOMap(
         nFANTOM100_iModule modulePtr,
         ViUInt32 offset,
         ViUInt32 numberBytesToRead,
         ViPBuf dataBuffer,
         ViStatus* status );

   nFANTOM100_kExport ViUInt32 _VI_FUNCC nFANTOM100_iModule_writeIOMap(
         nFANTOM100_iModule modulePtr,
         ViUInt32 offset,
         ViUInt32 numberBytesToWrite,
         const ViByte dataBuffer[],
         ViStatus* status );
}

#endif // ___fantom_iModule_h___
