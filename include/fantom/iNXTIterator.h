/*!
   \file iNXTIterator.h
   \brief Interface used for searching for LEGO MINDSTORMS NXTs.
*/
/*
   © Copyright 2005-2006,
   National Instruments Corporation.
   All rights reserved.

   File:        iNXTIterator.h
   Originated:  17 Oct 2005
*/
 
#ifndef ___fantom_iNXTIterator_h___
#define ___fantom_iNXTIterator_h___


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
   class iNXT;

   // typedefs...
   
   // classes...
      
   /*!
      \class iNXTIterator
      \brief Interface to an iterator for LEGO MINDSTORMS NXTs.
   */
   class iNXTIterator
   {
      friend class iNXT;
      
      // methods
      protected:

         //! Destructor
         virtual ~iNXTIterator() = 0;

      public:
         
         //! Retrieves the name of the NXT to which this iterator refers.
         /*
            \param resourceName Populated with the name of the NXT to which this iterator
               currently refers.  The resource name character array must have a capacity of 256
               bytes.
            \param status Status chaining object.
         */
         virtual void getName( ViChar resourceName[], tStatus& status ) const = 0;
         
         //! Advances this iterator.
         /*!
            Advances this iterator to the next NXT that was found. If no more NXTs are found,
               this iterator is advanced to the end of the list.
            The iterator is not advanced if the specified status is fatal.
            If this iterator is already at the end of the list, a fatal status will be generated.
            
            \param status Status chaining object.
         */
         virtual void advance( tStatus& status ) = 0;

         //! Creates an NXT object for the NXT referenced by this iterator.
         /*
            Creates an NXT object for the NXT referenced by this iterator.  An object is not
               created if the specified status is fatal or if this iterator refers to the end of
               the list.  The returned iNXT object should be destroyed using the iNXT::destroyNXT
               method.

            \param status Status chaining object.
            \return A pointer to the iNXT object that was created.
         */
         virtual iNXT* getNXT( tStatus& status ) = 0;
   };
   
   
   // constants...
   
} // namespace nFANTOM100


   // declarations for globally-scoped globals...

   // typedefs
   typedef ViObject nFANTOM100_iNXTIterator;
   
   // we must duplicate this typedef for the getNXT C wrapper
   typedef ViObject nFANTOM100_iNXT;

   extern "C"
   {
      nFANTOM100_kExport void _VI_FUNCC nFANTOM100_iNXTIterator_getName(
            nFANTOM100_iNXTIterator iteratorPtr,
            ViChar resourceName[],
            ViStatus* status );
      
      nFANTOM100_kExport void _VI_FUNCC nFANTOM100_iNXTIterator_advance(
            nFANTOM100_iNXTIterator iteratorPtr,
            ViStatus* status );

      nFANTOM100_kExport nFANTOM100_iNXT _VI_FUNCC nFANTOM100_iNXTIterator_getNXT(
            nFANTOM100_iNXTIterator iteratorPtr,
            ViStatus* status );
   }

#endif // ___fantom_iNXTIterator_h___
