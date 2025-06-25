
# Le jeu de le pouler 3(D)

## Keybinds:

LCtrl + K : close the game  

Z/S : move forward/backward  
Q/D : strafe left/right  
A/E : rotate left/right  
mouse : rotate left/right  
Left click : attack  
1/2/3/4/5 : weapon selection  
Lshift : sprint  
escape : pause (in game)  
enter : resume (in options and pause menu), go back to the main menu (in the win screen)  

(this layout was made for AZERTY keyboards)  

#### How to read the minimap
    - blue square = player's position (has priority over everything else)  
    - green square = spawn  
    - red square = teleporter to another map  
    - yellow square = win  

## Modding support

The game supports asset modding, this means that all assets used by the game can be overriden via mods.  
When starting, the game will first load the /assets/core/ folder then, any other folder in the assets/folder. Any asset loaded by the core module can be overriden by giving an asset of the same type in another module the same name.

### Correct map format :  
size_x size_y (as integers)   
floor_texture_name  
walls_tetxure_name  
ceiling_texture_name  
next_level_name  
(empty line)  
```
XXXXXX  
XS   X  
X XX X 
X XX X
X   TX
XXXXXX
```
 (the map itself)  
#### all map characters:  
    - X = solid wall  
    - S = level's spawn point
    - T = teleporter to next level
    - W = win
    - space = empty space

### Correct weapon file format:
damage (decimal number)  
ammo (integer)  
max_ammo (integer)  
firerate (delay in seconds between each shot, decimal number)  
explosive (0 or 1, not explosive or explosive)  
melee (0 or 1, not melee or melee)

___
## Subjet's Features

## MUST

### General
- [x] The window may be closed using events.
- [x] The windows may have differents mode:
  - Window mode
  - Full - screen mode
- [x] The game manages inputs from the mouse click and keyboard.
- [x] The game contains animated sprites rendered thanks to sprite sheets.
- [x] Animations in your program are frame rate independent.
- [x] Animations and movements in your program are timed by clocks.
### Gameplay and mechanics  
- [x] Movement: Basic movements (forward, backward, left and right).
- [x] First person : First-person perspective.
- [x] Textures and sprites : Use of textures and sprites for objects.
- [x] Light (flashlight).
- [x] A basic weapon (knife or pistol): possibility to hit the walls without enemies, enemies are NOT a MUST feature.
- [x] Save system.
### Environment
- [x] Environment display (floor, ceiling and walls).
- [x] Collision system.
### Sounds and Graphics
- [x] At least one animation: Movement, shots, enemies etc.
- [x] Sound effects and music: Sounds and music to enhance the gaming experience.
- [x] Particle effects: Use particles for explosions, shots, etc
### User interface
- [x] HUD: Interface displaying essential information such as health, ammunition, etc.
- [x] Options and Settings
- [x] The main menu must contain:
  - Start the game
  - Settings : volumes and windows
- [x] Leave the game
- [x] Volume options: for sound and music.
- [x] Window resolution options: for sound and music.

## Should  
- [ ] Weapons: Several weapons ranging from knife to missile launcher, through machine guns.
- [x] Map or mini map: Display of the level map to help navigation.
- [ ] Procedural Labyrinthine Levels: Procedural generation of levels with walls, doors, floor, ceiling.
- [ ] Various enemies: Different types of enemies with distinct behaviors.
- [ ] Inventory: Interface to manage the collected items.
- [ ] Localized Damage System: Different damage based on the affected areas on enemies.
- [x] Health system: Player’s health indicator.
- [x] Ammunition: Ammunition management for each weapon.
- [ ] Doors and secrets: Locked doors requiring keys, hidden walls with secrets.
- [ ] Collectibles: Treasures, keys and other collectibles.
- [ ] Environmental Interactions: For example, firing on explosive barrels or triggering traps

## Could  
- [x] Ladder management for different floors: Mechanical to move between different levels.
- [ ] Advanced health system: Understand health effects such as bleeding or bandages.
- [ ] Special weapons: Unique weapons with special effects.
- [ ] Dynamic Weather: Integrate changing weather conditions affecting visibility and gameplay.
- [ ] Difficulty levels: Different difficulty levels adjusting the game settings.
- [x] Score and time: Scoring and timing system to measure player performance.
- [ ] Destructible environment: Elements of the decor that can be destroyed or modified.
- [ ] More complex shapes: display and manage shapes other than squares.
- [ ] Have a map editor.

## Bonus  
- [x] Jukebox : random music player in levels  
- [x] Mod support : ability to overwrite assets and to create other easily  
