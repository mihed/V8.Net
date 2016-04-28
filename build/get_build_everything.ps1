$vs_version = $args[0]
$tag = $args[1]
$vs_path = $args[2]
$depot_tools_url = $args[3]

Invoke-Expression get_v8.ps1 $tag $depot_tools_url 
Invoke-Expression build_all_platforms.ps1 $vs_version $vs_path

