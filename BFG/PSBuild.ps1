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

Task default -Depends DownloadJar

Task DownloadJar {
	Write-Host "Downloading BFG-1.12.5... " -NoNewline

	try {
		Get-WebFile "http://repo1.maven.org/maven2/com/madgag/bfg/1.12.5/bfg-1.12.5.jar"
		Write-Host "done" -ForegroundColor Green
	} catch {
		Write-Host "failed" -ForegroundColor Red
		throw
	}
}
