#pragma once

#include "graphics/Window.h"
#include "graphics/Renderer.h"
#include "graphics/OpenGLRenderer.h"
#include "graphics/Object.h"
#include "graphics/Texture.h"
#include "graphics/Shader.h"
#include "graphics/Animation.h"
#include "graphics/AnimationController.h"
#include "graphics/TexturedObject.h"
#include "graphics/RenderLayer.h"
#include "graphics/Scene.h"
#include "graphics/VertexArrayObject.h"
#include "graphics/WireObject.h"
#include "graphics/Tile.h"
#include "graphics/Font.h"
#include "graphics/Resource.h"

namespace Engine::Graphics {
    // Forward all graphics classes into the namespace
    using ::Window;
    using ::Renderer;
    using ::OpenGLRenderer;
    using ::Object;
    using ::Texture;
    using ::Shader;
    using ::Animation;
    using ::AnimationController;
    using ::TexturedObject;
    using ::RenderLayer;
    using ::Scene;
    using ::VertexArrayObject;
    using ::WireObject;
    using ::Tile;
    using ::Font;
    using ::Resource;
}