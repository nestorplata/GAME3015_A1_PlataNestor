#include "AircraftShadow.hpp"
#include "Game.hpp"

AircraftShadow::AircraftShadow(Type type, Game* game) : Entity(game)
, mType(type)
{
	switch (type)
	{
	case (EagleShadow):
		mSprite = "EagleShadow";
		break;
	case (RaptorShadow):
		mSprite = "RaptorShadow";
	default:
		mSprite = "RaptorShadow";
		break;
	}
}

void AircraftShadow::drawCurrent() const
{
}

void AircraftShadow::GetAirCraftPosition(Aircraft a, AircraftShadow as)
{
	as.setPosition(a.getWorldPositionX(), a.getWorldPositionY(), a.getWorldPositionZ());
}

void AircraftShadow::buildCurrent()
{
	auto render = std::make_unique<RenderItem>();
	renderer = render.get();
	renderer->World = getTransform();
	renderer->ObjCBIndex = game->getRenderItems().size();
	renderer->Mat = game->getMaterials()[mSprite].get();
	renderer->Geo = game->getGeometries()["boxGeo"].get();
	renderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs["box"].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs["box"].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs["box"].BaseVertexLocation;

	game->getRenderItems().push_back(std::move(render));
}
