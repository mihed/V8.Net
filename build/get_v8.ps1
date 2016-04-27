$tag = $args[0]
$depot_tools_url = $args[1]
$current_location = Split-Path -Parent $MyInvocation.MyCommand.Definition
$depot_tools_path = [io.path]::Combine($current_location, "depot_tools")
$depot_tools_zip_path = [io.path]::Combine($depot_tools_path, "depot_tools.zip")

if(!$tag)
{
	$tag = "5.0.71"
	Write-Host "The v8 engine version is set to default"
	Write-Host "Plese check http://omahaproxy.appspot.com/ for the latest V8 versions that chrome is using"
}
Write-Host "The chosen V8 version is:"$tag

if(!$depot_tools_url)
{
	$depot_tools_url = "https://storage.googleapis.com/chrome-infra/depot_tools.zip"
	Write-Host "The depot tools url path is set to default"
}
Write-Host "The depot_tools url is: "$depot_tools_url

if(!(Test-Path $depot_tools_path))
{
	New-Item -ItemType directory -Path $depot_tools_path
	Write-Host "depot_tools is not found." 
	Write-Host "Downloading from "$depot_tools_url
	Write-Host "Inserting into: "$depot_tools_path
	
	Import-Module BitsTransfer
	Start-BitsTransfer -Source $depot_tools_url -Destination $depot_tools_zip_path
	
	Write-Host "Unpacking depot tools..."
	$shell = new-object -com shell.application
	$zip = $shell.NameSpace($depot_tools_zip_path)
	foreach($item in $zip.items())
	{
		$shell.Namespace($depot_tools_path).copyhere($item)
	}
	Write-Host "depot_tools is now unpacked"
}
else
{
	Write-Host "depot_tools was found and does not require a download"
}

Set-Location $depot_tools_path
$env:DEPOT_TOOLS_WIN_TOOLCHAIN=0

Write-Host "Firing up gclient..."
cmd.exe "/c gclient"
Write-Host "The exit code from gclient is: "$LastExitCode

Write-Host "Fetching V8..."
cmd.exe "/c fetch v8"
Write-Host "The exit code from fetch is: "$LastExitCode

Write-Host "Synchronizing gclient..."
cmd.exe "/c gclient sync"
Write-Host "The exit code from synchronizing is: "$LastExitCode

$v8_path = [io.path]::Combine($depot_tools_path, "v8")
Set-Location $v8_path

Write-Host "Checking out tag: "$tag
cmd.exe ("/c git checkout " + $tag)
Write-Host "The exit code from git checkout is: "$LastExitCode

Set-Location $current_location



