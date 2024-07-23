# compile.ps1
param (
    [string]$sourceFile,
    [string]$outputFile
)

if (-not $sourceFile -or -not $outputFile) {
    Write-Host "Usage: .\compile.ps1 <source_file> <output_file>"
    exit 1
}

$flags = "-Wall -Wextra -Wpedantic -Werror -std=c++23"
$command = "clang++ $flags $sourceFile -o $outputFile"

Write-Host "Compiling with command: $command"

Invoke-Expression $command

if ($LASTEXITCODE -eq 0) {
    Write-Host "Compilation successful."
} else {
    Write-Host "Compilation failed with exit code $LASTEXITCODE."
    exit $LASTEXITCODE
}
