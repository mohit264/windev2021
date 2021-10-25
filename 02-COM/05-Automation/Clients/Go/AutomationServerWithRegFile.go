package main

import (
	"fmt"
	"log"
	"syscall"
)

func main() {
	h, e := syscall.LoadLibrary("hello.dll")
	if e != 0 {
		log.Fatal(syscall.Errstr(e))
	}
	defer syscall.FreeLibrary(h)
	proc, e := syscall.GetProcAddress(h, "Hello")
	if e != 0 {
		log.Fatal(syscall.Errstr(e))
	}
	n, _, _ := syscall.Syscall(uintptr(proc), 0, 0, 0, 0)
	fmt.Printf("Hello dll function returns %d\n", n)
}
