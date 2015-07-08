#ifndef DUNJUN_RENDERSYSTEM_HPP
#define DUNJUN_RENDERSYSTEM_HPP

#include <Dunjun/Entity.hpp>
#include <Dunjun/RenderComponent.hpp>
#include <Dunjun/SceneGraph.hpp>

#include <Dunjun/Graphics/GBuffer.hpp>
#include <Dunjun/Graphics/RenderTexture.hpp>
#include <Dunjun/Graphics/Color.hpp>
#include <Dunjun/Graphics/Camera.hpp>
#include <Dunjun/Graphics/Texture.hpp>
#include <Dunjun/Scene/Lighting.hpp>

#include <Dunjun/System/Containers.hpp>

namespace Dunjun
{
class RenderSystem
{
public:
	using ComponentId = u32;

	GLOBAL const ComponentId EmptyComponentId = (ComponentId)(-1);

	struct InstanceData
	{
		u32 length   = 0;
		u32 capacity = 0;
		void* buffer = nullptr;

		EntityId* entityId         = nullptr;
		RenderComponent* component = nullptr;
	};

	Allocator& allocator;
	InstanceData data;
	HashMap<ComponentId> map;
	SceneGraph& sceneGraph;

	Vector2 fbSize;
	GBuffer gbuffer;
	RenderTexture lbuffer;
	RenderTexture outTexture;

	Color ambientColor;
	f32 ambientIntensity;

	Array<DirectionalLight> directionalLights;
	Array<PointLight> pointLights;
	Array<SpotLight> spotLights;

	const Camera* camera;

	RenderSystem(Allocator& a, SceneGraph& sg);
	~RenderSystem() = default;

	void allocate(u32 capacity);

	ComponentId create(EntityId id, const RenderComponent& component);
	void destroy(ComponentId id);

	ComponentId getComponentId(EntityId id);
	bool isValid(ComponentId id) const;

	void resetAllPointers();

	void render();

	void geometryPass();
	void lightPass();
	void outPass();

private:
	const Texture* currentTexture;

	bool setTexture(const Texture* texture, u32 position);
	// bool setShaders(const ShaderProgram* shaders);
};
} // namespace Dunjun

#endif
