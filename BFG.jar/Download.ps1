param(
	[uri]$URI = $(throw "URI must be specified"),
	[string]$OutputFile = $null,
	[switch]$SkipIfPresent
)

if ($OutputFile -eq $null -or $OutputFile -eq "") {
	$OutputFile = [system.io.path]::GetFileName($URI.AbsolutePath)
}

if ($SkipIfPresent -and [system.io.file]::Exists($OutputFile)) {
	echo "SkipIfPresent - $($OutputFile) present, not re-downloading"
} else {
	$client = new-object System.Net.WebClient
	$client.DownloadFile($URI, $OutputFile)
}
