#include "Skybox.h"
#include "Game.h"

Skybox::Skybox(Game* game) : Entity(game)
{
}

void Skybox::drawCurrent() const
{
	renderer->World = getTransform();
	renderer->NumFramesDirty++;

	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList = game->GetApp()->GetCommandList();

	cmdList->SetPipelineState(game->GetPSOs()["sky"].Get());

	UINT objCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(ObjectConstants));
	auto objectCB = game->getFrameResource()->ObjectCB->Resource();
	auto ri = renderer;
	auto vbv = ri->Geo->VertexBufferView();
	auto ibv = ri->Geo->IndexBufferView();

	cmdList->IASetVertexBuffers(0, 1, &vbv);
	cmdList->IASetIndexBuffer(&ibv);
	cmdList->IASetPrimitiveTopology(ri->PrimitiveType);

	D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = objectCB->GetGPUVirtualAddress() + ri->ObjCBIndex * objCBByteSize;

	cmdList->SetGraphicsRootConstantBufferView(0, objCBAddress);

	cmdList->DrawIndexedInstanced(ri->IndexCount, 1, ri->StartIndexLocation, ri->BaseVertexLocation, 0);
}

void Skybox::buildCurrent()
{
	auto render = std::make_unique<RenderItem>();
	renderer = render.get();
	renderer->World = getTransform();
	renderer->ObjCBIndex = game->getRenderItems().size();
	renderer->Mat = game->getMaterials()["sky"].get();
	renderer->Geo = game->getGeometries()["shapeGeo"].get();
	renderer->PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs["sphere"].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs["sphere"].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs["sphere"].BaseVertexLocation;


	game->mRitemLayer[(int)RenderLayer::Sky].push_back(render.get());
	game->getRenderItems().push_back(std::move(render));
}
