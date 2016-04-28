$vs_version = $args[0]
$tag = $args[1]
$vs_path = $args[2]
$depot_tools_url = $args[3]

If($depot_tools_url -and $tag)
{
	Invoke-Expression (".\get_v8.ps1 " + $tag + " " + $depot_tools_url )
}
ElseIf($tag)
{
	Invoke-Expression (".\get_v8.ps1 " + $tag)
}
ElseIf($depot_tools_url)
{
	Write-Host "Invalid parameters"
	return;
}
Else
{
	Invoke-Expression ".\get_v8.ps1"
}

If(!$vs_version)
{
	$vs_version = "2013"
	Write-Host "Using the default visual studio version: "$vs_version
}
If($vs_path)
{
	Invoke-Expression (".\build_all_platforms.ps1 " + $vs_version + " " + $vs_path)
}
Else
{
	Invoke-Expression (".\build_all_platforms.ps1 " + $vs_version)
}


