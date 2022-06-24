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
## Jerarquía de los Proyectos:
![Copia de Diagrama Proyectos](https://user-images.githubusercontent.com/62613312/166960800-33933d06-c510-432e-8fba-342dd802cd41.jpg)

## Organización y funcionalidad de los Proyectos:
### AegisAudio:
------
### AegisCommon:
------
### AegisEngine:
------
### AegisGraphics:
AegisGraphics sirve de enlace entre el motor y **Ogre**.

#### AegisCamera:
AeggisCamera se encarga de crear una Cámara en ogre y agregarla a un nodo. Contiene métodos set y get para acceder a la matriz vista, matriz de proyección, el viewport, y otros atributos.

También cuenta con un método **free()** que separa a todos los nodos adheridos al de la cámara, para luego destruir la misma.

#### AegisLight:
De manera similar a la cámara, se crea una luz de Ogre y se asocia a un nodo. Hay funciones para modificar o consultar los atributos de dicha luz.

#### WindowManager:
WindowManager se encarga de gestionar la ventana donde se renderiza el juego, principalmente el tamaño. A parte de crear la ventana de acuerdo a los argumentos recibidos por la constructora, la clase contiene un método **handleEvent(SDL_Event& evt)** que redimensiona el **render** en caso de recibir el evento de **SDL_WINDOWEVENT_RESIZED**.

También cuenta con métodos **getWidth/getHeight** que devuelven las dimensiones actuales de la ventana.

#### OgreWrapper:
OgreWrapper hereda de **Singleton**, y como su nombre indica, se encarga de englobar **Ogre**.

La constructora llama al método **init(std::string resourcesPath)**, el cual se encarga de cargar los archivos **resourcesCFG** y **pluginsCFG**. Una vez cargados los recursos crea un **WindowManager** y un **AegisCamera** que asocia al viewport del render.

------
### AegisPhysics:
AegisPhysics utiliza la librería **Bullet** para gestionar las físicas.

#### DebugDrawer.
OgreDebugDrawer hereda de **btIDebugDraw** y **Ogre::FrameListener** y se encarga de dibujar las aristas del cubo definido por el collider de una entidad física.

#### MotionState:
MotionState se encarga de la sincronizar la posición/rotación del **Transform** con la del **Rigidbody** y viceversa, mediante los métodos **getWorldTransform** y **setWorldTransform**.

#### OgreBulletUtils:
OgreBulletUtils contiene funciones para realizar la conversión de objetos de Ogre a objetos de Bullet, y viceversa.

#### PhysicsMain:
PhysicsMain hereda de **Singleton**, y se encarga de gestionar las físicas, principalmente las colisiones entre **Rigidbodies** mediante el **map<std::pair<RigidBody*, RigidBody*>, bool> contact**.

En la constructora inicializa las cosas de Bullet, y en caso de que esté en modo DEBUG, también crea un **OgreDebugDrawer**.

EXPLICAR CollisionEnterCallbacks, update, collisionEntersCallback!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#### Rigidbody:
Rigidbody crea una entidad física en Bullet. Contiene métodos setter y get para modificar sus atributos.

------
### AegisScripting:
AegisScripting es el eslavón del motor que une C++ con Lua.

#### LuaBasic:
Contiene unicamente los include de Lua. Tiene como función reducir el número de includes en otros scripts.

#### LuaManager:
LuaManager es el eslavón del motor que une C++ con Lua. Hereda de **Singleton** y se encarga tanto de la creación de un nuevo **LuaState**, como de parsear parámetros **LuaRef** a C++. También cuenta con una función **execute(string filename)** para  cargar y ejecutar el archivo.lua "filename". Devuelve true si se carga y ejecuta correctamente.

------
### AegisUI:
#### UISystem:
UISystem es un **Singleton** encardo de la gestión de **UIObjects**.

En la constructora crea un **OverlaySystem** y accede al **OverlayManager** con el fin de inicializar un nuevo **Overlay** para la gestión de imágenes. Contiene un **vector<UIObject*>ui_objects** donde se guardaran los objetos de tipo UI creados desde lua mediante la función **createUIElem(luabridge::LuaRef luaref)**. Dicha función leerá el string identificador que recibe como argumento LuaRef para crear el tipo de objeto oportuno.

El sistema también contiene una función **update** que recorre el vector ui_objects para que se actualicen.

#### UIObjects:
Debido a que de esta clase hereda tanto **Image** como **Text**, contamos con 2 constructoras distintas. En ambos casos, la constructora de UIObjects crea un nuevo **OverlayElement** de tipo Panel. Devido a que no se puede crear más de 1 elemento con el mismo nombre, se usa un int estático **num_ui_obj** para identificar al objeto. Dicho int incrmenta cada vez que se llama a la constructora.

Una vez creado el elemento, se le modifica mediante la posición, profundidad (eje z), dimenisones, visibilidad, y material definidas por los argumentos de la constructora. La clase cuenta con varias funciones setter y get para acceder y modificar dichas variables/estados.

También hay una función **onClick** que comprueba si la posición del ratón está dentro de la superficie definida por el UIObject si este es visible. Debido a que las posiciones de los UIObjects pertenecen al intervalo [(0,0), (1,1)] y no se miden en píxeles, se usan los métodos **getWidth/getHeight** del **WindowManager** de **AegisGraphics** para realizar la conversión a píxeles de la ventana. En dicho caso de se cumplan las condiciones, se ejecutará el **function<void()> clickCallback**.

#### Image:
Image hereda de **UIObject** y expande la funcionalidad de dicha clase añadiéndole un material que recibe como argumento en la constructora. Dicha constructora es llamada desde un método estático de la misma clase, **CreateImage(LuaRef args)**, la cual realiza la parsea los argumentos LuaRef al tipo recibido por la constructora. CreateImage es llamado desde **UISystem::createUIElem** cuando se crea un objeto de tipo UI en lua.

#### Button:
Button hereda de **Image** y contiene un método **buttonClickCallback()** que es asignado al **clickCallback** de **UIObject**. En buttonClickCallback se llamará a la función definida en lua.

Al igual que en Image, hay un método estático **CreateButton(LuaRef args)** que es llamado desde **UISystem::createUIElem**.

#### Text:
Text hereda de **UIObject** y crea un texto a partir de los argumentos recibidos en la constructora.

Hay un método estático **CreateText(LuaRef args)** que es llamado desde **UISystem::createUIElem**.

#### ImageResources:
ImageResources **parseDirectory(string dir)** incializa un **map<image,std::string> mapImage** con las imágenes encontradas en el directorio **dir**. Tambíen tiene un método **getImage(string name)** para devolver la imagen con dicho nombre en caso de estar contenida en el mapImage. 

------
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
