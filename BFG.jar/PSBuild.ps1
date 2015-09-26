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
	$outfile = "bfg-1.12.5.jar"
	Attempt "Downloading BFG-1.12.5" {
		if (-not [System.IO.File]::Exists($outfile)) {
			Get-WebFile "http://repo1.maven.org/maven2/com/madgag/bfg/1.12.5/bfg-1.12.5.jar" $outfile
		}
	}

	if (-not $OutDir -eq $null -and -not $OutDir -eq "") {
		Attempt "Copying jar to OutDir" {
			copy $outfile $OutDir\$outfile
		}
	}
}

Task Clean {
	Attempt "Deleting downloaded files" {
		rm -ErrorAction SilentlyContinue "bfg-1.12.5.jar"
	}
}
