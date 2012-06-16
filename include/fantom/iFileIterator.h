/*!
   \file iFileIterator.h
   \brief Interface for an iterator for files on a LEGO MINDSTORMS NXT.
*/
/*
   © Copyright 2005-2006,
   National Instruments Corporation.
   All rights reserved.

   File:        iFileIterator.h
   Originated:  12 May 2005
*/
 
#ifndef ___fantom_iFileIterator_h___
#define ___fantom_iFileIterator_h___


// includes...

#ifndef ___fantom_platform_h___
   #include "platform.h"
#endif

#ifndef ___fantom_iFile_h___
   #include "iFile.h"
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
      \class iFileIterator
      \brief Interface to an iterator for files on a LEGO MINDSTORMS NXT.
   */
   class iFileIterator
   {
      friend class tNXT;
      
      // methods
      protected:

         //! Destructor
         virtual ~iFileIterator() = 0;
   
      public:
         
         //! Creates a file object for the file referenced by this iterator.
         /*!
            Creates file object for the file referenced by this iterator.  An object is not
               created if the specified status is fatal or if this iterator refers to the end of
               the list.  The returned file object should be destroyed using the
               iNXT::destroyFile method.
            
            \param status Status chaining object.
            \return A pointer to the iFile object that was created.
         */
         virtual iFile* getFile( tStatus& status ) = 0;
         
         //! Advances this iterator.
         /*!
            Advances this iterator to the next file that matches the previously specified file
               name pattern.  If no more files match, this iterator is advanced to the end of the
               list.
            The iterator is not advanced if the specified status is fatal.
            If this iterator is already at the end of the list, a fatal status will be generated.
            
            \param status Status chaining object.
         */
         virtual void advance( tStatus& status ) = 0;

         //! Retrieves the name of the file to which this iterator refers.
         /*!
            \param fileName Populated with the name of the file to which this iterator refers.
               The file name character array must be able to accomodate a NULL-terminated, 15.3
               formatted file name.  This is, it must have a capacity of 20 bytes.
            \param status Status chaining object.
         */
         virtual void getName( ViChar fileName[], tStatus& status ) = 0;

         //! Retrieves the total size, in bytes, of the file to which this iterator refers.
         /*!
            \param status Status chaining object.
            \return The total size of the file in bytes.
         */
         virtual ViUInt32 getSize( tStatus& status ) = 0;

   };
   
   
   // constants...
   
} // namespace nFANTOM100


   // declarations for globally-scoped globals...

   // typedefs
   typedef ViObject nFANTOM100_iFileIterator;

   extern "C"
   {
      nFANTOM100_kExport nFANTOM100_iFile _VI_FUNCC nFANTOM100_iFileIterator_getFile(
            nFANTOM100_iFileIterator iteratorPtr,
            ViStatus* status );

      nFANTOM100_kExport void _VI_FUNCC nFANTOM100_iFileIterator_advance(
            nFANTOM100_iFileIterator iteratorPtr,
            ViStatus* status );

      nFANTOM100_kExport void _VI_FUNCC nFANTOM100_iFileIterator_getName(
            nFANTOM100_iFileIterator iteratorPtr,
            ViChar filename[],
            ViStatus* status );

      nFANTOM100_kExport ViUInt32 _VI_FUNCC nFANTOM100_iFileIterator_getSize(
            nFANTOM100_iFileIterator iteratorPtr,
            ViStatus* status );
   }

#endif // ___fantom_iFileIterator_h___
