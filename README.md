# Le jeu de le pouler 3(D)

## Modding support

### keybindings :  
Lshift : sprint  
LCtrl + K : emergency close  
escape : pause (in game)  
enter : resume (in pause menu)  

### Correct map format :
file ending with .lvl  
first line : int int -> define the width and the height  
then:  
#### all map characters:  
    - A = solid wall  
    - C = contact (A.K.A poulers)
    - 1 = loot, weapons group
    - 2 = solid wall, destructible group
    - 3 = standard door or destructible wall
    - L = locked door
    - K = key for the door
    - M = magazines (A.K.A ammunitions)
    - D = destructible walls
    - P = player
    - N = next floor trigger (stairway)

### Correct weapon file format:
damage : float  
ammo : int  
max_ammo : int >= ammo  
firerate : float (delay in seconds between each shot)  
explosive : 0 or 1 (not explosive or explosive)  
melee : 0 or 1 (not melee or melee)

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
- [ ] Save system.
### Environment
- [x] Environment display (floor, ceiling and walls).
- [x] Collision system.
### Sounds and Graphics
- [x] At least one animation: Movement, shots, enemies etc.
- [x] Sound effects and music: Sounds and music to enhance the gaming experience.
- [ ] Particle effects: Use particles for explosions, shots, etc
### User interface
- [ ] HUD: Interface displaying essential information such as health, ammunition, etc.
- [ ] Options and Settings
- [ ] The main menu must contain:
  - Start the game
  - Settings : volumes and windows
- [x] Leave the game
- [ ] Volume options: for sound and music.
- [ ] Window resolution options: for sound and music.

## Should  
- [ ] Weapons: Several weapons ranging from knife to missile launcher, through machine guns.
- [ ] Map or mini map: Display of the level map to help navigation.
- [ ] Procedural Labyrinthine Levels: Procedural generation of levels with walls, doors, floor, ceiling.
- [ ] Various enemies: Different types of enemies with distinct behaviors.
- [ ] Inventory: Interface to manage the collected items.
- [ ] Localized Damage System: Different damage based on the affected areas on enemies.
- [ ] Health system: Player’s health indicator.
- [ ] Ammunition: Ammunition management for each weapon.
- [ ] Doors and secrets: Locked doors requiring keys, hidden walls with secrets.
- [ ] Collectibles: Treasures, keys and other collectibles.
- [ ] Environmental Interactions: For example, firing on explosive barrels or triggering traps

## Could  
- [ ] Ladder management for different floors: Mechanical to move between different levels.
- [ ] Advanced health system: Understand health effects such as bleeding or bandages.
- [ ] Special weapons: Unique weapons with special effects.
- [ ] Dynamic Weather: Integrate changing weather conditions affecting visibility and gameplay.
- [ ] Difficulty levels: Different difficulty levels adjusting the game settings.
- [ ] Score and time: Scoring and timing system to measure player performance.
- [ ] Destructible environment: Elements of the decor that can be destroyed or modified.
- [ ] More complex shapes: display and manage shapes other than squares.
- [ ] Have a map editor.
