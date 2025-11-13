

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.xx.xxxx */
/* at a redacted point in time
 */
/* Compiler settings for ../../qorai/components/qorai_vpn/common/wireguard/win/qorai_wireguard_manager_idl.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=ARM64 8.01.0628 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __qorai_wireguard_manager_idl_h__
#define __qorai_wireguard_manager_idl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef DECLSPEC_XFGVIRT
#if defined(_CONTROL_FLOW_GUARD_XFG)
#define DECLSPEC_XFGVIRT(base, func) __declspec(xfg_virtual(base, func))
#else
#define DECLSPEC_XFGVIRT(base, func)
#endif
#endif

/* Forward Declarations */ 

#ifndef __IQoraiVpnWireguardManager_FWD_DEFINED__
#define __IQoraiVpnWireguardManager_FWD_DEFINED__
typedef interface IQoraiVpnWireguardManager IQoraiVpnWireguardManager;

#endif 	/* __IQoraiVpnWireguardManager_FWD_DEFINED__ */


#ifndef __IQoraiVpnWireguardManager_FWD_DEFINED__
#define __IQoraiVpnWireguardManager_FWD_DEFINED__
typedef interface IQoraiVpnWireguardManager IQoraiVpnWireguardManager;

#endif 	/* __IQoraiVpnWireguardManager_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IQoraiVpnWireguardManager_INTERFACE_DEFINED__
#define __IQoraiVpnWireguardManager_INTERFACE_DEFINED__

/* interface IQoraiVpnWireguardManager */
/* [unique][helpstring][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IQoraiVpnWireguardManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6D319801-690B-441E-8C94-5C18D8E7E9D7")
    IQoraiVpnWireguardManager : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE EnableVpn( 
            /* [in] */ BSTR public_key,
            /* [in] */ BSTR private_key,
            /* [in] */ BSTR address,
            /* [in] */ BSTR endpoint,
            /* [out] */ DWORD *last_error) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DisableVpn( 
            /* [out] */ DWORD *last_error) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IQoraiVpnWireguardManagerVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IQoraiVpnWireguardManager * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IQoraiVpnWireguardManager * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IQoraiVpnWireguardManager * This);
        
        DECLSPEC_XFGVIRT(IQoraiVpnWireguardManager, EnableVpn)
        HRESULT ( STDMETHODCALLTYPE *EnableVpn )( 
            IQoraiVpnWireguardManager * This,
            /* [in] */ BSTR public_key,
            /* [in] */ BSTR private_key,
            /* [in] */ BSTR address,
            /* [in] */ BSTR endpoint,
            /* [out] */ DWORD *last_error);
        
        DECLSPEC_XFGVIRT(IQoraiVpnWireguardManager, DisableVpn)
        HRESULT ( STDMETHODCALLTYPE *DisableVpn )( 
            IQoraiVpnWireguardManager * This,
            /* [out] */ DWORD *last_error);
        
        END_INTERFACE
    } IQoraiVpnWireguardManagerVtbl;

    interface IQoraiVpnWireguardManager
    {
        CONST_VTBL struct IQoraiVpnWireguardManagerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IQoraiVpnWireguardManager_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IQoraiVpnWireguardManager_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IQoraiVpnWireguardManager_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IQoraiVpnWireguardManager_EnableVpn(This,public_key,private_key,address,endpoint,last_error)	\
    ( (This)->lpVtbl -> EnableVpn(This,public_key,private_key,address,endpoint,last_error) ) 

#define IQoraiVpnWireguardManager_DisableVpn(This,last_error)	\
    ( (This)->lpVtbl -> DisableVpn(This,last_error) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IQoraiVpnWireguardManager_INTERFACE_DEFINED__ */



#ifndef __QoraiVpnWireguardServiceLib_LIBRARY_DEFINED__
#define __QoraiVpnWireguardServiceLib_LIBRARY_DEFINED__

/* library QoraiVpnWireguardServiceLib */
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_QoraiVpnWireguardServiceLib;
#endif /* __QoraiVpnWireguardServiceLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


