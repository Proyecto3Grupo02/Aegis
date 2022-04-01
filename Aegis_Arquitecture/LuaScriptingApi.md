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
- [Components](#components)
- [Entities and Scenes](#entities-and-scenes)
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

> CreateEntity(Scene scene) -> void

> CreateComponent(string componentName) -> AegisComponent

## Aegis.NativeComponents methods

These are methods for creating C++ prebuilt componentes, it will be explained better in [Components](#Components) section. (more components to be added soon)

> CreateRenderer(Entity* entity, string meshName) -> Renderer

## Aegis.Maths

Aegis.Maths contains types for math operations such as Vector3, Vector4, Quaternion... But it doesn't contain any functions.

# Types and Functions

Some c++ clases are exported to lua as userdata that can be used as tables.
When calling a function it's recommended to use ":" instead of "."

> entity.AddComponent(currentScene)

The example above is not correct, the two correct ways for calling a member function are

> entity.AddComponent(entity, currentScene)

> entity:AddComponent(currentScene)

Note how using ":" is less verbose than using ".". But be aware that this only apply to userdata/class functions. Namespaces functions are called using ".". For example: Aegis.CreateEntity() is correct, Aegis:CreateEntity() is not correct.

Calling a function that doesn't exist on a namespace or a userdata/class will result in an irrecuperable error.

Now here you can consult classes and class methods (these ones are called with ":", the ones in the previous section with "."). I've said this twice and you will still make mistakes, you'll remember this.

One last thing, classes/userdata exposes functions and properties. Functions always start uppercase while properties always start lowercase. Properties are accesed as public c++ properties using dot notation (entity.transform.position)

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

> transform -> Transform

### ComponentBase

As it name says, it's the parent class of AegisComponent, it doesn't have a constructor but it's registered as a "type" in lua and provides some properties to AegisComponent thourgh heritance

Properties:

> name -> string

> entity -> Entity

Notice that name is the "type" of the script and it's the id used to find when calling GetComponent on an entity.

### AegisComponent

This is the most importante piece, here is where we make out entities actually do things and react. It has some methods and properties, in the next section we'll talk more about this class.

Methods:

> SetCallbacks(LuaRef ref) -> void

Properties:

> data -> LuaRef

> type -> LuaRef

Note thas this class doesn't have a constructor, it's instead created calling Aegis.CreateComponent(name). This is done this way so the component is created in C++ and doesn't have lua lifetime. Creating the component in lua can lead to problems.

## Aegis.NativeComponents

### Transform

This component is automatically added to all entities when they are created in C++, but the class is exposed to lua so it can be actually useful. This class is still in progress.

Properties:

> position -> Vector3

### Renderer

Class that holds mesh and materials for Ogre to render. This class is still in progress

Properties:

> visible -> bool

## Aegis.Maths

### Vector3

Basic Vector3 to use mainly with transform. This is one of the few classes to have a constructor.

Constructor:

Vector3(float x, float y, float z) -> Vector3

Properties: (readonly)

> x -> float

> y -> float
 
> z -> float

### Vector4

Constructor:

Vector4(float x, float y, float z, float w) -> Vector4

Properties: (readonly)

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
You can create a lua table just like that. Name is the internal name of the Entity, you can use it to search entities through the scene method(WIP). Then you define and array of Components, a component must specify its type, it's not neccesary to define a custom data, in that case the script data will be used instead. This format can be parsed using Lua Utils (defined in next section).

Notice the optional parameter overrideData = false, if this is set to true or it's not defined, component data will be set to this data, if it's false, component will receive this data in its constructor but it won't be automaticaly assigned.

# Lua Utils

The engine provides some Utilities to make life easier, one of them is the Utils package that contains ParseEntity and ParseScene methods described previously

# Limitations

Some components have to be implemented in lua, some of them are incomplete but you can do pretty much what you want with your own components. SceneManagement and SceneHierarchy will be implemenented in the future.