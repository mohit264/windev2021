// #![allow(dead_code)]


// use windows::runtime::IUnknown;
// use windows::Win32::System::Com::CLSCTX_INPROC_SERVER;

// fn main() {
// 	/*
// 	Until `rustc` stops using the LLVM segmented stacks support on Windows, you have to call this to un-bork OS-private data.
// 	In this particular case, it causes CoCreateInstance to fail with ERROR_NOACCESS.
// 	*/
// 	//fix_corrupt_tlb();

	

//     let num1 = 155;
//     let num2 = 145;


// 	run_imymath_methods(num1,num2);
// }

// fn run_imymath_methods(num1: i32, num2: i32){
// 	use std::ptr::null_mut;
// 	use::windows::runtime;
// 	use::windows::Win32::System::Com;
// 	use::windows::Win32::System::Com::CLSCTX;
// 	use::windows::Win32::System::Ole;

	
// 	pub const CLSID_MY_MATH: runtime::GUID = runtime::GUID { data1: 0x9aea1e50, 
// 		data2: 0xd8c7, data3: 0x4353, data4: [0x9a, 0xa7, 0xb9, 0x1c, 0xb1, 0x74, 0xd9, 0xac] };
// 	//let CLSID_MY_MATH_PTR: *const runtime::GUID = &CLSID_MY_MATH;
	
// 	let mut obj: *mut IUnknown = null_mut();
	
// 	let result: windows::runtime::Result<IUnknown>;
// 	Com::CoInitialize(null_mut());
	
// 	//const obj1: ::windows::runtime::IntoParam<'_, ::windows::runtime::IUnknown> => ();

// 	Com::CoCreateInstance<'_, ::windows::runtime::IntoParam<'_, ::windows::runtime::IUnknown>,IUnknown>(&CLSID_MY_MATH,None,CLSCTX_INPROC_SERVER);

// }