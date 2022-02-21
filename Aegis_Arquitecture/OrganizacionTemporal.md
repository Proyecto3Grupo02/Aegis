# Bucle de juego
- Cargar Assets
- Fixed Update
    - En caso de colision (o trigger) llamar al evento correspondiente
- Input Events
- Bucle Update
- Sincronizar Transforms (componente Trasnform, nodo ogre, transform de bullet en caso de que haya)
- Borrar entidades que se han destruido (sacarlas del grafo de ogre)
- Scene endering
- GUI Rendering

# Scene Class
- Container(lista o array?) gameobjects (por ahora array)

# Gameobject
- InternalData
 - Nodo ogre (puede ser null)
 - Rigidbody bullet (puede ser null)
- Render
- Transform => ¿Ogre?
    - Parent (puede ser null
    - Array hijos

# Otros componente nativos
- Rigidbody
- Colliders

# Input System
 - Clase estática
 - Tiene un array de teclas
 - Metodos para saber si la tecla se pulso en ese frame, 
    si está pulsada o si se ha dejado de pulsar

# Canvas
- Canvas Transform 
- IMGUI