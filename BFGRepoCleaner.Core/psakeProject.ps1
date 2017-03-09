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

Task default -Depends build
Task build -Depends DownloadJar
Task DownloadJar -Description "Downloads bfg-1.12.15.jar and saves it into the `$(OutDir)" -RequiredVariables OutDir {
	$jarpath = "$($OutDir)\bfg-1.12.15.jar"
	Perform "Downloading bfg-1.12.15.jar" {
		if (-not [System.IO.File]::Exists($jarpath)) {
			iwr "http://repo1.maven.org/maven2/com/madgag/bfg/1.12.15/bfg-1.12.15.jar" -OutFile $jarpath
		}
	}
}

Task clean -Description "Removes all built products" -RequiredVariables OutDir {
	rm -Force "$($OutDir)\bfg-1.12.15.jar"
}
