#include "DebugShadowMap.h"
#include "Game.h"

DebugShadowMap::DebugShadowMap(Game* game) : Entity(game)
{
}

void DebugShadowMap::drawCurrent() const
{
	renderer->World = getTransform();
	renderer->NumFramesDirty++;

	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList = game->GetApp()->GetCommandList();

	cmdList->SetPipelineState(game->GetPSOs()["debug"].Get());

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

void DebugShadowMap::buildCurrent()
{
	auto render = std::make_unique<RenderItem>();
	renderer = render.get();
	renderer->World = MathHelper::Identity4x4();
	renderer->TexTransform = MathHelper::Identity4x4();
	renderer->ObjCBIndex = game->getRenderItems().size();
	renderer->Mat = game->getMaterials()["bricks0"].get();
	renderer->Geo = game->getGeometries()["shapeGeo"].get();
	renderer->PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs["quad"].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs["quad"].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs["quad"].BaseVertexLocation;


	game->mRitemLayer[(int)RenderLayer::Debug].push_back(render.get());
	game->getRenderItems().push_back(std::move(render));
}
