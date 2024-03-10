#include "World.hpp"
#include "Player.h"
#include "ShadowMap.h"

// add 4 sky
enum class RenderLayer : int
{
	Opaque = 0,
	Sky,
	Count
};

class Game : public D3DApp
{
public:
	Game(HINSTANCE hInstance);
	Game(const Game& rhs) = delete;
	Game& operator=(const Game& rhs) = delete;
	~Game();

	virtual bool Initialize()override;
private:
	virtual void CreateRtvAndDsvDescriptorHeaps()override;// add it shadow
	virtual void OnResize()override;
	virtual void Update(const GameTimer& gt)override;
	virtual void Draw(const GameTimer& gt)override;

	virtual void OnMouseDown(WPARAM btnState, int x, int y)override;
	virtual void OnMouseUp(WPARAM btnState, int x, int y)override;
	virtual void OnMouseMove(WPARAM btnState, int x, int y)override;
	virtual void OnKeyDown(WPARAM btnState )override;// add it for input

	void OnKeyboardInput(const GameTimer& gt);
	void ProcessEvents(WPARAM btnState);// add it for input
	void UpdateCamera(const GameTimer& gt);
	void AnimateMaterials(const GameTimer& gt);
	void UpdateObjectCBs(const GameTimer& gt);
	//void UpdateMaterialCBs(const GameTimer& gt);
	void UpdateMaterialBuffer(const GameTimer& gt);// shadow
	void UpdateMainPassCB(const GameTimer& gt);

	//step5
	void LoadTextures();

	void BuildRootSignature();

	//step9
	void BuildDescriptorHeaps();

	void BuildShadersAndInputLayout();
	void BuildShapeGeometry();
	void BuildPSOs();
	void BuildFrameResources();
	void BuildMaterials();
	void BuildRenderItems();
	//void DrawRenderItems(ID3D12GraphicsCommandList* cmdList, const std::vector<RenderItem*>& ritems);

	std::array<const CD3DX12_STATIC_SAMPLER_DESC, 7> GetStaticSamplers(); // it was 6

private:

	std::vector<std::unique_ptr<FrameResource>> mFrameResources;
	FrameResource* mCurrFrameResource = nullptr;
	int mCurrFrameResourceIndex = 0;

	UINT mCbvSrvDescriptorSize = 0;

	ComPtr<ID3D12RootSignature> mRootSignature = nullptr;

	//step11
	ComPtr<ID3D12DescriptorHeap> mSrvDescriptorHeap = nullptr;

	std::unordered_map<std::string, std::unique_ptr<MeshGeometry>> mGeometries;
	std::unordered_map<std::string, std::unique_ptr<Material>> mMaterials;

	//step7
	std::unordered_map<std::string, std::unique_ptr<Texture>> mTextures;

	std::unordered_map<std::string, ComPtr<ID3DBlob>> mShaders;

	std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;



	CD3DX12_GPU_DESCRIPTOR_HANDLE mNullSrv;// add it for shadows
	UINT mSkyTexHeapIndex = 0;// add it for shadows
	UINT mShadowMapHeapIndex = 0;// add it for shadows

	UINT mNullCubeSrvIndex = 0;// add it for shadows
	UINT mNullTexSrvIndex = 0;// add it for shadows

	std::unique_ptr<ShadowMap> mShadowMap; // add it for shadows



	DirectX::BoundingSphere mSceneBounds;// add it for shadows

	float mLightNearZ = 0.0f;// add it for shadows
	float mLightFarZ = 0.0f;// add it for shadows
	XMFLOAT3 mLightPosW;
	XMFLOAT4X4 mLightView = MathHelper::Identity4x4();// add it for shadows
	XMFLOAT4X4 mLightProj = MathHelper::Identity4x4();
	XMFLOAT4X4 mShadowTransform = MathHelper::Identity4x4();// add it for shadows

	float mLightRotationAngle = 5.0f;// add it for shadows
	XMFLOAT3 mBaseLightDirections[3] = {
		XMFLOAT3(0.57735f, -0.57735f, 0.57735f),
		XMFLOAT3(-0.57735f, -0.57735f, 0.57735f),
		XMFLOAT3(0.0f, -0.707f, -0.707f)
	};
	XMFLOAT3 mRotatedLightDirections[3];// add it for shadows


	ComPtr<ID3D12PipelineState> mOpaquePSO = nullptr;
	std::unordered_map<std::string, ComPtr<ID3D12PipelineState>> mPSOs; // add 4 sky

	// List of all the render items.
	std::vector<std::unique_ptr<RenderItem>> mAllRitems;

	// Render items divided by PSO. add 4 sky
	//std::vector<RenderItem*> mRitemLayer[(int)RenderLayer::Count];


	//UINT mSkyTexHeapIndex = 0;// add 4 sky

	// Render items divided by PSO.
	std::vector<RenderItem*> mOpaqueRitems;

	PassConstants mMainPassCB;

	//XMFLOAT3 mEyePos = { 0.0f, 0.0f, -10.0f };
	//XMFLOAT4X4 mView = MathHelper::Identity4x4();
	//XMFLOAT4X4 mProj = MathHelper::Identity4x4();

	//float mTheta = 1.3f * XM_PI;
	//float mPhi = 0.4f * XM_PI;
	//float mRadius = 2.5f;

	POINT mLastMousePos;
	Camera mCamera;
	World mWorld;
	Player mplayer; // add it for input
public:
	std::vector<std::unique_ptr<RenderItem>>& getRenderItems() { return mAllRitems; }
	std::unordered_map<std::string, std::unique_ptr<Material>>& getMaterials() { return mMaterials; }
	std::unordered_map<std::string, std::unique_ptr<MeshGeometry>>& getGeometries() { return mGeometries; }
	std::unordered_map<std::string, ComPtr<ID3D12PipelineState>> GetPSOs() { return mPSOs; }//  add 4 draw in scene node
	FrameResource* getFrameResource() { return mCurrFrameResource; }//  add 4 draw in scene node

	ComPtr<ID3D12DescriptorHeap> getmSrvDescriptorHeap() { return mSrvDescriptorHeap; }//  add 4 draw in scene node
	UINT GetmCbvSrvDescriptorSize() { return mCbvSrvDescriptorSize; }// add 4 draw in scene node
};

