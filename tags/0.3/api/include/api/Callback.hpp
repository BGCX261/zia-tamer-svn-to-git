/*!
 * \class zia::api::Callback_1p
 * \brief Impossible fast delegates
 *
 *      Imposible fast delegates GLH
 *                             ( Goes Like Hell )
 *
 * Generic method pointeur
 *    ( Equivalent to a function ptr )
 *
 *   - No allocation
 *   - Light ( size of 2 pointers )
 *   - No virtual
 *   - Strict signature ( like a function pointer type )
 *   - One Callback signature can store any method ptr of any object
 *   - >> Fastest C++ method callback
 *
 * \a Callback_2p : Callback with 2 parameters
 *
 * \a Callback_3p : Callback with 3 parameters
 *
 * \a Callback_4p : Callback with 4 parameters
 *
 * \a Callback_5p : Callback with 5 parameters
 *
 * \a Callback_6p : Callback with 6 parameters
 *
 * \a Callback_7p : Callback with 7 parameters
 *
 * \a Callback_8p : Callback with 8 parameters
 *
 * e.g.:
 *
 * How to create a \a Callback_3p:
 * \code
 * zia::api::Callback_3p< return_type, arg1_type, arg2_type, arg3_type >
 *     ::create< object_type, mehtod_ptr >( object_instance_ptr )
 * \endcode
 *
 * Full usage:
 * \code
 * //
 * // Typedef it to simplify usage
 * //
 *
 *      typedef zia::api::Callback_2p< int, double, size_t >  MyCallback;
 *
 * //
 * // Create a callback
 * //
 *
 *      class A // example class
 *      {
 *      public:
 *          int     method(double, size_t);
 *      };
 *
 *      A           a;
 *      MyCallback  callback = MyCallback::create< A, &A::method >( &a );
 *
 * //
 * // Call it
 * //
 *
 *      callback(2.45, 1256);
 *      callback(42.635, 65553);
 *      callback(5454.0, 454);
 *
 * // enjoy
 * \endcode
 */


#ifndef _ZIA_API_CALLBACK_H_
#define _ZIA_API_CALLBACK_H_

#include "defines.hpp"

_BOF_ZIA_API_

#define CALLBACK(_CLASS_NAME, _TN_TARGS, _TARGS, _TN_ARGS, _ARGS)       \
template <typename TRET, _TN_TARGS>                                     \
class _CLASS_NAME                                                       \
{                                                                       \
public:                                                                 \
    template <typename T>                                               \
    struct Traits                                                       \
    {                                                                   \
        typedef TRET                    (T::*TMethod)(_TARGS);          \
    };                                                                  \
    typedef _CLASS_NAME<TRET, _TARGS>   This;                           \
    typedef TRET                        (*CallerPtr)(void*, _TARGS);    \
                                                                        \
    inline _CLASS_NAME()                                                \
        : mInstance(0), mCaller(0)                                      \
    { }                                                                 \
                                                                        \
    template < typename T, typename Traits<T>::TMethod TMethod >        \
    inline static This      create(T* instance)                         \
    {                                                                   \
        return (This(instance, &caller<T, TMethod>));                   \
    }                                                                   \
                                                                        \
    inline TRET             operator () (_TN_ARGS)                      \
    {                                                                   \
        return ((*mCaller)(mInstance, _ARGS));                          \
    }                                                                   \
                                                                        \
    inline bool             isSet() const                               \
    {                                                                   \
        return (mInstance != 0);                                        \
    }                                                                   \
                                                                        \
    inline void             clear()                                     \
    {                                                                   \
        mInstance = 0;                                                  \
    }                                                                   \
                                                                        \
                                                                        \
private:                                                                \
    void*                   mInstance;                                  \
    CallerPtr               mCaller;                                    \
                                                                        \
    inline _CLASS_NAME(void* instance, CallerPtr caller)                \
        : mInstance(instance), mCaller(caller)                          \
    { }                                                                 \
                                                                        \
    template < typename T, typename Traits<T>::TMethod TMethod >        \
    inline static TRET      caller(void* instance, _TN_ARGS)            \
    {                                                                   \
        return ((static_cast<T*>(instance)->*TMethod)(_ARGS));          \
    }                                                                   \
};

// 1 parameter
#define _TN_TARGS_1     typename TARG1
#define _TARGS_1        TARG1
#define _TN_ARGS_1      TARG1 _arg1
#define _ARGS_1         _arg1
CALLBACK( Callback_1p, _TN_TARGS_1, _TARGS_1, _TN_ARGS_1, _ARGS_1 )

// 2 parameters
#define _TN_TARGS_2     _TN_TARGS_1,    typename TARG2
#define _TARGS_2        _TARGS_1,       TARG2
#define _TN_ARGS_2      _TN_ARGS_1,     TARG2 _arg2
#define _ARGS_2         _ARGS_1,        _arg2
CALLBACK( Callback_2p, _TN_TARGS_2, _TARGS_2, _TN_ARGS_2, _ARGS_2 )

// 3 parameters
#define _TN_TARGS_3     _TN_TARGS_2,    typename TARG3
#define _TARGS_3        _TARGS_2,       TARG3
#define _TN_ARGS_3      _TN_ARGS_2,     TARG3 _arg3
#define _ARGS_3         _ARGS_2,        _arg3
CALLBACK( Callback_3p, _TN_TARGS_3, _TARGS_3, _TN_ARGS_3, _ARGS_3 )

// 4 parameters
#define _TN_TARGS_4     _TN_TARGS_3,    typename TARG4
#define _TARGS_4        _TARGS_3,       TARG4
#define _TN_ARGS_4      _TN_ARGS_3,     TARG4 _arg4
#define _ARGS_4         _ARGS_3,        _arg4
CALLBACK( Callback_4p, _TN_TARGS_4, _TARGS_4, _TN_ARGS_4, _ARGS_4 )

// 5 parameters
#define _TN_TARGS_5     _TN_TARGS_4,    typename TARG5
#define _TARGS_5        _TARGS_4,       TARG5
#define _TN_ARGS_5      _TN_ARGS_4,     TARG5 _arg5
#define _ARGS_5         _ARGS_4,        _arg5
CALLBACK( Callback_5p, _TN_TARGS_5, _TARGS_5, _TN_ARGS_5, _ARGS_5 )

// 6 parameters
#define _TN_TARGS_6     _TN_TARGS_5,    typename TARG6
#define _TARGS_6        _TARGS_5,       TARG6
#define _TN_ARGS_6      _TN_ARGS_5,     TARG6 _arg6
#define _ARGS_6         _ARGS_5,        _arg6
CALLBACK( Callback_6p, _TN_TARGS_6, _TARGS_6, _TN_ARGS_6, _ARGS_6 )

// 7 parameters
#define _TN_TARGS_7     _TN_TARGS_6,    typename TARG7
#define _TARGS_7        _TARGS_6,       TARG7
#define _TN_ARGS_7      _TN_ARGS_6,     TARG7 _arg7
#define _ARGS_7         _ARGS_6,        _arg7
CALLBACK( Callback_7p, _TN_TARGS_7, _TARGS_7, _TN_ARGS_7, _ARGS_7 )

// 8 parameters
#define _TN_TARGS_8     _TN_TARGS_7,    typename TARG8
#define _TARGS_8        _TARGS_7,       TARG8
#define _TN_ARGS_8      _TN_ARGS_7,     TARG8 _arg8
#define _ARGS_8         _ARGS_7,        _arg8
CALLBACK( Callback_8p, _TN_TARGS_8, _TARGS_8, _TN_ARGS_8, _ARGS_8 )

_EOF_ZIA_API_

#endif /* _ZIA_API_CALLBACK_H_ */
