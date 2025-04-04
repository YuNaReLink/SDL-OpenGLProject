#include "SkeletalMeshRenderer.h"
#include "Shader.h"
#include "Mesh.h"
#include "Actor.h"
#include "WinMain.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Animation.h"
#include "Skeleton.h"

SkeletalMeshRenderer::SkeletalMeshRenderer(ActorObject* owner)
	:MeshRenderer(owner, true)
	, mSkeleton(nullptr)
{
}

void SkeletalMeshRenderer::Draw(Shader* shader)
{
	for (unsigned int i = 0; i < mMeshs.size(); i++) 
	{
		for (unsigned int j = 0; j < mMeshs[i]->GetVertexArrays().size(); j++) 
		{
			if (mMeshs[i])
			{
				// Set the world transform
				shader->SetMatrixUniform("uWorldTransform",
					mOwner->GetWorldTransform());
				// Set the matrix palette
				shader->SetMatrixUniforms("uMatrixPalette", &mPalette.mEntry[0],
					MAX_SKELETON_BONES);
				// Set specular power
				shader->SetFloatUniform("uSpecPower", mMeshs[i]->GetMaterialInfo()[j].Shininess);
				Texture* t = nullptr;
				// Set the active texture
				t = mMeshs[i]->GetTexture(j);
				if (t)
				{
					t->SetActive();
				}
				else {
					shader->SetNoTexture();
				}
				MaterialInfo m = mMeshs[i]->GetMaterialInfo()[j];
				shader->SetColorUniform("uTexture", m);
				// Set the mesh's vertex array as active
				VertexArray* va = mMeshs[i]->GetVertexArrays()[j];
				va->SetActive();
				// Draw
				glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
			}
		}
	}
}

void SkeletalMeshRenderer::Update(float deltaTime)
{
	if (mAnimation && mSkeleton)
	{
		mAnimTime += deltaTime * mAnimPlayRate;
		// Wrap around anim time if past duration
		while (mAnimTime > mAnimation->GetDuration())
		{
			mAnimTime -= mAnimation->GetDuration();
		}

		// Recompute matrix palette
		ComputeMatrixPalette();
	}
}

float SkeletalMeshRenderer::PlayAnimation(const Animation* anim, float playRate)
{
	if (mAnimation == anim) { return 0.0f; }
	mAnimation = anim;
	mAnimTime = 0.0f;
	mAnimPlayRate = playRate;

	if (!mAnimation) { return 0.0f; }

	ComputeMatrixPalette();

	return mAnimation->GetDuration();
}

void SkeletalMeshRenderer::ComputeMatrixPalette()
{
	const std::vector<Matrix4>& globalInvBindPoses = mSkeleton->GetGlobalInvBindPoses();
	std::vector<Matrix4> currentPoses;
	mAnimation->GetGlobalPoseAtTime(currentPoses, mSkeleton, mAnimTime);

	// Setup the palette for each bone
	for (size_t i = 0; i < mSkeleton->GetNumBones(); i++)
	{
		// Global inverse bind pose matrix times current pose matrix
		mPalette.mEntry[i] = globalInvBindPoses[i] * currentPoses[i];
		/*
		// 行列をログに出力
		SDL_Log("Bone %zu Matrix:", i);
		for (int row = 0; row < 4; row++)
		{
			SDL_Log("%f %f %f %f",
				mPalette.mEntry[i].mat[row][0],
				mPalette.mEntry[i].mat[row][1],
				mPalette.mEntry[i].mat[row][2],
				mPalette.mEntry[i].mat[row][3]);
		}
		*/
	}
}