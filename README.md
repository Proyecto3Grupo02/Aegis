# Aegis

Documento de diseño de motor

---------------------------------

**Grupo 2 - Kirin Studios**

*Jonathan Sebastián Andrade Gordillo | Álvaro Cuerva Hernández | Rubén González Ortiz | Sergio Alberto Luis Cano | Javier Meitín Moreno | Nicolás Rosa Caballero | Amparo Rubio Bellón | Rodrigo Tobar Guillén | Jorge Zurdo Izquierdo*

## **Páginas de interés**
* [**Página web**]()
* [**Pivotal Tracker**](https://www.pivotaltracker.com/n/projects/2555675)
* [**Repositorio**](https://github.com/Proyecto3Grupo02)
* [**Scripting API**](Aegis_Arquitecture/LuaScriptingApi.md)

## Intro
Aegis es un motor de videojuegos hecho por G.Q.P.L.C.E (Grupo Que Presenta La Célula Eucariota) GQPLPCS (Gente que pesca los PeCeS) diseñado para crear juegos en C++ y LUA como lenguaje de scripting en el uso de blueprints.

### Features
* Renderizado en 3D con shaders (OGRE)
* Animaciones, partículas (OGRE)
* Manejo de eventos por teclado y gamepads(SDL)
* Uso de física (PhysX)
* Gestión de sonido (FMOD)

## Arquitectura
Los Game Objects vendrían estructurados mediante la política de EC
* Entidades: equivalente a un gameobject en Unity, contiene componentes y funciona mediante estos
* Componentes (Transform, RenderMesh, Rigidbody, Colliders, Animators, EventHandlers… )
![Untitled Diagram drawio](https://user-images.githubusercontent.com/62613312/157743110-91a47321-25e3-442c-a97a-dd12bf4dcf50.png)

## Estructura de la solución y proyecto
Aegis Engine  (carpeta principal)
* Temp(archivos generados)
* Src
** Código
* dependencies (con las librerías separadas con su carpeta )
* builds (.exe y .dll)
* Projects
** .vcxproj y filters
* .sln

## Repositorio GitHub
El repositorio de GitHub incluirá:
* Readme.md con el GDD del juego y el documento de la arquitectura.
* Carpeta de la solución con el proyecto del motor y el proyecto del juego, sin ningún tipo de archivo innecesario (.dll, archivos temporales…)

## Pipeline
* Se crea la historia de usuario.
* Durante un meeting se le asigna a uno o más desarrolladores en función de los puntos.
* Las personas encargadas de esta historia crean una rama en Github con una pull request en la que se encargaran de esa historia.
* Una vez finalizada, en un meeting se comprobará su validez.
* Se une esta rama a la principal y se finaliza la historia.

## Estructura clases

### Application

#### Atributos

- Scene* currentScene
- ResourceManager* manager

#### Metodos

> Load_Game(string path)

> Load_Scene()

> Change_Scene()

> Update

### Scene

#### Atributos

- List<Entity*> entities
- List<List<Entity*>::iterator> entitiesToDelete

####  Metodos

> AddEntity(Entity* entity)

> DestroyEntity(Entity* entity)

> FixedUpdate()

> Update()

> LateUpdate()

### Entity

#### Atributos

- Scene* scene
- bool isActive
- List<int> activeComponents
- vecto<Component*> components
- string name

####  Metodos

> Init()

> FixedUpdate()

> Update()

> LateUpdate()

> bool IsActive()

> void SetActive(bool active)

> void SetName(string name)

> string GetName()

Dudas

> Render()

> GetScene()

> SetScene(Scene* scene)

> ReceiveEvent()

> HasComponent(int cmpId)

> OnCollision(Entity* other)

> OnTrigger(Entity* other)

### Input System (static)

#### Atributos

```c++
struct key
{
    bool pressedThisFrame, down, releasedThisFrame;
}
```

- vector<key> keys[256]

####  Metodos

Public
> bool IsKeyDown

> IsPressedThisFrame

> IsReleasedThisFrame


Private

> void OnKeyDown(SDLK key)

> void OnKeyUp()

> void UpdateState()

> int SDLK_ToInt();


## Licencias
Ogre3D (Copyright (c) 2000-2013 Torus Knot Software Ltd)
SDL 2.0 (Copyright (c) SDL Community)??
Bullet
FMOD
imgui???
