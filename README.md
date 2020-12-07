GaME is an acronym for GaME Mechanics Engine.

Setup Instructions

GaME uses [depot_tools]((https://commondatastorage.googleapis.com/chrome-infra-docs/flat/depot_tools/docs/html/depot_tools_tutorial.html#_setting_up) for downloading dependencies.

'''bash
mkdir new-directory-for-depot-tools-solutions
cd new-directory-for-depot-tools-solutions
git clone https://github.com/lavima/GaME.git
gclient config https://github.com/lavima/GaME.git --unmanaged
cd GaME
gclient sync
