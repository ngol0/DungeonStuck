# Stuck In A Dungeon
## Introduction
A 2D dungeon crawler game made with a simple custom 2D game engine. This game and the game engine is made using C++ and SDL2. This is made for educational purpose and I referenced different sources which are mentioned in the `Attribute` section.

<img src="https://github.com/ngol0/DungeonStuck/blob/main/gameplay.gif" width="900" title="build">

## Current technical features
  * #### ECS architecture:
    ECS (Entity Component System) to help manage entities, components, and systems that are in the game.

 * #### Input Binding Tool:
   A tool created using DearImGui to help player rebind the input by choosing from the Drop down menu and click Save. User cannot choose the input that is already in use for other actions

   <img src="https://github.com/ngol0/DungeonStuck/blob/main/input.gif" width="900" title="build">

 * #### Event System:
   An event system that allows user to pass custom data (i.e: CollisionData, InputData, etc.)
   
 * #### Collision System:
   Collision system with OnCollisionEnter, OnCollisionStay and OnCollisionExit. This is used to prevent player from going through wall or to allow hitbox - and to trigger certain events when player touches a checkpoint

 * #### Data-driven level:
   A .map file with data about tile, transform, colliders is read to create the level layout

## Future Plans
- [ ] AI System and Pathfinding
- [ ] Combat System
- [ ] Interation System (with things/people)
- [ ] Dialogue System
- [ ] Shop System
- [ ] Inventory System
- [ ] Some other useful tools such as Level Editor, etc.
- [ ] UI System
- [ ] Scripting with Lua

## Build
The game is currently only run in Mac & Linux. Download the project and type `make run` in the terminal to run the game.

## Attribute
The game engine with the ECS structure is made using references from [Pikuma Game Engine Course](https://pikuma.com/courses/cpp-2d-game-engine-development) course and from this [Link](https://www.david-colson.com/2020/02/09/making-a-simple-ecs.html).
