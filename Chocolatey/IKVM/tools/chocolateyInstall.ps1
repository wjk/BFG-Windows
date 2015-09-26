$url = 'http://www.frijters.net/ikvmbin-8.1.5717.0.zip'
$location = $(Split-Path -Parent $MyInvocation.MyCommand.Definition)
Install-ChocolateyZipPackage 'ikvm' $url $location -checksum '50ebac19ddb25c6f0082b071a366bde04f0ff2a4' -checksumType 'SHA1'
