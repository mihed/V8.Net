$vs_version = $args[0]
$vs_path = $args[1]

If(!$vs_version)
{
	$vs_version = "2013"
	Write-Host "Using the default visual studio version: "$vs_version
}
If(!$vs_path)
{
	Invoke-Expression (".\build_v8.ps1 Debug ia32 " + $vs_version)
	Invoke-Expression (".\build_v8.ps1 Release ia32 " + $vs_version)
	Invoke-Expression (".\build_v8.ps1 Debug x64 " + $vs_version)
	Invoke-Expression (".\build_v8.ps1 Release x64 " + $vs_version)	
}
Else
{
	Invoke-Expression (".\build_v8.ps1 Debug ia32 " + $vs_version + " " + $vs_path)
	Invoke-Expression (".\build_v8.ps1 Release ia32 " + $vs_version + " " + $vs_path)
	Invoke-Expression (".\build_v8.ps1 Debug x64 " + $vs_version + " " + $vs_path)
	Invoke-Expression (".\build_v8.ps1 Release x64 " + $vs_version + " " + $vs_path)
}