#![allow(dead_code)]
pub extern crate libc;

macro_rules! DEFINE_GUID{
	($name:ident, $l:expr, $w1:expr, $w2:expr, $($bs:expr),+) => {
		pub static $name: crate::types::GUID = crate::types::GUID {
			data1: $l,
			data2: $w1,
			data3: $w2,
			data4: [$($bs),+]
		};
	};
}

fn main() {
	/*
	Until `rustc` stops using the LLVM segmented stacks support on Windows, you have to call this to un-bork OS-private data.
	In this particular case, it causes CoCreateInstance to fail with ERROR_NOACCESS.
	*/
	//fix_corrupt_tlb();
    let num1 = 155;
    let num2 = 145;
	win32::run_imymath_methods(num1,num2);
}


mod win32 {
	use libc::c_void;
	use crate::types::{DWORD, HRESULT, REFCLSID, REFIID};
	use crate::types::{IUnknown};

	pub fn run_imymath_methods(num1: i32, num2: i32) {
		use std::mem::transmute;
		use std::ptr::null_mut;
		use crate::types::{IID_IMYMATH, IMyMath};

		match unsafe { CoInitializeEx(null_mut(), COINIT_APARTMENTTHREADED) } {
			S_OK => (),
			S_FALSE => (),
			result => panic!("call to CoInitializeEx failed: {}", result)
		}

		/*
		You know what would make this easier?  Being able to do this:
		
			match CoCreateInstance(..., &mut let obj) { ... }
			// obj is in scope here
		Not *widely* useful, especially not in idiomatic Rust, but still nice for dealing with these sorts of APIs.
		*/
		let mut obj: *mut IMyMath = null_mut();
		let mut my_summation: i32 = 0;
        let sum: *mut i32 = &mut my_summation;

		let mut my_subtraction = 0;
		let sub: *mut i32 = &mut my_subtraction;

		match unsafe { CoCreateInstance(&CLSID_MY_MATH, null_mut(), CLSCTX_INPROC_SERVER, 
            &IID_IMYMATH, transmute(&mut obj)) } {
			S_OK => (),
			REGDB_E_CLASSNOTREG => panic!("CoCreateInstance failed: class not registered"),
			E_NOINTERFACE => panic!("CoCreateInstance failed: class does not implement interface"),
			0x800703e6 => panic!("CoCreateInstance failed: ERROR_NOACCESS; see https://github.com/rust-lang/rust/issues/13259"),
			result => panic!("CoCreateInstance failed: error {:#08x}", result)
		}

		assert!(obj != null_mut());

		match unsafe { ((*(*obj).__vtable).SumOfTwoIntegers)(transmute(obj), 
			num1, num2, sum) } {
			S_OK => println!("Addition of {0} and {1}, is {2}", num1, num2, my_summation),
			result => panic!("IMyMath.SumOfTwoIntegers failed: error {:#08x}", result)
		}

        match unsafe { ((*(*obj).__vtable).SubtractionOfTwoIntegers)(transmute(obj),
		num1, num2, sub) } {
			S_OK => println!("Subtraction of {0} and {1}, is {2}", num1, num2, my_subtraction),
			result => panic!("IMyMath.SubtractionOfTwoIntegers 
            failed: error {:#08x}", result)
		}

		unsafe {
			((*(*obj).__vtable).__base.__base.Release)(transmute(obj));
		}

		unsafe {
			CoUninitialize();
		}
	}

	#[link(name = "ole32")]
	extern "stdcall" {
		fn CoCreateInstance(rclsid: REFCLSID, pUnkOuter: *mut IUnknown, dwClsContext: DWORD, riid: REFIID, ppv: *mut *mut c_void) -> HRESULT;
		fn CoInitializeEx(pvReserved: *mut c_void, dwCoInit: DWORD) -> HRESULT;
		fn CoUninitialize();
	}

	static CLSCTX_INPROC_SERVER: DWORD = 0x1;

	static COINIT_APARTMENTTHREADED: DWORD = 0x2;

	const S_OK: HRESULT = 0x00000000;
	const S_FALSE: HRESULT = 0x00000001;

	static CLASS_E_NOAGGREGATION: HRESULT = 0x80040110;
	const E_NOINTERFACE: HRESULT = 0x80004002;
	const REGDB_E_CLASSNOTREG: HRESULT = 0x80040154;
	static REGDB_E_IIDNOTREG: HRESULT = 0x80040155;

	// {13709620-C279-11CE-A49E-444553540000}
	DEFINE_GUID!{CLSID_MY_MATH, 0x9aea1e50, 0xd8c7, 0x4353, 0x9a, 0xa7, 0xb9, 0x1c, 0xb1, 0x74, 0xd9, 0xac}
}

#[allow(non_snake_case)]
mod types {
	use libc::c_void;

	#[repr(C)]
	pub struct GUID {
		pub data1: u32,
		pub data2: u16,
		pub data3: u16,
		pub data4: [u8; 8]
	}

	pub type BOOL = u32;
	pub type DWORD = u32;
	pub type HRESULT = u32;
	pub type LONG = i32;
	pub type ULONG = u32;
	pub type WORD = u16;

	pub type LCID = DWORD;

	pub type CLSID = GUID;
	pub type FMTID = GUID;
	pub type IID = GUID;

	pub type REFGUID = *const GUID;
	pub type REFCLSID = *const CLSID;
	pub type REFIID = *const IID;
	pub type REFFMTID = *const FMTID;

	pub type DISPID = LONG;
	pub type MEMBERID = DISPID;

	pub type OLECHAR = u16;
	pub type BSTR = *mut OLECHAR;
	pub type LPBSTR = *mut BSTR;

	#[repr(C)]
	pub struct DISPPARAMS {
		rgvarg: *mut VARIANTARG,
		rgdispidNamedArgs: *mut DISPID,
		cArgs: u32,
		cNamedArgs: u32,
	}

	pub struct VARIANT;
	type VARIANTARG = VARIANT;

	pub struct EXCEPINFO;

	pub type ComPtr = *mut c_void;

	#[repr(C)]
	pub struct IUnknown {
		pub __vtable: *mut IUnknown_vtable,
	}

	//pub static IID_IUnknown: &'static str = "00000000-0000-0000-C000-000000000046";
	DEFINE_GUID!(IID_IUNKNOWN, 0x00000000, 0x0000, 0x0000, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

	#[repr(C)]
	pub struct IUnknown_vtable {
		pub QueryInterface: extern "stdcall" fn(ComPtr, REFIID, *mut ComPtr) -> HRESULT,
		pub AddRef: extern "stdcall" fn(ComPtr) -> ULONG,
		pub Release: extern "stdcall" fn(ComPtr) -> ULONG,
	}

	#[repr(C)]
	pub struct IDispatch {
		pub __vtable: *mut IDispatch_vtable,
	}

	//pub static IID_IDispatch: &'static str = "00020400-0000-0000-C000000000000046";
	DEFINE_GUID!(IID_IDISPATCH, 0x00020400, 0x0000, 0x0000, 0xc0,0x00, 0x00,0x00,0x00,0x00,0x00,0x46);

	#[repr(C)]
	pub struct IDispatch_vtable {
		pub __base: IUnknown_vtable,
		pub GetTypeInfoCount: extern "stdcall" fn(ComPtr, *mut u32) -> HRESULT,
		pub GetTypeInfo: extern "stdcall" fn(ComPtr, u32, LCID, *mut *mut ITypeInfo) -> HRESULT,
		pub GetIDsOfNames: extern "stdcall" fn(ComPtr, REFIID, *mut BSTR, u32, LCID, *mut DISPID) -> HRESULT,
		pub Invoke: extern "stdcall" fn(ComPtr, DISPID, REFIID, LCID, WORD, *mut DISPPARAMS, *mut VARIANT, *mut EXCEPINFO, *mut u32) -> HRESULT,
	}

	#[repr(C)]
	pub struct ITypeInfo {
		pub __vtable: *mut ITypeInfo_vtable,
	}

	//pub static IID_ITypeInfo: &'static str = "00020401-0000-0000-C000-000000000046";
	DEFINE_GUID!{IID_ITYPE_INFO, 0x00020401, 0x0000, 0x0000, 0xc0,0x00, 0x00,0x00,0x00,0x00,0x00,0x46}

	#[repr(C)]
	//#[idl="oaidl.idl"]
	pub struct ITypeInfo_vtable {
		pub base: IUnknown_vtable,
		// TODO
	}

    #[repr(C)]
    pub struct IMyMath {
        pub __vtable: *mut ImyMathVtable
    }

    DEFINE_GUID!{IID_IMYMATH, 0xbac91261, 0x3c2f, 0x4cfb, 0x9a, 0xfb, 0xf8, 0x23, 0x57, 0x2f, 0x83, 0x8f}
    pub struct ImyMathVtable {
        pub __base: IDispatch_vtable,

        pub SumOfTwoIntegers: extern "stdcall" fn(ComPtr, i32, i32, *mut i32) -> HRESULT,
        pub SubtractionOfTwoIntegers: extern "stdcall" fn(ComPtr, i32, i32, *mut i32) -> HRESULT
    }
}