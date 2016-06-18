param(
	[Parameter(Mandatory=$true)][string[]]$Targets
)

$mypath = (Split-Path -Parent $MyInvocation.MyCommand.Path)

$propnames = $env:_MSB_PROPERTIES
$properties = @{}

if ($propnames -ne $null) {
	$propnames = $propnames.Split(";")
	foreach ($name in $propnames) {
		$properties[$name] = (cat Env:\$name)
	}
}

Import-Module "$($mypath)\psake\psake.psm1"
Invoke-Psake -BuildFile "$($mypath)\psakeProject.ps1" -Properties $properties -TaskList $Targets
