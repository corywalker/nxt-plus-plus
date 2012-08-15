/*!
   \file iModuleIterator.h
   \brief Interface for an iterator for firmware modules on a LEGO MINDSTORMS NXT.
*/
/*
   © Copyright 2005-2006,
   National Instruments Corporation.
   All rights reserved.

   File:        iModuleIterator.h
   Originated:  8 Aug 2005
*/
 
#ifndef ___fantom_iModuleIterator_h___
#define ___fantom_iModuleIterator_h___


// includes...

#ifndef ___fantom_platform_h___
   #include "platform.h"
#endif

#ifndef ___fantom_iModule_h___
   #include "iModule.h"
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
      \class iModuleIterator
      \brief Interface to an iterator for firmware modules on a LEGO MINDSTORMS NXT.
   */
   class iModuleIterator
   {
      friend class tNXT;

      // methods
      protected:

         //! Destructor
         virtual ~iModuleIterator() = 0;
   
      public:
         
         //! Creates a module object for the module referenced by this iterator.
         /*!
            Creates a module object for the module referenced by this iterator.  An object is not
               created if the specified status is fatal or if this iterator refers to the end of
               the list.  The returned module object should be destroyed using the
               iNXT::destroyModule method.
            
            \param status Status chaining object.
            \return A pointer to the iModule object that was created.
         */
         virtual iModule* getModule( tStatus& status ) = 0;

         //! Advances this iterator.
         /*!
            Advances this iterator to the next module that matches the previously specified
               module name pattern.  If no more modules match, this iterator is advanced to the
               end of the list.
            The iterator is not advanced if the specified status is fatal.
            If this iterator is already at the end of the list, a fatal status will be generated.
            
            \param status Status chaining object.
         */
         virtual void advance( tStatus& status ) = 0;
         
         //! Retrieves the name of the module to which this iterator refers.
         /*!
            \param moduleName Populated with the name of the module to which this iterator
               refers.  The module name character array must be able to accomodate a
               NULL-terminated, 15.3 formatted module name.  This is, it must have a capacity of
               20 bytes.
            \param status Status chaining object.
         */
         virtual void getName( ViChar moduleName[], tStatus& status ) = 0;

   };
   
   
   // constants...
   
} // namespace nFANTOM100


   // declarations for globally-scoped globals...

   // typedefs
   typedef ViObject nFANTOM100_iModuleIterator;

   extern "C"
   {
      nFANTOM100_kExport nFANTOM100_iModule _VI_FUNCC nFANTOM100_iModuleIterator_getModule(
            nFANTOM100_iModuleIterator iteratorPtr,
            ViStatus* status );

      nFANTOM100_kExport void _VI_FUNCC nFANTOM100_iModuleIterator_advance(
            nFANTOM100_iModuleIterator iteratorPtr,
            ViStatus* status );

      nFANTOM100_kExport void _VI_FUNCC nFANTOM100_iModuleIterator_getName(
            nFANTOM100_iModuleIterator iteratorPtr,
            ViChar moduleName[],
            ViStatus* status );
   }

#endif // ___fantom_iModuleIterator_h___
