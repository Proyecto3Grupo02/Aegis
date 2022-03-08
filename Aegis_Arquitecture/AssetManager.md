# Asset Manager

## Table of contents:

Load / Unload a set of assets from memory that are feed from an asset importer / lurker

### Type of assets
- 3D Assets
    - FBX
        - Mesh
        - Animation
    - DAE (?)
- 2D Textures
    - PNG
    - JPG
- Material / Shader
- Audio
    - MP3
    - WAV

### Internal representation

- Map<key: string, Map<key : string, value: pointer>> asset

### Loading Type

- On Demand 
- All preloaded

### High level configuration
 - JSON

### JSON FIELDS
- Type: 3D, 2D, Material, Audio
- Subtype: FBX, DAE, PNG, JPG, MP3, WAV...

# Asset importer / loader (lurker)

- Given a folder, search for assets and import them to Asset manager. Before feeding the asset they must be converted to a data format the engine can use