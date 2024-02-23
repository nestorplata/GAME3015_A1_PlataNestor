#include "Aircraft.hpp"
#include "DirectXMath.h"
#include "Game.hpp"

Aircraft::Aircraft(Type type, Game* game) : Entity(game)
	, mType(type)
{
	AircraftShadow::Type shadowtype;
	switch (type)
	{
	case (Eagle):
		mSprite = "Eagle";
		shadowtype = AircraftShadow::EagleShadow;
		break;
	case (Raptor):
		mSprite = "Raptor";
		shadowtype = AircraftShadow::RaptorShadow;
		break;
	default:
		mSprite = "Eagle";
		shadowtype = AircraftShadow::EagleShadow;
		break;
	}

	std::unique_ptr<AircraftShadow> Eagleshadowtest1(new AircraftShadow(shadowtype, game));
 	mPlayerAircraftShadow = Eagleshadowtest1.get();
	
	attachChild(std::move(Eagleshadowtest1));
	XMFLOAT3 tempPositon = this->getWorldPosition();

	mPlayerAircraftShadow->setPosition(tempPositon.x +0.0, tempPositon.y+ -0.05 /2, tempPositon.z + -0.5);
	mPlayerAircraftShadow->setScale(1.0, 0.5, 0.5);
}

void Aircraft::drawCurrent() const
{	
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList = game->GetApp()->GetCommandList();

	cmdList->SetPipelineState(game->GetPSOs()["opaque"].Get());

	UINT objCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(ObjectConstants));
	UINT matCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(MaterialConstants));

	auto objectCB = game->getFrameResource()->ObjectCB->Resource();
	auto matCB = game->getFrameResource()->MaterialCB->Resource();
	;
	auto ri = renderer;

	cmdList->IASetVertexBuffers(0, 1, &ri->Geo->VertexBufferView());
	cmdList->IASetIndexBuffer(&ri->Geo->IndexBufferView());
	cmdList->IASetPrimitiveTopology(ri->PrimitiveType);

	////step18
	CD3DX12_GPU_DESCRIPTOR_HANDLE tex(game->getmSrvDescriptorHeap()->GetGPUDescriptorHandleForHeapStart());
	tex.Offset(ri->Mat->DiffuseSrvHeapIndex, game->GetmCbvSrvDescriptorSize());

	D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = objectCB->GetGPUVirtualAddress() + ri->ObjCBIndex * objCBByteSize;
	D3D12_GPU_VIRTUAL_ADDRESS matCBAddress = matCB->GetGPUVirtualAddress() + ri->Mat->MatCBIndex * matCBByteSize;

	//step19
	cmdList->SetGraphicsRootDescriptorTable(0, tex);
	cmdList->SetGraphicsRootConstantBufferView(1, objCBAddress);
	cmdList->SetGraphicsRootConstantBufferView(3, matCBAddress);

	cmdList->DrawIndexedInstanced(ri->IndexCount, 1, ri->StartIndexLocation, ri->BaseVertexLocation, 0);
}

void Aircraft::buildCurrent()
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
