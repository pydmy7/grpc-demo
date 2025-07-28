param (
    [string]$preset = "ninja-multi-config-clang",
    [string]$config = "Debug",
    [string]$target = "all"
)

$ErrorActionPreference = "Stop"

clear
echo "clear"

echo "`npreset: $preset, config: $config, target: $target"

# echo "`nRemove-Item -Recurse -Force -Path .cache"
# Remove-Item -Recurse -Force -Path .cache

# echo "`nRemove-Item -Recurse -Force -Path build"
# Remove-Item -Recurse -Force -Path build

echo "`ncmake -E make_directory ./build/.cmake/api/v1/query/client-vscode"
cmake -E make_directory ./build/.cmake/api/v1/query/client-vscode

echo "`ncmake -E capabilities | jq '.fileApi' > ./build/.cmake/api/v1/query/client-vscode/query.json"
cmake -E capabilities | jq '.fileApi' > ./build/.cmake/api/v1/query/client-vscode/query.json

echo "`nsource: cmake --preset $preset || exit 1"
cmake --preset $preset || exit 1

echo "`nbuild: cmake --build --parallel --preset $preset --config $config --target $target || exit 1"
cmake --build --parallel --preset $preset --config $config --target $target || exit 1

if ($target -eq "all") {
    exit
}

if ($?) {
    . ./scripts/path-info.ps1
    $path = getTargetPath "target_path.toml" $config $target

    echo "`nrun: cmake -E time pwsh -Command $path"
    Invoke-Expression "cmake -E time pwsh -Command $path"
} else {
    echo "`nbuild failed!!!"
    exit 1
}
