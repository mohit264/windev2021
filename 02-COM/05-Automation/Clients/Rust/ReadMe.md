
# Rust IClassFactory Client for COM Automation Server
1. Install Rust from https://www.rust-lang.org/tools/install as per your OS architecure
2. download required cargo tools and configure the environment variables for the downloaded tools
3. Your all other COM clients must be working as expected.
4. Create new directory in your COM Automation Clients directory and name it as Rust.
5. Create IClassFactory directory in your newly created Rust directory
6. Download the source code from this GitHub Repo
7. Ensure your folder structure as per https://github.com/mohit264/windev2021/tree/master/02-COM/05-Automation/Clients/Rust/IClassFactory
8. Modify the GUIDs for CLSID and IID of IMyMath as per created in your COM Automation server.
9. In Powershell, navigate to your IClassfactory directory and run 
  > cargo build
10. This will compile, download the dependencies and generate .exe file. 
11. Now execute below command
> cargo run
12. You should be able to see below output.
![image](https://user-images.githubusercontent.com/19527422/140683332-b5e5354c-558c-4d46-9620-0e8af95296af.png)
