//
//  TSLAvailabilityMacros.h
//
//  Copyright © 2020 Technology Solutions UK Ltd. All rights reserved.
//

#ifndef TSLAvailabilityMacros_h
#define TSLAvailabilityMacros_h

#if defined(__has_feature) && defined(__has_attribute)
    #if __has_attribute(deprecated)
        #define TSL_DEPRECATED_ATTRIBUTE __attribute__((deprecated))
        #if __has_feature(attribute_deprecated_with_message)
            #define TSL_DEPRECATED_MSG_ATTRIBUTE(s) __attribute__((deprecated(s)))
        #else
            #define TSL_DEPRECATED_MSG_ATTRIBUTE(s) __attribute__((deprecated))
        #endif
    #else
        #define TSL_DEPRECATED_ATTRIBUTE
        #define TSL_DEPRECATED_MSG_ATTRIBUTE(s)
    #endif
#else
    #define TSL_DEPRECATED_ATTRIBUTE
    #define TSL_DEPRECATED_MSG_ATTRIBUTE(s)
#endif

#endif /* TSLAvailabilityMacros_h */
