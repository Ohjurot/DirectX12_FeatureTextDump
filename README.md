# DirectX12 Feature To Text
Just a small application witch dumps cpu and gpu capabilities to a text file

**Usage**

Just drag and drop the Dx12Features-v?_?-x86_64-Release.exe file from the your downloads to any location on your computer. Double click the application, a cmd window will pop up and close again imidiatly. You should now have a text file ("dxFeatures.txt") created at the location you opened the application. 
If the text file was not created try to run the application from the cmd, it will give you additional information if somothing failed. Also check that you have write permission for the folder where the application tryes to create the file!

**Features (Version 1.0)**

- CPUID (Vendor, Brand, Instruction sets)
- System info ( Processor packages, processor cores, processor vitual cores, processor caches, physical memory)
- GPU enumeration (Description, Vendorid, Deviceid, Subsysid, Revision, Memory)
- Shader modell version
- DirectX 12 feature level (Level 12.2 currently not implemented in the windows sdk)
- Root signature version
- Shader cache support
- Existing heaps support
- Wave lane count max / min
- Total lanes count
- Int64 support
- MSAA64KB support
- Render passes tier
- Raytracing support
- Variable shading rate support
- Additional shading rates
- Per primitive shading rate with indexing
- Mesh shader support
- Sampler feedback support


**Requirements - For Developers / Compiling**

- Windows 10
- DirectX 12 Ultimate (Windows Version 2004 - Windows 10 May 2020 Update) or later
- Windows 10 SDK (10.0.19041.0) or later
- GPU Driver that support DirectX 12 Ultimate (Only for certain features like checking for Mesh shader support)
  - Nvidia: [https://developer.nvidia.com/directx](https://developer.nvidia.com/directx) (Currently only availible for developers; The Application will still work on Systems with older drivers)
  - AMD: [https://www.amd.com/de/technologies/directx12](https://www.amd.com/de/technologies/directx12)  

**Requirements - For target system**

- Windows 10
- DirectX 12 Ultimate (Windows Version 2004 - Windows 10 May 2020 Update; Only for full feature support. The application will still run if DirectX 12 Ultimate is not available)
- GPU Driver that support DirectX 12 Ultimate (Only for full feature support. The application will still run on older driver versions)

**Build Instructions**

You need [Premake 5](https://premake.github.io/) for creating the project files. The premake5.lua file will be present in the main directory of the project. Please refer to the premake documentation on how to use premake for your system and IDE!
