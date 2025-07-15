Write-Host "`n=== 📁 Add New File to CMake Project ===`n"

# Define possible projects
$projectDirs = @("ByteCore")  # add more if needed

# Show numbered list
Write-Host "Select project folder:"
for ($i = 0; $i -lt $projectDirs.Length; $i++) {
    Write-Host "[$($i+1)] $($projectDirs[$i])"
}

# Get user selection by number
$selection = Read-Host "Enter number (1-$($projectDirs.Length))"

# Validate input
if (-not [int]::TryParse($selection, [ref]$null) -or $selection -lt 1 -or $selection -gt $projectDirs.Length) {
    Write-Host "❌ Invalid selection." -ForegroundColor Red
    exit
}

$projectDir = $projectDirs[$selection - 1]

Write-Host "Selected project: $projectDir"

# Then your existing prompts for baseDir, subDir, fileName...

$baseDir = Read-Host "Enter base folder (`src` or `include`)"
if ($baseDir -ne "src" -and $baseDir -ne "include") {
    Write-Host "❌ Invalid base folder. Use 'src' or 'include'." -ForegroundColor Red
    exit
}

$subDir = Read-Host "Enter subdirectory (e.g., Engine/Core)"
$fileName = Read-Host "Enter file name with extension (e.g., MySystem.cpp)"

$halfPath = Join-Path $projectDir $baseDir

if ($baseDir -eq "include") {
    $halfPath = Join-Path $halfPath $projectDir
}

$fullPath = Join-Path $halfPath $subDir
$filePath = Join-Path $fullPath $fileName

if (-Not (Test-Path $fullPath)) {
    New-Item -ItemType Directory -Path $fullPath -Force | Out-Null
    Write-Host "📁 Created directory: $fullPath"
}

if (-Not (Test-Path $filePath)) {
    "// File: $fileName" | Out-File $filePath -Encoding UTF8
    Write-Host "📝 Created file: $filePath"
} else {
    Write-Host "⚠️ File already exists: $filePath"
}

$rerun = Read-Host "Do you want to run cmake to refresh the build files? (y/n)"
if ($rerun -eq "y") {
    if (Test-Path "build") {
        Write-Host "🔄 Refreshing CMake..."
        cmake -S . -B build | Out-Null
        Write-Host "✅ Done!"
    } else {
        Write-Host "❗ 'build' folder not found. Skipping CMake refresh."
    }
}

Write-Host "`n🎉 Done!" -ForegroundColor Green
