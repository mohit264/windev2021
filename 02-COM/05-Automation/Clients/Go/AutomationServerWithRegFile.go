package main

import (
	ole "github.com/go-ole/go-ole"
)

func main() {
	ole.CoInitialize(nil);
	
	ole.CoUninitialize()
	
}


