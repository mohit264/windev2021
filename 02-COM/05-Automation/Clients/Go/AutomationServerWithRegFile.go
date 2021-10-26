package main

import (
	"fmt"
	"syscall"
)

func main() {
	libole32, _ := syscall.LoadLibrary("ole32.dll")
	
	ptrcoInitialize, _ := syscall.GetProcAddress(syscall.Handle(libole32), "CoInitialize")
	ptrcoCreateInstance, _ := syscall.GetProcAddress(syscall.Handle(libole32), "CoCreateInstance")

	ptrcoCreateInstance()
	
}
