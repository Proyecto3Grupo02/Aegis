# Aegis

Documento de diseño de motor

---------------------------------

**Grupo 2 - Kirin Studios**

|Jonathan Sebastián Andrade Gordillo|Rubén González Ortiz | Álvaro Cuerva Hernández |Sergio Alberto Luis Cano |Javier Meitín Moreno| Nicolás Rosa Caballero | Amparo Rubio Bellón |Rodrigo Tobar Guillén|Jorge Zurdo Izquierdo|
|--|--|--|--|--|--|--|--|--|

## **Páginas de interés**
* [**Pivotal Tracker**](https://www.pivotaltracker.com/n/projects/2555675)
* [**Repositorio**](https://github.com/Proyecto3Grupo02)
* [**Scripting API**](Aegis_Arquitecture/LuaScriptingApi.md)
* [**Documentación del juego**](https://github.com/Proyecto3Grupo02/ThrowTheLine/blob/main/README.md)

## Intro
Aegis es un motor de videojuegos desarrollado por Kirin Studios en C++ con el fin de proporcionar un soporte para programar juegos usando LUA como lenguaje de scripting. ([**Consultar la documentación de la API**](Aegis_Arquitecture/LuaScriptingApi.md))

## Arquitectura
El motor esta estructurado mediante la política de Entity-Component:
* **Entidades:** Equivalentes a los gameobject en Unity. Se les puede asociar Componentes para dotarles funciones y/o comportamientos especificos.
* **Componentes:** Hay dos tipos. El programador que use Aegis puede o bien utilizar componentes proporcionados por el propio motor (Ejemplos: Tranform, Renderer, Rigidbody), o bien programar en LUA sus propios componentes que doten a la entidad de distintos comportamientos.

Aegis cuenta con las siguientes Fatures:
* **Renderizado en 3D con shaders** (OGRE)
* **Manejo de eventos por teclado y ratón** (SDL)
* **Uso de física** (Bullet)
* **Gestión de colisiones** (Bullet)
* **Gestión de sonido** (FMOD)

La solución del motor viene estructurada en proyectos, cada uno encargado de realizar una función concreta. Los proyectos más básicos se encargan de la comunicación entre Aegis y las librerías que hemos usado (Ogre, Bullet, etc). Estos  proyectos son a su vez la base de proyectos mas generales encargados de gestionar las escenas, entidades, y componentes.
### Jerarquía de los Proyectos:
![Copia de Diagrama Proyectos](https://user-images.githubusercontent.com/62613312/166960800-33933d06-c510-432e-8fba-342dd802cd41.jpg)

### Organización de los Proyectos:
![Diagrama Proyectos drawio](https://user-images.githubusercontent.com/62613312/166960843-3bf62eb9-0eb1-4a19-92b1-00195deb26d9.png)

## Organización del directorio:
Aegis Engine  (carpeta principal)
* **Dependencias:** Contiene las librerías utilizadas; Bullet, FMOD, LUA, OGRE.
* **Exes:** Contiene los archivos autogenerados al compilar cada poryecto, junto con el juego programado en LUA que se desea ejecutar mediante Aegis (provisional?).
* **Proyects:** Contiene los archivos .vcxproj y filters de cada proyecto.
* **Src:** Contiene los archivos .h y .cpp del motor.
* **Temp:**(archivos generados)
* **AegisEngine.sln**
* **build_up.bat:** Archivo .bat que compila las librerías en Dependencias.

## Repositorio GitHub
El repositorio de GitHub incluiye:
* Readme.md con el GDD del juego y el documento de la arquitectura.
* Carpeta de la solución con el proyecto del motor y el proyecto del juego, sin ningún tipo de archivo innecesario (.dll, archivos temporales…)

## Pipeline
* Se crea la historia de usuario.
* Durante un meeting se le asigna a uno o más desarrolladores en función de los puntos.
* Las personas encargadas de esta historia crean una rama en Github con una pull request en la que se encargaran de esa historia.
* Una vez finalizada, en un meeting se comprobará su validez.
* Se une esta rama a la principal y se finaliza la historia.

## Licencias

Aegis Engine ha sido diseñado y creado por **Kirin Studios**

**Ogre3D** (Copyright (c) 2000-2013 [Torus Knot Software Ltd](https://www.ogre3d.org/))

**Bullet Continuous Collision Detection and Physics Library** (Copyright (c) 2003-2006 [Erwin Coumans](https://pybullet.org/Bullet/phpBB3/))

**FMOD Studio** (Copyright (c)[Firelight Technologies Pty Ltd](https://www.fmod.com/))

**SDL 2.0** (Copyright (c) [SDL Community](https://github.com/libsdl-org/SDL))

**CEGUI** (Copyright (c) [The CEGUI Team](http://cegui.org.uk/wiki/))

**Lua** (Copyright (c) [The Lua Team](https://www.lua.org/))

**LuaBridge** (Copyright (c) [Vinnie Falco](https://github.com/vinniefalco/LuaBridge))
