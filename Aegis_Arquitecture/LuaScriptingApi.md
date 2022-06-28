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
    - [SceneManager](#scenemanager)
    - [SoundSystem](#soundsystem)
      - [Channel](#channel)
    - [UISystem](#uisystem)
    - [Entity](#entity)
    - [ComponentBase](#componentbase)
    - [AegisComponent](#aegiscomponent)
  - [Aegis.NativeComponents](#aegisnativecomponents)
    - [Transform](#transform)
    - [Renderer](#renderer)
    - [Light](#light)
    - [SoundEmitter](#soundemitter)
    - [SoundListener](#soundlistener)
    - [Animation](#animation)
    - [Rigidbody](#rigidbody)
  - [Aegis.Maths](#aegismaths-1)
    - [Vector3](#vector3)
    - [Vector4](#vector4)
    - [Quaternion](#quaternion)
- [Components](#components)
- [Entities and Scenes](#entities-and-scenes)
  - [Scene dependencies](#scene-dependencies)
- [Limitations](#limitations)

# Game Init

AegisEngine calls init.lua script before the game loop. This script should be located inside your game scripts folder.

# Tables and Namespaces

Aegis provides one table that acts as namespace: Aegis.
This table contains the namespaces NativeComponents and Maths.
There are also some global variables: Input, SceneManager and SoundManager. We'll talk about these later.

Now I'll list the functions in each namespace.


## Aegis methods

> CreateEntity(Scene scene, Vector3 pos) -> void

> CreateComponent(string componentName, Entity entity) -> AegisComponent

## Aegis.NativeComponents methods

These are methods for creating C++ prebuilt componentes, it will be explained better in [Components](#Components) section. (more components to be added soon).

This methods are used internally when creating scenes but they are public for the user in case you want to add these components at runtime.

> CreateRenderer(Entity* entity, string meshName) -> Renderer

> CreateLight(Entity* entity, luaTable args) -> Light

> CreateAnimation(Entity* entity, luaTable args) -> Animation

> CreateRigidBody(Entity* entity, luaTable args) -> RigidBody

> CreateSoundEmitter(Entity* entity, luaTable args) -> SoundEmitter

> CreateSoundListener(Entity* entity, luaTable args) -> SoundListener

## Aegis.Maths

Aegis.Maths contains types for math operations such as Vector3, Vector4, Quaternion... But it doesn't contain any functions at namespace level.

# Types and Functions

## Functions

Some c++ clases are exported to lua that can be used as tables.
When calling an object function it's recommended to use ":" instead of "."

> entity.AddComponent(component)

The example above is not correct, the two correct ways for calling a member function are

> entity.AddComponent(entity, component)

> entity:AddComponent(component)

Note how using ":" is less verbose than using ".". But be aware that this only apply to class functions. Namespaces functions are called using ".". For example: Aegis.CreateEntity() is correct, Aegis:CreateEntity() is not correct.

Calling a function that doesn't exist on a namespace or a class will result in an irrecuperable error. 

Now here you can consult classes and class methods (these ones are called with ":", the ones in the previous section with "."). I've said this twice and you will still make mistakes, you'll remember this.

## Properties

Classes exposes functions and properties. Functions always start uppercase while properties always start lowercase. Properties are accessed as public c++ properties using dot notation (entity.transform.position)

Some of the properties are inmutable, this means you can change instance variable but not override the instance.

Example (mutable data):
transform.position = Vector3(0,0,0) is correct
transform.position.x = 5 is correct (but this won't work, explained later)

Example (inmutable data):
transform = otherTransform; is not correct, you can't override transform
transform.position is correct, you can change the instance property

## Operators

Some classes support operator through metamethods (__add, __sub...).
But these only work for the right part, example:

Vector3 * float -> is correct
float * Vector3 -> not correct, will through error

## Aegis

### Scene

This is the class that contains all the entities and the methods for managing them.

Methods:

> AddEntity(Entity* entity) -> void

> InstantiatePrefab(luaTable args) -> Entity

InstantiatePrefab will be explained in [entities and scenes section](#entities-and-scenes)

### InputSystem

This is a singleton class that is also a global variable in lua. It allows you to read from keyboard (gamepad not for now)

Methods:

> KeyWasPressed(string key) -> bool

> IsKeyDown(string key) -> bool

> KeyWasReleased(string key) -> bool

> AnyKeyWasPressed() -> bool

> AnyKeyIsDown() -> bool

> AnyKeyWasReleased() -> bool

> GetMouseMotion() -> Vector2

> IsMouseButtonDown(int button) -> bool

  - 0 -> left
  - 1 -> right
  - 2 -> middle 

> MouseButtonWasPressed(int button) -> bool

> MouseButtonWasReleased(int button) -> bool

> BlockMouse(bool block) -> void

### SceneManager

This is a singleton class that is also a global variable in lua. It allows you to load scenes. In lua is called SceneManageret

Methods:

> LoadScene(luaTable args) -> void

> GetCurrentScene() -> Scene

### SoundSystem

This is a singleton class that is also a global variable in lua. It allows you to play sounds. In lua is called SoundManager

Methods:

> GetChannelVolume(string channel) -> float

> SetChannelVolume(float volume, string channel) -> void

> PlayOneShot(string soundName, string channel) -> Channel

Properties:

> generalVolume -> float (mutable, default 1)

#### Channel

This is the object that is returned by SoundManager:PlayOneShot.

Methods:

> SetVolume(float volume) -> void

> SetPaused(bool paused) -> void

> Stop() -> void

> SetLoopCount(int loopCount) -> void

### UISystem

This is a singleton class that is also a global variable in lua. It allows you to create UI elements. In lua is called UISystem

Methods:

> CreateUIElement(luaTable args) -> UIElement

Currently there is a single method to build a UI element. So now I'll explain how to use it.

When creating a Scene, UIElements are described this way

```lua

{
  type = "UI",
  data = {
    type = "Button"/"Text"/"Image",
    name = "uiName",
    order = 0, -- optional, default 0, higher values are drawn on top of lower values
    x = 0, -- optional, default 0, value is between 0 and 1
    y = 0, -- optional, default 0, value is between 0 and 1
    visible = true, -- optional, default true
    uiData = {} --table
    updateFunc = function(uiData, self, deltaTime) end -- optional
    -- Only For text
    text = "text", -- optional, default ""
    charHeight = 0, -- optional, default 0, value is between 0 and 1
    -- Only for Button and Image
    width = 0, -- optional, default 0, value is between 0 and 1
    height = 0, -- optional, default 0, value is between 0 and 1
    material = "materialName", -- optional, default ""
    -- Only for Button
    callback = function(uiData, self) end --optional, default nil, called when clicked
  }
}

```

When two or more buttons share the same space, only the top one will receive the callback when clicked unless it is not visible.

### Entity

Base class for the game, it holds components at updates them by calling their methods. Currently there is no way to parent/nest entities due to Ogre SceneNode limitations, but it will be added.

Methods:

> AddComponent(AegisComponent* component) -> void

> GetComponent(string componentName) -> AegisComponent*<sup>1</sup>

> IsActive() -> bool

> SetActive(bool active) -> void

> GetName() -> string

> SetName(string name) -> void

> GetScene() -> Scene

> SetParent(Entity* parent) -> void

> Destroy() -> void
 
Properties:

> transform -> Transform (inmutable)

<sup>1</sup> GetComponent returns the actual component. For example, if you make entity:GetComponent("Renderer") it won't return a general AegisComponent parent, it will return Renderer as expected.

### ComponentBase

As it name says, it's the parent class of AegisComponent, it doesn't have a constructor but it's registered as a "type" in lua and provides some properties to AegisComponent through inheritance

Properties:

> name -> string (inmutable)

> entity -> Entity (inmutable)

Notice that name is the "type" of the script and it's the id used to find when calling GetComponent on an entity. This methods are available in all components.

### AegisComponent

This is the most importante piece, here is where we make out entities actually do things and react. It has some methods and properties, in the next section we'll talk more about this class.

Properties:

> data -> LuaRef (inmutable)

> funcs -> LuaRef (inmutable)

Note thas this class doesn't have a constructor, it's instead created calling Aegis.CreateComponent(name). This is done this way for design and technical reasons.

## Aegis.NativeComponents

### Transform

This component is automatically added to all entities when they are created in C++, but the class is exposed to lua so it can be actually useful. This class is still in progress.

Methods:

> SetParent(Entity* parent) -> void

> Yaw(float angle) -> void

> Pitch(float angle) -> void

> Roll(float angle) -> void

Properties:

> position -> Vector3 (mutable)

> scale -> Vector3 (mutable)

> rotation -> Quaternion (mutable)

> localEulerAngles -> Vector3 (mutable)

> forward -> Vector3 (inmutable)

> right -> Vector3 (inmutable)

> up -> Vector3 (inmutable)

 	Be aware that localEulerAngles return a value between -180 and 180 instead of 0 and 360.

### Renderer

Class that holds mesh and materials for Ogre to render. This class is still in progress

Properties:

> visible -> bool (mutable)

### Light

Methods:

> SetDirection(Vector3 direction) -> void

Properties:

> diffuse -> Vector3 (mutable)

> specular -> Vector3 (mutable)

### SoundEmitter

Methods:

> PlayClip() -> void

> StopClip() -> void

> PauseClip() -> void

> ResumeClip() -> void

Properties:

> volume -> float (mutable)

> pitch -> float (mutable)

> loop -> int (mutable)

> sound -> string (mutable)

> channel -> string (mutable)

When creating a sound emitter component, all parameters except "sound" are optional. This is an example of SoundEmitter. This will make more sense in entities and scene section

```lua
{
  type = "SoundEmitter",
  data = 
  {
    sound = "sound.wav",
    volume = 1, --optional, default 1
    pitch = 1, --optional, default 1
    loop = 0, --optional, default 0, -1 for infinite
    channel = "default" --optional
    playOnInit = true --optional, default false
    minMax3DDistance
    {
      min = 0,
      max = 100
    } -- optional, if not defined sound is 2D
  }
}
```

### SoundListener

It doesn't have any special methods or properties, but inherits ComponentBase ones (name, enabled, entity...)

### Animation

This component is used to keyframe animate entities.
It doesn't have any special methods or properties, but inherits ComponentBase ones (name, enabled, entity...).

### Rigidbody

Methods:

> SetPosition(Vector3 position) -> void

> SetRotationEuler(Vector3 euler) -> void

> AddForce(Vector3 force) -> void

> GetForce() -> Vector3

> ClearForce() -> void

> AccelerateTo(Vector3 targetVelocity, float maxAcceleration) -> void

> AddTorque(Vector3 torque) -> void

> ChangeGravity(float gravity) -> void

> RayCastWorld(Vector3 origin, Vector3 direction, float distance) -> int*<sup>1</sup>

> SetAngular(Vector3 angular) -> void

> FreezeRot(bool x, bool y, bool z) -> void

> EnableCol(bool enable) -> void

Properties

> trigger -> bool (mutable)

> position -> Vector3 (mutable)

> useGravity -> bool (mutable)

*<sup>1</sup> Return value of raycast is an int that represents the result

  - 0 -> no collision
  - 1 -> kinetic collision
  - 2 -> trigger collision
  - 3 -> dynamic collision

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


# Entities and Scenes

Entities can be created calling Aegis.CreateEntity(SceneManager::GetCurrentScene()), then you can create a component, call GetComponent... That's pretty boring... If have some appreciation for yourself, you'll probably prefer to write entities this way:

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
  },
  {
    type = "UI",
		data = 
			{
				type = "Button",
				name = "HowToPlay",
				material = "htp_material",
				order = 1,
				x = 0.45,
				y = 0.7,
				width = 0.1,
				height = 0.1,
				visible = true,
				uiData = { count = 1 },
				callback = function(uiData)
					print("Count: " .. uiData.count);
          uiData.count = uiData.count + 1;	
					SoundManager:PlayOneShot("clin");
				end 
			},
	}
-- UI 
};
return scene;

```

This is a scene, a collection of entities and UI.
You can create a lua table just like that. Name is the internal name of the Entity. Then you define and array of Components, a component must specify its type, it's not neccesary to define a custom data, in that case the script data will be used instead. A scene can be loaded with SceneManager::LoadScene(scene).

Notice the optional parameter overrideData = false, if this is set to true or it's not defined, component data will be set to this data, if it's false, component will receive this data in its constructor but it won't be automaticaly assigned. As data is inmutable, internally the parser iterate data keys and assign them to the component.data. If data contains a key that component.data doesn't, it will be ignored and will throw a warning through console (only if developing in debug mode).

Notice also how position is declared outside component array, this is a shorthand so you don't have to wrap trasform component. You can write there transform, rotation (works as Vector3) and scale. You can even define position = { y = 5 } and that will be converted to Vector3(0,5,0). You don't have to define all fields in Vector3 here (but you have to do when using Aegis.Maths.Vector3).

UIData is defined similar to entities. You just declare that type is UI and then data table with all the parameters needed that were explained in UI Section.

## Scene dependencies

Imagine we want a certain entity component to get accesss to other entity component. For example and enemy entity wants the player position. The parser provide with the engine allows to inject dependencies from the creation. Here is an example:

```lua

-- Example of scene, it's just a table with list of entities

local NAME = "TestScene";
local scene = {
	{
		type = "Entity",
		name = "Fish",
		components = {
			{
				type = "Renderer",
				data = {
					mesh = "fish.mesh",
					material= "blue"
				}
			},
		},
	},
	{
		type = "Entity",
		name = "LittleFish",
		components = {
			{
				type = "Renderer",
				data = {
					mesh = "fish.mesh",
					material= "red"
				}
			},
			{
				type = "ParentTest",
				data = {
					parent="@Fish",
					parentRender = "@Fish.Renderer",
				}
			},
		},
	},
  {
    type = "UI",
		data = 
			{
				type = "Button",
				name = "HowToPlay",
				material = "htp_material",
				order = 1,
				x = 0.45,
				y = 0.7,
				width = 0.1,
				height = 0.1,
				visible = true,
				uiData = { count = 1, renderer = "@Fish.Renderer" },
				callback = function(uiData)
					print("Count: " .. uiData.count);
          print(renderer.entity:GetName());
          uiData.count = uiData.count + 1;	
					SoundManager:PlayOneShot("clin");
				end 
			},
	}
};
return scene;

```

We have two entities that follows this structure of components and an UIObject

```
Fish
│ Renderer
LittleFish
│ Renderer
│ ParentTest
HowToPlay (UI: Button)
```

Now, if we execute the code, we wil get this output:

```
DEBUG: Aegis loaded


DEBUG: SOUND SYSTEM: System started
Creating Scene Objects
-------------------

Resolving dependencies:
-------------------
Solving dependencies for LittleFish:

Inyecting Fish.Renderer into ParentTest.parentRender
Inyecting Fish into ParentTest.parent

Dependency solved correctly
-------------------
Solving dependencies for HowToPlay:

Inyecting Fish.Renderer into uiData.renderer

Dependency solved correctly
-------------------
ParentMat is blue
```

If just one dependency is missing, the message will change to indicate the error but the scene will still be loaded.

Dependencies are solved after component data is resolved, so you can access it in the Init method without any danger. Although it's recommended to check if it's nil.

```lua
local NAME = "ParentTest";
local table = {};
function table.GetNew(entity, params)
	local component = Aegis.CreateComponent(NAME, entity);
	local data = component.data;
	local funcs = component.funcs;
	local entity = component.entity;

	data.parent = "undefined";
	data.parentRender = "null";

	function Init()
		print("ParentMat is " .. data.parentRender.data.material);
	end;

```
Be aware that you shouldn't initialize data to nil outside init, because then the parser will think it's a missing entry to the table and won't be able to inject data and neither solve dependencies for that field.


# Limitations

Some components should have more functionality, some other doesn't exist and should... UI is fixed so you can't really create your own UIElements easily.
