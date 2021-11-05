### Go Client for COM ClassFactory and Automation Server with dual mode
1. Download and install Go from the https://golang.org/dl/ as per your OS and CPU architecture. (This client is tested on **64bit**)
2. After installing Go, in the cmd line/powershell type ```Go version``` 
3. It should show the version of the Go language
![image](https://user-images.githubusercontent.com/19527422/139787816-ea6bc10d-0a81-4fbe-9ed1-2b481d11b257.png)
4. Your COM Server must be working for all other clients
5. Create new directory named as **GO** inside the Automation/Clients
6. Download the **AutomationIClassFactoryClient.go and Run.bat** in your newly created Go directory
7. Modify the **AutomationIClassFactoryClient.go** to update the CLSID and IID of MyMath as per **your COM Server implementation.
8. Go to the powershell and run the bat file
9. Go will download the required dependencies(require internet connection) and execute the program.
![image](https://user-images.githubusercontent.com/19527422/139788323-ba0a1e13-c728-4877-88e9-719bcb0c14e5.png)

