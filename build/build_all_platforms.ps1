$vs_version = $args[0]
$vs_path = $args[1]

Invoke-Expression build_v8.ps1 Debug ia32 $vs_version $vs_path
Invoke-Expression build_v8.ps1 Release ia32 $vs_version $vs_path
Invoke-Expression build_v8.ps1 Debug x64 $vs_version $vs_path
Invoke-Expression build_v8.ps1 Release x64 $vs_version $vs_path