$vs_version = $args[0]
$vs_path = $args[1]
$tag = $args[2]

If(!$vs_version)
{
	$vs_version = "2013"
	Write-Host "Using the default visual studio version: "$vs_version
}
if(!$tag)
{
	$tag = "5.0.71"
	Write-Host "The v8 engine version is set to default"
	Write-Host "Plese check http://omahaproxy.appspot.com/ for the latest V8 versions that chrome is using"
}

If(!$vs_path)
{
	Invoke-Expression (".\build_v8.ps1 Debug ia32 " + $vs_version + " " + $tag)
	Invoke-Expression (".\build_v8.ps1 Release ia32 " + $vs_version + " " + $tag)
	Invoke-Expression (".\build_v8.ps1 Debug x64 " + $vs_version + " " + $tag)
	Invoke-Expression (".\build_v8.ps1 Release x64 " + $vs_version + " " + $tag)	
}
Else
{
	Invoke-Expression (".\build_v8.ps1 Debug ia32 " + $vs_version + " " + $tag + " " + $vs_path)
	Invoke-Expression (".\build_v8.ps1 Release ia32 " + $vs_version + " " + $tag + " " + $vs_path)
	Invoke-Expression (".\build_v8.ps1 Debug x64 " + $vs_version + " " + $tag + " " + $vs_path)
	Invoke-Expression (".\build_v8.ps1 Release x64 " + $vs_version + " " + $tag + " " + $vs_path)
}