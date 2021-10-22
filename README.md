# Project Plasma

An object and component oriented game engine focused on 2D games.
Deals with rendering sprites and text, physics, controller inputs, shader compiling and window control.

## TODO
- Documentation on API and engine inner workings
- Turn the `Input` class into a static class.
- Merge the `TextRenderer` and `SpriteRenderer` into one renderer class.
- The `TextRenderer` should rely on `Resources` to load and store fonts and textures.
- Implement a tile system and tileset.


<br>

## Classes
- GameObject


## `GameObject`
*The base class for an object in the game. A player, cube, item ect.*

### ToString()
Returns `std::string`. `virtual`. <br>
*A string describing the GameObject, transform, components, ect.*
*Useful for debugging.*

### transform
`Transform` <br>
*The transform of the GameObject, position, rotation and scale*

### colour
`vec3` <br>
*The colour the texture is multipled by.*

### sprite
`Texture2D` <br>
*The Texture the gameObject is rendered as.*




