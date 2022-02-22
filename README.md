# Aegis

Documento de diseño de motor

---------------------------------

**Grupo 2 - Kirin Studios**

*Jonathan Sebastián Andrade Gordillo | Álvaro Cuerva Hernández | Rubén González Ortiz | Sergio Alberto Luis Cano | Javier Meitín Moreno | Nicolás Rosa Caballero | Amparo Rubio Bellón | Rodrigo Tobar Guillén | Jorge Zurdo Izquierdo*

## **Páginas de interés**
### [Página web]()
### [Pivotal Tracker](https://www.pivotaltracker.com/n/projects/2551633)
### [Repositorio](https://github.com/Proyecto3Grupo02)

## Intro
Aegis es un motor de videojuegos hecho por G.Q.P.L.C.E (Grupo Que Presenta La Célula Eucariota) GQPLPCS (Gente que pesca los PeCeS) diseñado para crear juegos en C++ y LUA como lenguaje de scripting en el uso de blueprints.

### Features
* Renderizado en 3D con shaders (OGRE)
* Animaciones, partículas (OGRE)
* Manejo de eventos por teclado y gamepads(SDL)
* Uso de física (PhysX)
* Gestión de sonido (FMOD)

## Arquitectura
Gestión del proyecto mediante el uso de GameManagers:
* PhysicsManager (maneja colisiones)
* RenderManager (superposición de entidades??)
* SoundManager (maneja y reproduce sfx y música)
* EntityManager (maneja a todas las entidades)
* InputManager (maneja inputs)
* SceneManager
* Bucle principal: llamará a todos los managers para que manejen lo necesario 

Los Game Objects vendrían estructurados mediante la política de EC
* Entidades: equivalente a un gameobject en Unity, contiene componentes y funciona mediante estos
* Componentes (Transform, RenderMesh, Rigidbody, Colliders, Animators, EventHandlers… )

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

## Estructura clases (UML)

## Licencias
Ogre3D (Copyright (c) 2000-2013 Torus Knot Software Ltd)
SDL 2.0 (Copyright (c) SDL Community)??
Bullet
FMOD
imgui??
