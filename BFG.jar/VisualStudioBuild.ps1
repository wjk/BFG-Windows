param(
	[string[]]$Params = @(),
	[string[]]$Tasks = @()
)

$ParsedParams = @{}
$isKey = $true; $key = $null
foreach ($param in $Params) {
	if ($isKey) {
		$key = $param
	} else {
		$ParsedParams[$key] = $param
	}
	$isKey = -not $isKey
}

$ScriptPath = (Split-Path -Parent $MyInvocation.MyCommand.Path)
& "$ScriptPath\psake\psake.ps1" -BuildFile PSBuild.ps1 -Parameters $ParsedParams -TaskList $Tasks
