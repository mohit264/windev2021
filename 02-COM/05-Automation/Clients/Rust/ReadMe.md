
# Rust IClassFactory Client for COM Automation Server
1. Install Rust from https://www.rust-lang.org/tools/install as per your OS architecure.
2. This client is tested on 64bit version of Rust
3. download required cargo tools and configure the environment variables for the downloaded tools
4. Your all other COM clients must be working as expected.
5. Create new directory in your COM Automation Clients directory and name it as Rust.
6. Create IClassFactory directory in your newly created Rust directory
7. Download the source code from this GitHub Repo
8. Ensure your folder structure as per https://github.com/mohit264/windev2021/tree/master/02-COM/05-Automation/Clients/Rust/IClassFactory
9. Modify the GUIDs for CLSID and IID of IMyMath as per created in your COM Automation server.
10. In Powershell, navigate to your IClassfactory directory and run 
  > cargo build
11. This will compile, download the dependencies and generate .exe file. 
12. Now execute below command
> cargo run
13. You should be able to see below output.
![image](https://user-images.githubusercontent.com/19527422/140683332-b5e5354c-558c-4d46-9620-0e8af95296af.png)
