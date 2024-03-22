#include "AircraftShadow.hpp"
#include "Game.h"

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
//AircraftShadow::AircraftShadow() : Entity(game)
//{
//	
//}

void AircraftShadow::drawCurrent() const
{
//	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList = game->GetApp()->GetCommandList();
//
//	cmdList->SetPipelineState(game->GetPSOs()["opaque"].Get());
//
//	UINT objCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(ObjectConstants));
//	UINT matCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(MaterialConstants));
//
//	auto objectCB = game->getFrameResource()->ObjectCB->Resource();
//	auto matCB = game->getFrameResource()->MaterialCB->Resource();
//	;
//	auto ri = renderer;
//
//	cmdList->IASetVertexBuffers(0, 1, &ri->Geo->VertexBufferView());
//	cmdList->IASetIndexBuffer(&ri->Geo->IndexBufferView());
//	cmdList->IASetPrimitiveTopology(ri->PrimitiveType);
//
//	////step18
//	CD3DX12_GPU_DESCRIPTOR_HANDLE tex(game->getmSrvDescriptorHeap()->GetGPUDescriptorHandleForHeapStart());
//	tex.Offset(ri->Mat->DiffuseSrvHeapIndex, game->GetmCbvSrvDescriptorSize());
//
//	D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = objectCB->GetGPUVirtualAddress() + ri->ObjCBIndex * objCBByteSize;
//	D3D12_GPU_VIRTUAL_ADDRESS matCBAddress = matCB->GetGPUVirtualAddress() + ri->Mat->MatCBIndex * matCBByteSize;
//
//	//step19
//	cmdList->SetGraphicsRootDescriptorTable(0, tex);
//	cmdList->SetGraphicsRootConstantBufferView(1, objCBAddress);
//	cmdList->SetGraphicsRootConstantBufferView(3, matCBAddress);
//
//	cmdList->DrawIndexedInstanced(ri->IndexCount, 1, ri->StartIndexLocation, ri->BaseVertexLocation, 0);
}

//void AircraftShadow::GetAirCraftPosition(Aircraft a, AircraftShadow as)
//{
//	as.setPosition(a.getWorldPositionX(), a.getWorldPositionY(), a.getWorldPositionZ());
//}

void AircraftShadow::buildCurrent()
{
	//auto render = std::make_unique<RenderItem>();
	//renderer = render.get();
	//renderer->World = getTransform();
	//renderer->ObjCBIndex = game->getRenderItems().size();
	//renderer->Mat = game->getMaterials()[mSprite].get();
	//renderer->Geo = game->getGeometries()["shapeGeo"].get();//renderer->Geo = game->getGeometries()["boxGeo"].get();
	//renderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	//renderer->IndexCount = renderer->Geo->DrawArgs["box"].IndexCount;
	//renderer->StartIndexLocation = renderer->Geo->DrawArgs["box"].StartIndexLocation;
	//renderer->BaseVertexLocation = renderer->Geo->DrawArgs["box"].BaseVertexLocation;

	//game->getRenderItems().push_back(std::move(render));
}
