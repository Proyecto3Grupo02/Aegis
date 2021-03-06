# Aegis
Documento de diseño del motor

---------------------------------

**Grupo 2 - Kirin Studios**

|Jonathan Sebastián Andrade Gordillo|Rubén González Ortiz | Álvaro Cuerva Hernández |Sergio Alberto Luis Cano |Javier Meitín Moreno| Nicolás Rosa Caballero | Amparo Rubio Bellón |Rodrigo Tobar Guillén|Jorge Zurdo Izquierdo|
|--|--|--|--|--|--|--|--|--|

## **Páginas de interés**
* [**Pivotal Tracker**](https://www.pivotaltracker.com/n/projects/2555675)
* [**Repositorio**](https://github.com/Proyecto3Grupo02)
* [**Scripting API**](Aegis_Arquitecture/LuaScriptingApi.md)
* [**Documentación del juego**](https://github.com/Proyecto3Grupo02/ThrowTheLine/blob/main/README.md)

## Índice:
- [**Introducción**](#introducción)
- [**Organización y funcionalidad de los Proyectos**](#organización-y-funcionalidad-de-los-proyectos)
  - [**AegisAudio**](#aegisaudio)
  - [**AegisCommon**](#aegiscommon)
  - [**AegisEngine**](#aegisengine)
  - [**AegisGraphics**](#aegisgraphics)
  - [**AegisPhysics**](#aegisphysics)
  - [**AegisUI**](#aegisui)
 - [**Organización del directorio**](#organización-del-directorio)
 - [**Licencias**](#licencias)

## Introducción:
Aegis es un motor de videojuegos desarrollado por Kirin Studios en C++ con el fin de proporcionar un soporte para programar juegos usando LUA como lenguaje de scripting. ([**Consultar la documentación de la API**](Aegis_Arquitecture/LuaScriptingApi.md))

El motor esta estructurado mediante la política de Entity-Component:
* **Entidades:** Equivalentes a los GameObject en Unity. Se les puede asociar Componentes para dotarles de funciones y/o comportamientos especificos.
* **Componentes:** Hay dos tipos. El programador que use Aegis puede o bien utilizar componentes proporcionados por el propio motor (Tranform, Renderer, Rigidbody), o bien programar en LUA sus propios componentes que doten a la entidad de distintos comportamientos.

Aegis cuenta con las siguientes características:
* **Renderizado en 3D con shaders** (OGRE)
* **Manejo de eventos por teclado y ratón** (SDL)
* **Uso de física** (Bullet)
* **Gestión de colisiones** (Bullet)
* **Gestión de sonido** (FMOD)
* **Creación de botones, imágenes, y textos** (Ogre Overlay)

La solución del motor viene estructurada en proyectos, cada uno encargado de realizar una función concreta. Los proyectos más básicos se encargan de la comunicación entre Aegis y las librerías que hemos usado (Ogre, Bullet, etc). Estos  proyectos son a su vez la base de proyectos más generales encargados de gestionar las escenas, entidades, y componentes.

### ¿Cómo usar el motor?
Para poder ejecutar el motor, será necesario seguir los siguientes pasos:
1) Configura el **Directorio de Trabajo** de AegisEngine en Debug y Release:
```
AegisEngine > Propiedades > Depuración > Directorio de trabajo > $(SolutionDir)Exes\AegisEngine\$(Platform)\$(Configuration)
```
2) Ejecuta Ctrl+Ñ ==> Ejecuta **./build_up.bat**. Esto compilará las librerías en la carpeta Dependencias, y los proyectos del propio motor, además de generar un ejecutable que se guardará en una carpeta **Build**.

## Jerarquía de los Proyectos:
![Copia de Diagrama Proyectos](https://user-images.githubusercontent.com/62613312/166960800-33933d06-c510-432e-8fba-342dd802cd41.jpg)

## Organización y funcionalidad de los Proyectos:
### AegisAudio:
AegisAudio funciona como enlace entre la librería **FMOD** y Aegis, nuestro motor.

#### SoundResources:
SoundResources cuenta con un método **parseDirectory(string dir)** que incializa un **map<cancion,std::string> mapSound** con las sonidos encontrados en el directorio dir. Tambíen tiene un método **getSound(string name)** para devolver el sonido con dicho nombre en caso de estar contenida en el mapSound.

#### SoundSystem:
SoundSystem hereda de **Singleton** e **ILuaObject**, y se encarga de gestionar los sonidos.
Actúa a modo de puente entre la libreria FMOD y las características del motor.
Cuenta con los structs SoundChannel para la gestión de los canales y su play/pause, EmitterData para contener las posiciones de los emisores y soportar que tengan más de un canal de sonido y ListenerData que contiene la posición y el ángulo del Listener para crear el sonido espacial.
Contiene también un puntero a SoundResources para los sonidos gestionados del directorio.
Contiene métodos para cambiar manualmente las características del sonido (SetVolume para los canales y los grupos)
El sistema llama a la inicialización del sistema de FMOD y carga los sonidos cuando se llama, en los metodos Update y Stop se encarga de compobrar las características del SoundSystem y las actualiza en el System de FMOD.

#### SoundListener:
Se usa para obtener la posición y el ángulo de lo que queremos que sea el listener (Camara, jugador...)
Actualiza su posición en el sistema cuando se actualiza la del objeto.

#### SoundEmitter:
Hereda de **AegisComponent**
Se usa para cargar en el sistema los sonidos y la posición del objeto emisor.
Un objeto emisor puede contener varios canales para reproducir varios sonidos a la vez.
Contiene una implementación que permite reproducir sonidos en loop configurable, en caso de, por ejemplo, querer crear un objeto para la musica del nivel.
La gestión del sonido se realiza sobre el SoundSystem, no se reproduce por sí mismo.

------
### AegisCommon:

#### ILuaObject:
El struct ILuaObject solo cuenta con la definción de un método estático **ConvertToLua(lua_State state)**. Dicho método es sobreescrito por las clases que heredan de ILuaObject.

En el archivo ILuaObject.h también hay una función **exportToLua(T item, string name)**.

#### Component:
Component hereda de **ILuaObject** y contiene métodos virtuales vacíos: **init, fixedUpdate, update, lateUpdate, render, onCollision y onTrigger** que pueden ser sobreescritos por las clases que hereden de él.

En esta clase también se guarda un puntero al **Entity** al que está asociado el componente, junto con un string **componentName** y un bool **isActive**.

#### AegisComponent:
AegisComponent hereda de **Component** e **ILuaObject** y es la clase de la que heredan todos los demás componentes. Sobreescribe los métodos virtuales de Component haciendo que llamen a **AegisComponent::callLuaRefFunc(LuaRef func, T args)**.

AegisComponent tiene variables privadas de tipo **LuaRef** para **type y funcs**, además de los callbacks **initFunc, updateFunc, lateUpdateFunc, fixedUpdateFunc, onCollisionFunc, onTriggerFunc**. Debido a que LuaRef no tiene una constructora por defecto, estas son incializadas en AegisComponent.h por **LuaMngr->getSharedEmptyLuaRef()**.

AegisComponent cuenta también con métodos set y get que reciben/devuelven dichos **LuaRef**. Se sobreescribe **ConverToLua** para poder acceder/modificar dichos métodos mediante el operador **=** desde lua.

#### CameraComponent:
CameraComponent guarda tanto un bool que determina si es "MainCamera" como un puntero a la **AegisCamera** a la que está asociada.

Esta clase cuenta con 2 constructoras. Una que es llamada desde Lua (recibiendo argumentos de tipo LuaRef), y otra que es llamada desde C++ (recibiendo una **AegisCamera** ya creada). La de Lua crea un AegisCamera y llama a la segunda constructora pasándosela como argumento.

Hay un método **CameraComponent* createCamera(Entity* ent, LuaRef args)** que será llamado desde Lua gracias al **ConvertToLua**. La función de este método es llamar a la primera constructora.

Esta clase tambíen contiene métodos **worldToScreen(const Vector3& worldPoint)** y **worldToScreenPixel(const Vector3& worldPoint)**

#### LightComponent:
De manera similar a **CameraComponent**, LightComponent guarda un puntero a un **AegisLight**, la cual se crea en la constructora. Cuenta con métodos set y get para modificar los atributos de la luz.

#### TransformComponent:
Transform guarda un puntero al **Ogre::SceneNode** y a la **Entity** padre de la entidad, junto con una lista de entidades de los hijos. 

#### RenderComponent:
Dota a la entidad de una **mesh** y le asigna un material.

#### RigidbodyComponent:
Crea un **Rigidbody** del proyecto **AegisPhysics** y lo guarda en un puntero. También guarda otra referencia al **Transform** de la entidad, con el fin de sincronizar sus atributos (posición, rotación, ...) cuando se modifiquen los del RigidbodyComponent (método **syncTransformToRigidbody**).

También cuenta con una **list<RigidbodyComponent*>::iterator physicsEntityIt** de sí mismo para cuando haya que borrarlo.

#### SoundEmitterComponent:
SoundEmitterComponent guarda un string con el sonido asociado a la entidad. En caso de que se desee utilizar dicho sonido, la clase cuenta con métodos para comunicarse con la instancia de **SoundSystem**.

#### Entity:
Entity hereda de **ILuaObject**. Cuenta con los siguientes atributos:
* **Puntero a la Scene** 
* **unordered_map <std::string, Ref AegisComponent> mComponents_;**
* **vector<AegisComponent*> mComponentsArray_;**
* **list<Entity*>::iterator entityIterator;**
* **bool nodeDestroyedOrBlocked;**

* **bool active_;**
* **SceneNode* mNode_**
* **string mName_;**
* **TransformComponent* transform;**

Cuenta con métodos **init, fixedUpdate, update, lateUpdate, y render**. En dichos métodos recorre **mComponentsArray_**, ejecutando los métodos correspondientes.

#### Initializable:
Contiene un método **virtual bool init() = 0** con el fin de obligar a sobreescribir dicho método en las clases que hereden de él.

#### Utils:
Diversos archivos .h que facilitan la gestión de recursos, ya sean Vector, Quaternion, includes, etc.

De estos recursos, el más notable es **Singleton**:
* **Singleton<T><T**> esta formado principalmente por un template con métodos estáticos para gestionar una única instancia de dicha objeto. Al tratar de crear una instancia, se comprueba si **mInstance_ == nullptr**. Dependiendo de esa comprobación se creará un nuevo T o no.

#### DebugManager:
Hereda de **Singleton** e **Initializable**. Tiene varios métodos **log(string msg)** para mostrar información en consola. Se utiliza con la funcionalidad de depurar y comprobar si se llama a ciertos métodos.

#### GameLoopData:
La clase GameLoopData hereda de **Singleton** y ayuda a gestionar el **deltaTime, frameStartTime, y timeSinceAppStartMS**.

#### Scene:
Hereda de **ILuaObject** y contiene varias **listas** para gestionar las **Entidades**: **entities, physicsEntities, uninitializedEntities y entitiesToDelete.**

* En el método **init**, crea una Entidad y le asocia el **CameraComponent**, creando así la **AegisCamera** de **AegisGraphics**. Esta cámara es exportada a Lua con el nombre **"MainCamera"**.

* En el método **fixedUpdate** solo se recorre la lista **physicsEntities** debido a que este método solo se encarga de actualizar las físicas. Una vez se ha llamado al fixedUpdate de cada **RigidbodyComponent**, se accede a la instancia de **PhysicsSystem** y se actualiza mediante su **update**. Tras esto, se llama al método **syncTransforms**, el cual vuelve a recorrer **physicsEntities** ejecutando el método **syncTransformToRigidbody** de cada una.

* **updateScene** llama a **initEntities**, el cual recorre **uninitializedEntities**, llamando al método **init** de cada una. Una vez finalizado dicho bucle, se ejecuta **fixedUpdate, update, lateUpdate, syncRigidbodies, y removeAndFreePendingEntities**, que de manera similar a initEntities, recorrerrá **entitiesToDelete** borrándolas.

* Hay un método **instantiatePrefab** que como su nombre indica, permite instanciar prefabs.

#### SceneManager:
SceneManager hereda de **Singelton** e **ILuaObject**. Guarda una referencia tanto a **OgreWrapper**, como a **currentScene**. También guarda un **LuaRef sceneToLoad** inicializado con **LuaManager::getInstance()->getSharedEmptyLuaRef()** por razones explicadas anteriormente. Cuando se desee cargar una nueva escena desde Lua, se llamará al método **loadScene (LuaRef newScenecene)** para que actualice el valor de sceneToLoad. En el método **refresh**, se borrará **currentScene** para cargar sceneToLoad sise detecta que sceneToLoad ya no es NilValue.

#### InputSystem:
InputSystem hereda de **Singleton** e **ILuaObject**. Contiene 2 strcuts:
* **key**: Gestiona las pulsaciones de una tecla/botón. Contiene 3 bools ==> **wasPressed, down, wasReleased**.
* **MouseButton**: Contiene 3 keys ==> **right, left, middle**.

A parte de guardar en todo momento un **MouseButton y un pair<Sint32, Sint32>** con el **estado y posición del ratón** en todo momento, también hay un **vector keys** para guardar el estado actual de cada tecla.

Hay métodos tanto para consultar los diversos estados de dichas variables, como para actualizarlos en función del input de SDL.

------
### AegisEngine:
AegisEngine es el proyecto principal de la solución desde el cual se instancian y gestionan los otros managers.

#### GameConfig:
Contiene un struct GameConfig donde se guardan 3 strings: **scriptPath, soundPath, resourcesCfgPath**. Dichas cadenas guardan las rutas a los scripts de lua usados en el juego, los sonidos, y el resources.cfg respecivamente.

#### AegisMain:
AegisMain hereda de **IInitializable**.

* En el método **init()**, utiliza el método **searchConfig()** para crear una variable temporal de tipo **GameConfig** en la que se guarden las rutas de los directorios necesarios para arrancar el juego escritos en **config.txt**. En caso de que se hayan localizado dichas rutas se instancia el **LuaManager** y se llama al método **convertToLua**, el cual a su vez llamará a los **ConvertToLua** estáticos de todas las demás clases.

Con el LuaManager creado, se instancian los otros managers y se exporta a Lua el **SceneManager**, **InputSystem** y **UISystem** mediante el método **ILuaObject::exportToLua**.

En caso de que se haya incializado todo correctamente, se ejecutarán los scripts **initLua.lua** del motor, e **init.lua** del juego mediante **execute** del **LuaManager**.

* La clase cuenta también con un método **GameLoop** donde se ejecuta el bucle principal del motor, gestionando el tiempo, eventos de la ventana, y llamando a los métodos **update**, **render**, **refresh** y **clear** de los otros managers.

#### main.cpp:
main.cpp contiene el método main. Inicializa **AegisMain**, y en caso de que no haya fallo, da paso al **GameLoop** a traves de **AegisMain::startGame**. En caso de error, hace **free** y termina. En modo DEBUG se muestra la memoria no liberada (**Memory Leaks**) en la pestaña de Salida de Visual Studio gracias al archivo **checkML.h**.

------
### AegisGraphics:
AegisGraphics sirve de enlace entre el motor y **OGRE**.

#### AegisCamera:
AegisCamera se encarga de crear una Cámara en ogre y agregarla a un nodo. Contiene métodos set y get para acceder a la matriz vista, matriz de proyección, el viewport, y otros atributos.

* También cuenta con un método **free()** que separa a todos los nodos adheridos al de la cámara, para luego destruir la misma.

#### AegisLight:
De manera similar a la cámara, se crea una luz de Ogre y se asocia a un nodo. Hay funciones para modificar o consultar los atributos de dicha luz.

#### WindowManager:
WindowManager se encarga de gestionar la ventana donde se renderiza el juego, principalmente el tamaño. A parte de crear la ventana de acuerdo a los argumentos recibidos por la constructora, la clase contiene un método **handleEvent(SDL_Event& evt)** que redimensiona el **render** en caso de recibir el evento de **SDL_WINDOWEVENT_RESIZED**.

También cuenta con métodos **getWidth/getHeight** que devuelven las dimensiones actuales de la ventana.

#### OgreWrapper:
OgreWrapper hereda de **Singleton**, y como su nombre indica, se encarga de englobar **OGRE**.

* La constructora llama al método **init(std::string resourcesPath)**, el cual se encarga de cargar los archivos **resources.cfg** y **plugins.cfg**. Una vez cargados los recursos crea un **WindowManager** y un **AegisCamera** que asocia al viewport del render.

------
### AegisPhysics:
AegisPhysics utiliza la librería **Bullet** para gestionar las físicas.

#### DebugDrawer.
OgreDebugDrawer hereda de **btIDebugDraw** y **Ogre::FrameListener** y se encarga de dibujar las aristas del cubo definido por el collider de una entidad física.

#### MotionState:
MotionState se encarga de sincronizar la posición/rotación del **Transform** con la del **Rigidbody** y viceversa, mediante los métodos **getWorldTransform** y **setWorldTransform**.

#### OgreBulletUtils:
OgreBulletUtils contiene funciones para realizar la conversión de objetos de Ogre a objetos de Bullet, y viceversa.

#### PhysicsMain:
PhysicsMain hereda de **Singleton**, y se encarga de gestionar las físicas, principalmente las colisiones entre **Rigidbodies** mediante el **map<std::pair<RigidBody*, RigidBody*>, bool> contact**.

En la constructora inicializa las cosas de Bullet, y en caso de que esté en modo DEBUG, también crea un **OgreDebugDrawer**.

Esta clase usa una variable scene, que es la agrupación de objetos físicos la cual debe encargarse de actualizar, tanto las fuerzas que les afectan como sus colisiones.

En el método update hace avanzar el mundo físico y comprueba si ha habido colisiones en el método checkCollision, en cuyo caso, para cada par de colisiones se llama a CollisionEnterCallbacks desde donde se llama a los oncollision/ontrigger respectivos de cada entidad.

También tiene el método createRigidBody que permite crear un nuevo rigidBody, además de los métodos parseToBulletTransform, parseToBulletTransform con los cuales a partir de un vector3 y de un vector3/4 se puede obtener un btTransform.

#### Rigidbody:
Rigidbody crea una entidad física en Bullet. Contiene métodos setter y get para modificar sus atributos.

------
### AegisScripting:
AegisScripting es el eslavón del motor que une C++ con Lua.

#### LuaBasic:
Contiene únicamente los include de Lua. Tiene como función reducir el número de includes en otros scripts.

#### LuaManager:
LuaManager es el eslavón del motor que une C++ con Lua. Hereda de **Singleton** y se encarga tanto de la creación de un nuevo **LuaState**, como de parsear parámetros **LuaRef** a C++. También cuenta con una función **execute(string filename)** para  cargar y ejecutar el archivo.lua "filename". Devuelve true si se carga y ejecuta correctamente.

------
### AegisUI:
#### UISystem:
UISystem es un **Singleton** encardo de la gestión de **UIObjects**.

En la constructora crea un **OverlaySystem** y accede al **OverlayManager** con el fin de inicializar un nuevo **Overlay** para la gestión de imágenes. Contiene un **vector de UIObjects** donde se guardaran los objetos de tipo UI creados desde lua mediante la función **createUIElem(luabridge::LuaRef luaref)**. Dicha función leerá el string identificador que recibe como argumento LuaRef para crear el tipo de objeto oportuno.

* El sistema también contiene una función **update** que recorre el vector ui_objects para que se actualicen.

#### UIObjects:
Debido a que de esta clase hereda tanto **Image** como **Text**, contamos con dos constructoras distintas. En ambos casos, la constructora de UIObjects crea un nuevo **OverlayElement** de tipo Panel. Debido a que no se puede crear más de un elemento con el mismo nombre, se usa un int estático **num_ui_obj** para identificar al objeto. Dicho int incrmenta cada vez que se llama a la constructora.

Una vez creado el elemento, se le modifica mediante la posición, profundidad (eje z), dimenisones, visibilidad, y material definidas por los argumentos de la constructora. La clase cuenta con varias funciones set y get para acceder y modificar dichas variables/estados.

* También hay una función **onClick** que comprueba si la posición del ratón está dentro de la superficie definida por el UIObject si éste es visible. Debido a que las posiciones de los UIObjects pertenecen al intervalo [(0,0), (1,1)] y no se miden en píxeles, se usan los métodos **getWidth/getHeight** del **WindowManager** de **AegisGraphics** para realizar la conversión a píxeles de la ventana. En dicho caso de que se cumplan las condiciones, se ejecutará el **function<void()> clickCallback**.

#### Image:
Image hereda de **UIObject** y expande la funcionalidad de dicha clase añadiéndole un material que recibe como argumento en la constructora. Dicha constructora es llamada desde un método estático de la misma clase, **CreateImage(LuaRef args)**, la cual realiza el parseo los argumentos LuaRef al tipo recibido por la constructora. CreateImage es llamado desde **UISystem::createUIElem** cuando se crea un objeto de tipo UI en lua.

#### Button:
Button hereda de **Image** y contiene un método **buttonClickCallback()** que es asignado al **clickCallback** de **UIObject**. En buttonClickCallback se llamará a la función definida en lua.

* Al igual que en Image, hay un método estático **CreateButton(LuaRef args)** que es llamado desde **UISystem::createUIElem**.

#### Text:
Text hereda de **UIObject** y crea un texto a partir de los argumentos recibidos en la constructora.

* Hay un método estático **CreateText(LuaRef args)** que es llamado desde **UISystem::createUIElem**.

#### ImageResources:
ImageResources **parseDirectory(string dir)** incializa un **map<image,std::string> mapImage** con las imágenes encontradas en el directorio **dir**. Tambíen tiene un método **getImage(string name)** para devolver la imagen con dicho nombre en caso de estar contenida en el mapImage. 

------
## Organización del directorio:
Aegis Engine  (carpeta principal)
* **Dependencias:** Contiene las librerías utilizadas; Bullet, FMOD, Lua, OGRE.
* **Exes:** Contiene los archivos autogenerados al compilar cada poryecto, junto con el juego programado en LUA que se desea ejecutar mediante Aegis
* **Projects:** Contiene los archivos .vcxproj y filters de cada proyecto.
* **Src:** Contiene los archivos .h y .cpp del motor. En la carpeta correspondiente a AegisEngine también hay un subdirectorio **Scripts** donde se guardan init.lua, utils.lua, y los componentes de lua proporcionados por el motor.
* **Temp:** Guarda los archivos objetos autogenerados al compilar.
* **AegisEngine.sln**
* **build_up.bat:** Archivo .bat que compila las librerías en Dependencias.

## Licencias

Aegis Engine ha sido diseñado y creado por **Kirin Studios** usando las siguientes librerías:

* **Ogre3D** (Copyright (c) 2000-2013 [Torus Knot Software Ltd](https://www.ogre3d.org/))

  
* **OgreOverlays** (Copyright (c) 2000-2013 [Torus Knot Software Ltd](https://www.ogre3d.org/))
  

* **Bullet Continuous Collision Detection and Physics Library** (Copyright (c) 2003-2006 [Erwin Coumans](https://pybullet.org/Bullet/phpBB3/))

* **FMOD Studio** (Copyright (c)[Firelight Technologies Pty Ltd](https://www.fmod.com/))

* **Lua** (Copyright (c) [The Lua Team](https://www.lua.org/))

* **LuaBridge** (Copyright (c) [Vinnie Falco](https://github.com/vinniefalco/LuaBridge))
