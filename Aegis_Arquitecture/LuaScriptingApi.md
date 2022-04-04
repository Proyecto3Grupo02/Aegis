# Aegis Scripting Api

## Table of Contents
- [Aegis Scripting Api](#aegis-scripting-api)
	- [Table of Contents](#table-of-contents)
- [Game Init](#game-init)
- [Tables and Namespaces](#tables-and-namespaces)
	- [Aegis methods](#aegis-methods)
	- [Aegis.NativeComponents methods](#aegisnativecomponents-methods)
	- [Aegis.Maths](#aegismaths)
- [Types and Functions](#types-and-functions)
	- [Functions](#functions)
	- [Properties](#properties)
	- [Operators](#operators)
	- [Aegis](#aegis)
		- [Scene](#scene)
		- [InputSystem](#inputsystem)
		- [Entity](#entity)
		- [ComponentBase](#componentbase)
		- [AegisComponent](#aegiscomponent)
	- [Aegis.NativeComponents](#aegisnativecomponents)
		- [Transform](#transform)
		- [Renderer](#renderer)
	- [Aegis.Maths](#aegismaths-1)
		- [Vector3](#vector3)
		- [Vector4](#vector4)
		- [Quaternion](#quaternion)
- [Components](#components)
- [Entities and Scenes](#entities-and-scenes)
	- [Scene dependencies](#scene-dependencies)
- [Lua Utils](#lua-utils)
- [Limitations](#limitations)

# Game Init

AegisEngine calls init.lua script before the game loop. This script should be located inside the engine folder or LuaScripts folder outside the engine folder. You can define them custom paths for your other scripts (which I do not recommend)

# Tables and Namespaces

Aegis provides one table that acts as namespace: Aegis.
This table contains the namespaces NativeComponents and Maths.
There are also some global variables: currentScene and Input.

Now I'll list the functions in each namespace.

Note that these functions are lua functions but they expect C++ parameters. This parameters are userdata types in lua and some of them have functions (explained later in next section). All userdata are ref values

## Aegis methods

> CreateEntity(Scene scene, Vector3 pos) -> void

> CreateComponent(string componentName, Entity entity) -> AegisComponent

## Aegis.NativeComponents methods

These are methods for creating C++ prebuilt componentes, it will be explained better in [Components](#Components) section. (more components to be added soon)

> CreateRenderer(Entity* entity, string meshName) -> Renderer

## Aegis.Maths

Aegis.Maths contains types for math operations such as Vector3, Vector4, Quaternion... But it doesn't contain any functions at namespace level.

# Types and Functions

## Functions

Some c++ clases are exported to lua as userdata that can be used as tables.
When calling a function it's recommended to use ":" instead of "."

> entity.AddComponent(component)

The example above is not correct, the two correct ways for calling a member function are

> entity.AddComponent(entity, component)

> entity:AddComponent(component)

Note how using ":" is less verbose than using ".". But be aware that this only apply to userdata/class functions. Namespaces functions are called using ".". For example: Aegis.CreateEntity() is correct, Aegis:CreateEntity() is not correct.

Calling a function that doesn't exist on a namespace or a userdata/class will result in an irrecuperable error.

Now here you can consult classes and class methods (these ones are called with ":", the ones in the previous section with "."). I've said this twice and you will still make mistakes, you'll remember this.

## Properties

Classes/userdata exposes functions and properties. Functions always start uppercase while properties always start lowercase. Properties are accessed as public c++ properties using dot notation (entity.transform.position)

Some of the properties are inmutable, this means you can change instance variable but not override the instance.

Example (mutable data):
transform.position = Vector3(0,0,0) is correct
transform.position.x = 5 is correct (but this won't work, explained later)

Example (inmutable data):
transform = otherTransform; is not correct, you can't override transform
transform.position is correct, you can change the instance property

## Operators

Some classes/userdata support operator through metamethods (__add, __sub...).
But these only work for the right part, example:

Vector3 * float -> is correct
float * Vector3 -> not correct, will through error

## Aegis

### Scene

This is the class that contains all the entities and the methods for managing them. Currently there is no way to remove and entity from the scene. This class doesn't have a constructor for lua, instances of this class are managed in C++ and controlled by functions from lua (still wip)

Methods:

> AddEntity(Entity* entity) -> void

### InputSystem

This is a singleton class that is also a global variable in lua. It allows you to read from keyboard (gamepad not for now)

Methods:

> KeyWasPressed(string key) -> bool

> IsKeyDown(string key) -> bool

> KeyWasReleased(string key) -> bool

> AnyKeyWasPressed() -> bool

> AnyKeyIsDown() -> bool

> AnyKeyWasReleased() -> bool

### Entity

Base class for the game, it holds components at updates them by calling their methods. Currently there is no way to parent/nest entities due to Ogre SceneNode limitations, but it will be added.

Methods:

> AddComponent(AegisComponent* component) -> void

> GetComponent(string componentName) -> AegisComponent

> IsActive() -> bool

> SetActive(bool active) -> void

> GetName() -> string

> SetName(string name) -> void

> GetScene() -> Scene
 
Properties:

> transform -> Transform (inmutable)

### ComponentBase

As it name says, it's the parent class of AegisComponent, it doesn't have a constructor but it's registered as a "type" in lua and provides some properties to AegisComponent thourgh heritance

Properties:

> name -> string (inmutable)

> entity -> Entity (inmutable)

Notice that name is the "type" of the script and it's the id used to find when calling GetComponent on an entity.

### AegisComponent

This is the most importante piece, here is where we make out entities actually do things and react. It has some methods and properties, in the next section we'll talk more about this class.

Properties:

> data -> LuaRef (inmutable)

> type -> LuaRef (inmutable)

Note thas this class doesn't have a constructor, it's instead created calling Aegis.CreateComponent(name). This is done this way so the component is created in C++ and doesn't have lua lifetime. Creating the component in lua can lead to problems.

## Aegis.NativeComponents

### Transform

This component is automatically added to all entities when they are created in C++, but the class is exposed to lua so it can be actually useful. This class is still in progress.

Properties:

> position -> Vector3 (mutable)

> rotation -> Quaternion (mutable)

> localEulerAngles -> Vector3 (mutable)

 	Be aware that localEulerAngles return a value between -180 and 180 instead of 0 and 360.

### Renderer

Class that holds mesh and materials for Ogre to render. This class is still in progress

Properties:

> visible -> bool (mutable)

## Aegis.Maths

### Vector3

Basic Vector3 to use mainly with transform. This is one of the few classes to have a constructor.

Constructor:

Vector3(float x, float y, float z) -> Vector3

Properties: (readonly, aka inmutable)

> x -> float

> y -> float
 
> z -> float

Operators:

> Vector3 supports +, -, * and / operators

### Vector4

Constructor:

Vector4(float x, float y, float z, float w) -> Vector4

Properties: (readonly)

> x -> float

> y -> float

> z -> float

> w -> float

### Quaternion

Constructor

Quaternion(float x, float y, float z, float w) -> Quaternion

Methods:

> ToEuler() -> Vector3

> GetAngle() -> float

> Rotate(Vector3) -> Vector3

Static methods:

> EulerToQuaternion(Vector3) -> Quaternion

Properties (readonly)

> x -> float

> y -> float

> z -> float

> w -> float

# Components

Component creation is simple but it can get pretty verbose, so better see some components for yourself.

Check commented component template [here](luaexamples/TemplateComponent(verbose).lua)

Also Check empty template [here](luaexamples/TemplateComponent.lua)

Now, you should always create Components in that way, in separete files inside a constructor functions. It's recommended you do the same for NativeComponents:

```lua
-- Wrapper for native component renderer, so it can be used in "json" style and parsed correctly
local NAME="Renderer"

-- table for our functions
local table = { }

function table.GetNew(entity, data) 
    local component = Aegis.NativeComponents.CreateRenderer(entity, data.mesh);

    return component;
end

return table
```

This way you can automatize the creation of components and you can use the same code for all components. The engine will already provide these wrappers.

# Entities and Scenes

Entities can be created calling Aegis.CreateEntity(currentScene), then you can create a component, call Getcomponent... That's pretty boring... If have some appreciation for yourself, you'll probably prefer to write entities this way:

```lua
-- Example of scene, it's just a table with list of entities

local NAME = "TestScene";
local scene = {
  {
    type = "Entity",
    name = "TestEntity",
    position = { x = 0, y = 0, z = 0},
    components = {
      {
        type = "TestComponent",
        overrideData = true,
        data = {
          test = 10,
          time = 0
        }
      },
      {
        type = "Renderer",
        data = {
          mesh = "fish.mesh"
        }
      }
    }
  }
};
return scene;

```

This is a scene, a collection of entities (and other type of objects, maybe).
You can create a lua table just like that. Name is the internal name of the Entity, you can use it to search entities through the scene method(WIP). Then you define and array of Components, a component must specify its type, it's not neccesary to define a custom data, in that case the script data will be used instead. This format can be parsed using Lua Utils provided with the engine.

Notice the optional parameter overrideData = false, if this is set to true or it's not defined, component data will be set to this data, if it's false, component will receive this data in its constructor but it won't be automaticaly assigned. As data is inmutable, internally the parser iterate data keys and assign them to the component.data. If data contains a key that component.data doesn't contain it will be ignored and will through a warning through console.

Notice also how position is declared outside component array, this is a shorthand so you don't have to wrap trasform component. You can write there transform, rotation (works as Vector3) and scale. You can even define position = { y = 5 } and that will be converted to Vector3(0,5,0). You don't have to define all fields in Vector3 here (but you have to do when using Aegis.Maths.Vector3).

## Scene dependencies

Imagine we want a certain entity component to get accesss to other entity component. For example and enemy entity wants the player position. The parser provide with the engine allows to inject dependencies from the creation. Here is an example:

```lua

local NAME = "TestScene";
local scene = {
	{
		type = "Entity",
		name = "Fish",
		position = { x = 0, y = 0, z = 0},
		components = {
			{
				type = "SimpleRotate",
				
				dependencies=
				{
					{
						entity = "Rust",
						components = {
								"TestComponent", "NonExistingComponent"
						}
					},
					{
						entity = "TestEntity3",
						components = {
								"TestComponent"
						}
					}
				}
			},
			{
				type = "Renderer",
				data = {
					mesh = "fish.mesh"
				}
			}
		}
	},
	{
		type = "Entity",
		name = "Rust",
		components = {
			{
				type = "TestComponent",
				data = {
					test2 = 1,
					--This will be ignored as it doesn exist in TestComponent
					test4 = 3 
				}
			},
			{
				type = "Renderer",
				data = {
					mesh = "Rust.mesh"
				}
			}
		}
	}
};
return scene;

```

Alright, let's go step by step

We have two entities that follows this structure of components

```
Fish
│ SimpleRotate
│ Renderer
Rust
│ TestComponent
│ Renderer
```

Now if you look at the code, the component SimpleRotate of Fish has a dependency on Rust, an entity that exist. It has two dependencies, one for TestComponent and one for NonExistingComponent.

During dependency solving, TestComponent will be injected into component.external.Rust.TestComponent, while NonExistingComponent, as it isn't a Rust component, won't be injected. A message will be printed to console warning that.
Rust entity will also be injected in component.external.Rust.entity, just as a
shorthand, you can it too from the injected component.

Now the next dependency is from TestEntity3, but there isn't any TestEntity3 defined, so it will be ignored and printed as warning to console. Console log will be this.

```
DEBUG: Aegis loaded

Creating Scene Objects
-------------------
Error: test4 is not a field of TestComponent.data, test4 wasn't copied (Rust)

Resolving dependencies:
-------------------
Solving dependencies for Fish:

--Solving dependencies from Rust:
----Inyecting TestComponent from Rust into SimpleRotate
----Component NonExistingComponent wasn't found in Rust, dependency could not be resolved
--Solving dependencies from TestEntity3:
----Entity TestEntity3 wasn't found, dependency could not be resolved

Could not resolve dependencies for Fish
-------------------
```

Notice how test4 wasn't copied as it isn't a field of TestComponent.data.


Despite the last message some dependencies were resolved and can be used in SimpleRotate.

Dependencies are solved after component data is resolved, so if SimpleRotate Init code is this:

```lua
        local entName = component.entity:GetName();
        print("Init: " .. component.name .. " from " .. entName);
        local rust = component.external.Rust;
        print("EntityDependency: " .. rust.entity:GetName());
        print("ComponentDependenty: " .. rust.TestComponent.name);
        rust.TestComponent.data.test = 5;
        print("ComponentTest2: " .. rust.TestComponent.data.test2);

        -- this will throw a warning through console, you can modify component.data
        -- but you can't override it
        component.data = {}
```

TestComponent.data.test will be 5 after init, TestComponent.data.test2 will be 1. This is the output

```
Init: SimpleRotate from Fish
EntityDependency: Rust
ComponentDependenty: TestComponent
ComponentTest2: 1
```

# Lua Utils

The engine provides some Utilities to make life easier, one of them is the Utils package that contains ParseScene method described previously

# Limitations

Some components have to be implemented in lua, some of them are incomplete but you can do pretty much what you want with your own components. SceneManagement and SceneHierarchy will be implemenented in the future.
