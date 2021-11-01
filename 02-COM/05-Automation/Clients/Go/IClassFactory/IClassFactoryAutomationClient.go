package main

import (
	"fmt"
	"log"
	"syscall"
	"unsafe"

	"golang.org/x/sys/windows"
)

// Structure of GID Data type
type GUID struct {
	Data1 uint32
	Data2 uint16
	Data3 uint16
	Data4 [8]byte
}

// Go is similar to C!
// Structure of ISum vtable
type IMyMathVtbl struct {
	// every COM object starts with these three
	QueryInterface uintptr
	AddRef         uintptr
	Release        uintptr

	//IDispatch methods
	GetTypeInfoCount uintptr
	GetTypeInfo      uintptr
	GetIDsOfNames    uintptr
	Invoke           uintptr

	// here are all additional methods of this ISum interface
	SumOfTwoIntegers         uintptr
	SubtractionOfTwoIntegers uintptr
}

// ISum interface
type IMyMath struct {
	lpVtbl *IMyMathVtbl
}

// Type definitions for better readability and feel of WINDOWS Programming
type IID syscall.GUID
type CLSID syscall.GUID
type REFIID *IID
type REFCLSID *CLSID

// Need to pass to the COM CO-Create Instance
const (
	CLSCTX_INPROC_SERVER = 0x1
)

//This is MUST!
//In Latest COM implementation for GO Projections, CoInitilize is deprecated!.
// So we need to call COInitializeEx API with Apartment threaded. If we don't pass
// apartment threaded COM gives error!
const (
	COINIT_APARTMENTTHREADED = 0x2
)

func main() {

	// Variable declarations
	var ppv unsafe.Pointer
	var pIMyMath *IMyMath

	//CLSID of CSumSubtract
	CLSID_MyMath := CLSID{0x9aea1e50, 0xd8c7, 0x4353,
		[8]byte{0x9a, 0xa7, 0xb9, 0x1c, 0xb1, 0x74, 0xd9, 0xac}}

	//IID of ISum
	IID_IMyMath := IID{0xbac91261, 0x3c2f, 0x4cfb,
		[8]byte{0x9a, 0xfb, 0xf8, 0x23, 0x57, 0x2f, 0x83, 0x8f}}

	var (
		handle, _ = syscall.LoadLibrary("ole32.dll")
	)

	//pSum := &int
	//code
	//As mentioned above we need to call windows COINIT apartment threaded
	windows.CoInitializeEx(uintptr(0), COINIT_APARTMENTTHREADED)

	// Either there is any error / panic situations
	// or before finishing main the "defer" function gets called
	defer windows.CoUninitialize()

	procCoCreateInstance, _ := syscall.GetProcAddress(handle, "CoCreateInstance")

	// Pass Required paramaeters to CoCreateInstance.

	hr := coCreateInstance(procCoCreateInstance, &CLSID_MyMath, nil, 1, &IID_IMyMath, &ppv)
	if hr < 0 {
		return
	}

	pIMyMath = (*IMyMath)(ppv)

	num1 := 155
	num2 := 145
	// Go is really good in type safety. You need to initialize integer sum variable.

	sum := 0
	// Assign the address of sum variable to the ptrSum to pass
	// as argument to Sum of Two integers
	ptrSum := &sum
	retSum := pIMyMath.SumOfTwoIntegers(num1, num2, ptrSum)

	if retSum == 0 {
		str := fmt.Sprintf("Sum of %d and %d is %d", num1, num2, sum)
		println(str)
	}

	// Initialize sub to get some memory location as an integer type
	sub := 0

	// Get the pointer to sub
	ptrSub := &sub

	retSub := pIMyMath.SubtractionOfTwoIntegers(num1, num2, ptrSub)

	if retSub < 0 {
		pIMyMath.Release()
		panic(-1)
	}
	pIMyMath.Release()
	str := fmt.Sprintf("Subtraction of %d and %d is %d", num1, num2, sub)
	println(str)
}

func checkOK(hr uintptr, caller string) {
	if hr != 0x0 {
		log.Fatalf("%s returned 0x%08x", caller, hr)
	}
}

func coCreateInstance(ptrcoCreateInstance uintptr, rclsid REFCLSID,
	pUnkOuter unsafe.Pointer, dwClsContext uint32, riid REFIID, ppv *unsafe.Pointer) int32 {

	// syscall is a package provideded by Go language to call OS SDK APIs
	// SysCall6 means you have to pass 6 parameters to the SDK API you are calling
	// 1st Parameter: Address of CoCreate Instance
	// 2nd Parameter: count of parameters/arguments to CoCreate Instance
	// 3rd Parameter: 1st parameter of CoCreateInstance (CSumSubtract CLSID)
	// 4th Parameter: 2nd parameter of CoCreateInstance (pUnknown Outer will be nil = NULL in Go)
	// 5th Parameter: 3rd Parameter of CoCreateInstance (CLSCTX_INPROC_SERVER)
	// 6th Parameter: 4th Parameter of CoCreateInstance (IID of ISum)
	// 7th Parameter: 5th Parameter of CoCreateIntance (To receive Pointer to ISum from
	// COM Server we have implemented using Class Factory)

	ret, _, _ := syscall.Syscall6(ptrcoCreateInstance, 5,
		uintptr(unsafe.Pointer(rclsid)),
		uintptr(pUnkOuter),
		uintptr(dwClsContext),
		uintptr(unsafe.Pointer(riid)),
		uintptr(unsafe.Pointer(ppv)),
		0)
	checkOK(ret, "CoCreateInstance")
	return int32(ret)
}

func (this *IMyMath) SumOfTwoIntegers(num1 int, num2 int, pSum *int) int32 {

	ret, _, _ := syscall.Syscall6(this.lpVtbl.SumOfTwoIntegers, 4,
		uintptr(unsafe.Pointer(this)),
		uintptr(num1),
		uintptr(num2),
		uintptr(unsafe.Pointer(pSum)),
		0, 0)

	checkOK(ret, "SumOfTwoIntegers")
	return int32(ret)
}

func (this *IMyMath) Release() uint32 {
	ret, _, _ := syscall.Syscall(this.lpVtbl.Release, 1,
		uintptr(unsafe.Pointer(this)),
		0,
		0)

	return uint32(ret)
}

func (this *IMyMath) SubtractionOfTwoIntegers(num1 int, num2 int, pSub *int) int32 {

	ret, _, _ := syscall.Syscall6(this.lpVtbl.SubtractionOfTwoIntegers, 4,
		uintptr(unsafe.Pointer(this)),
		uintptr(num1),
		uintptr(num2),
		uintptr(unsafe.Pointer(pSub)),
		0, 0)

	checkOK(ret, "SubtractionOfTwoIntegers")
	return int32(ret)
}
