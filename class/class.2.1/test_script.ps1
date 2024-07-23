# test_script.ps1

function ClearStatsFile {
    "" > user.txt
    Write-Host "user.txt cleared."
}


function RunTest {
    param (
        [string]$arguments,
        [string]$expectedOutput
    )

    
    ClearStatsFile

    $output = .\hello $arguments
    $outputLines = $output -split "`r?`n"
    $expectedOutputLines = $expectedOutput -split "`r?`n"
    
    $success = $true
    if ($outputLines.Length -ne $expectedOutputLines.Length) {
        $success = $false
    } else {
        for ($i = 0; $i -lt $outputLines.Length; $i++) {
            if ($outputLines[$i] -ne $expectedOutputLines[$i]) {
                $success = $false
                break
            }
        }
    }

    if ($success) {
        Write-Host "Test with arguments '$arguments' passed."
    } else {
        Write-Host "Test with arguments '$arguments' failed."
        Write-Host "Expected:"
        $expectedOutputLines | ForEach-Object { Write-Host $_ }
        Write-Host "Got:"
        $outputLines | ForEach-Object { Write-Host $_ }
    }
}


.\compile.ps1 hello.cpp hello


$testCases = @(
    @{ arguments = "Alice"; expected = "Program started.`nLoaded stats from file.`nWelcome, Alice!`nSaved stats to file.`nProgram finished." },
    @{ arguments = "Alice"; expected = "Program started.`nLoaded stats from file.`nHello again(x2), Alice!`nSaved stats to file.`nProgram finished." },
    @{ arguments = "Charlie"; expected = "Program started.`nLoaded stats from file.`nWelcome, Charlie!`nSaved stats to file.`nProgram finished." },
    @{ arguments = "Charlie delete"; expected = "Program started.`nLoaded stats from file.`nStatistics reset for Charlie.`nSaved stats to file.`nProgram finished." },
    @{ arguments = "bread"; expected = "Program started.`nLoaded stats from file.`nAll history cleared.`nSaved stats to file.`nProgram finished." }
)


foreach ($testCase in $testCases) {
    RunTest -arguments $testCase.arguments -expectedOutput $testCase.expected
}
