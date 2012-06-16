/*!
   \file iFile.h
   \brief Interface for a file on a LEGO MINDSTORMS NXT.
*/
/*
   © Copyright 2005-2006,
   National Instruments Corporation.
   All rights reserved.

   File:        iFile.h
   Originated:  12 May 2005
*/

#ifndef ___fantom_iFile_h___
#define ___fantom_iFile_h___

// includes...

#ifndef ___fantom_platform_h___
   #include "platform.h"
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
      \class iFile
      \brief Interface to a file on a LEGO MINDSTORMS NXT.
   */
   class iFile
   {
      friend class tNXT;

      // methods
      protected:

         //! Destructor
         virtual ~iFile() = 0;

      public:

         //! Retrieves the name of this file.
         /*!
            \param fileName Populated with the name of this file.  The file name character array
               must be able to accomodate a NULL-terminated, 15.3 formatted module name.  That
               is, it must have a capacity of 20 bytes.
         */
         virtual void getName( ViChar fileName[] ) const = 0;

         //! Retrieves the total size of this file in bytes.
         /*!
            The returned size is undefined if the specified status is fatal.
            
            \param status Status chaining object.
            \return The total size of this file in bytes.
         */
         virtual ViUInt32 getSize( tStatus& status ) = 0;

         //! Retrieves the remaining available size, in bytes, in this file.
         /*!
            This number is only helpful for data logging files, which can contain variable
               amounts of data.
            The returned size is undefined if the specified status is fatal.

            \param status Status chaining object.
            \return The remaining available size, in bytes, in this file.
         */
         virtual ViUInt32 getAvailableSize( tStatus& status ) = 0;


         //! Opens this file for reading.
         /*!
            Opens, for reading, the file that corresponds to this object on the associated NXT.
            The file is not opened if the specified status is fatal.

            \param status Status chaining object.
         */
         virtual void openForRead( tStatus& status ) = 0;


         //! Open this file for writing.
         /*!
            Opens, for writing, the file that corresponds to this object on the associated NXT.
               If this file doesn't exist on the NXT, it is created.  If this file does exist on
               the NXT, an error is generated.
            The file is not opened if the specified status is fatal.

            \param sizeInBytes Size of the data, in bytes, that will be written to this file.
            \param status Status chaining object.
         */
         virtual void openForWrite( ViUInt32 sizeInBytes, tStatus& status ) = 0;


         //! Open this file for linear (contiguous) writing.
         /*!
            Opens, for linear (contiguous) writing, the file that corresponds to this object on
               the associated NXT. If this file doesn't exist on the NXT, it is created.  If this
               file does exist on the NXT, an error is generated.
            The file is not opened if the specified status is fatal.

            \param sizeInBytes Size of the data, in bytes, that will be written to the file.
            \param status Status chaining object.
         */
         virtual void openForLinearWrite( ViUInt32 sizeInBytes, tStatus& status ) = 0;


         //! Open this data file for writing.
         /*!
            Opens, for writing, the data file that corresponds to this object on the associated
               NXT.  This data file differs from normal files in that a data file can be closed
               before the entire file has been written.  If this file doesn't exist on the NXT,
               it is created.  If this file does exist on the NXT, an error is generated.
            The file is not opened if the specified status is fatal.

            \param sizeInBytes Size of the data, in bytes, that may be written to the file.
            \param status Status chaining object.
         */
         virtual void openForDataWrite( ViUInt32 sizeInBytes, tStatus& status ) = 0;


         //! Open this data file for appending additional data.
         /*!
            Opens, for appending additional data, the data file that corresponds to this object
               on the associated NXT. If this file doesn't exist on the NXT, the behavior is
               undefined.  If this file does exist on the NXT, the data that is written is
               appended to the end of the exiting data.
            The file is not opened if the specified status is fatal.

            \param status Status chaining object.
         */
         virtual void openForDataAppend( tStatus& status ) = 0;


         //! Closes this file.
         /*!
            Closes the file that corresponds to this object on the associated NXT.
            The file is not closed if the specified status is fatal.

            \param status Status chaining object.
         */
         virtual void close( tStatus& status ) = 0;


         //! Reads from this file
         /*!
            Reads the specified number of bytes from this file into the specified buffer. No data
               is read if the specified status is fatal.  The ownership of the buffer is not
               transferred to this file object.

            \param bufferPtr A pointer to the buffer that will be populated with the data that is
               read.  The capacity of the specified buffer must be at least the specified number
               of bytes.
            \param numberOfBytes Number of bytes to read.
            \param status Status chaining object.
            \return The number of bytes actually read from this file.

            \pre This file must have been opened for reading with the iFile::openForRead method.
            \post The specified buffer may be deallocated.
         */
         virtual ViUInt32 read( ViPBuf bufferPtr, ViUInt32 numberOfBytes, tStatus& status ) = 0;


         //! Writes to this file
         /*!
            Writes the specified number of bytes from the specified buffer to this file. No data
               is written if the specified status is fatal. The ownership of the buffer is not
               transferred to this file object.

            \param bufferPtr A pointer to the buffer that contains the data that will be written.
                The capacity of the specified buffer must be at least the specified number of
               bytes.
            \param numberOfBytes Number of bytes to write to this file.
            \param status Status chaining object.
            \return The number of bytes actually written to this file.

            \pre This file must have previously been opened for writing.
            \post The specified buffer may be deallocated.
         */
         virtual ViUInt32 write( const ViByte bufferPtr[], ViUInt32 numberOfBytes,
               tStatus& status ) = 0;


         //! Removes this file
         /*!
            Removes the file that corresponds to this object on the associated NXT.
            The file is not removed if the specified status is fatal.

            \param status Status chaining object.
         */
         virtual void remove( tStatus& status ) = 0;

   };


   // constants...
   const ViUInt8 kProtocolFilenameLength = 19;   // 15 basename + 1 dot + 3 extension = 19

} // namespace nFANTOM100


   // declarations for globally-scoped globals...

   // typedefs...
   typedef ViObject nFANTOM100_iFile;

   // prototypes...
   extern "C"
   {
      nFANTOM100_kExport void _VI_FUNCC nFANTOM100_iFile_getName(
            nFANTOM100_iFile filePtr,
            ViChar fileName[],
            ViStatus* status );

      nFANTOM100_kExport ViUInt32 _VI_FUNCC nFANTOM100_iFile_getSize(
            nFANTOM100_iFile filePtr,
            ViStatus* status );

      nFANTOM100_kExport ViUInt32 _VI_FUNCC nFANTOM100_iFile_getAvailableSize(
            nFANTOM100_iFile filePtr,
            ViStatus* status );

      nFANTOM100_kExport void _VI_FUNCC nFANTOM100_iFile_openForRead(
            nFANTOM100_iFile filePtr,
            ViStatus* status );

      nFANTOM100_kExport void _VI_FUNCC nFANTOM100_iFile_openForWrite(
            nFANTOM100_iFile filePtr,
            ViUInt32 sizeInBytes,
            ViStatus* status );

      nFANTOM100_kExport void _VI_FUNCC nFANTOM100_iFile_openForLinearWrite(
            nFANTOM100_iFile filePtr,
            ViUInt32 sizeInBytes,
            ViStatus* status );

      nFANTOM100_kExport void _VI_FUNCC nFANTOM100_iFile_openForDataWrite(
            nFANTOM100_iFile filePtr,
            ViUInt32 sizeInBytes,
            ViStatus* status );

      nFANTOM100_kExport void _VI_FUNCC nFANTOM100_iFile_openForDataAppend(
            nFANTOM100_iFile filePtr,
            ViStatus* status );

      nFANTOM100_kExport void _VI_FUNCC nFANTOM100_iFile_close(
            nFANTOM100_iFile filePtr,
            ViStatus* status );

      nFANTOM100_kExport void _VI_FUNCC nFANTOM100_iFile_read(
            nFANTOM100_iFile filePtr,
            ViPBuf bufferPtr,
            ViUInt32 numberOfBytes,
            ViStatus* status );

      nFANTOM100_kExport void _VI_FUNCC nFANTOM100_iFile_write(
            nFANTOM100_iFile filePtr,
            const ViByte bufferPtr[],
            ViUInt32 numberOfBytes,
            ViStatus* status );

      nFANTOM100_kExport void _VI_FUNCC nFANTOM100_iFile_remove(
            nFANTOM100_iFile filePtr,
            ViStatus* status );

   }

#endif // ___fantom_iFile_h___
