$url = 'http://www.frijters.net/ikvmbin-8.1.5717.0.zip'
$location = $(Split-Path -Parent $MyInvocation.MyCommand.Definition)
Install-ChocolateyZipPackage 'ikvm' $url $location -checksum '260D63DA158103F9C5B385CAFF61BD47E78FB824C29C37373639C9488F973FB1' -checksumType 'SHA256'
