# コマンドライン引数 アドレス ポート番号 文字
param (
    [Parameter(Mandatory=$true)]
    [string]$ipAddress,

    [Parameter(Mandatory=$true)]
    [int]$port,

    [Parameter(Mandatory=$true)]
    [string]$message
)

$endpoint = New-Object System.Net.IPEndPoint ([System.Net.IPAddress]::Parse($ipAddress), $port)
$udpclient = New-Object System.Net.Sockets.UdpClient
$byteData = [Text.Encoding]::ASCII.GetBytes($message)
$udpclient.Send($byteData, $byteData.Length, $endpoint)
$udpclient.Close()
