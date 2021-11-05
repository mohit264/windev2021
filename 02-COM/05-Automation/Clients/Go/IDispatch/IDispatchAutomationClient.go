package main

import (
	"fmt"
	"syscall"
	"unsafe"

	com "github.com/go-ole/go-ole"
)

// This struct is defined in go-ole package, however due to some null pointer exception
// I'm bypassing package struct and creating it here
type DISPPARAM struct {
	rgvarg            []com.VARIANT
	cArgs             int32
	cNamedArgs        int32
	rgdispidNamedArgs uintptr
}

func main() {

	// Variable declarations
	var num1, num2 int32
	var vArgs [2]com.VARIANT
	var vRet com.VARIANT
	var params DISPPARAM

	num1 = 155
	num2 = 145
	
	/*----------------------------------------------------------*/
	// We don't need to do this at all as this is already taken care in
	// go-ole package invoke call. However it is throwing null reference
	// exception. So initalizing all the variants myself
	// Need to do further study on the null reference exception.
	// I am sure I am missing something
	/*------ Nehami Apanach Chukato----------------------------*/

	com.VariantInit(&vArgs[0])
	com.VariantInit(&vRet)

	vArgs[0].VT = com.VT_INT
	vArgs[0].Val = int64(num2)

	vArgs[1].VT = com.VT_INT
	vArgs[1].Val = int64(num1)
	/*----------------------------------------------------------*/
	vRet.VT = com.VT_INT
	vRet.Val = 0

	params.cNamedArgs = 0
	params.cArgs = 2
	params.rgdispidNamedArgs = uintptr(0)
	params.rgvarg = vArgs[:]

	//CLSID of CSumSubtract
	CLSID_MyMath := com.NewGUID("{9AEA1E50-D8C7-4353-9AA7-B91CB174D9AC}")

	//code
	com.CoInitialize(0)
	defer com.CoUninitialize()

	unknown, err := com.CreateInstance(CLSID_MyMath, com.IID_IUnknown)
	if err != nil {
		return
	}

	dispatch, err := unknown.QueryInterface(com.IID_IDispatch)
	if err != nil {
		return
	}
	unknown.Release()

	dispid, err := dispatch.GetSingleIDOfName("SumOfTwoIntegers")
	if err != nil {
		return
	}

	var excepInfo com.EXCEPINFO

	hr, _, _ := syscall.Syscall9(
		dispatch.VTable().Invoke,
		9,
		uintptr(unsafe.Pointer(dispatch)),
		uintptr(dispid),
		uintptr(unsafe.Pointer(com.IID_NULL)),
		uintptr(com.GetUserDefaultLCID()),
		uintptr(com.DISPATCH_METHOD),
		uintptr(unsafe.Pointer(&params)),
		uintptr(unsafe.Pointer(&vRet)),
		uintptr(unsafe.Pointer(&excepInfo)),
		0)

	if hr != 0 {
		println("some error occured")
	}

	str := fmt.Sprintf("Sum of %d and %d is %d", num1, num2, vRet.Val)
	println(str)

	dispid, err = dispatch.GetSingleIDOfName("SubtractionOfTwoIntegers")
	if err != nil {
		return
	}

	hr, _, _ = syscall.Syscall9(
		dispatch.VTable().Invoke,
		9,
		uintptr(unsafe.Pointer(dispatch)),
		uintptr(dispid),
		uintptr(unsafe.Pointer(com.IID_NULL)),
		uintptr(com.GetUserDefaultLCID()),
		uintptr(com.DISPATCH_METHOD),
		uintptr(unsafe.Pointer(&params)),
		uintptr(unsafe.Pointer(&vRet)),
		uintptr(unsafe.Pointer(&excepInfo)),
		0)

	if hr != 0 {
		println("some error occured")
	}

	str = fmt.Sprintf("Subtraction of %d and %d is %d", num1, num2, vRet.Val)
	println(str)
}
