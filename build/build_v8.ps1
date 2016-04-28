$build_type = $args[0]
$arch = $args[1]
$vs_version = $args[2]
$tag = $args[3]
$vs_path = $args[4]
$current_location = Split-Path -Parent $MyInvocation.MyCommand.Definition
$depot_tools_path = [io.path]::Combine($current_location, "depot_tools")
$v8_path = [io.path]::Combine($depot_tools_path, "v8")

If(!((Test-Path $depot_tools_path) -and (Test-Path $v8_path)))
{
	Write-Host "Depot tools and v8 need to be set up correctly before launching the build"
	return
}

If(!$arch)
{
	$arch = "x64"
}
ElseIf($arch -ne "x64" -and $arch -ne "ia32")
{
	Write-Host "The target architecture is not valid"
	return
}

If(!$build_type)
{
	$build_type = "Release"
}
ElseIf($build_type -ne "Release" -and $build_type -ne "Debug")
{
	Write-Host "The build type is not valid"
	return
}

If(!$vs_version)
{
	$vs_version = "2013"
}

If(!$vs_path)
{
	$vs_path = "c:\Program Files (x86)\Microsoft Visual Studio"
	If($vs_version -eq "2010")
	{
		$vs_path += " 10.0"
	}
	ElseIf($vs_version -eq "2012")
	{
		$vs_path += " 11.0"
	}
	ElseIf($vs_version -eq "2013")
	{
		$vs_path += " 12.0"
	}
	ElseIf($vs_version -eq "2015")
	{
		$vs_path += " 14.0"
	}
	Else
	{
		Write-Host "The visual studio version is not supported"
		return
	}
}
ElseIf(!(Test-Path $vs_path))
{
	Write-Host "The visual studio path is not valid"
	return
}

if(!$tag)
{
	$tag = "5.0.71"
	Write-Host "The v8 engine version is set to default"
	Write-Host "Plese check http://omahaproxy.appspot.com/ for the latest V8 versions that chrome is using"
}

$ms_builder = [io.path]::Combine($vs_path, "Common7\IDE\devenv.com")
Set-Location $depot_tools_path
$env:DEPOT_TOOLS_WIN_TOOLCHAIN=0
$env:GYP_MSVS_VERSION=$vs_version

Set-Location $v8_path
Write-Host "Cleaning the directory from previous builds..."
$git_path = [io.path]::Combine($depot_tools_path, "git")
cmd.exe /c $git_path clean -d -f -x
Write-Host "The exit code from the clean command: "$LastExitCode
Set-Location $depot_tools_path

Write-Host "Synchronizing gclient..."
cmd.exe "/c gclient sync"
Write-Host "The exit code from synchronizing is: "$LastExitCode

Set-Location $v8_path
Write-Host "Checking out tag: "$tag
cmd.exe ("/c git checkout " + $tag)
Write-Host "The exit code from git checkout is: "$LastExitCode
Set-Location $depot_tools_path

Write-Host "Launching gyp..."
cmd.exe ("/c python v8\build\gyp_v8 -Dv8_target_arch=" + $arch)
Write-Host "The exit code from gyp is: "$LastExitCode

$solution_file = [io.path]::Combine($v8_path, "build\All.sln")
If(!(Test-Path $solution_file))
{
	Write-Host "Not found: "$solution_file 
	return
}

Write-Host "Building v8..."
cmd.exe /c $ms_builder $solution_file /rebuild $build_type
Write-Host "The exit code from devenv.com is: "$LastExitCode

Write-Host "Testing v8..."
cmd.exe /c python .\v8\tools\run-tests.py --buildbot --outdir build --arch $arch --mode $build_type
Write-Host "The exit code from the tests: "$LastExitCode

$destination_lib_path = [io.path]::Combine($current_location, "..", "lib", $arch)
$destination_lib_folder = [io.path]::Combine($destination_lib_path, $build_type)
if(Test-Path $destination_lib_folder)
{
	Remove-Item -Recurse -Force $destination_lib_folder
}
if(!(Test-Path $destination_lib_path))
{
	New-Item -ItemType directory -Path $destination_lib_path
}

$output_directory = [io.path]::Combine($v8_path, "build", $build_type)
Write-Host "Copying the libraries to /lib..."
Copy-Item -Path $output_directory -Destination $destination_lib_path -recurse -Force
Write-Host "Done copying"

Set-Location $current_location






