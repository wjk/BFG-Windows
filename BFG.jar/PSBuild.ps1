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

function Attempt {
	param(
		[string]$Description = $(throw "Description must be specified"),
		[scriptblock]$Task
	)

	try {
		Write-Host "$($Description)... " -NoNewline
		$Task.Invoke()
		Write-Host "done" -ForegroundColor Green
	} catch {
		Write-Host "failed" -ForegroundColor Red
		throw
	}
}

Task default -Depends build
Task build -Depends DownloadJar

Task DownloadJar {
	Attempt "Downloading BFG-1.12.5" {
		Get-WebFile "http://repo1.maven.org/maven2/com/madgag/bfg/1.12.5/bfg-1.12.5.jar"
	}
}

Task Clean {
	Attempt "Deleting downloaded files" {
		rm -ErrorAction SilentlyContinue "bfg-1.12.5.jar"
	}
}
