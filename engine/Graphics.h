#pragma once

#include "graphics/Animation.h"
#include "graphics/AnimationController.h"
#include "graphics/Font.h"
#include "graphics/IResource.h"
#include "graphics/Object.h"
#include "graphics/Renderer.h"
#include "graphics/RenderLayer.h"
#include "graphics/Scene.h"
#include "graphics/SDL2Window.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include "graphics/TexturedObject.h"
#include "graphics/VertexArrayObject.h"
#include "graphics/WireObject.h"

namespace Engine::Graphics {
    // Forward all graphics classes into the namespace
    using ::SDL2Window;
    using ::Renderer;
    using ::Object;
    using ::Texture;
    using ::Shader;
    using ::Animation;
    using ::AnimationController;
    using ::TexturedObject;
    using ::RenderLayer;
    using ::Scene;
    using ::IGameScene;
    using ::VertexArrayObject;
    using ::WireObject;
    using ::Font;
    using ::IResource;
}