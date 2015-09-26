param(
	[uri]$URI = $(throw "URI must be specified"),
	[string]$OutputFile = $null
)

if ($OutputFile -eq $null -or $OutputFile -eq "") {
	$OutputFile = [system.io.path]::GetFileName($URI.AbsolutePath)
}

$client = new-object System.Net.WebClient
$client.DownloadFile($URI, $OutputFile)
