# Building Caps on Windows

This document describes how to build Caps from source on Windows using Visual Studio 2022.

## Prerequisites

### Required Software
- **Visual Studio 2022** (Community edition is fine)
  - Install "Desktop development with C++" workload
- **Python 3** (for build script)
- **Git** (for cloning vcpkg)

### Optional (for GUI)
- **Qt 5.15.10** static build (see GUI section below)

## Step 1: Install vcpkg

```powershell
cd C:\Users\ShaeOJ\Documents\GitHub
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg integrate install
```

## Step 2: Install Dependencies

```powershell
cd C:\Users\ShaeOJ\Documents\GitHub\vcpkg
.\vcpkg install berkeleydb:x64-windows-static boost-multi-index:x64-windows-static boost-process:x64-windows-static boost-signals2:x64-windows-static boost-test:x64-windows-static sqlite3:x64-windows-static "libevent[thread]:x64-windows-static" zeromq:x64-windows-static
```

This installs all required dependencies (takes ~10-15 minutes).

## Step 3: Generate Project Files

```powershell
cd C:\Users\ShaeOJ\Documents\GitHub\Caps-new
python build_msvc\msvc-autogen.py
```

## Step 4: Build

### Build Daemon Only (capsd.exe)
```powershell
"C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" build_msvc\capsd\capsd.vcxproj -property:Configuration=Release -property:Platform=x64 -verbosity:minimal
```

### Build CLI (caps-cli.exe)
```powershell
"C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" build_msvc\caps-cli\caps-cli.vcxproj -property:Configuration=Release -property:Platform=x64 -verbosity:minimal
```

### Build Everything (excluding Qt GUI)
```powershell
"C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" build_msvc\caps.sln -property:Configuration=Release -property:Platform=x64 -verbosity:minimal
```

## Output Locations

After successful build:
- `build_msvc\capsd\x64\Release\capsd.exe` - Daemon (node)
- `build_msvc\caps-cli\x64\Release\caps-cli.exe` - Command-line interface
- `build_msvc\caps-tx\x64\Release\caps-tx.exe` - Transaction tool
- `build_msvc\caps-wallet\x64\Release\caps-wallet.exe` - Wallet tool

---

## Fixes Applied (Boost 1.90+ / Modern Libraries)

The following fixes were needed for compatibility with current library versions:

### 1. Boost.Process v1 API (src/common/run_command.cpp)

Boost 1.86+ defaults to Process v2 API. Add compatibility code:

```cpp
#ifdef ENABLE_EXTERNAL_SIGNER
#include <boost/version.hpp>
#if BOOST_VERSION >= 108600
#include <boost/process/v1.hpp>
namespace bp = boost::process::v1;
#else
#include <boost/process.hpp>
namespace bp = boost::process;
#endif
#endif
```

### 2. Libevent const-correctness (build_msvc/caps_config.h)

Add this define for libevent 2.1.12+:
```cpp
#define HAVE_EVHTTP_CONNECTION_GET_PEER_CONST_CHAR 1
```

### 3. Empty Seed Arrays (src/chainparamsseeds.h)

If testnet seeds array is empty, add placeholder:
```cpp
static const uint8_t chainparams_seed_test[] = {0x00};
```

### 4. BCrypt Library (build_msvc/common.init.vcxproj)

Add `bcrypt.lib` to AdditionalDependencies:
```xml
<AdditionalDependencies>bcrypt.lib;Iphlpapi.lib;ws2_32.lib;...</AdditionalDependencies>
```

### 5. Disable vcpkg Manifest Mode (build_msvc/common.init.vcxproj)

To use pre-installed packages instead of per-project install:
```xml
<VcpkgEnableManifest>false</VcpkgEnableManifest>
<VcpkgManifestInstall>false</VcpkgManifestInstall>
```

### 6. Library Folder Naming

Ensure build_msvc library folders match solution references:
- `libcaps_cli`, `libcaps_common`, `libcaps_consensus`, `libcaps_crypto`
- `libcaps_node`, `libcaps_util`, `libcaps_wallet`, `libcaps_wallet_tool`
- `libcaps_zmq`, `libcaps_qt`, `bench_caps`, `test_caps`

### 7. ZMQ Sources (build_msvc/libcaps_zmq/libcaps_zmq.vcxproj)

If ZMQ sources are missing, add:
```xml
<ItemGroup>
  <ClCompile Include="..\..\src\zmq\zmqabstractnotifier.cpp" />
  <ClCompile Include="..\..\src\zmq\zmqnotificationinterface.cpp" />
  <ClCompile Include="..\..\src\zmq\zmqpublishnotifier.cpp" />
  <ClCompile Include="..\..\src\zmq\zmqrpc.cpp" />
  <ClCompile Include="..\..\src\zmq\zmqutil.cpp" />
</ItemGroup>
```

---

## Building the GUI (caps-qt.exe)

### Step 1: Download Qt Source

Download from: https://download.qt.io/official_releases/qt/5.15/5.15.10/single/qt-everywhere-opensource-src-5.15.10.zip

Extract to `C:\dev\qt-source`

### Step 2: Build Qt Static

Open **"x64 Native Tools Command Prompt for VS 2022"** and run:

```cmd
cd C:\dev\qt-source
mkdir build
cd build

..\configure -release -silent -opensource -confirm-license -opengl desktop -static -static-runtime -mp -qt-zlib -qt-pcre -qt-libpng -nomake examples -nomake tests -nomake tools -no-angle -no-dbus -no-gif -no-gtk -no-ico -no-icu -no-libjpeg -no-libudev -no-sql-sqlite -no-sql-odbc -no-sqlite -no-vulkan -skip qt3d -skip qtactiveqt -skip qtandroidextras -skip qtcharts -skip qtconnectivity -skip qtdatavis3d -skip qtdeclarative -skip doc -skip qtdoc -skip qtgamepad -skip qtgraphicaleffects -skip qtimageformats -skip qtlocation -skip qtlottie -skip qtmacextras -skip qtmultimedia -skip qtnetworkauth -skip qtpurchasing -skip qtquick3d -skip qtquickcontrols -skip qtquickcontrols2 -skip qtquicktimeline -skip qtremoteobjects -skip qtscript -skip qtscxml -skip qtsensors -skip qtserialbus -skip qtserialport -skip qtspeech -skip qtsvg -skip qtvirtualkeyboard -skip qtwayland -skip qtwebchannel -skip qtwebengine -skip qtwebglplugin -skip qtwebsockets -skip qtwebview -skip qtx11extras -skip qtxmlpatterns -no-openssl -no-feature-bearermanagement -no-feature-printdialog -no-feature-printer -no-feature-printpreviewdialog -no-feature-printpreviewwidget -no-feature-sql -no-feature-sqlmodel -no-feature-textbrowser -no-feature-textmarkdownwriter -no-feature-textodfwriter -no-feature-xml -prefix C:\Qt_static

nmake
nmake install
```

### Step 3: Build caps-qt

```powershell
set QTBASEDIR=C:\Qt_static
"C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" build_msvc\caps-qt\caps-qt.vcxproj -property:Configuration=Release -property:Platform=x64
```

Output: `build_msvc\caps-qt\x64\Release\caps-qt.exe`

---

## Icon Locations

Icons are embedded from these locations:
- `src\qt\res\icons\caps.ico` - Main application icon
- `src\qt\res\icons\caps_testnet.ico` - Testnet variant
- `share\pixmaps\caps.ico` - Installer icon
- `share\pixmaps\caps16.png` through `caps256.png` - Various sizes

---

## Running the Node

```powershell
# Start daemon
.\capsd.exe

# Connect to a specific node
.\capsd.exe -addnode=192.168.1.100

# Use CLI
.\caps-cli.exe getblockchaininfo
.\caps-cli.exe getpeerinfo
```

---

## Troubleshooting

### "Cannot allocate array of constant size 0"
Empty seed arrays in `chainparamsseeds.h` - add placeholder byte.

### "BCryptGenRandom unresolved"
Add `bcrypt.lib` to linker dependencies.

### "boost::process::child not found"
Using Boost 1.86+, need to include `<boost/process/v1.hpp>` instead.

### "evhttp_connection_get_peer const char**"
Define `HAVE_EVHTTP_CONNECTION_GET_PEER_CONST_CHAR` in config.

### vcpkg keeps reinstalling packages
Disable manifest mode in `common.init.vcxproj`.

### "bitcoinstrings.cpp not found"
The project references old Bitcoin naming. Update `libcaps_qt.vcxproj`:
```xml
<!-- Change from: -->
<ClCompile Include="..\..\src\qt\bitcoinstrings.cpp" />
<!-- To: -->
<ClCompile Include="..\..\src\qt\capsstrings.cpp" />
```

### Project file naming mismatch
Rename `libbitcoin_qt.vcxproj` to `libcaps_qt.vcxproj` in the `libcaps_qt` folder.

---

## Build Date
Last successful build: February 2, 2026 (daemon + GUI)

## Environment
- Windows 11
- Visual Studio 2022 (v17.14)
- vcpkg (2025-12-16)
- Boost 1.90.0
- libevent 2.1.12
