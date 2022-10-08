<h1 align="center">
  <a href=""><img width="200" height="200" src="https://github.com/ByCubed7/Plasma/blob/master/docs/PlasmaLogo.png"/></a>
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
Scene* scene = app.CreateGame();

// Prepares an OpenGL context so that we can send API calls
app.Build();
app.Load(scene);

scene->Load();

app.Run(scene);
```
