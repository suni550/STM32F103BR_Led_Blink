// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch. 
// SW guideline: Technote Coding Guidelines Ver. 1.4

#ifndef PLATFORMCONFIGAPP_H
#define PLATFORMCONFIGAPP_H

//@{
// This is a application specific file which is used to configure Imt.Base.Dff.Core.
// All source files of Imt.Base.Dff do include this file. So when the sources should be compiled
// a copy of this application specific file needs to be copied to Imt.Base.Dff.Core *before* the build
// of Imt.Base.Dff starts. This can easily be done by a build tools as a pre-build step. 
//@}

#ifdef WIN32
    #ifndef USE_STL
    #define USE_STL
    #endif
#endif

// In order to use inbuilt ROM-HAL code of Tiva processors library, we have to define which CPU we are using
//#ifndef PART_STM32F103xB
//    #define PART_STM32F103xB
//#endif // PART_STM32F103xB

//#ifndef TARGET_IS_STM32F103RBT6
//    #define TARGET_IS_STM32F103RBT6
//#endif // TARGET_IS_STM32F103RB

// Uncomment next line for enabling runtime statistics
// #define RUNTIME_STATISTICS
#endif // #ifndef PLATFORMCONFIGAPP_H
