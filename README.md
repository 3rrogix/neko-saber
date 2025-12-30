# neko-saber

A Beat Saber mod for Oculus Quest that makes all text pink, adds "UwU~" to the end of all text, makes the background pink, and replaces background images for play, settings, campaign, and multiplayer with anime girls.

## Features
- All UI text is colored pink
- "UwU~" is appended to all text
- Background color is set to pink
- Custom background images for each menu section

## Setup
1. Add your anime girl images to the `assets/` folder:
   - `solo_bg.png` (for Play/Solo menu)
   - `settings_bg.png` (for Settings menu)
   - `campaign_bg.png` (for Campaign menu)
   - `multiplayer_bg.png` (for Multiplayer menu)
   - Images should be 1024x1024 PNG with transparency if needed.

2. Build the mod using the Quest Modding Toolchain:
   - Clone https://github.com/RedBrumbler/QuestModdingToolchain
   - Copy this project into the toolchain's mods folder
   - Run the build script

3. Install the resulting .qmod file via SideQuest on your Quest.

## Note
This mod requires Scotland2 modloader and the listed dependencies in mod.json. Ensure Beat Saber version matches the packageVersion.