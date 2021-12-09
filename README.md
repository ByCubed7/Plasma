<h1 align="center">
  <a href=""><img width="200" height="200" src="https://github.com/ByCubed7/Plasma/blob/master/Docs/PlasmaLogo.png"/></a>
  <br>
  The Plasma Engine Project
</h1>

<blockquote align="center">
  <em>An object and component oriented game engine API focused on 2D games.
Deals with rendering sprites and text, physics, controller inputs, shader compiling and window control.</em>
</blockquote>

<p align="center">
  <a href="#getting-started">Getting started</a> | 
  <a href="#documentation">Documentation</a> | 
  <a href="#demos-and-examples">Demos and examples</a>
</p>

## Getting started

#### [Download](https://github.com/ByCubed7/Plasma/archive/master.zip)

## Documentation 
\[ Insert wiki here ]


## Demos and examples

### Helloworld
```cpp
App app = App();

GameConfig gameConfig;
Scene* scene = app.CreateGame(gameConfig);

scene->Initialize();

app.Prepare(scene);
app.Run(scene);
```

Changing Window properties
```cpp
App app = App();

GameConfig gameConfig;
gameConfig.PPU = 16;
gameConfig.screenHeight = gameConfig.PPU * 31;
gameConfig.screenWidth  = gameConfig.PPU * 28;

Scene* scene = app.CreateGame(gameConfig);
scene->Initialize();

app.Prepare(scene);
app.Run(scene);
```

Creating a GameObject
```cpp
GameObject* player = scene->CreateGameObject();
player->position = { 17,17 };
player->scale = { 2,2 };
```

Loading files
```cpp
. . .

scene->Initialize();

Resources::LoadShader("assets/shaders/sprite.vs", "assets/shaders/sprite.frag", nullptr, "sprite");
Resources::LoadTexture("assets/textures/Player.png", true, "player");
Resources::LoadWav("assets/audio/beginning.wav", "beginning");
Resources::LoadTilemap("assets/tilemaps/Pacman.tmx", "tilemap");
Resources::LoadFont("assets/fonts/arial.ttf", "arial");

. . .
```

Adding a Component (+ Getting Resource files)
```cpp
SpriteComponent* playerSprite = new SpriteComponent(player);
	
playerSprite
	->Set(Resources::GetTexture("player"))
	->AnimationSpeed(4);

CharacterControllerComponent* playerController = new CharacterControllerComponent(player);
```


## TODO
- Turn Input class into a static class.
- Documentation API.
