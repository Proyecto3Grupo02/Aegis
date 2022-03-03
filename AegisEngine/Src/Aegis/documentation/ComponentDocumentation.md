## Component documentation

Components are defined in ComponentManager singleton which handles a factory.
So for defining our custom component you have to:

### Writing in cpp

1. Create a class inheriting from Component
2. In the .cpp file write at the beginning "REGISTER_FACTORY(unique name for your component)"
3. Code your own custom class 

### Using Lua to write your own components

[Complete here]
