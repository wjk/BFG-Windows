function Get-WebFile {
	param(
		[uri]$URI = $(throw "URI must be specified"),
		[string]$OutputFile = $null
	)

	if ($OutputFile -eq $null -or $OutputFile -eq "") {
		$OutputFile = [system.io.path]::GetFileName($URI.AbsolutePath)
	}

	$client = new-object System.Net.WebClient
	$client.DownloadFile($URI, $OutputFile)
}

function Perform {
	param(
		[Parameter(Mandatory=$true)][string]$Description,
		[Parameter(Mandatory=$true)][scriptblock]$Task
	)

	Write-Host "$($Description)"
	$Task.Invoke()
	Write-Host "$($Description) -- " -NoNewline
	Write-Host "OK" -ForegroundColor Green
}

Properties {
	$OutDir = $null
}

Task default -Depends empty
Task empty {}

Task build -Depends DownloadJar
Task DownloadJar -Description "Downloads bfg-1.12.5.jar and saves it into the `$(OutDir)" -RequiredVariables OutDir {
	$jarpath = "$($OutDir)\bfg-1.12.5.jar"
	Perform "Downloading bfg-1.12.5.jar" {
		if (-not [System.IO.File]::Exists($jarpath)) {
			Get-WebFile -URI "http://repo1.maven.org/maven2/com/madgag/bfg/1.12.5/bfg-1.12.5.jar" -OutputFile $jarpath
		}
	}
}

Task clean -Description "Removes all built products" -RequiredVariables OutDir {
	rm -Force "$($OutDir)\bfg-1.12.5.jar"
}
