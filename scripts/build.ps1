<# 
 # Copyright (c) 2022-2023, Gabriel Kutuzov
 # SPDX-License-Identifier: MIT
-------------------------------------------------------------------------------
.TITLE
build.ps1
-------------------------------------------------------------------------------
#>

$run_demo = ($args[0] -eq "--demo");
$run_tests = ($args[0] -eq "--test");

# check cmake version
try {
    & 'cmake.exe' --version
} catch {
    Write-Warning "Missing cmake.exe in system path"
    Exit
}

# check msbuild version
try {
    & 'MSBuild.exe' -v
} catch {
    Write-Warning "Missing MSBuild.exe in system path. Attempting to locate..."
    
    $vswhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
    if (Test-Path $vswhere) {
        $msbuild_path = & $vswhere -latest -requires Microsoft.Component.MSBuild -find MSBuild\**\Bin\MSBuild.exe
        if ($msbuild_path) {
            $env:Path += ";$(Split-Path -Path $msbuild_path)"
        } else {
            Write-Warning "MSBuild.exe not found via vswhere."
            Exit
        }
    } else {
        Write-Warning "vswhere.exe not found. Please install Visual Studio or manually set PATH."
        Exit
    }
}

# run cmake with vcpkg
& 'cmake.exe' -S . -B build/ `
    -G "Visual Studio 17 2022" `
    -DCMAKE_TOOLCHAIN_FILE="C:\Users\conno\vcpkg\scripts\buildsystems\vcpkg.cmake" 

# msbuild
& 'MSBuild.exe' .\build\GoodsackEngine.sln

if($run_demo) {
    & .\build\output\bin\Debug\demo.exe
}
elseif($run_tests) {
    & .\build\output\bin\Debug\GoodsackEngine_Test.exe
}