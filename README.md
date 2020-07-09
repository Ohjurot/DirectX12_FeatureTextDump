# DirectX12 Feature To Text
Just a small application witch dumps cpu and gpu capabilities to a text file

**Features**
Still working on the final feature list. Probably: CPUIP, System-Memory, Logical processor count, Ray-Tracing Tier, Mesh Shader Support, ...

**Requirements - For Developers / Compiling**

- Windows 10
- DirectX 12 Ultimate (Windows Version 2004 - Windows 10 May 2020 Update) or later
- Windows 10 SDK (10.0.19041.0) or later
- GPU Driver that support DirectX Ultimate (Only for certain features like checking for Mesh shader support)
  - Nvidia: [https://developer.nvidia.com/directx](https://developer.nvidia.com/directx) (Currently only availible for developers; The Application will still work on Systems with older drivers)
  - AMD: [https://www.amd.com/de/technologies/directx12](https://www.amd.com/de/technologies/directx12)  

**Requirements - For target system**

- Windows 10
- DirectX 12 Ultimate (Windows Version 2004 - Windows 10 May 2020 Update; Only for full feature support. The application will still run if DirectX 12 Ultimate is not available)
- GPU Driver that support DirectX Ultimate (Only for full feature support. The application will still run on older driver versions)

**Build Instructions**

You need [Premake 5](https://premake.github.io/) for creating the project files. The premake5.lua file will be present in the main directory of the project. Please refer to the premake documentation on how to use premake for your system and IDE!
