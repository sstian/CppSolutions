

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for ExportExcel.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0622 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */


#ifndef __ExportExcel_h_h__
#define __ExportExcel_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IExportExcel_FWD_DEFINED__
#define __IExportExcel_FWD_DEFINED__
typedef interface IExportExcel IExportExcel;

#endif 	/* __IExportExcel_FWD_DEFINED__ */


#ifndef __ExportExcel_FWD_DEFINED__
#define __ExportExcel_FWD_DEFINED__

#ifdef __cplusplus
typedef class ExportExcel ExportExcel;
#else
typedef struct ExportExcel ExportExcel;
#endif /* __cplusplus */

#endif 	/* __ExportExcel_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __ExportExcel_LIBRARY_DEFINED__
#define __ExportExcel_LIBRARY_DEFINED__

/* library ExportExcel */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_ExportExcel;

#ifndef __IExportExcel_DISPINTERFACE_DEFINED__
#define __IExportExcel_DISPINTERFACE_DEFINED__

/* dispinterface IExportExcel */
/* [uuid] */ 


EXTERN_C const IID DIID_IExportExcel;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("8307b794-1d6b-4b15-9818-0fd3c50b81ec")
    IExportExcel : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IExportExcelVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IExportExcel * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IExportExcel * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IExportExcel * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IExportExcel * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IExportExcel * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IExportExcel * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IExportExcel * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IExportExcelVtbl;

    interface IExportExcel
    {
        CONST_VTBL struct IExportExcelVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IExportExcel_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IExportExcel_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IExportExcel_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IExportExcel_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IExportExcel_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IExportExcel_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IExportExcel_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IExportExcel_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ExportExcel;

#ifdef __cplusplus

class DECLSPEC_UUID("e4702f1f-84dc-4d36-aa25-804e8b941cc6")
ExportExcel;
#endif
#endif /* __ExportExcel_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


